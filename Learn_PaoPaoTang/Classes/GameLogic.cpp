#include "GameLogic.h"

USING_NS_CC;


GameLogic::GameLogic()
	:mSceneRoot(nullptr),mBeginScene(nullptr)
{

}

GameLogic::~GameLogic() 
{

}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void GameLogic::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool GameLogic::applicationDidFinishLaunching() {
    // initialize director
    auto pDirector = Director::getInstance();
    auto glview = pDirector->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Learn_PaoPaoTang", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Learn_PaoPaoTang");
#endif
        pDirector->setOpenGLView(glview);
    }

	//
	pDirector->getScheduler()->scheduleUpdate(this, 0,	false);

	// 创建场景
	mSceneRoot = Scene::create();
	mBeginScene = new (CBeginScene)();
	mPlayScene = new (CPlayScene)();

	mSceneRoot->addChild(mBeginScene->getSceneLayer());
	mCurrentScene = mBeginScene;
	mCurrentScene->onEnterScene();
    
	// run
    pDirector->runWithScene(mSceneRoot);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void GameLogic::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void GameLogic::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void GameLogic::handleEvent(int eventType, void * data)
{
	// 过滤事件
	switch (eventType)
	{
	case ESSE_Play:
	{
		mCurrentScene->onExitScene(); // 退出当前场景
		mSceneRoot->removeChild(mCurrentScene->getSceneLayer(), false);
		
		mCurrentScene = mPlayScene;  //当前场景转化为下一场景
		mSceneRoot->addChild(mCurrentScene->getSceneLayer());
		mCurrentScene->onEnterScene();
		return;
	}
	case ESSE_Exit:
		{
			mCurrentScene->onExitScene();// 释放当前场景
			mCurrentScene = nullptr;
			Director::getInstance()->end();
			
			delete mBeginScene;
			mBeginScene = nullptr;
			delete mPlayScene;
			mPlayScene = nullptr;

			return;// 结束处理
		}
	
	case ESSE_Back2Menu: /* 返回开始菜单 */
		{
			mCurrentScene->onExitScene(); // 退出当前场景
			mSceneRoot->removeChild(mCurrentScene->getSceneLayer(), false);
			
			mCurrentScene = mBeginScene;  //当前场景转化为开始场景
			mSceneRoot->addChild(mCurrentScene->getSceneLayer());
			mCurrentScene->onEnterScene();
			return;
		}
	
	}
	mCurrentScene->onHandleEvent(eventType,data);
}

GameLogic & GameLogic::sharedGameLogic()
{
	return ((GameLogic&)*Application::getInstance());
}

void GameLogic::update(float dt)
{
	// to do

	// ...
	if (mCurrentScene)// 当前场景存在
		mCurrentScene->onUpdate(dt);
}

