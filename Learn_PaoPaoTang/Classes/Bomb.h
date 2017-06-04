#ifndef _BOMB_H_
#define _BOMB_H_

#include "GameObject.h"

class CBomb :public CGameObject
{
public:
	CBomb(CPlayScene& rScene) :CGameObject(rScene, EGOT_Bomb)
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
