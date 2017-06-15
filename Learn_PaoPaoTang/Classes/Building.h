///////////////////////////////////////////////////////////////////////////////
/// \file Building.h
/// \brief ʵ��Building��
/// 
/// 
///
/// \author ������
///////////////////////////////////////////////////////////////////////////////

#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "GameObject.h"
#include "BuildingInfoConfig.h"
#include "Animation.h"
#include "Item.h"

class Building :public GameObject
{
private:                   // ��̬����
	int mBarrierGridCntX;  // ռ�õ������
	int mBarrierGridCntY;  // ռ�õ������
	bool mDestroyEnable;   // �Ƿ�ɴݻ�
public:
	Building(PlayScene& rScene) 
		:GameObject(rScene, GOT_Building)
		, mBarrierGridCntX(0)
		, mBarrierGridCntY(0)
		, mDestroyEnable(false)
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
			int bw = info.barrierX*GRID_SIZE;         // �赲�Ŀ�
			int fw = mRenderObj.getSize()->size.width;// ����Ŀ�
			int anx = (fw - bw) / 2;                  // ê�������
			mRenderObj.setAnchorPoint(Point(anx, 0));
		}
	
		mBarrierGridCntX = info.barrierX;
		mBarrierGridCntY = info.barrierY;
		mDestroyEnable = info.isDestroyEnable;
	}
	
	void init()
	{
		for (int i = 0; i < mBarrierGridCntX; ++i)
			for (int j = 0; j < mBarrierGridCntY; ++j)
				mScene.setBarrier(mGridX + i, mGridY + j, true);
	}

	virtual float getDepth()
	{
		return -(mRenderObj.getPosition().y + GRID_SIZE-GRID_SIZE/6); // ����Ư��һ��
	}

	virtual void update(float dt)
	{
		//  ������

		GameObject::update(dt);
	}
	
	virtual void beAttacked()
	{
		if (mDestroyEnable) {
			destroy(); // ���ݻ�
			mNeedDestroy = true;
			// ��ʾ����
			if (CCRANDOM_0_1() < mScene.getGlobalPercent()) {
				Item* pItem = (Item*)mScene.createObject(GOT_Item);
				int idx = int(CCRANDOM_0_1()*(mScene.getItemsPercent().size()));
				if (pItem->init(mScene.getItemsPercent()[idx])) {
					pItem->setPosition(mRenderObj.getPosition());
					mScene.addObj(pItem, mGridX, mGridY);
				}
				else {  // ��������ʧ��
					delete pItem;
					return;
				}
			}
		}
	}

	bool destroyEnable() 
	{
		return mDestroyEnable;
	}

	void destroy()
	{
		for (int i = 0; i < mBarrierGridCntX; ++i)
			mScene.setBarrier(mGridX + i, mGridY, false);
	}
};

#endif // !_PALYER_H_
