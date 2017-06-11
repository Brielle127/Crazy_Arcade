#include "GameLogic.h"

USING_NS_CC;
GameLogic::GameLogic()
	:mSceneRoot(nullptr),mBeginScene(nullptr)
{

}

GameLogic::~GameLogic() 
{

}

bool GameLogic::applicationDidFinishLaunching() {
	srand(time(nullptr));
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

	// ��������
	mSceneRoot = Scene::create();
	mBeginScene = new (BeginScene)();
	mPlayScene = new (PlayScene)();

	mSceneRoot->addChild(mBeginScene->getSceneLayer());
	mCurrentScene = mBeginScene;
	mCurrentScene->onEnterScene();
    
	// run
    pDirector->runWithScene(mSceneRoot);

    return true;
}


void GameLogic::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

}


void GameLogic::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

}



// ��������

void GameLogic::handleInput(ControlType ectType, PressState epState)
{
	mCurrentScene->handleInput(ectType, epState);
}

void GameLogic::handleEvent(int eventType, void * data)
{
	// �����¼�
	switch (eventType)
	{
	case SSE_Play:
	{
		mCurrentScene->onExitScene(); // �˳���ǰ����
		mSceneRoot->removeChild(mCurrentScene->getSceneLayer(), false);
		
		mCurrentScene = mPlayScene;  //��ǰ����ת��Ϊ��һ����
		mSceneRoot->addChild(mCurrentScene->getSceneLayer());
		mCurrentScene->onEnterScene();
		return;
	}
	case SSE_Exit:
		{
			mCurrentScene->onExitScene();// �ͷŵ�ǰ����
			mCurrentScene = nullptr;
			Director::getInstance()->end();
			
			delete mBeginScene;
			mBeginScene = nullptr;
			delete mPlayScene;
			mPlayScene = nullptr;

			return;// ��������
		}
	
	case SSE_Back2Menu: /* ���ؿ�ʼ�˵� */
		{
			mCurrentScene->onExitScene(); // �˳���ǰ����
			mSceneRoot->removeChild(mCurrentScene->getSceneLayer(), false);
			
			mCurrentScene = mBeginScene;  //��ǰ����ת��Ϊ��ʼ����
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

//typedef EventKeyboard::KeyCode KC;
void GameLogic::update(float dt)
{
	//log("GameLogic::update");
	
	// to do
	
	if (mCurrentScene)// ��ǰ��������
		mCurrentScene->onUpdate(dt);
}

