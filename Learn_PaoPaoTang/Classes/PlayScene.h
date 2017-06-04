#pragma once
#ifndef _PLAY_SCENE_H_
#define _PLAY_SCENE_H_

#include "cocos2d.h"
#include "BaseScene.h"
#include "BaseDef.h"
#include "Animation.h"
#include "tinyxml.h"
#include "GameObject.h"
#include "Player.h"
#include <vector>
USING_NS_CC;
using namespace std;

class PlayScene:public BaseScene
{
	Layer* mGroundLayer; // 地砖
	Layer* mObjectLayer; // 物件
	Layer* mUILayer;     // UI
	string mCurrentFile; // 当前场景的文件
	Player mPlayer;
	vector<GameObject*> mMapObject[GRID_WIDTH][GRID_HEIGHT];  // 静态对象
public:
	PlayScene();

	virtual void onEnterScene();
	virtual void onExitScene();
	virtual void onUpdate(float dt);
public:
	void setCurrentSceneFile(const char* szFile);// 设置当前场景的文件
	void loadScene();
public:
	GameObject* createObject(EGameObjectType ovjType);
	void destroy(GameObject* obj);
	vector<GameObject*>& getObject(int gridx, int gridy);
	virtual void handleInput(EControlType ectType, EPressState epState)
	{
		mPlayer.handleInput(ectType, epState);
	}
private:
	Sprite* createGroundTile(const char* ani,size_t gx,size_t gy);

};
#endif // !_PLAY_SCENE_H_
