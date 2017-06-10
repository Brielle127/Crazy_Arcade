#ifndef _BOMB_H_
#define _BOMB_H_

#include "GameObject.h"
#include "BaseDef.h"

#define TIME_OUT 1
class Bomb :public GameObject
{
	int mIdleTime;// ��ըʱ��
	int mLength;  // ����
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

	virtual void load(const char* szName)
	{

	}

	virtual void setGrid(int gridx, int gridy)
	{
		GameObject::setGrid(gridx, gridy);
		mScene.setBarrier(gridx, gridy,true);
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
				// ... 
				mState = BS_EXPLODE;       // ״̬�л�Ϊ��ը
			}
			break;
		case BS_EXPLODE:
			if (mCurrentTime > TIME_OUT)
			{
				mNeedDestroy = true;
				//mScene.destroy(this);
			}
			break;
		}

		GameObject::update(dt);
	}
private:
	void explosion()  // ��ըЧ��
	{
		mRenderObj.removePart("p0");
		mRenderObj.removePart("p1");
		mRenderObj.setAnchorPoint(Point::ZERO);
		mRenderObj.setPosition(Point(mGridX*GRID_SIZE, mGridY*GRID_SIZE));
		
		mRenderObj.addPart("middle", Point::ZERO);
		mRenderObj.setAni("middle", "Explosion", "middle");

		static char buf[256];
		for (int i = 0; i < mLength * 2 + 1; ++i) {

			for (int j = 0; j < mLength * 2 + 1; ++j) {
				if ((i == j&&i == mLength) || (i != mLength && j != mLength)) {
					continue; // �м�
				}
				int px, py;
				px = (i - mLength)*GRID_SIZE;
				py = (mLength - j)*GRID_SIZE;
				sprintf(buf, "part_%d", i + j);
				mRenderObj.addPart(buf, Point(px, py));

				if (j == mLength) {
					if (i == 0) {  // ��߽�
						mRenderObj.setAni(buf, "Explosion", "left");
					}
					else if (i == mLength * 2) { //�ұ߽�
						mRenderObj.setAni(buf, "Explosion", "right");
					}
					else if (i < mLength) {
						mRenderObj.setAni(buf, "Explosion", "left_m");
					}
					else {
						mRenderObj.setAni(buf, "Explosion", "right_m");
					}
				}

				if (i == mLength) {
					if (j == 0) {   // �ϱ߽�
						mRenderObj.setAni(buf, "Explosion", "up");
					}
					else if (j == mLength * 2) {   // �±߽�
						mRenderObj.setAni(buf, "Explosion", "down");
					}
					else if (j < mLength) {
						mRenderObj.setAni(buf, "Explosion", "up_m");
					}
					else {
						mRenderObj.setAni(buf, "Explosion", "down_m");
					}
				}
			}
		}

	}
};

#endif // !_PALYER_H_