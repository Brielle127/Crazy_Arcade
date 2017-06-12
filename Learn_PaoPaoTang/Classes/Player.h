#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"
#include "RoleTableConfig.h"
#include"ItemConfig.h"

#include<map>
#include <vector>
using namespace std;

#define PART_BODY  "body"
#define PART_EFX "dead"  // Ŀǰֻ��һ����Ч������
#define PART_RIDE "ride"

class Player;
typedef void(Player::*Method)();       // Player���޲��޷���ֵ��Ա����
typedef void(Player::*UpdateMethod)(float); // ���·���
typedef void(Player::*OrderMethod)(OrderType, void*);   // �߼���������
struct StateMethod  // ״̬����
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
	PlayerLogicState mState; // ��ɫ��ǰ״̬
	PlayerDirection mDirection; // �ƶ�����
	TransParam mTransParam;
	float mSpeed;     // �ٶ�
	int mMaxBombNum;  // ը������
	int mBombStrength;// ը������
	bool mIsRiding;   // �Ƿ����
	bool mCanKickPopo;  
	PlayerLogicState mTransTable[PI_NUM][PLS_NUM]; // ״̬ת����  ������+��ǰ״̬->��һ״̬
	StateMethod states[PLS_NUM];
	bool move_flag=false;

	RoleInfo* mRoleInfo;
	class ItemInfo* mRideInfo;
public:
	Player(PlayScene& rScene);
	
	virtual void load(const char* szName)
	{
		mRoleInfo = RoleInfoMgr::getRoleInfo(100);
		mMaxBombNum = mRoleInfo->original_popo_num;
		mSpeed = mRoleInfo->original_speed;
		mBombStrength = mRoleInfo->original_str;

		mRenderObj.setAni(PART_BODY, mRoleInfo->group.c_str(), "stand_up");
		mRenderObj.modifyPartOffset(PART_BODY,Point(-mRenderObj.getSize()->size.width / 2, 0));
		
		/*mRenderObj.setAni(PART_RIDE, "FastTurtle", "stand_up");
		mRenderObj.modifyPartOffset(PART_RIDE, Point(-mRenderObj.getSize()->size.width / 2, 0));*/
	}
	virtual void update(float dt)
	{
		(this->*states[mState].update)(dt); // ���ó�Ա����
		GameObject::update(dt);
	}
public:
	void ride(ItemInfo* rideInfo);
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
	
	void changeState(PlayerLogicState nextState);// �л�״̬
private:
	void standStateEnter();

	
	void moveStateEnter();// �л�����
	void moveStateUpdate(float dt);
	void moveAndStandOrderHandler(OrderType type, void* data);
	const char* getCurrentAni(PlayerDirection dir);
	const char* getRideAni(PlayerDirection dir);
private: // Ĭ�Ϸ���
	void defaultEnter() {}
	void defaultExit() {}
	void defaultUpdate(float dt) {}
	void defaultHandleInput(ControlType ectType, PressState epState) {}
	void defaultOrderHandler(OrderType, void*) {}
};

#endif // !_PALYER_H_
