#include"BaseScene.h"

USING_NS_CC;

CBaseScene::CBaseScene()
{
	mSceneLayer = Layer::create();
	mSceneLayer->retain(); // 增加引用计数
}

Layer* CBaseScene::getSceneLayer()
{
	return mSceneLayer;
}

void CBaseScene::onHandleEvent(int eventType, void * data)
{

}
