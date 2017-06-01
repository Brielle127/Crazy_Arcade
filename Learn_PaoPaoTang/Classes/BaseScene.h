#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class CBaseScene
{
public:
	CBaseScene();
	Layer* getSceneLayer();

public:
	virtual void onEnterScene(){}
	virtual void onExitScene(){}
	virtual void onHandleEvent(int eventType, void* data );
protected:
	Layer* mSceneLayer;
};

#endif /gmk/ !_BASE_SCENE_H_
