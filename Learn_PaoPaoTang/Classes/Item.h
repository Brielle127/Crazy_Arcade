//////////////////////////////
/// \file Item.h
///  \brief source file for class Item
/// 实现道具类
///  
///
///
///
///\author 蓝楚迪
/////////////////////////////

#ifndef _ITEM_H_
#define _ITEM_H_

#include "GameObject.h"

class Item :public GameObject
{
public:
	Item(PlayScene& rScene) :GameObject(rScene, GOT_Item)

	{

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
