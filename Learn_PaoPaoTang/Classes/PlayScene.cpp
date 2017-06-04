#include "PlayScene.h"
#include "MenuSelectHandler.h"

USING_NS_CC;

CRenderObj* pRenderObj = nullptr; // ���ڲ��Դ���

CPlayScene::CPlayScene()
{
	
}

void CPlayScene::onEnterScene()
{
	/*��������*/


	Sprite* pBG = Sprite::create("pic/BG.png");	 // ��Ϸ��������
	pBG->setAnchorPoint(Point::ZERO);
	mSceneLayer->addChild(pBG);

	/*�������˵���ť*/
	auto back_label = Label::createWithSystemFont(CStringTableMgr::getString("main_menu"), "Arial", 24);
	auto back_labelItem = MenuItemLabel::create(back_label, CC_CALLBACK_1(CMenuSelectHandler::onMenu_Back2Menu, CMenuSelectHandler::sharedHandler()));
	back_labelItem->setPosition(designResolutionSize.width-80,25);

	Menu* menu = Menu::create(back_labelItem, NULL);
	menu->setPosition(Vec2::ZERO);
	mSceneLayer->addChild(menu, 1);
	
	//���Դ���
	pRenderObj = new (CRenderObj)();
	pRenderObj->addPart("root",Point::ZERO);
	pRenderObj->addPart("head", Point(0, 71));

	pRenderObj->setAni(0, "oasis", "root");
	pRenderObj->setAni("head", "oasis", "head");

	mSceneLayer->addChild(pRenderObj->sprite);
	pRenderObj->sprite->setPosition(Point(designResolutionSize.width/2,designResolutionSize.height/2));
	

}

void CPlayScene::onExitScene()
{
	mSceneLayer->removeAllChildrenWithCleanup(true);
}

void CPlayScene::onUpdate(float dt)
{
	pRenderObj->update(dt);
}
