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

/*��Ⱦ����*/
class CRenderObj
{
	float currentElapsed;
public:
	Sprite* sprite;
	int currentFrame;
	CAniData* currentAniData;
	CRenderObj()
		:currentFrame(0),
		currentElapsed(0),
		currentAniData(nullptr)
	{
		sprite = Sprite::create();

		currentAniData = new (CAniData)();
		
		/* // ���Դ���
		currentAniData = CAnimationMgr::getAni("role1", "walk_down");
		*/

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

#endif
