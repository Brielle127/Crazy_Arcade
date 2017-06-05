#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_

#include "cocos2d.h"
#include "StringTableMgr.h"
#include "BaseDef.h"
USING_NS_CC;

class BaseScene
{
public:
	BaseScene()
	{
		mSceneLayer = Layer::create();
		mSceneLayer->retain(); // 增加引用计数
	}

	virtual ~BaseScene()
	{
		mSceneLayer->release();
		mSceneLayer = nullptr;
	}

	Layer* getSceneLayer()
	{
		return mSceneLayer;
	}

public:
	virtual void onEnterScene(){}
	virtual void onExitScene(){}
	virtual void onUpdate(float dt) 
	{

	}

	virtual void handleInput(ControlType ectType, PressState epState)
	{

	}
	// UI使用
	virtual void onHandleEvent(int eventType, void* data)
	{

	}
protected:
	Layer* mSceneLayer;
};

#endif /gmk/ !_BASE_SCENE_H_
