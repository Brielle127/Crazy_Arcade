#ifndef _BOMB_H_
#define _BOMB_H_

#include "GameObject.h"
#include "BaseDef.h"
#include "PlayScene.h"
#define TIME_OUT 1
class Bomb :public GameObject
{
	int mIdleTime;// ��ըʱ��
	int mLength;  // ����
	int *mBombPtr; //����Player������Ŀ
	float mCurrentTime; // ��ǰ����ʱ��
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
		// ����ê��
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
	// ȡ�����ݵ����
	virtual float getDepth()
	{
		if (mState == BS_EXPLODE) 
		{
			return -0xffff;    // ��ը���Ƿ���������·�
		}
	   return -mRenderObj.getPosition().y-GRID_SIZE/4;// δ��ը״̬

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
			if (mCurrentTime > mIdleTime)  // ����ʱ�䳬����ըʱ��
			{
				
				mCurrentTime = 0;
				mScene.setBarrier(mGridX, mGridY, false);
				explosion();
				(*mBombPtr)++;  // ����ը������
				// ... 
				mState = BS_EXPLODE;       // ״̬�л�Ϊ��ը
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
	void beKicked(int dirx,int diry) // ��ը��
	{
		if (mState != BS_IDLE)
			return;
		int newPx = mGridX, newPy = mGridY;
		
		while (dirx!=0) {  // ���ҷ���
				if (mScene.getBarrier(newPx + dirx, mGridY))  // ��ǰ�����ϰ���
					break;  
			newPx += dirx;
		}
		while (diry!=0) { // ���·���
			if (mScene.getBarrier(mGridX, newPy+diry))  // ��ǰ�����ϰ���
				break;
			newPy += diry;
		}
	
		if (newPx == mGridX && newPy == mGridY)
			return;
		mScene.setBarrier(mGridX, mGridY, false);  // �����ǰλ�õ�ը��
		setGrid(newPx, newPy);
	}
private:
	void explosion();// ��ըЧ��
	void attack();   // ը������
};

#endif // !_PALYER_H_