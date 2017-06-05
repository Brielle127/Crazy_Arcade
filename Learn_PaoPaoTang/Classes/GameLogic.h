#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "BaseDef.h"
#include "Player.h"
#include "BeginScene.h"
#include "PlayScene.h"


USING_NS_CC;

class  GameLogic : private Application,private Scheduler
{
public:
    GameLogic();
    virtual ~GameLogic();

    virtual bool applicationDidFinishLaunching();

    virtual void applicationDidEnterBackground();

    virtual void applicationWillEnterForeground();
	
	// 处理输入
	void handleInput(ControlType ectType, PressState epState);

	void handleEvent(int eventType, void *data=nullptr);

	static GameLogic& sharedGameLogic();

	// 主循环
	virtual void update(float dt);
private:
	Scene* mSceneRoot;
	class BeginScene*  mBeginScene;
	class PlayScene* mPlayScene;
	class BaseScene* mCurrentScene;
};

#endif // _APP_DELEGATE_H_

