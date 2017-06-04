#ifndef _BOMB_H_
#define _BOMB_H_

#include "GameObject.h"

class Bomb :public GameObject
{
public:
	Bomb(PlayScene& rScene) :GameObject(rScene, EGOT_Bomb)
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
