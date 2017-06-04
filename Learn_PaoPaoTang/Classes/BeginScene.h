#ifndef BEGIN_SCENE_H
#define BEGIN_SCENE_H

#include"cocos2d.h"
#include"BaseScene.h"
#include"BaseDef.h"
#include"tinyxml.h"
#include"StringTableMgr.h"
#include<xstring>

USING_NS_CC;

class BeginScene :public BaseScene
{
public:
	BeginScene();

	virtual void onEnterScene();
	virtual void onExitScene();
	
};

#endif // !BEGIN_SCENE_H
