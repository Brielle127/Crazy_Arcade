#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "GameObject.h"
#include "BuildingInfoConfig.h"
#include "Animation.h"

class Building :public GameObject
{
private:// ��̬����
	int mBarrierGridCnt;  // ռ�õ��赲������
	bool mDestroyEnable;  // �Ƿ�ɴݻ�
public:
	Building(PlayScene& rScene) 
		:GameObject(rScene, GOT_Building)
		,mBarrierGridCnt(0)
		,mDestroyEnable(false)
	{
	
	}

	virtual void load(const char* szName)
	{
		BuildingInfo& info = *BuildingInfoMgr::getBuildingInfo(szName);
		 
		for (size_t i = 0; i < info.partInfo.size(); ++i)
		{
			mRenderObj.addPart(info.partInfo[i].name.c_str(), info.partInfo[i].offset);
			mRenderObj.setAni(info.partInfo[i].name.c_str(), info.partInfo[i].group.c_str(), info.partInfo[i].aniName.c_str());
		}

		auto rect = mRenderObj.getSize();
		if (rect) {
			int bw = info.barrierX*GRID_SIZE; // �赲�Ŀ�
			int fw = mRenderObj.getSize()->size.width;// ����Ŀ�
			int anx = (bw - fw) / 2; // ê�������
			mRenderObj.setAnchorPoint(Point(anx, 0));
		}
	
		mBarrierGridCnt = info.barrierX;
		mDestroyEnable = info.isDestroyEnable;
	}
	
	// ��������
	virtual float getDepth()
	{
		return -(mRenderObj.getPosition().y + GRID_SIZE); // ����Ư��һ��
	}

	virtual void update(float dt)
	{
		//  ������

		GameObject::update(dt);
	}

	// ��ʼ��
	void init()
	{
		for (int i = 0; i < mBarrierGridCnt; ++i)
			mScene.setBarrier(mGridX + i, mGridY, true);
	}

	virtual void beAttacked()
	{
		if (mDestroyEnable) {
			destroy();
			mNeedDestroy = true;
		}
	}

	void destroy()
	{
		for (int i = 0; i < mBarrierGridCnt; ++i)
			mScene.setBarrier(mGridX + i, mGridY, false);
	}
};

#endif // !_PALYER_H_
