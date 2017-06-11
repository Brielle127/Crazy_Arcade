#ifndef _BOMB_H_
#define _BOMB_H_

#include "GameObject.h"
#include "BaseDef.h"
#include "PlayScene.h"
#define TIME_OUT 1
class Bomb :public GameObject
{
	int mIdleTime;// 爆炸时间
	int mLength;  // 威力
	int *mBombPtr; //持有Player泡泡数目
	float mCurrentTime; // 当前读秒时间
	BombState mState;
public:

	Bomb(PlayScene& rScene, int idleTime = 3, int len = 3)
		:GameObject(rScene, GOT_Bomb)
		, mIdleTime(idleTime)
		, mLength(len)
		, mState(BS_IDLE)
		, mCurrentTime(0.0f)
	{
		mRenderObj.addPart("p0", Point::ZERO);
		mRenderObj.addPart("p1", Point::ZERO);

		mRenderObj.setAni("p0", "Popo", "idle");
		mRenderObj.setAni("p1", "Popo", "shadow");
		// 修正锚点
		mRenderObj.setAnchorPoint(Point(mRenderObj.getSize()->size.width / 2, 10));
	}

public:
	void setStrLen(int len)
	{
		mLength = len;
	}

	void setRelatedPtr(int *ptr)
	{
		mBombPtr = ptr;
	}
	virtual void load(const char* szName)
	{

	}

	virtual void setGrid(int gridx, int gridy)
	{
		GameObject::setGrid(gridx, gridy);
		mScene.setBarrier(gridx, gridy, true);
		setPosition(Point(gridx*GRID_SIZE + GRID_SIZE / 2, gridy*GRID_SIZE + GRID_SIZE / 2));
	}
	// 取得泡泡的深度
	virtual float getDepth()
	{
		if (mState == BS_EXPLODE) 
		{
			return -0xffff;    // 爆炸总是发生在玩家下方
		}
	   return -mRenderObj.getPosition().y-GRID_SIZE/4;// 未爆炸状态

	}

	virtual void update(float dt)
	{
		if (mNeedDestroy)
			return;
		//  
		mCurrentTime += dt;
		switch (mState)
		{
		case BS_IDLE:
			if (mCurrentTime > mIdleTime)  // 读秒时间超过爆炸时间
			{
				
				mCurrentTime = 0;
				mScene.setBarrier(mGridX, mGridY, false);
				explosion();
				(*mBombPtr)++;  // 增加炸弹计数
				// ... 
				mState = BS_EXPLODE;       // 状态切换为爆炸
			}
			break;
		case BS_EXPLODE:
			if (mCurrentTime > TIME_OUT)
			{
				mNeedDestroy = true;
				attack();
				//mScene.destroy(this);
			}
			break;
		}

		GameObject::update(dt);
	}
	void beKicked(int dirx,int diry) // 踢炸弹
	{
		if (mState != BS_IDLE)
			return;
		int newPx = mGridX, newPy = mGridY;
		
		while (dirx!=0) {  // 左右方向
				if (mScene.getBarrier(newPx + dirx, mGridY))  // 向前搜索障碍物
					break;  
			newPx += dirx;
		}
		while (diry!=0) { // 上下方向
			if (mScene.getBarrier(mGridX, newPy+diry))  // 向前搜索障碍物
				break;
			newPy += diry;
		}
	
		if (newPx == mGridX && newPy == mGridY)
			return;
		mScene.setBarrier(mGridX, mGridY, false);  // 清除当前位置的炸弹
		setGrid(newPx, newPy);
	}
private:
	void explosion();// 爆炸效果
	void attack();   // 炸弹攻击
};

#endif // !_PALYER_H_