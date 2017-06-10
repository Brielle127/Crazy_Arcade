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
typedef void(Player::*OrderMethod)(OrderType,void*);   // �߼���������
struct StateMethod  // ״̬����
{
	Method enter;
	Method exit;
	UpdateMethod update;
	OrderMethod orderHandler;
	//InputMethod input;
	void init(Method en, Method ex, UpdateMethod up,OrderMethod oh)
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
<<<<<<< HEAD
	Player(PlayScene& rScene);
=======
	
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
>>>>>>> db872432032f8c33494e292918e07a44dcd62716

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
<<<<<<< HEAD
	void defaultOrderHandler(OrderType,void*){}
=======

public:
	//�õ����ﷶΧ�����ڵ����� //��־��
	Rect BoundingBox() { return mRenderObj.sprite->getBoundingBox(); }
>>>>>>> db872432032f8c33494e292918e07a44dcd62716
 };

#endif // !_PALYER_H_
