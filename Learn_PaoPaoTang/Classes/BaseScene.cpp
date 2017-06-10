#include"BaseScene.h"

USING_NS_CC;


BaseScene::BaseScene()
{
	mSceneLayer = Layer::create();
	mSceneLayer->retain(); // �������ü���
}

Layer* BaseScene::getSceneLayer()
{
	return mSceneLayer;
}


void BaseScene::onHandleEvent(int eventType, void * data) {}
