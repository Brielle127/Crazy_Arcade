#ifndef _MENU_SELECT_HANDLER_H_
#define _MENU_SELECT_HANDLER_H_

#include"cocos2d.h"
#include"GameLogic.h"

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

	void beginScene_PlayItem(Ref* sender)
	{

	}
};

#endif // !_MENU_SELECT_HANDLER_H_
