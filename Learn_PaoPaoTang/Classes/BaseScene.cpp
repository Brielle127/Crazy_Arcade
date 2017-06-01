#include"BaseScene.h"

USING_NS_CC;

CBaseScene::CBaseScene()
{
	mSceneLayer = Layer::create();
}

Layer* CBaseScene::getSceneLayer()
{
	return mSceneLayer;
}

void CBaseScene::onHandleEvent(int eventType, void * data)
{

}
