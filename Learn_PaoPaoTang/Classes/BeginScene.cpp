#include"BeginScene.h"
#include"MenuSelectHandler.h"

using namespace std;
USING_NS_CC;

BeginScene::BeginScene()
{

}


void BeginScene::onEnterScene()
{
	Sprite* pBG = Sprite::create("pic/BeginScene.png");
	pBG->setAnchorPoint(Point::ZERO);
	mSceneLayer->addChild(pBG);
	//system("pause");
	// ´´½¨²Ëµ¥
	auto play_label = Label::createWithSystemFont(StringTableMgr::getString("play"), "Arial", 24);
	auto play_labelItem = MenuItemLabel::create(play_label, CC_CALLBACK_1(MenuSelectHandler::onMenu_Play, MenuSelectHandler::sharedHandler()));
	play_labelItem->setPosition(designResolutionSize.width / 2, designResolutionSize.height / 2 );

	auto exit_label = Label::createWithSystemFont(StringTableMgr::getString("exit"), "Arial", 24);
	auto exit_labelItem = MenuItemLabel::create(exit_label, CC_CALLBACK_1(MenuSelectHandler::onMenu_Exit, MenuSelectHandler::sharedHandler()));
	exit_labelItem->setPosition(designResolutionSize.width / 2, designResolutionSize.height / 2-50);

	Menu* menu = Menu::create(play_labelItem, exit_labelItem, NULL);
	menu->setPosition(Vec2::ZERO);
	mSceneLayer->addChild(menu,1);
	
}

void BeginScene::onExitScene()
{
	mSceneLayer->removeAllChildrenWithCleanup(true);
}

