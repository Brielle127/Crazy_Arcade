#pragma once
#ifndef _PLAY_SCENE_H_
#define _PLAY_SCENE_H_

#include "cocos2d.h"
#include "BaseScene.h"
#include "GameObject.h"
#include <vector>
#include <map>
#include"Player.h"
USING_NS_CC;
using namespace std;

class PlayScene:public BaseScene,public Scene
{
	Layer* mGroundLayer; // 地砖
	Layer* mObjectLayer; // 物件
	Layer* mUILayer;     // UI
	string mCurrentFile; // 当前场景的文件
	Player mPlayer;
	vector<GameObject*> mMapObject[GRID_WIDTH][GRID_HEIGHT];  // 静态对象
	bool mMapBarrier[GRID_WIDTH][GRID_HEIGHT]; // 阻挡格子
	map<EventKeyboard::KeyCode, bool> keys;    // 按键状态
	vector<ControlType> ectTypes;// 输入缓存
public:
	PlayScene()
		:mGroundLayer(nullptr)
		, mObjectLayer(nullptr)
		, mUILayer(nullptr)
		,mPlayer(*this)
	{
		mGroundLayer = Layer::create();
		mGroundLayer->setPosition(Point(20, 40)); // 定位
		mSceneLayer->addChild(mGroundLayer);

		mObjectLayer = Layer::create();
		mObjectLayer->setPosition(Point(20, 40));
		mSceneLayer->addChild(mObjectLayer);

		mUILayer = Layer::create();
		mSceneLayer->addChild(mUILayer);

		memset(mMapBarrier, false, sizeof(mMapBarrier));
		
		
	}


	virtual void onEnterScene();
	virtual void onExitScene();
	virtual void onUpdate(float dt);
public:
	void setCurrentSceneFile(const char* szFile);// 设置当前场景的文件
	void loadScene();

	// 设置障碍物
	void setBarrier(int gridx, int gridy, bool bBarrier)
	{
		if (gridx >= 0 && gridx < GRID_WIDTH&&gridy >= 0 && gridy << GRID_HEIGHT)
			mMapBarrier[gridx][gridy] = bBarrier;
	}

	bool getBarrier(int gridx, int gridy)
	{
		if (gridx >= 0 && gridx < GRID_WIDTH&&gridy >= 0 && gridy << GRID_HEIGHT)
			return mMapBarrier[gridx][gridy];
		return true; // 地图以外设为阻挡
	}
public:
	// 创建对象
	GameObject* createObject(GameObjectType objType);
	// 销毁对象
	void destroy(GameObject* obj);
	void addObj(GameObject *obj, int gridX, int gridY)
	{
		mMapObject[gridX][gridY].push_back(obj);
		mObjectLayer->addChild(obj->getSprite());
	}
	// 根据坐标返回该位置上的对象数组
	vector<GameObject*>& getObject(int gridx, int gridy)
	{
		return mMapObject[gridx][gridy];
	}
	virtual void handleInput(ControlType ectType, PressState epState)
	{
		mPlayer.handleInput(ectType, epState);
	}
private:
	Sprite* createGroundTile(const char* ani,size_t gx,size_t gy);
private:
	void onKeyPressedss(EventKeyboard::KeyCode keyCode, Event* ev)
	{
		log("key %d pressed", keyCode);
	}
	void onKeyReleasedss(EventKeyboard::KeyCode keyCode, Event* ev)
	{
		log("key released");
	}
};
#endif // !_PLAY_SCENE_H_
