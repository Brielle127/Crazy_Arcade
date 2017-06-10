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
//typedef void(Player::*InputMethod)(ControlType, PressState);
struct StateMethod  // 状态方法
{
	Method enter;
	Method exit;
	UpdateMethod update;
	//InputMethod input;
	void init(Method en, Method ex, UpdateMethod up/*,InputMethod ip*/)
	{
		enter = en;
		exit = ex;
		update = up;
		//input = ip;
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

	virtual void load(const char* szName)
	{
		//mRenderObj.addPart(PART_BODY, Point::ZERO);
		mRenderObj.setAni(PART_BODY, "role1", "walk_up");
	}
	virtual void update(float dt) 
	{
		(this->*states[mState].update)(dt); // 调用成员函数
		GameObject::update(dt);
	}
public:
	void handleInput(ControlType ectType, PressState epState)
	{ 
		switch (epState)
		{
		case PS_DOWN:
			handleDown(ectType);
			break;
		case PS_UP:
			handleUp(ectType);
			break;
		default:
			return;
		}
	}
	
private:
	void handleDown(ControlType ectType) // 处理键盘按下事件
	{
		switch (ectType)
		{
		case CT_PRESS: // 空格放置炸弹
		{
			
		}
		break;
		case CT_LEFT:
		case CT_RIGHT:
		case CT_UP:
		case CT_DOWN:
		{	
			
			static PlayerMoveState getMoveState[] = { PMS_UP,PMS_DOWN,PMS_LEFT,PMS_RIGHT };
			mTransParam.nextMoveState = getMoveState[ectType-CT_UP];
			PlayerLogicState s = mTransTable[PI_MOVE][mState];  // 请求移动
			if (s != PLS_NONE)
				changeState(s);
		}
		break;
		default:
			return;

		}
	}
	void handleUp(ControlType ectType)
	{

		switch (ectType)
		{
		case CT_PRESS: // 空格放置炸弹
		{

		}
		break;
		case CT_LEFT:
		case CT_RIGHT:
		case CT_UP:
		case CT_DOWN:
		{
			//auto it = mInputCache.begin(), end = mInputCache.end();
			//for (; it != end; ++it) {
				//if (*it == ectType) {
					//mInputCache.erase(it);// 删除
					//break;
				//}
			//}

			//if (mInputCache.empty()) {     // 缓存为空
				PlayerLogicState s = mTransTable[PI_STOP][mState];  // 请求停下
				if (s != PLS_NONE)
					changeState(s);
			//}
			//else {
				//auto ec = mInputCache[0];
				
			//}
		}
		break;
		default:
			return;

		}
	}
	// 切换状态
	void changeState(PlayerLogicState nextState)
	{
		// 退出先前状态
		StateMethod rCurrent = states[mState];
		(this->*rCurrent.exit)();

		mState = nextState;
		StateMethod rNext = states[nextState];
		(this->*rNext.enter)();
	}
	void moveStateUpdate(float dt);
private:
	// 切换动画
	void moveStateEnter()
	{
		switch (mTransParam.nextMoveState)
		{
		case PMS_UP:
			mRenderObj.setAni(PART_BODY, "role1", "walk_up");
			break;
		case PMS_DOWN:
			mRenderObj.setAni(PART_BODY, "role1", "walk_down");
			break;
		case PMS_LEFT:
			mRenderObj.setAni(PART_BODY, "role1", "walk_left");
			break;
		case PMS_RIGHT:
			mRenderObj.setAni(PART_BODY, "role1", "walk_right");
			break;
		default:
			return;
		}
		mMoveState = mTransParam.nextMoveState;
	}
private: // 默认方法
	void defaultEnter() {}
	void defaultExit() {}
	void defaultUpdate(float dt) {}
	void defaultHandleInput(ControlType ectType, PressState epState) {}

public:
	//得到人物范围，用于道具类 //李志鹏
	Rect BoundingBox() { return mRenderObj.sprite->getBoundingBox(); }
 };


#endif // !_PALYER_H_
