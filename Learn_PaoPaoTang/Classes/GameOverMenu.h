#ifndef _GAME_OVER_MENU_H_
#define _GAME_OVER_MENU_H_

#include "cocos2d.h"
USING_NS_CC;
#include "MenuSelectHandler.h"

class GameOverMenu :public Layer
{
public:
	GameOverMenu() 
	{
		auto replay_label = Label::createWithSystemFont(StringTableMgr::getString("replay"), "Arial", 24);
		auto replay_labelItem = MenuItemLabel::create(replay_label, CC_CALLBACK_1(MenuSelectHandler::onMenu_Replay, MenuSelectHandler::sharedHandler()));
		replay_labelItem->setPositionY(100);

		auto back2menu_label = Label::createWithSystemFont(StringTableMgr::getString("back2menu"), "Arial", 24);
		auto back2menu_labelItem = MenuItemLabel::create(back2menu_label, CC_CALLBACK_1(MenuSelectHandler::onMenu_Back2Menu, MenuSelectHandler::sharedHandler()));

		auto exit_label = Label::createWithSystemFont(StringTableMgr::getString("exit"), "Arial", 24);
		auto exit_labelItem = MenuItemLabel::create(exit_label, CC_CALLBACK_1(MenuSelectHandler::onMenu_Exit, MenuSelectHandler::sharedHandler()));
		exit_labelItem->setPositionY(-100);

		Menu* menu = Menu::create(replay_labelItem, back2menu_labelItem,exit_labelItem, NULL);
		menu->setPosition(Point::ZERO);
		this->addChild(menu, 1);
	}
};

#endif