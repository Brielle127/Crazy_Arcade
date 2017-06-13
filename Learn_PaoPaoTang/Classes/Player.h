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
	PlayerDirection nextDirection;
};
// 玩家基本属性
struct BaseAttri 
{
	float mSpeed;     // 速度
	int mMaxBombNum;  // 炸弹数量
	int mBombStrength;// 炸弹威力
	bool mCanKickPopo;
	bool mIgnoreItem;   // 忽略道具
	bool mIgnoreStatic; // 忽略阻挡物
};

class Player :public GameObject
{
	PlayerLogicState mState; // 角色当前状态
	PlayerDirection mDirection; // 移动方向
	bool mIsRiding;   // 是否骑乘
	TransParam mTransParam;
	BaseAttri mAttri;
	BaseAttri mAttriEx; // 附加属性 
	PlayerLogicState mTransTable[PI_NUM][PLS_NUM]; // 状态转换表  请求动作+当前状态->下一状态
	StateMethod states[PLS_NUM];
	bool move_flag=false;
	RoleInfo* mRoleInfo;
	struct ItemInfo* mRideInfo;
	
	vector<Buff*> mBuffList;
	int mCurrentUsedBombNum;
public:
	Player(PlayScene& rScene);
	
	void addBuff(Buff* p)
	{
		if (mBuffList.size())
			mBuffList.erase(mBuffList.begin()); // 移除之前的Buff
		mBuffList.push_back(p);
		p->attach(this);
		refreshBuff();
	}
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

	virtual void load(const char* szName)
	{
		mRoleInfo = RoleInfoMgr::getRoleInfo(100);
		mAttri.mMaxBombNum = mRoleInfo->original_popo_num;
		mAttri.mSpeed = mRoleInfo->original_speed;
		mAttri.mBombStrength = mRoleInfo->original_str;
		mCurrentUsedBombNum = 0;
		mRenderObj.setAni(PART_BODY, mRoleInfo->group.c_str(), "stand_up");
		mRenderObj.modifyPartOffset(PART_BODY,Point(-mRenderObj.getSize()->size.width / 2, 0));
		
		/*mRenderObj.setAni(PART_RIDE, "FastTurtle", "stand_up");
		mRenderObj.modifyPartOffset(PART_RIDE, Point(-mRenderObj.getSize()->size.width / 2, 0));*/
	}
	virtual void update(float dt)
	{
		for (size_t i = 0; i < mBuffList.size(); ++i)
			mBuffList[i]->update(0);

		(this->*states[mState].update)(dt); // 调用成员函数
		GameObject::update(dt);
	}
public:
	void ride(ItemInfo* rideInfo);
	void handleInput(ControlType ectType, PressState epState);
public:
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
private:
	void handleDown(ControlType ectType);
	void handleUp(ControlType ectType);
	
	void changeState(PlayerLogicState nextState);// 切换状态
private:
	void standStateEnter();

	
	void moveStateEnter();// 切换动画
	void moveStateUpdate(float dt);
	void moveAndStandOrderHandler(OrderType type, void* data);
	const char* getCurrentAni(PlayerDirection dir);
	const char* getRideAni(PlayerDirection dir);
private: // 默认方法
	void defaultEnter() {}
	void defaultExit() {}
	void defaultUpdate(float dt) {}
	void defaultHandleInput(ControlType ectType, PressState epState) {}
	void defaultOrderHandler(OrderType, void*) {}
};

#endif // !_PALYER_H_
