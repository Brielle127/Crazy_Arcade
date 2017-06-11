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

	void init(int tid)
	{
		auto info = ItemInfoMgr::getItemInfo(tid);
		mRenderObj.addPart("p", Point::ZERO);
		mRenderObj.setAni("p", info->group.c_str(), info->ani.c_str());
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
