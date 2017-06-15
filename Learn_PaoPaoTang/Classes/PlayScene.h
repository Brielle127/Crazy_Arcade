///////////////////////////////////////////////////////////////////////////////
/// \file PlayScene.h
/// \brief ʵ��PlayScene
/// 
/// 
///
/// \author ������
///////////////////////////////////////////////////////////////////////////////

#ifndef _PLAY_SCENE_H_
#define _PLAY_SCENE_H_

#include "cocos2d.h"
#include "BaseScene.h"
#include "GameObject.h"
#include <vector>
#include <map>
#include"Player.h"
#include "GameOverMenu.h"

USING_NS_CC;
using namespace std;
class PlayScene:public BaseScene,public Scene
{
	string mCurrentFile; // ��ǰ�������ļ�
	Layer* mGroundLayer; // ��ש��
	Layer* mObjectLayer; // �����
	Layer* mUILayer;     // UI��
	Player mPlayer;
	Player mPlayer2;
	vector<GameObject*> mMapObject[GRID_WIDTH][GRID_HEIGHT];  // ��̬����
	bool mMapBarrier[GRID_WIDTH][GRID_HEIGHT];                // �ϰ���
	
	map<EventKeyboard::KeyCode, bool> keys; // ����״̬
	vector<ControlType> ectTypes;           // ���뻺��
	
	float mGlobalPercent;      // ȫ�ֵ���Ʒ�������
	vector<int> mItemsPercent; // ��ͬ���ߵĵ������
	
	struct BornPoint {
		int gridx;
		int gridy;
	};
	vector<BornPoint> mBornPoints;
	
	GameOverMenu* mGameOverMenu;
public:
	PlayScene()
		:mGroundLayer(nullptr)
		, mObjectLayer(nullptr)
		, mUILayer(nullptr)
		, mPlayer(*this)
		, mPlayer2(*this)
		, mGlobalPercent(0.0f)
	{
		mGroundLayer = Layer::create();
		mGroundLayer->setPosition(Point(20, 40));
		mSceneLayer->addChild(mGroundLayer);

		mObjectLayer = Layer::create();
		mObjectLayer->setPosition(Point(20, 40));
		mSceneLayer->addChild(mObjectLayer);

		mUILayer = Layer::create();
		mSceneLayer->addChild(mUILayer);

		mGameOverMenu = new GameOverMenu();
		mGameOverMenu->autorelease();
		mSceneLayer->addChild(mGameOverMenu);
		mGameOverMenu->setPosition(designResolutionSize.width / 2, designResolutionSize.height / 2);

		memset(mMapBarrier, false, sizeof(mMapBarrier));
	}
public:
	virtual void onEnterScene();    // ���볡��
	virtual void onExitScene();     // �˳�����
	virtual void onUpdate(float dt);// ��������
	virtual void handleInput(ControlType ectType, PressState epState)
	{
		mPlayer.handleInput(ectType, epState);
	}
public:/* ���� */
	void setCurrentSceneFile(const char* szFile) { mCurrentFile = szFile; } // ���õ�ǰ�������ļ�
	void loadScene();                                                       // ���س���
private:
	Sprite* createGroundTile(const char* ani,size_t gx,size_t gy);          // ������ש
public:/* ���� */
	GameObject* createObject(GameObjectType objType);    // ��������
	void addObj(GameObject *obj, int gridX, int gridY);  // ��Ӷ���
	void destroy(GameObject* obj);                       // ���ٶ���
	vector<GameObject*>& getObject(int gridx, int gridy);// ���������ϵĶ�������
public:/* ��ɫ */
	Player* getPlayer() { return &mPlayer; }
public:/* ���� */
	float getGlobalPercent() { return mGlobalPercent; }
	vector<int>& getItemsPercent() { return mItemsPercent; }
public:/* �ϰ��� */
	void setBarrier(int gridx, int gridy, bool bBarrier); // �����ϰ���
	bool getBarrier(int gridx, int gridy, bool isIgnoreStatic = false);
};
#endif // !_PLAY_SCENE_H_
