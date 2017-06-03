#include"BeginScene.h"
#include"MenuSelectHandler.h"

using namespace std;
USING_NS_CC;

CBeginScene::CBeginScene()
{

}


void CBeginScene::onEnterScene()
{
	Sprite* pBG = Sprite::create("pic/BeginScene.png");
	pBG->setAnchorPoint(Point::ZERO);
	mSceneLayer->addChild(pBG);

	// ´´½¨²Ëµ¥
	auto play_label = Label::createWithSystemFont(CStringTableMgr::getString("play"), "Arial", 24);
	auto play_labelItem = MenuItemLabel::create(play_label, CC_CALLBACK_1(CMenuSelectHandler::onMenu_Play, CMenuSelectHandler::sharedHandler()));
	play_labelItem->setPosition(designResolutionSize.width / 2, designResolutionSize.height / 2 );

	auto exit_label = Label::createWithSystemFont(CStringTableMgr::getString("exit"), "Arial", 24);
	auto exit_labelItem = MenuItemLabel::create(exit_label, CC_CALLBACK_1(CMenuSelectHandler::onMenu_Exit, CMenuSelectHandler::sharedHandler()));
	exit_labelItem->setPosition(designResolutionSize.width / 2, designResolutionSize.height / 2-50);

	Menu* menu = Menu::create(play_labelItem, exit_labelItem, NULL);
	menu->setPosition(Vec2::ZERO);
	mSceneLayer->addChild(menu,1);
	
}

void CBeginScene::onExitScene()
{
	mSceneLayer->removeAllChildrenWithCleanup(true);
}

