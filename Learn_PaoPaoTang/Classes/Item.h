#ifndef _ITEM_H_
#define _ITEM_H_

#include "GameObject.h"
#include "ItemConfig.h"
class Item :public GameObject
{
public:
	Item(PlayScene& rScene) :GameObject(rScene, GOT_Item)
	{
		 
	}

	bool init(int tid)
	{
		char buf[256];
		sprintf(buf, "iem_%d", tid);
		auto info = ItemInfoMgr::getItemInfo(tid);
		if (info == nullptr)
			return false;
		mRenderObj.addPart(buf, Point::ZERO);
		mRenderObj.setAni(buf, info->group.c_str(), info->ani.c_str());
		return true;
	}

	virtual void load(const char* szName)
	{

	}

	virtual void update(float dt)
	{
		//  

		GameObject::update(dt);
	}

};

#endif // !_PALYER_H_
