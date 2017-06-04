#ifndef _PALYER_H_
#define _PLAYER_H_

#include "GameObject.h"

class CPlayer:public CGameObject
{
public:
	CPlayer(CPlayScene& rScene) :CGameObject(rScene, EGOT_Player)
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
