#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "GameObject.h"

#define PART_BODY  "body"
#define PART_EFX "dead"  // 目前只有一种特效：死亡
#define PART_RIDE "ride"

class Player;
typedef void(Player::*Method)();       // Player的无参无返回值成员函数
typedef void(Player::*UpdateMethod)(float); // 更新方法
typedef void(Player::*InputMethod)(ControlType, PressState);
struct StateMethod  // 状态方法
{
	Method enter;
	Method exit;
	UpdateMethod update;
	InputMethod input;
	void init(Method en, Method ex, UpdateMethod up,InputMethod ip)
	{
		enter = en;
		exit = ex;
		update = up;
		input = ip;
	}
};
class Player:public GameObject
{
	PlayerLogicState mState; // 角色当前状态
	float mSpeed;     // 速度
	int mMaxBombNum;  // 炸弹数量
	int mBombStrength;// 炸弹威力
	bool mIsRiding;   // 是否骑乘
	PlayerMoveState mMoveState; // 移动方向
	bool mTransTable[PLS_NUM][PLS_NUM]; // 状态转换表
	StateMethod states[PLS_NUM];
public:
	Player(PlayScene& rScene);

	virtual void load(const char* szName)
	{
		mRenderObj.setAni(PART_BODY, "role1", "walk_up");
	}
	virtual void update(float dt) 
	{
		(this->*states[mState].update)(dt); // 调用成员函数
		// ...
		GameObject::update(dt);
	}
public:
	void handleInput(ControlType ectType, PressState epState)
	{ 
		(this->*states[mState].input)(ectType,epState);
	}
	void standHandleInput(ControlType ectType, PressState epState)
	{
		if (epState == PS_DOWN) {
			mState = PLS_MOVE;//切换逻辑状态为移动
			switch (ectType)
			{
			case CT_LEFT:
				mMoveState = PMS_LEFT;
				break;
			case CT_RIGHT:
				mMoveState = PMS_RIGHT;
				break;
			case CT_UP:
				mMoveState = PMS_UP;
				break;
			case CT_DOWN:
				mMoveState = PMS_DOWN;
				break;
			default:
				mState = PLS_STAND;
			}
		}
	}

	void moveHandleInput(ControlType ectType, PressState epState)
	{

	}
private: // 默认方法
	void defaultEnter() {}
	void  defaultExit() {}
	void defaultUpdate(float dt) {}
	void defaultHandleInput(ControlType ectType, PressState epState) {}
 };


#endif // !_PALYER_H_
