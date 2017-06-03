#pragma once
#ifndef _PLAY_SCENE_H_
#define _PLAY_SCENE_H_

#include "cocos2d.h"
#include "BaseScene.h"

#include "BaseDef.h"

USING_NS_CC;

class CPlayScene:public CBaseScene
{
public:
	CPlayScene();

	virtual void onEnterScene();
	virtual void onExitScene();
};
#endif // !_PLAY_SCENE_H_
