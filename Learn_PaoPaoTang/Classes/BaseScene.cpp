#include"BaseScene.h"

USING_NS_CC;


BaseScene::BaseScene()
{
	mSceneLayer = Layer::create();
	mSceneLayer->retain(); // 增加引用计数
}

Layer* BaseScene::getSceneLayer()
{
	return mSceneLayer;
}


void BaseScene::onHandleEvent(int eventType, void * data) {}
