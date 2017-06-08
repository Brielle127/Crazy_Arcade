#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "GameObject.h"
#include "BuildingInfoConfig.h"
#include "Animation.h"

class Building :public GameObject
{
private:// 静态属性
	int mBarrierGridCnt;  // 占用的阻挡格子数
public:
	Building(PlayScene& rScene) :GameObject(rScene, GOT_Building)
	{
	
	}

	virtual void load(const char* szName)
	{
		BuildingInfo& info = *BuildingIfoMgr::getBuildingInfo(szName);
		 
		for (size_t i = 0; i < info.partInfo.size(); ++i)
		{
			mRenderObj.addPart(info.partInfo[i].name.c_str(), info.partInfo[i].offset);
			mRenderObj.setAni(info.partInfo[i].name.c_str(), info.partInfo[i].group.c_str(), info.partInfo[i].aniName.c_str());
		}

		auto rect = mRenderObj.getSize();
		if (rect) {
			int bw = info.barrierX*GRID_SIZE; // 阻挡的宽
			int fw = mRenderObj.getSize()->size.width;// 对象的宽
			int anx = (bw - fw) / 2; // 锚点横坐标
			mRenderObj.setAnchorPoint(Point(anx, 0));
		}
	
		mBarrierGridCnt = info.barrierX;
	}
	
	// 用于排序
	virtual float getDepth()
	{
		return -(mRenderObj.getPosition().y + GRID_SIZE); // 向上漂移一格
	}

	virtual void update(float dt)
	{
		//  。。。

		GameObject::update(dt);
	}

	// 初始化
	void init()
	{
		for (int i = 0; i < mBarrierGridCnt; ++i)
			mScene.setBarrier(mGridX + i, mGridY, true);
	}

	void destroy()
	{
		for (int i = 0; i < mBarrierGridCnt; ++i)
			mScene.setBarrier(mGridX + i, mGridY, false);
	}
};

#endif // !_PALYER_H_
