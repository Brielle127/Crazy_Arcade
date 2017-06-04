#ifndef _PALYER_H_
#define _PLAYER_H_

#include "GameObject.h"

#define PART_BODY  "body"
#define PART_EFX "dead"  // Ŀǰֻ��һ����Ч������
#define PART_RIDE "ride"

class CPlayer:public CGameObject
{
	EPlayerLogicState mState;
	float mSpeed;     // �ٶ�
	int mMaxBombNum;  // ը������
	int mBombStrength;// ը������
public:
	CPlayer(CPlayScene& rScene) 
		:CGameObject(rScene, EGOT_Player)
		,mState(EPLS_STAND)
		,mSpeed(0)
		,mMaxBombNum(0)
		,mBombStrength(0)
	{
		mRenderObj.addPart(PART_BODY, Point::ZERO);
		mRenderObj.addPart(PART_EFX, Point::ZERO);
		mRenderObj.addPart(PART_RIDE, Point::ZERO);
	}

	virtual void load(const char* szName)
	{

	}
	virtual void update(float dt) 
	{
		//  

		CGameObject::update(dt);
	}
public:
	/* ����ը�� */
	void setBomb()
	{

	}

	/* ��ɫ�ƶ� */
	void move()
	{

	}

	void stop()
	{

	}
};


#endif // !_PALYER_H_
