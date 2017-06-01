#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "BeginScene.h"
#include "PlayScene.h"
#include "EndScene.h"
#include "BaseDef.h"

USING_NS_CC;

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  GameLogic : private cocos2d::Application
{
public:
    GameLogic();
    virtual ~GameLogic();

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
	// ¥¶¿Ì ‰»Î
	void handleInput(EControlType ectType, EPressState epState)
	{

	}


	void handleEvent(int eventType, void *data);

	static GameLogic& sharedGameLogic()
	{
		return ((GameLogic&)*CCApplication::getInstance());
	}
private:
	Scene* mSceneRoot;
	class CBeginScene*  mBeginScene;
	class CPlayScene* mPlayeScene;
	class CEndScene* mEndScene;
	class CBaseScene* mCurrentScene;
};

#endif // _APP_DELEGATE_H_

