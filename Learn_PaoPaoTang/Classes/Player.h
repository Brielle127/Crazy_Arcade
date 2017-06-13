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
// ��һ�������
struct BaseAttri 
{
	float mSpeed;     // �ٶ�
	int mMaxBombNum;  // ը������
	int mBombStrength;// ը������
	bool mCanKickPopo;
	bool mIgnoreItem;   // ���Ե���
	bool mIgnoreStatic; // �����赲��
};

class Player :public GameObject
{
	PlayerLogicState mState; // ��ɫ��ǰ״̬
	PlayerDirection mDirection; // �ƶ�����
	bool mIsRiding;   // �Ƿ����
	TransParam mTransParam;
	BaseAttri mAttri;
	BaseAttri mAttriEx; // �������� 
	PlayerLogicState mTransTable[PI_NUM][PLS_NUM]; // ״̬ת����  ������+��ǰ״̬->��һ״̬
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
			mBuffList.erase(mBuffList.begin()); // �Ƴ�֮ǰ��Buff
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
		memset(&mAttriEx, 0, sizeof(mAttriEx)); // ��ո�������
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

		(this->*states[mState].update)(dt); // ���ó�Ա����
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
