#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "GameObject.h"
#include "BuildingInfoConfig.h"
#include "Animation.h"

class Building :public GameObject
{
private:// ��̬����
	int mBarrierCnt;  // ռ�õ��赲������
public:
	Building(PlayScene& rScene) :GameObject(rScene, GOT_Building)
	{
		load("oasis");
	}

	virtual void load(const char* szName)
	{
		BuildingInfo& info = *BuildingIfoMgr::getBuildingInfo(szName);
		 
		for (int i = 0; i < info.partInfo.size(); ++i)
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
