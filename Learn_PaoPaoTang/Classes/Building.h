//////////////////////////////
/// \file Building.h
///  \brief Head file for class Building
/// 实现静态对象的配置
///  加载以及管理
///
///
///
///\author 蓝楚迪
/////////////////////////////







#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "GameObject.h"
#include "BuildingInfoConfig.h"
#include "Animation.h"

class Building :public GameObject
{
private:///静态属性
	int mBarrierCnt;  ///< 占用的阻挡格子数
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
			int bw = info.barrierX*GRID_SIZE; ///<阻挡的宽
			int fw = mRenderObj.getSize()->size.width;///< 对象的宽
			int anx = (bw - fw) / 2; ///< 锚点横坐标
			mRenderObj.setAnchorPoint(Point(anx, 0));
		}
	}
	/// 用于排序
	virtual float getDepth()
	{
		return -(mRenderObj.getPosition().y + GRID_SIZE); /// 向上漂移一格
	}

	virtual void update(float dt)
	{
		/// 。。。

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
