#ifndef _MENU_SELECT_HANDLER_H_
#define _MENU_SELECT_HANDLER_H_

#include"cocos2d.h"
#include"GameLogic.h"
#include"BaseDef.h"

USING_NS_CC;

class CMenuSelectHandler :public Ref
{
private:
	CMenuSelectHandler(){}
public:
	static CMenuSelectHandler* sharedHandler()
	{
		static CMenuSelectHandler* instance=NULL;
		if (instance == NULL)
			instance = new (CMenuSelectHandler)();
		return instance;
	}

	/*
	void beginScene_PlayItem(Ref* sender)
	{
		GameLogic::sharedGameLogic().handleEvent(ESSE_Play);// 测试代码 
	}
	*/

	/* 处理菜单事件 */
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
