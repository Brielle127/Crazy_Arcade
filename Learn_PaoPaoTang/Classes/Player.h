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
	PlayerMoveState nextMoveState;
};

class Player :public GameObject
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
	Player(PlayScene& rScene);
	
	virtual void load(const char* szName)
	{
		mRenderObj.setAni(PART_BODY, "role1", "stand_down");
	}
	virtual void update(float dt)
	{
		(this->*states[mState].update)(dt); // ���ó�Ա����
		GameObject::update(dt);
	}
public:
	void handleInput(ControlType ectType, PressState epState);
public:
	void setBombNum(int bn) { mMaxBombNum = bn; }
	void setStr(int bs) { mBombStrength = bs; }
	void setSpeed(int sp) { mSpeed = sp; }
	int getBombNum() { return mMaxBombNum; }
	int getStr() { return mBombStrength; }
	int getSpeed() { return mSpeed; }
private:
	void handleDown(ControlType ectType);
	void handleUp(ControlType ectType);
	// �л�״̬
	void changeState(PlayerLogicState nextState);
private:
	// �л�����
	void moveStateEnter();
	void moveStateUpdate(float dt);
	void moveAndStandOrderHandler(OrderType type, void* data);
private: // Ĭ�Ϸ���
	void defaultEnter() {}
	void defaultExit() {}
	void defaultUpdate(float dt) {}
	void defaultHandleInput(ControlType ectType, PressState epState) {}
	void defaultOrderHandler(OrderType, void*) {}
};

#endif // !_PALYER_H_
