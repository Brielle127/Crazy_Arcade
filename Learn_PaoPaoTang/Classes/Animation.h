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
	// 动画名
	string name;
	// 动画资源文件
	string fileName;
	// 帧率
	int fps;
	// 动画帧数据
	vector<Rect> framesData;
};

typedef map<string, AniData> AniGroup;      // 一个AniGroup类型的对象表示一个动画： 动画名->动画的参数配置

class AnimationMgr 
{
private: 
	// 加载配置文件
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
		static map<string, AniGroup> aniGroup; // aniGroup表示一个动画组：组名->动画
		if (aniGroup.size() == 0)
			load(aniGroup);
		auto it = aniGroup.find(groupName);
		if (it != aniGroup.end())       // 找到动画组
		{
			auto ii = it->second.find(aniName);
			if (ii != it->second.end())   // 找到动画
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


/* 渲染对象部件 */
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
	Sprite* sprite; // 用于显示
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
			if (currentAniData->framesData.size() == 1) // 处理只有1帧的动画
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

/* 渲染对象 */
class RenderObj
{
	vector<RenderPart*> parts;          // vector用于快速访问
	map<string, RenderPart*> partsMap;  // 部件名称->部件对象的映射
public:
	Sprite* sprite;
public:
	RenderObj()
	{
		sprite = Sprite::create();
	}

	// 设置锚点
	void setAnchorPoint(const Point& rPoint)
	{
		sprite->setAnchorPoint(rPoint);
	}

	// 使用名字设置部件动画
	void setAni(const char* partName,const char* groupName,const char* aniName)
	{
		auto it = partsMap.find(partName);
		if (it != partsMap.end())                      // 在partsMap中找到对应的部件
			it->second->setAni(groupName, aniName);    // 将任务转接给CRendrPart::setAni()
	}
	// 使用索引设置部件动画
	void setAni(int idx,const char* groupName, const char* aniName)
	{
		auto p = parts[idx];
		p->setAni(groupName, aniName);
	}

	/* 添加部件 */
	void addPart(const char* partName, /*部件的偏移*/const Point& offset) 
	{
		auto pNewPart = new RenderPart(partName);   // 生成
		pNewPart->sprite->setPosition(offset);
		pNewPart->name = partName;

		sprite->addChild(pNewPart->sprite);// 将部件精灵添加到sprite
		parts.push_back(pNewPart);         // 向vector中注册
		partsMap[partName] = pNewPart;     // 向map中注册
	}
	
	/* 修正相对位移 */
	void modifyPartOffset(const char* partName,const Point& offset)
	{
		auto it = partsMap.find(partName);
		if (it != partsMap.end())
			it->second->sprite->setPosition(offset);
	}

	void removePart(const char* partName)
	{
		auto it = partsMap.find(partName);  // 取出

		sprite->removeChild(it->second->sprite,true);// 从sprite移除部件精灵
		// 从vector移除
		auto iter = parts.begin(), end = parts.end();
		for (; iter != end; ++iter) {
			if ((*iter)->name == partName)
				parts.erase(iter);
			delete *iter; 
		}
		
	}

	void update(float dt)
	{
		// 遍历parts
		auto it = parts.begin(), end = parts.end();
		for (; it != end; ++it)
			(*it)->update(dt);
	}
};

#endif
