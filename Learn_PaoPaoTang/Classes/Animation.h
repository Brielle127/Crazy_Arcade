#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "cocos2d.h"
USING_NS_CC;

#include "tinyxml.h"
#include <vector>
#include <map>
using namespace std;


struct AniData
{
	// ������
	string name;
	// ������Դ�ļ�
	string fileName;
	// ֡��
	int fps;
	// ����֡����
	vector<Rect> framesData;
};

typedef map<string, AniData> AniGroup;      // һ��AniGroup���͵Ķ����ʾһ�������� ������->�����Ĳ�������

class AnimationMgr 
{
private: 
	// ���������ļ�
	static void load(map<string,AniGroup>& rAniGroups)                             
	{
		TiXmlDocument doc;
		if (doc.LoadFile("Config/GroupTable.xml"))
		{
			auto root = doc.RootElement();
			auto group = root->FirstChildElement();
			TiXmlElement *sub = nullptr, *ani = nullptr;
			while (group)
			{
				auto groupName = group->Attribute("name");
				rAniGroups.insert(make_pair(groupName, AniGroup()));
				auto& rGroup = rAniGroups[groupName];

				sub = group->FirstChildElement();
				while(sub)
				{
					auto file = sub->Attribute("file");
					int tileWidth, tileHeight, width, height;
					sub->Attribute("tileWidth", &tileWidth);
					sub->Attribute("tileHeight", &tileHeight);
					sub->Attribute("width", &width);
					sub->Attribute("height", &height);
					width /= tileWidth;
					height /= tileHeight;
					ani = sub->FirstChildElement();
					while (ani)
					{
						auto aniName = ani->Attribute("name");
						rGroup.insert(make_pair(aniName,AniData()));
						auto& rAni = rGroup[aniName];

						int begin, end, fps;
						ani->Attribute("begin", &begin);
						ani->Attribute("end", &end);
						ani->Attribute("fps", &fps);

						rAni.name = aniName;
						rAni.fileName = file;
						rAni.fps = fps;

						for (int i = begin; i <= end; ++i)
						{
							int x = i%tileWidth;
							int y = int(i / tileWidth);
							rAni.framesData.push_back(Rect(x*width, y*height, width, height));
						}
						
						ani = ani->NextSiblingElement();
					}
					sub = sub->NextSiblingElement();
				}
				group = group->NextSiblingElement();
			}
		}
	}
	static map<string, AniGroup>& getGroups()
	{
		static map<string, AniGroup> aniGroups;
		return aniGroups;
	}
public:
	static AniData* getAni(const char* groupName, const char* aniName)
	{
		static map<string, AniGroup> aniGroup; // aniGroup��ʾһ�������飺����->����
		if (aniGroup.size() == 0)
			load(aniGroup);
		auto it = aniGroup.find(groupName);
		if (it != aniGroup.end())       // �ҵ�������
		{
			auto ii = it->second.find(aniName);
			if (ii != it->second.end())   // �ҵ�����
				return &ii->second;
		}
		return nullptr;
	}
	static const AniGroup* getGroup(const char* groupName)
	{
		map<string, AniGroup>& aniGroups = getGroups();
		if (aniGroups.size() == 0)
			load(aniGroups);
		map<string, AniGroup>::iterator it = aniGroups.find(groupName);
		if (it != aniGroups.end()) {
			return &it->second;
		}
		return nullptr;
	}
};


/* ��Ⱦ���󲿼� */
class RenderPart
{
public:
	enum PlayFlag {
		PF_LOOP,
		PF_COMPLETE_CLEAR,
		PF_COMPLETE_STOP,
	};
private:
	float currentElapsed;
	int currentFrame;
	AniData* currentAniData;

	PlayFlag mFlag;
	bool mPlaying;

public:
	Sprite* sprite; // ������ʾ
	string name;

	RenderPart(const char* szName)
		:currentFrame(0),
		currentElapsed(0),
		currentAniData(nullptr),
		name(szName)
		, mPlaying(true)
		, mFlag(PF_LOOP)
	{
		sprite = Sprite::create();
		sprite->retain();
		sprite->setAnchorPoint(Size::ZERO);

		currentAniData = new AniData();

	}
	~RenderPart()
	{
		sprite->release();
	}

	void setAni(const char* groupName, const char* aniName)
	{

		mPlaying = true;
		//mFlag = flag;
		if (groupName == NULL || aniName == NULL) {
			currentAniData = NULL;
			sprite->setTexture(NULL);
		}
		else {
			currentAniData = AnimationMgr::getAni(groupName, aniName);
			if (currentAniData == NULL) {
				sprite->setTexture(NULL);
			}
			else {
				Texture2D* pTexture = Director::getInstance()->getTextureCache()->addImage(currentAniData->fileName.c_str());
				sprite->setTexture(pTexture);
				sprite->setTextureRect(currentAniData->framesData[0]);
			}
		}

		currentAniData = AnimationMgr::getAni(groupName, aniName);
		auto pTexture = Director::getInstance()->getTextureCache()->addImage(currentAniData->fileName);
		sprite->setTexture(pTexture);
		sprite->setTextureRect(currentAniData->framesData[0]);

	}

	void update(float dt)
	{
		if (mPlaying == false)
			return;
		if (currentAniData) {
			if (currentAniData->framesData.size() == 1) // ����ֻ��1֡�Ķ���
				return;
			currentElapsed += dt;
			currentFrame = currentElapsed*currentAniData->fps;
			const int maxFrame = currentAniData->framesData.size();
			if (currentFrame >= maxFrame) {
				switch (mFlag)
				{
				case PF_LOOP:
				{
					currentFrame %= maxFrame;
				}
				break;
				case PF_COMPLETE_CLEAR:
					setAni(NULL, NULL);
					return;
				case PF_COMPLETE_STOP:
					currentFrame = maxFrame - 1;
					mPlaying = false;
					break;
				}
			}
			sprite->setTextureRect(currentAniData->framesData[currentFrame]);
		}

	}
};

/* ��Ⱦ���� */
class RenderObj
{
	vector<RenderPart*> parts;          // vector���ڿ��ٷ���
	map<string, RenderPart*> partsMap;  // ��������->���������ӳ��
public:
	Sprite* sprite;
public:
	RenderObj()
	{
		sprite = Sprite::create();
	}

	// ����ê��
	void setAnchorPoint(const Point& rPoint)
	{
		sprite->setAnchorPoint(rPoint);
	}

	// ʹ���������ò�������
	void setAni(const char* partName,const char* groupName,const char* aniName)
	{
		auto it = partsMap.find(partName);
		if (it != partsMap.end())                      // ��partsMap���ҵ���Ӧ�Ĳ���
			it->second->setAni(groupName, aniName);    // ������ת�Ӹ�CRendrPart::setAni()
	}
	// ʹ���������ò�������
	void setAni(int idx,const char* groupName, const char* aniName)
	{
		auto p = parts[idx];
		p->setAni(groupName, aniName);
	}

	/* ��Ӳ��� */
	void addPart(const char* partName, /*������ƫ��*/const Point& offset) 
	{
		auto pNewPart = new RenderPart(partName);   // ����
		pNewPart->sprite->setPosition(offset);
		pNewPart->name = partName;

		sprite->addChild(pNewPart->sprite);// ������������ӵ�sprite
		parts.push_back(pNewPart);         // ��vector��ע��
		partsMap[partName] = pNewPart;     // ��map��ע��
	}
	
	/* �������λ�� */
	void modifyPartOffset(const char* partName,const Point& offset)
	{
		auto it = partsMap.find(partName);
		if (it != partsMap.end())
			it->second->sprite->setPosition(offset);
	}

	void removePart(const char* partName)
	{
		auto it = partsMap.find(partName);  // ȡ��

		sprite->removeChild(it->second->sprite,true);// ��sprite�Ƴ���������
		// ��vector�Ƴ�
		auto iter = parts.begin(), end = parts.end();
		for (; iter != end; ++iter) {
			if ((*iter)->name == partName)
				parts.erase(iter);
			delete *iter; 
		}
		
	}

	void update(float dt)
	{
		// ����parts
		auto it = parts.begin(), end = parts.end();
		for (; it != end; ++it)
			(*it)->update(dt);
	}
};

#endif
