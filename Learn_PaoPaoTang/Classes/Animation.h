#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "cocos2d.h"
USING_NS_CC;

#include "tinyxml.h"
#include <vector>
#include <map>
using namespace std;


struct CAniData
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

typedef map<string, CAniData> AniGroup;      // һ��AniGroup���͵Ķ����ʾһ�������� ������->�����Ĳ�������

class CAnimationMgr 
{
private: 
	// ���������ļ�
	static void load(map<string,AniGroup>& raniGroup)                             
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
				raniGroup.insert(make_pair(groupName, AniGroup()));
				auto& rGroup = raniGroup[groupName];

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
						rGroup.insert(make_pair(aniName,CAniData()));
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
public:
	static CAniData* getAni(const char* groupName, const char* aniName)
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
};

/* ��Ⱦ���󲿼� */
class CRenderPart
{
	float currentElapsed;
	int currentFrame;
	CAniData* currentAniData;
public:
	Sprite* sprite; // ������ʾ
	string name;

	CRenderPart(const char* szName)
		:currentFrame(0),
		currentElapsed(0),
		currentAniData(nullptr),
		name(szName)
	{
		sprite = Sprite::create();
		sprite->retain();
		sprite->setAnchorPoint(Size::ZERO);
		currentAniData = new CAniData();
	}
	~CRenderPart()
	{
		sprite->release();
	}

	void setAni(const char* groupName, const char* aniName)
	{
		currentAniData = CAnimationMgr::getAni(groupName, aniName);
		auto pTexture = Director::getInstance()->getTextureCache()->addImage(currentAniData->fileName);
		sprite->setTexture(pTexture);
		sprite->setTextureRect(currentAniData->framesData[0]);
	}

	void update(float dt)
	{
		if (currentAniData) {
			if (currentAniData->framesData.size() == 1) // ����ֻ��1֡�Ķ���
				return;
			currentElapsed += dt;
			currentFrame = currentElapsed*currentAniData->fps;
			currentFrame %= currentAniData->framesData.size();
			sprite->setTextureRect(currentAniData->framesData[currentFrame]);
		}

	}
};

/* ��Ⱦ���� */
class CRenderObj
{
	vector<CRenderPart*> parts;          // vector���ڿ��ٷ���
	map<string, CRenderPart*> partsMap;  // ��������->���������ӳ��
public:
	Sprite* sprite;
public:
	CRenderObj()
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
		auto pNewPart = new CRenderPart(partName);   // ����
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
