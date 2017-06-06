#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "GameObject.h"

class Building :public GameObject
{
private:// ��̬����
	int mBarrierCnt;  // ռ�õ��赲������
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
	// ��������
	virtual int getDepth()
	{
		return -mRenderObj.getPosition().y + GRID_SIZE; // ����Ư��һ��
	}

	virtual void update(float dt)
	{
		//  ������

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
