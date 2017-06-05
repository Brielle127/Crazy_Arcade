#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "GameObject.h"

#define PART_BODY  "body"
#define PART_EFX "dead"  // Ŀǰֻ��һ����Ч������
#define PART_RIDE "ride"

class Player;
typedef void(Player::*Method)();       // Player���޲��޷���ֵ��Ա����
typedef void(Player::*UpdateMethod)(float); // ���·���
typedef void(Player::*InputMethod)(ControlType, PressState);
struct StateMethod  // ״̬����
{
	Method enter;
	Method exit;
	UpdateMethod update;
	InputMethod input;
	void init(Method en, Method ex, UpdateMethod up,InputMethod ip)
	{
		enter = en;
		exit = ex;
		update = up;
		input = ip;
	}
};
class Player:public GameObject
{
	PlayerLogicState mState; // ��ɫ��ǰ״̬
	float mSpeed;     // �ٶ�
	int mMaxBombNum;  // ը������
	int mBombStrength;// ը������
	bool mIsRiding;   // �Ƿ����
	PlayerMoveState mMoveState; // �ƶ�����
	bool mTransTable[PLS_NUM][PLS_NUM]; // ״̬ת����
	StateMethod states[PLS_NUM];
public:
	Player(PlayScene& rScene);

	virtual void load(const char* szName)
	{
		mRenderObj.setAni(PART_BODY, "role1", "walk_up");
	}
	virtual void update(float dt) 
	{
		(this->*states[mState].update)(dt); // ���ó�Ա����
		// ...
		GameObject::update(dt);
	}
public:
	void handleInput(ControlType ectType, PressState epState)
	{ 
		(this->*states[mState].input)(ectType,epState);
	}
	void standHandleInput(ControlType ectType, PressState epState)
	{
		if (epState == PS_DOWN) {
			mState = PLS_MOVE;//�л��߼�״̬Ϊ�ƶ�
			switch (ectType)
			{
			case CT_LEFT:
				mMoveState = PMS_LEFT;
				break;
			case CT_RIGHT:
				mMoveState = PMS_RIGHT;
				break;
			case CT_UP:
				mMoveState = PMS_UP;
				break;
			case CT_DOWN:
				mMoveState = PMS_DOWN;
				break;
			default:
				mState = PLS_STAND;
			}
		}
	}

	void moveHandleInput(ControlType ectType, PressState epState)
	{

	}
private: // Ĭ�Ϸ���
	void defaultEnter() {}
	void  defaultExit() {}
	void defaultUpdate(float dt) {}
	void defaultHandleInput(ControlType ectType, PressState epState) {}
 };


#endif // !_PALYER_H_
