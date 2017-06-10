#ifndef _BOMB_H_
#define _BOMB_H_

#include "GameObject.h"
#include "BaseDef.h"
class Bomb :public GameObject
{
	int mIdleTime;// 爆炸时间
	int mLength;  // 威力
	float mCurrentTime; // 当前读秒时间
	BombState mState;
public:

	Bomb(PlayScene& rScene,int idleTime=3,int len=3) 
		:GameObject(rScene, GOT_Bomb)
		,mIdleTime(idleTime)
		,mLength(len)
		,mState(BS_IDLE)
		,mCurrentTime(0.0f)
	{
		mRenderObj.addPart("p0", Point::ZERO);
		mRenderObj.addPart("p1", Point::ZERO);

		mRenderObj.setAni("p0", "Popo", "idle");
		mRenderObj.setAni("p1", "Popo", "shadow");
		// 修正锚点
		mRenderObj.modifyPartOffset("p0", Point(-mRenderObj.getSize()->size.width / 2, -10));
		mRenderObj.modifyPartOffset("p1", Point(-mRenderObj.getSize()->size.width / 2, -10));
	}

	virtual void load(const char* szName)
	{

	}

	virtual void update(float dt)
	{
		//  
		mCurrentTime += dt;
		switch (mState)
		{
		case BS_IDLE:
			if (mCurrentTime > mIdleTime)  // 读秒时间超过爆炸时间
			{
				// ... 
				mState = BS_EXPLODE;       // 状态切换为爆炸
			}
			break;
		case BS_EXPLODE:
			break;
		}

		GameObject::update(dt);
	}

};

#endif // !_PALYER_H_
