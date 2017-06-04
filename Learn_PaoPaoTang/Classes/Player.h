#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"

#define PART_BODY  "body"
#define PART_EFX "dead"  // 目前只有一种特效：死亡
#define PART_RIDE "ride"

class Player;
typedef void (Player::*Method)(); // 状态机的处理方法
typedef void (Player::*UpdateMethod)(float); // 更新方法
typedef void(Player::*InputMethod)(EControlType, EPressState);
struct StateMethod
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
	EPlayerLogicState mState;
	EPlayerMoveState mMoveState;
	float mSpeed;     // 速度
	int mMaxBombNum;  // 炸弹数量
	int mBombStrength;// 炸弹威力
	bool mIsRiding;   // 是否骑乘
	bool mTransTable[EPLS_NUM][EPLS_NUM]; // 状态转换表
	StateMethod states[EPLS_NUM];
public:
	Player(PlayScene& rScene) 
		:GameObject(rScene, EGOT_Player)
		,mState(EPLS_STAND)
		,mSpeed(0)
		,mMaxBombNum(0)
		,mBombStrength(0)
		,mIsRiding(false)
	{
		mRenderObj.addPart(PART_BODY, Point::ZERO);
		mRenderObj.addPart(PART_EFX, Point::ZERO);
		mRenderObj.addPart(PART_RIDE, Point::ZERO);

		memset(mTransTable, false, sizeof(mTransTable));
	    
		/* 默认合法的动作请求 */
		mTransTable[EPLS_STAND][EPLS_WRAPPED] = true;  // 站立->被泡泡包裹
		mTransTable[EPLS_STAND][EPLS_MOVE] = true;     // 站立->行走

		mTransTable[EPLS_MOVE][EPLS_STAND] = true;     // 行走->站立
		mTransTable[EPLS_MOVE][EPLS_WRAPPED] = true;   // 行走->被包裹

		mTransTable[EPLS_WRAPPED][EPLS_STAND] = true;  // 被包裹->站立
		mTransTable[EPLS_WRAPPED][EPLS_DEAD] = true;   // 被包裹->死亡

		states[EPLS_STAND].init(&Player::defaultEnter, &Player::defaultEnter, &Player::defaultUpdate, &Player::standHandleInput);
		states[EPLS_MOVE].init(&Player::defaultEnter, &Player::defaultEnter, &Player::defaultUpdate, &Player::moveHandleInput);
		states[EPLS_WRAPPED].init(&Player::defaultEnter, &Player::defaultEnter, &Player::defaultUpdate, &Player::defaultHandleInput);
		states[EPLS_DEAD].init(&Player::defaultEnter, &Player::defaultEnter, &Player::defaultUpdate, &Player::defaultHandleInput);
	}

	virtual void load(const char* szName)
	{
		mRenderObj.setAni(PART_BODY, "role1", "walk_up");
	}
	virtual void update(float dt) 
	{
		// (this->*funcPtr)()
		// (obj.*funcPtr)()
		(this->*states[mState].update)(dt);
		//  

		GameObject::update(dt);
	}
public:
	void handleInput(EControlType ectType, EPressState epState)
	{
		(this->*states[mState].input)(ectType,epState);
	}
	void standHandleInput(EControlType ectType, EPressState epState)
	{
		if (epState == EPS_DOWN) {
			mState = EPLS_MOVE;
			switch (ectType)
			{
			case ECT_LEFT:
				mMoveState = EPMS_LEFT;
				break;
			case ECT_RIGHT:
				mMoveState = EPMS_RIGHT;
				break;
			case ECT_UP:
				mMoveState = EPMS_UP;
				break;
			case ECT_DOWN:
				mMoveState = EPMS_DOWN;
				break;
			default:
				mState = EPLS_STAND;
				break;
			}
		}
	}

	void moveHandleInput(EControlType ectType, EPressState epState)
	{

	}
private:
	void defaultEnter(){}
	void defaultExit() {}
	void defaultUpdate(float dt){}
	void defaultHandleInput(EControlType ectType, EPressState epState){}
};

#endif 
