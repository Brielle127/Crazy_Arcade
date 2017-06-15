///////////////////////////////////////////////////////////////////////////////
/// \file Player.h
/// \brief ʵ��Player��
/// 
/// 
///
/// \author ������ 
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
#define PART_EFX "dead"  // Ŀǰֻ��һ����Ч������
#define PART_RIDE "ride"

class Player;
typedef void(Player::*Method)();                        // ��ͬ״̬��enter��exit����
typedef void(Player::*UpdateMethod)(float);             // ��ͬ״̬�ĸ��·���
typedef void(Player::*OrderMethod)(OrderType, void*);   // �߼�����
// ��ͬ״̬�ķ���
// ����Ĺ�����Ϊ״̬���ṩ��Ӧ�ĳ�ʼ������
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

struct BaseAttri        // ��һ�������
{
	float mSpeed;       // �ٶ�
	int mMaxBombNum;    // ը������
	int mBombStrength;  // ը������
	bool mCanKickPopo;  // ʱ�����������
	bool mIgnoreItem;   // ���Ե���
	bool mIgnoreStatic; // �����赲��
};

class Player :public GameObject
{
	BaseAttri mAttri;           // �����������
	BaseAttri mAttriEx;         // ���߸������� 
	
	TransParam mTransParam;     // ״̬ת������
	PlayerLogicState mTransTable[PI_NUM][PLS_NUM]; // ״̬ת����:������+��ǰ״̬->��һ״̬
	
	PlayerLogicState mState;    // ��ɫ��ǰ״̬
	StateMethod states[PLS_NUM];// ״̬����
	
	RoleInfo* mRoleInfo;        // ��ɫ��Ϣ
	struct ItemInfo* mRideInfo; // ������Ϣ
	vector<Buff*> mBuffList;    // ����Buff�б�
	
	PlayerDirection mDirection; // �ƶ�����
	bool mIsRiding;             // �Ƿ��������
	int mCurrentUsedBombNum;
	float mSurroundedTime;
	bool move_flag=false;

public:
	Player(PlayScene& rScene);

public:/*   �ӿ�   */	
	void addBuff(Buff* p)
	{
		if (mBuffList.size())
			mBuffList.erase(mBuffList.begin()); // �Ƴ�֮ǰ��Buff
		mBuffList.push_back(p);
		p->attach(this);
		refreshBuff();
	}
	void ride(ItemInfo* rideInfo); // �������
	bool isDead() { return mState == PLS_DEAD; }
public:/* ��д���� */
	void handleInput(ControlType ectType, PressState epState);
	virtual void load(const char* szName);
	virtual void update(float dt);
	virtual void beAttacked();

public:/* ���Բ��� */
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

private:/* ״̬���� */
	void changeState(PlayerLogicState nextState);// �л�״̬
	
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
	void handleDown(ControlType ectType);// ������̰����¼�
	void handleUp(ControlType ectType);  // ��������ɿ��¼�
	
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

	const char* getCurrentAni(PlayerDirection dir);
	const char* getRideAni(PlayerDirection dir);
	
	void reset();// ���֮ǰ��״̬
};

#endif