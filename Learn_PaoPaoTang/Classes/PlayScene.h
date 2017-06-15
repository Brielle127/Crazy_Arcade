///////////////////////////////////////////////////////////////////////////////
/// \file PlayScene.h
/// \brief 实现PlayScene
/// 
/// 
///
/// \author 蓝楚迪
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
	string mCurrentFile; // 当前场景的文件
	Layer* mGroundLayer; // 地砖层
	Layer* mObjectLayer; // 物件层
	Layer* mUILayer;     // UI层
	Player mPlayer;
	Player mPlayer2;
	vector<GameObject*> mMapObject[GRID_WIDTH][GRID_HEIGHT];  // 静态对象
	bool mMapBarrier[GRID_WIDTH][GRID_HEIGHT];                // 障碍物
	
	map<EventKeyboard::KeyCode, bool> keys; // 按键状态
	vector<ControlType> ectTypes;           // 输入缓存
	
	float mGlobalPercent;      // 全局的物品掉落概率
	vector<int> mItemsPercent; // 不同道具的掉落概率
	
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
	virtual void onEnterScene();    // 进入场景
	virtual void onExitScene();     // 退出场景
	virtual void onUpdate(float dt);// 场景更新
	virtual void handleInput(ControlType ectType, PressState epState)
	{
		mPlayer.handleInput(ectType, epState);
	}
public:/* 场景 */
	void setCurrentSceneFile(const char* szFile) { mCurrentFile = szFile; } // 设置当前场景的文件
	void loadScene();                                                       // 加载场景
private:
	Sprite* createGroundTile(const char* ani,size_t gx,size_t gy);          // 创建地砖
public:/* 对象 */
	GameObject* createObject(GameObjectType objType);    // 创建对象
	void addObj(GameObject *obj, int gridX, int gridY);  // 添加对象
	void destroy(GameObject* obj);                       // 销毁对象
	vector<GameObject*>& getObject(int gridx, int gridy);// 返回坐标上的对象数组
public:/* 角色 */
	Player* getPlayer() { return &mPlayer; }
public:/* 道具 */
	float getGlobalPercent() { return mGlobalPercent; }
	vector<int>& getItemsPercent() { return mItemsPercent; }
public:/* 障碍物 */
	void setBarrier(int gridx, int gridy, bool bBarrier); // 设置障碍物
	bool getBarrier(int gridx, int gridy, bool isIgnoreStatic = false);
};
#endif // !_PLAY_SCENE_H_
