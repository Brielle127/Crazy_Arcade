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
typedef void(Player::*OrderMethod)(OrderType, void*);   // 逻辑命令输入
struct StateMethod  // 状态方法
{
	Method enter;
	Method exit;
	UpdateMethod update;
	OrderMethod orderHandler;
	void init(Method en, Method ex, UpdateMethod up, OrderMethod oh)
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

class Player :public GameObject
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
	Player(PlayScene& rScene);
	
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
public:
	void setBombNum(int bn) { mMaxBombNum = bn; }
	void setStr(int bs) { mBombStrength = bs; }
	void setSpeed(int sp) { mSpeed = sp; }
	int getBombNum() { return mMaxBombNum; }
	int getStr() { return mBombStrength; }
	int getSpeed() { return mSpeed; }
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
	void defaultOrderHandler(OrderType, void*) {}
};

#endif // !_PALYER_H_
