#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "GameObject.h"

#include<map>
#include <vector>
using namespace std;

#define PART_BODY  "body"
#define PART_EFX "dead"  // 目前只有一种特效：死亡
#define PART_RIDE "ride"

class Player;
typedef void(Player::*Method)();       // Player的无参无返回值成员函数
typedef void(Player::*UpdateMethod)(float); // 更新方法
typedef void(Player::*OrderMethod)(OrderType,void*);   // 逻辑命令输入
struct StateMethod  // 状态方法
{
	Method enter;
	Method exit;
	UpdateMethod update;
	OrderMethod orderHandler;
	//InputMethod input;
	void init(Method en, Method ex, UpdateMethod up,OrderMethod oh)
	{
		enter = en;
		exit = ex;
		update = up;
		orderHandler = oh;
	}
};

union TransParam
{
	PlayerMoveState nextMoveState;
};

class Player:public GameObject
{
	PlayerLogicState mState; // 角色当前状态
	PlayerMoveState mMoveState; // 移动方向
	TransParam mTransParam;
	float mSpeed;     // 速度
	int mMaxBombNum;  // 炸弹数量
	int mBombStrength;// 炸弹威力
	bool mIsRiding;   // 是否骑乘
	
	
	PlayerLogicState mTransTable[PI_NUM][PLS_NUM]; // 状态转换表  请求动作+当前状态->下一状态
	StateMethod states[PLS_NUM];
public:
<<<<<<< HEAD
	Player(PlayScene& rScene);
=======
	
	Player(PlayScene& rScene)
		:GameObject(rScene, GOT_Player)
		, mState(PLS_STAND)
		, mSpeed(100)
		, mMaxBombNum(0)
		, mBombStrength(0)
		, mIsRiding(false)
	{
		mRenderObj.addPart(PART_BODY, Point::ZERO);
		//mRenderObj.addPart(PART_EFX, Point::ZERO);
		//mRenderObj.addPart(PART_RIDE, Point::ZERO);
		mRenderObj.setAnchorPoint(Point(24, 0));
		memset(mTransTable, 0, sizeof(mTransTable));

		// 设置默认允许的操作……
		mTransTable[PI_KILL][PLS_STAND] = PLS_WRAPPED; // 静止状态+炸弹爆炸->被泡泡包裹
		mTransTable[PI_MOVE][PLS_STAND] = PLS_MOVE;    // 静止状态+请求移动->移动状态

		mTransTable[PI_MOVE][PLS_MOVE] = PLS_MOVE;
		mTransTable[PI_KILL][PLS_MOVE] = PLS_WRAPPED;
		mTransTable[PI_STOP][PLS_MOVE] = PLS_STAND;

		// 飞针道具…
		mTransTable[PI_KILL][PLS_WRAPPED] = PLS_DEAD;

		// 初始化默认方法
		states[PLS_STAND].init(&Player::defaultEnter, &Player::defaultExit, &Player::defaultUpdate);
		states[PLS_MOVE].init(&Player::moveStateEnter, &Player::defaultExit, &Player::moveStateUpdate);
		states[PLS_WRAPPED].init(&Player::defaultEnter, &Player::defaultExit, &Player::defaultUpdate);
		states[PLS_DEAD].init(&Player::defaultEnter, &Player::defaultExit, &Player::defaultUpdate);
		
	
	}
>>>>>>> db872432032f8c33494e292918e07a44dcd62716

	virtual void load(const char* szName)
	{
		mRenderObj.setAni(PART_BODY, "role1", "stand_down");
	}
	virtual void update(float dt) 
	{
		(this->*states[mState].update)(dt); // 调用成员函数
		GameObject::update(dt);
	}
public:
	void handleInput(ControlType ectType, PressState epState);
	
private:
	void handleDown(ControlType ectType);
	void handleUp(ControlType ectType);
	// 切换状态
	void changeState(PlayerLogicState nextState);
private:
	// 切换动画
	void moveStateEnter();
	void moveStateUpdate(float dt);

	void moveAndStandOrderHandler(OrderType type, void* data);
private: // 默认方法
	void defaultEnter() {}
	void defaultExit() {}
	void defaultUpdate(float dt) {}
	void defaultHandleInput(ControlType ectType, PressState epState) {}
<<<<<<< HEAD
	void defaultOrderHandler(OrderType,void*){}
=======

public:
	//得到人物范围，用于道具类 //李志鹏
	Rect BoundingBox() { return mRenderObj.sprite->getBoundingBox(); }
>>>>>>> db872432032f8c33494e292918e07a44dcd62716
 };

#endif // !_PALYER_H_
