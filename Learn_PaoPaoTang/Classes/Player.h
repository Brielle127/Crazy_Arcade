#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"
#include "RoleTableConfig.h"

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

class Player :public GameObject
{
	PlayerLogicState mState; // 角色当前状态
	PlayerDirection mDirection; // 移动方向
	TransParam mTransParam;
	float mSpeed;     // 速度
	int mMaxBombNum;  // 炸弹数量
	int mBombStrength;// 炸弹威力
	bool mIsRiding;   // 是否骑乘
	bool mCanKickPopo;  
	PlayerLogicState mTransTable[PI_NUM][PLS_NUM]; // 状态转换表  请求动作+当前状态->下一状态
	StateMethod states[PLS_NUM];
	bool move_flag=false;

	RoleInfo* mRoleInfo;
public:
	Player(PlayScene& rScene);
	
	virtual void load(const char* szName)
	{
		mRoleInfo = RoleInfoMgr::getRoleInfo(100);
		mMaxBombNum = mRoleInfo->original_popo_num;
		mSpeed = mRoleInfo->original_speed;
		mBombStrength = mRoleInfo->original_str;
		mRenderObj.setAni(PART_BODY, mRoleInfo->group.c_str(), "stand_down");
		mRenderObj.setAnchorPoint(Point(mRenderObj.getSize()->size.width/2, 0));
	}
	virtual void update(float dt)
	{
		(this->*states[mState].update)(dt); // 调用成员函数
		GameObject::update(dt);
	}
public:
	void handleInput(ControlType ectType, PressState epState);
public:
	void setBombNum(int bn)
	{
		bn = bn > mRoleInfo->min_popo_num? bn : mRoleInfo->min_popo_num ;
		bn = bn < mRoleInfo->max_popo_num ? bn : mRoleInfo->max_popo_num  ;

		mMaxBombNum = bn; 
	}
	void setStr(int bs) 
	{
		bs = bs >  mRoleInfo->min_str? bs : mRoleInfo->min_str;
		bs = bs <  mRoleInfo->max_str? bs : mRoleInfo->max_str;
		mBombStrength = bs; 
	}
	void setSpeed(int sp) 
	{ 
		sp = sp > mRoleInfo->min_speed ? sp : mRoleInfo->min_speed;
		sp = sp <  mRoleInfo->max_speed? sp : mRoleInfo->max_speed;
		mSpeed = sp; 
	}
	int getBombNum() { return mMaxBombNum; }
	int getStr() { return mBombStrength; }
	int getSpeed() { return mSpeed; }
	void setCanKickPopo(bool value)
	{
		mCanKickPopo = value;
	}
private:
	void handleDown(ControlType ectType);
	void handleUp(ControlType ectType);
	// 切换状态
	void changeState(PlayerLogicState nextState);
private:
	void standStateEnter();

	// 切换动画
	void moveStateEnter();
	void moveStateUpdate(float dt);
	void moveAndStandOrderHandler(OrderType type, void* data);
	const char* getCurrentAni(PlayerDirection);
private: // 默认方法
	void defaultEnter() {}
	void defaultExit() {}
	void defaultUpdate(float dt) {}
	void defaultHandleInput(ControlType ectType, PressState epState) {}
	void defaultOrderHandler(OrderType, void*) {}
};

#endif // !_PALYER_H_
