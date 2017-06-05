#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "GameObject.h"

#define PART_BODY  "body"
#define PART_EFX "dead"  // Ŀǰֻ��һ����Ч������
#define PART_RIDE "ride"

class Player;
typedef void(Player::*Method)();       // Player���޲��޷���ֵ��Ա����
typedef void(Player::*UpdateMethod)(float); // ���·���
struct StateMethod  // ״̬����
{
	Method enter;
	Method exit;
	UpdateMethod update;
	void init(Method en, Method ex, UpdateMethod up)
	{
		enter = en;
		exit = ex;
		update = up;
	}
};
class Player:public GameObject
{
	PlayerLogicState mState; // ��ɫ��ǰ״̬
	float mSpeed;     // �ٶ�
	int mMaxBombNum;  // ը������
	int mBombStrength;// ը������
	bool mIsRiding;   // �Ƿ����
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
		(this->*states[PLS_STAND].update)(dt); // ���ó�Ա����
		// ...
		GameObject::update(dt);
	}
private: // Ĭ�Ϸ���
	void defaultEnter() {}
	void  defaultExit() {}
	void defaultUpdate(float dt) {}
};


#endif // !_PALYER_H_
