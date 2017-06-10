#pragma once
#ifndef _PLAY_SCENE_H_
#define _PLAY_SCENE_H_

#include "cocos2d.h"
#include "BaseScene.h"
#include "GameObject.h"
#include <vector>
#include <map>
#include <stack>
#include"Player.h"
USING_NS_CC;
using namespace std;


class PlayScene:public BaseScene,public Scene
{
	Layer* mGroundLayer; // ��ש
	Layer* mObjectLayer; // ���
	Layer* mUILayer;     // UI
	Layer* mToolLayer;  //����
	string mCurrentFile; // ��ǰ�������ļ�
	Player mPlayer;  
	vector<GameObject*> mMapObject[GRID_WIDTH][GRID_HEIGHT];  // ��̬����
	bool mMapBarrier[GRID_WIDTH][GRID_HEIGHT]; // �赲����
	map<EventKeyboard::KeyCode, bool> keys;    // ����״̬
	ControlType ectType1;
	ControlType ectType2;
	ControlType ectType3;
	stack<ControlType> ectTypes;// ���뻺��
public:
	PlayScene()
		:mGroundLayer(nullptr)
		, mObjectLayer(nullptr)
		, mUILayer(nullptr),mToolLayer(nullptr)
		,mPlayer(*this)
		,ectType1(CT_NONE)
		,ectType2(CT_NONE)
		, ectType3(CT_NONE)
	{
		mGroundLayer = Layer::create();
		mGroundLayer->setPosition(Point(20, 40)); // ��λ
		mSceneLayer->addChild(mGroundLayer);

		mObjectLayer = Layer::create();
		mObjectLayer->setPosition(Point(20, 40));
		mSceneLayer->addChild(mObjectLayer);

		mToolLayer = Layer::create();
		mSceneLayer->addChild(mToolLayer);

		mUILayer = Layer::create();
		mSceneLayer->addChild(mUILayer);

		memset(mMapBarrier, false, sizeof(mMapBarrier));
		
		
	}


	virtual void onEnterScene();
	virtual void onExitScene();
	virtual void onUpdate(float dt);
public:
	void setCurrentSceneFile(const char* szFile);// ���õ�ǰ�������ļ�
	void loadScene();

	// �����ϰ���
	void setBarrier(int gridx, int gridy, bool bBarrier)
	{
		if (gridx >= 0 && gridx < GRID_WIDTH&&gridy >= 0 && gridy << GRID_HEIGHT)
			mMapBarrier[gridx][gridy] = bBarrier;
	}

	bool getBarrier(int gridx, int gridy)
	{
		if (gridx >= 0 && gridx < GRID_WIDTH&&gridy >= 0 && gridy << GRID_HEIGHT)
			return mMapBarrier[gridx][gridy];
		return true; // ��ͼ������Ϊ�赲
	}
public:
	// ��������
	GameObject* createObject(GameObjectType objType);
	// ���ٶ���
	void destroy(GameObject* obj);
	// �������귵�ظ�λ���ϵĶ�������
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
