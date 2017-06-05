#pragma once
#ifndef _PLAY_SCENE_H_
#define _PLAY_SCENE_H_

#include "cocos2d.h"
#include "BaseScene.h"
#include "GameObject.h"
#include <vector>
#include"Player.h"
USING_NS_CC;
using namespace std;

class PlayScene:public BaseScene
{
	Layer* mGroundLayer; // ��ש
	Layer* mObjectLayer; // ���
	Layer* mUILayer;     // UI
	string mCurrentFile; // ��ǰ�������ļ�
	Player mPlayer;
	vector<GameObject*> mMapObject[GRID_WIDTH][GRID_HEIGHT];  // ��̬����
public:
	PlayScene()
		:mGroundLayer(nullptr)
		, mObjectLayer(nullptr)
		, mUILayer(nullptr)
		,mPlayer(*this)
	{
		mGroundLayer = Layer::create();
		mGroundLayer->setPosition(Point(20, 40)); // ��λ
		mSceneLayer->addChild(mGroundLayer);

		mObjectLayer = Layer::create();
		mObjectLayer->setPosition(Point(20, 40));
		mSceneLayer->addChild(mObjectLayer);

		mUILayer = Layer::create();
		mSceneLayer->addChild(mUILayer);
	}


	virtual void onEnterScene();
	virtual void onExitScene();
	virtual void onUpdate(float dt);
public:
	void setCurrentSceneFile(const char* szFile);// ���õ�ǰ�������ļ�
	void loadScene();
public:
	GameObject* createObject(GameObjectType objType);
	void destroy(GameObject* obj);
	vector<GameObject*>& getObject(int gridx, int gridy);
	virtual void handleInput(ControlType ectType, PressState epState)
	{
		mPlayer.handleInput(ectType, epState);
	}
private:
	Sprite* createGroundTile(const char* ani,size_t gx,size_t gy);

};
#endif // !_PLAY_SCENE_H_
