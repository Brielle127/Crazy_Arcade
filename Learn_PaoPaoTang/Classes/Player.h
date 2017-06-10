#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "GameObject.h"

#include<map>
#include <vector>
using namespace std;

#define PART_BODY  "body"
#define PART_EFX "dead"  // Ŀǰֻ��һ����Ч������
#define PART_RIDE "ride"

class Player;
typedef void(Player::*Method)();       // Player���޲��޷���ֵ��Ա����
typedef void(Player::*UpdateMethod)(float); // ���·���
//typedef void(Player::*InputMethod)(ControlType, PressState);
struct StateMethod  // ״̬����
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
	PlayerLogicState mState; // ��ɫ��ǰ״̬
	PlayerMoveState mMoveState; // �ƶ�����
	TransParam mTransParam;
	float mSpeed;     // �ٶ�
	int mMaxBombNum;  // ը������
	int mBombStrength;// ը������
	bool mIsRiding;   // �Ƿ����
	
	
	PlayerLogicState mTransTable[PI_NUM][PLS_NUM]; // ״̬ת����  ������+��ǰ״̬->��һ״̬
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

		// ����Ĭ������Ĳ�������
		mTransTable[PI_KILL][PLS_STAND] = PLS_WRAPPED; // ��ֹ״̬+ը����ը->�����ݰ���
		mTransTable[PI_MOVE][PLS_STAND] = PLS_MOVE;    // ��ֹ״̬+�����ƶ�->�ƶ�״̬

		mTransTable[PI_MOVE][PLS_MOVE] = PLS_MOVE;
		mTransTable[PI_KILL][PLS_MOVE] = PLS_WRAPPED;
		mTransTable[PI_STOP][PLS_MOVE] = PLS_STAND;

		// ������ߡ�
		mTransTable[PI_KILL][PLS_WRAPPED] = PLS_DEAD;

		// ��ʼ��Ĭ�Ϸ���
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
		(this->*states[mState].update)(dt); // ���ó�Ա����
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
	void handleDown(ControlType ectType) // ������̰����¼�
	{
		switch (ectType)
		{
		case CT_PRESS: // �ո����ը��
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
			PlayerLogicState s = mTransTable[PI_MOVE][mState];  // �����ƶ�
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
		case CT_PRESS: // �ո����ը��
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
					//mInputCache.erase(it);// ɾ��
					//break;
				//}
			//}

			//if (mInputCache.empty()) {     // ����Ϊ��
				PlayerLogicState s = mTransTable[PI_STOP][mState];  // ����ͣ��
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
	// �л�״̬
	void changeState(PlayerLogicState nextState)
	{
		// �˳���ǰ״̬
		StateMethod rCurrent = states[mState];
		(this->*rCurrent.exit)();

		mState = nextState;
		StateMethod rNext = states[nextState];
		(this->*rNext.enter)();
	}
	void moveStateUpdate(float dt);
private:
	// �л�����
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
private: // Ĭ�Ϸ���
	void defaultEnter() {}
	void defaultExit() {}
	void defaultUpdate(float dt) {}
	void defaultHandleInput(ControlType ectType, PressState epState) {}

public:
	//�õ����ﷶΧ�����ڵ����� //��־��
	Rect BoundingBox() { return mRenderObj.sprite->getBoundingBox(); }
 };


#endif // !_PALYER_H_
