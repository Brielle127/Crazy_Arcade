#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "GameObject.h"

class Building :public GameObject
{
public:
	Building(PlayScene& rScene) :GameObject(rScene, GOT_Building)

	{
		mRenderObj.addPart("root", Point::ZERO);
		mRenderObj.addPart("head", Point(0, 71));

		mRenderObj.setAni(0, "oasis", "root");
		mRenderObj.setAni("head", "oasis", "head");

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
