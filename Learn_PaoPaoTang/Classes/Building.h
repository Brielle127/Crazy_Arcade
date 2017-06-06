#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "GameObject.h"

class Building :public GameObject
{
private:// 静态属性
	int mBarrierCnt;  // 占用的阻挡格子数
public:
	Building(PlayScene& rScene) :GameObject(rScene, GOT_Building)
	{
		
	}

	virtual void load(const char* szName)
	{
		mRenderObj.addPart("root", Point::ZERO);
		mRenderObj.addPart("head", Point(0, 71));

		mRenderObj.setAni(0, "oasis", "root");
		mRenderObj.setAni("head", "oasis", "head");

	}
	// 用于排序
	virtual int getDepth()
	{
		return -mRenderObj.getPosition().y + GRID_SIZE; // 向上漂移一格
	}

	virtual void update(float dt)
	{
		//  。。。

		GameObject::update(dt);
	}

	void init()
	{
		for (int i = 0; i < mBarrierCnt; ++i)
			mScene.setBarrier(mGridX + i, mGridY, true);
	}

	void destroy()
	{
		for (int i = 0; i < mBarrierCnt; ++i)
			mScene.setBarrier(mGridX + i, mGridY, false);
	}
};

#endif // !_PALYER_H_
