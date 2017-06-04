#ifndef _PALYER_H_
#define _PLAYER_H_

#include "GameObject.h"

#define PART_BODY  "body"
#define PART_EFX "dead"  // 目前只有一种特效：死亡
#define PART_RIDE "ride"

class CPlayer:public CGameObject
{
	EPlayerLogicState mState;
	float mSpeed;     // 速度
	int mMaxBombNum;  // 炸弹数量
	int mBombStrength;// 炸弹威力
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
	/* 放置炸弹 */
	void setBomb()
	{

	}

	/* 角色移动 */
	void move()
	{

	}

	void stop()
	{

	}
};


#endif // !_PALYER_H_
