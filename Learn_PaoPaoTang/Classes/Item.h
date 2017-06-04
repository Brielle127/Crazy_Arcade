#ifndef _ITEM_H_
#define _ITEM_H_

#include "GameObject.h"

class CItem :public CGameObject
{
public:
	CItem(CPlayScene& rScene) :CGameObject(rScene, EGOT_Item)
	{

	}

	virtual void load(const char* szName)
	{

	}

	virtual void update(float dt)
	{
		//  

		CGameObject::update(dt);
	}

};

#endif // !_PALYER_H_
