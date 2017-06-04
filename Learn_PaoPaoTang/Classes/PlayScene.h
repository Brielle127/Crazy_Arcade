#pragma once
#ifndef _PLAY_SCENE_H_
#define _PLAY_SCENE_H_

#include "cocos2d.h"
#include "BaseScene.h"
#include "BaseDef.h"
#include "Animation.h"
#include "tinyxml.h"
#include "GameObject.h"
#include <vector>
USING_NS_CC;
using namespace std;

class CPlayScene:public CBaseScene
{
	Layer* mGroundLayer; // ��ש
	Layer* mObjectLayer; // ���
	Layer* mUILayer;     // UI
	string mCurrentFile; // ��ǰ�������ļ�
	vector<CGameObject*> mMapObject[GRID_WIDTH][GRID_HEIGHT];  // ��̬����
public:
	CPlayScene();

	virtual void onEnterScene();
	virtual void onExitScene();
	virtual void onUpdate(float dt);
public:
	void setCurrentSceneFile(const char* szFile);// ���õ�ǰ�������ļ�
	void loadScene();
public:
	CGameObject* createObject(EGameObjectType ovjType);
	vector<CGameObject*>& getObject(int gridx, int gridy);
private:
	Sprite* createGroundTile(const char* ani,size_t gx,size_t gy);

};
#endif // !_PLAY_SCENE_H_
