#ifndef _MENU_SELECT_HANDLER_H_
#define _MENU_SELECT_HANDLER_H_

#include"cocos2d.h"
#include"GameLogic.h"
#include"BaseDef.h"

USING_NS_CC;

class MenuSelectHandler :public Ref
{
private:
	MenuSelectHandler(){}
public:
	static MenuSelectHandler* sharedHandler()
	{
		static MenuSelectHandler* instance=NULL;
		if (instance == NULL)
			instance = new (MenuSelectHandler)();
		return instance;
	}

	/*
	void beginScene_PlayItem(Ref* sender)
	{
		GameLogic::sharedGameLogic().handleEvent(ESSE_Play);// ���Դ��� 
	}
	*/

	/* ����˵��¼� */
	void onMenu_Play(Ref* pSeder)
	{
		GameLogic::sharedGameLogic().handleEvent(ESSE_Play);
	}

	void onMenu_Exit(Ref* pSender)
	{
		GameLogic::sharedGameLogic().handleEvent(ESSE_Exit);
	}

	void onMenu_Back2Menu(Ref* pSender)
	{
		GameLogic::sharedGameLogic().handleEvent(ESSE_Back2Menu);
	}
};

#endif // !_MENU_SELECT_HANDLER_H_
