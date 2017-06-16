#include"BeginScene.h"
#include"MenuSelectHandler.h"
#include"GameConfig.h"
#include "SoundMgr.h"
#include"cocos2d.h"
USING_NS_CC;

void BeginScene::onEnterScene()
{
	auto pPic = GameConfig::getInfo("begin_scene_bg_pic");
	Sprite* pBG = Sprite::create(pPic);
	pBG->setAnchorPoint(Point::ZERO);
	mSceneLayer->addChild(pBG);

	///创建开始和结束标签
	auto play_label = Label::createWithSystemFont(StringTableMgr::getString("play"), "Arial", 24);
	auto play_labelItem = MenuItemLabel::create(play_label, CC_CALLBACK_1(MenuSelectHandler::onMenu_Play, MenuSelectHandler::sharedHandler()));
	play_labelItem->setPosition(designResolutionSize.width / 2, designResolutionSize.height / 2 );

	auto exit_label = Label::createWithSystemFont(StringTableMgr::getString("exit"), "Arial", 24);
	auto exit_labelItem = MenuItemLabel::create(exit_label, CC_CALLBACK_1(MenuSelectHandler::onMenu_Exit, MenuSelectHandler::sharedHandler()));
	exit_labelItem->setPosition(designResolutionSize.width / 2, designResolutionSize.height / 2-50);

	Menu* menu = Menu::create(play_labelItem, exit_labelItem, NULL);
	menu->setPosition(Vec2::ZERO);
	mSceneLayer->addChild(menu,1);
	 ///设置音效
	SoundMgr::playBackgroundMusic("begin_scene_bg_music",true);
}

void BeginScene::onExitScene()
{
	mSceneLayer->removeAllChildrenWithCleanup(true);
}

