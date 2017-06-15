///////////////////////////////////////////////////////////////////////////////
/// \file Player.h
/// \brief 实现Player类
/// 
/// 
///
/// \author 蓝楚迪 
///////////////////////////////////////////////////////////////////////////////

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"
#include "RoleTableConfig.h"
#include"ItemConfig.h"
#include "Buff.h"

#include<map>
#include <vector>
using namespace std;

#define PART_BODY  "body"
#define PART_EFX "dead"  // 目前只有一种特效：死亡
#define PART_RIDE "ride"

class Player;
typedef void(Player::*Method)();                        // 不同状态的enter、exit方法
typedef void(Player::*UpdateMethod)(float);             // 不同状态的更新方法
typedef void(Player::*OrderMethod)(OrderType, void*);   // 逻辑输入
// 不同状态的方法
// 本类的功能是为状态机提供对应的初始化方法
struct StateMethod  
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
	PlayerDirection nextDirection;
};

struct BaseAttri        // 玩家基本属性
{
	float mSpeed;       // 速度
	int mMaxBombNum;    // 炸弹数量
	int mBombStrength;  // 炸弹威力
	bool mCanKickPopo;  // 时候可以踢泡泡
	bool mIgnoreItem;   // 忽略道具
	bool mIgnoreStatic; // 忽略阻挡物
};

class Player :public GameObject
{
	BaseAttri mAttri;           // 玩家自身属性
	BaseAttri mAttriEx;         // 道具附加属性 
	
	TransParam mTransParam;     // 状态转换参数
	PlayerLogicState mTransTable[PI_NUM][PLS_NUM]; // 状态转换表:请求动作+当前状态->下一状态
	
	PlayerLogicState mState;    // 角色当前状态
	StateMethod states[PLS_NUM];// 状态方法
	
	RoleInfo* mRoleInfo;        // 角色信息
	struct ItemInfo* mRideInfo; // 道具信息
	vector<Buff*> mBuffList;    // 道具Buff列表
	
	PlayerDirection mDirection; // 移动方向
	bool mIsRiding;             // 是否骑乘坐骑
	int mCurrentUsedBombNum;
	float mSurroundedTime;
	bool move_flag=false;

public:
	Player(PlayScene& rScene);

public:/*   接口   */	
	void addBuff(Buff* p)
	{
		if (mBuffList.size())
			mBuffList.erase(mBuffList.begin()); // 移除之前的Buff
		mBuffList.push_back(p);
		p->attach(this);
		refreshBuff();
	}
	void ride(ItemInfo* rideInfo); // 骑乘坐骑
	bool isDead() { return mState == PLS_DEAD; }
public:/* 重写函数 */
	void handleInput(ControlType ectType, PressState epState);
	virtual void load(const char* szName);
	virtual void update(float dt);
	virtual void beAttacked();

public:/* 属性操作 */
	void setBombNum(int value)
	{
		value = value > mRoleInfo->min_popo_num? value : mRoleInfo->min_popo_num ;
		value = value < mRoleInfo->max_popo_num ? value : mRoleInfo->max_popo_num  ;
		mAttri.mMaxBombNum = value;
	}
	void setBombNumEx(int value)
	{
		value = value > mRoleInfo->min_popo_num ? value : mRoleInfo->min_popo_num;
		value = value < mRoleInfo->max_popo_num ? value : mRoleInfo->max_popo_num;
		mAttriEx.mMaxBombNum = value - mAttri.mMaxBombNum;
	}
	int getBombNum() { return mAttri.mMaxBombNum+mAttriEx.mMaxBombNum; }
	
	void setStr(int value) 
	{
		value = value >  mRoleInfo->min_str? value : mRoleInfo->min_str;
		value = value <  mRoleInfo->max_str? value : mRoleInfo->max_str;
		mAttri.mBombStrength = value; 
	}
	void setStrEx(int value)
	{
		value = value >  mRoleInfo->min_str ? value : mRoleInfo->min_str;
		value = value <  mRoleInfo->max_str ? value : mRoleInfo->max_str;
		mAttriEx.mBombStrength = value - mAttri.mBombStrength;
	}
	int getStr() { return mAttri.mBombStrength+mAttriEx.mBombStrength; }

	void setSpeed(int value) 
	{ 
		value = value > mRoleInfo->min_speed ? value : mRoleInfo->min_speed;
		value = value <  mRoleInfo->max_speed? value : mRoleInfo->max_speed;
		mAttri.mSpeed = value;
	}
	void setSpeedEx(float value)
	{
		value = value > mRoleInfo->min_speed ? value : mRoleInfo->min_speed;
		value = value <  mRoleInfo->max_speed ? value : mRoleInfo->max_speed;
		mAttriEx.mSpeed = value - mAttri.mSpeed;
	}
	int getSpeed() { return mAttri.mSpeed+mAttriEx.mSpeed; }
	
	void setIgnoreItem(bool value)
	{
		mAttri.mIgnoreItem = mAttri.mIgnoreItem || value;
	}
	void setIgnoreItemEx(bool value)
	{
		mAttriEx.mIgnoreItem = mAttriEx.mIgnoreItem || value;
	}
	bool getIgnoreItem()
	{
		return mAttri.mIgnoreItem || mAttriEx.mIgnoreItem;
	}

	void setIgnoreStatic(bool value)
	{
		mAttri.mIgnoreStatic = mAttri.mIgnoreStatic || value;
	}
	void setIgnoreStaticEx(bool value)
	{
		mAttriEx.mIgnoreStatic = mAttriEx.mIgnoreStatic || value;
	}
	bool getIgnoreStatic()
	{
		return mAttri.mIgnoreStatic || mAttriEx.mIgnoreStatic;
	}

	void setCanKickPopo(bool value)
	{
		mAttri.mCanKickPopo = mAttri.mCanKickPopo || value;
	}
	void setCanKickPopoEx(bool value)
	{
		mAttriEx.mCanKickPopo = mAttriEx.mCanKickPopo || value;
	}
	bool getCanKickPopo()
	{
		return mAttri.mCanKickPopo || mAttriEx.mCanKickPopo;
	}

private:/* 状态操作 */
	void changeState(PlayerLogicState nextState);// 切换状态
	
	void standStateEnter();
	
	void moveStateEnter();
	void moveStateUpdate(float dt);

	void surroundedStateEnter();
	void surroundedStateExit();
	void surroundedStateUpdate(float dt);

	void deadStateEnter();

	void moveAndStandOrderHandler(OrderType type, void* data);
private:
	void defaultEnter() {}
	void defaultExit() {}
	void defaultUpdate(float dt) {}
	void defaultHandleInput(ControlType ectType, PressState epState) {}
	void defaultOrderHandler(OrderType, void*) {}

private:
	void handleDown(ControlType ectType);// 处理键盘按下事件
	void handleUp(ControlType ectType);  // 处理键盘松开事件
	
	void removeBuff(Buff* p)
	{
		for (auto it = mBuffList.begin(); it != mBuffList.end();++it)
		{
			if (*it == p) {
				p->remove();
				mBuffList.erase(it);
				break;
			}
		}
		refreshBuff();
	}
	void refreshBuff()
	{
		memset(&mAttriEx, 0, sizeof(mAttriEx)); // 清空附加属性
		for (size_t i = 0; i < mBuffList.size(); ++i)
			mBuffList[i]->compute();
	}

	const char* getCurrentAni(PlayerDirection dir);
	const char* getRideAni(PlayerDirection dir);
	
	void reset();// 清除之前的状态
};

#endif