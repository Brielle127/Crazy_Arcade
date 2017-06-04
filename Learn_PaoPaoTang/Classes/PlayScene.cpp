#include "PlayScene.h"
#include "MenuSelectHandler.h"
#include "Player.h"  
#include "Building.h"
#include "Bomb.h"
#include "Item.h"
USING_NS_CC;

//RenderObj* pRenderObj = nullptr; // 用于测试代码

PlayScene::PlayScene()
	:mGroundLayer(nullptr)
	, mObjectLayer(nullptr)
	, mUILayer(nullptr)
	,mPlayer(*this)
{
	mGroundLayer = Layer::create();
	mGroundLayer->setPosition(Point(20, 40)); // 定位
	mSceneLayer->addChild(mGroundLayer);

	mObjectLayer = Layer::create();
	mObjectLayer->setPosition(Point(20, 40));
	mSceneLayer->addChild(mObjectLayer);

	mUILayer = Layer::create();
	mSceneLayer->addChild(mUILayer);
}

void PlayScene::onEnterScene()
{
	/*处理缩放*/

	Sprite* pBG = Sprite::create("pic/BG.png");	 // 游戏场景背景
	pBG->setAnchorPoint(Point::ZERO);
	pBG->setPosition(Point(-20, -40));
	mGroundLayer->addChild(pBG, 0);

	/*返回主菜单按钮*/
	auto back_label = Label::createWithSystemFont(StringTableMgr::getString("main_menu"), "Arial", 24);
	auto back_labelItem = MenuItemLabel::create(back_label, CC_CALLBACK_1(MenuSelectHandler::onMenu_Back2Menu, MenuSelectHandler::sharedHandler()));
	back_labelItem->setPosition(designResolutionSize.width - 80, 25);

	Menu* menu = Menu::create(back_labelItem, NULL);
	menu->setPosition(Point::ZERO);
	mUILayer->addChild(menu, 1);

	//测试代码
	//pRenderObj = new (RenderObj)();
	//mObjectLayer->addChild(pRenderObj->sprite);

	//pRenderObj->sprite->setPosition(Point(designResolutionSize.width/2,designResolutionSize.height/2));
	setCurrentSceneFile("Scenes/test.xml");
	loadScene();

	mPlayer.load("");
	mPlayer.getSprite()->setPosition(Point::ZERO);
	mObjectLayer->addChild(mPlayer.getSprite());
	
}

void PlayScene::onExitScene()
{
	//mSceneLayer->removeAllChildrenWithCleanup(true);
	mGroundLayer->removeAllChildrenWithCleanup(true);
	
	mObjectLayer->removeAllChildrenWithCleanup(true);
	for (int w = 0; w < GRID_WIDTH; ++w) {
		for (int h = 0; h < GRID_HEIGHT; ++h) {
			auto& rObjects = mMapObject[w][h];
			for (int i = rObjects.size() - 1; i >= 0; --i) {
				auto obj = rObjects[i];
				delete obj;
			}
			rObjects.clear();
		}
	}

	mUILayer->removeAllChildrenWithCleanup(true);
}

void PlayScene::onUpdate(float dt)
{
	//pRenderObj->update(dt);
	for (int w = 0; w < GRID_WIDTH; ++w) {
		for (int h = 0; h < GRID_HEIGHT; ++h) {
			auto& rObjects = mMapObject[w][h];
			for (int i = rObjects.size() - 1; i >= 0; --i) {
				auto obj = rObjects[i];
				mSceneLayer->reorderChild(obj->getSprite(), obj->getDepth());
				obj->update(dt);
			}
		}
	}
	mPlayer.update(dt);
	mSceneLayer->reorderChild(mPlayer.getSprite(), mPlayer.getDepth());

}

void PlayScene::setCurrentSceneFile(const char * szFile)
{
	mCurrentFile = szFile;
}

void PlayScene::loadScene()
{
	TiXmlDocument doc;
	if (doc.LoadFile(mCurrentFile.c_str())) {
		map<size_t, bool> usedMap; // 地图网格被占用情况
		auto root = doc.RootElement();
		auto grounds = root->FirstChildElement();
		auto defaultAni = grounds->Attribute("defaultAni"); // 默认背景
		auto ground = grounds->FirstChildElement();
		while (ground) {
			auto ani = ground->Attribute("ani");
			string tiles = ground->Attribute("tiles");
			auto idx = tiles.find_first_of(',');
			while(idx) {
				string sub = tiles.substr(0, idx);
				int gridIdx = atoi(sub.c_str());
				int gx, gy;
				gx = gridIdx % GRID_WIDTH;
				gy = gridIdx / GRID_WIDTH;
				createGroundTile(ani, gx, gy);
				usedMap[gridIdx] = true;
				tiles = tiles.substr(idx + 1, tiles.length());
				idx= tiles.find_first_of(',');
				if (idx ==size_t(-1)) 
				{
					gridIdx = atoi(tiles.substr(0, idx).c_str());
					gx = gridIdx % GRID_WIDTH;
					gy = gridIdx / GRID_WIDTH;
					createGroundTile(ani, gx, gy);
					usedMap[gridIdx] = true;
					break;
				}
			}
			ground = ground->NextSiblingElement();
		}
			for (size_t i = 0; i < GRID_WIDTH; ++i) {
				for (size_t j = 0; j < GRID_HEIGHT; ++j) {
					auto it = usedMap.find(i + j*GRID_WIDTH);
					if (it == usedMap.end())
						createGroundTile(defaultAni, i, j);
				}
			}
	}

	{
		auto obj = createObject(EGOT_Building);
		obj->getSprite()->setPosition(Point(400, 300));
		(mMapObject[0][0]).push_back(obj);
		mObjectLayer->addChild(obj->getSprite());
	}
	
	{// object initialize
	// 测试代码
		auto obj = createObject(EGOT_Building);
		obj->getSprite()->setPosition(Point(400, 350));
		(mMapObject[0][0]).push_back(obj);
		mObjectLayer->addChild(obj->getSprite());
	}
}

GameObject * PlayScene::createObject(EGameObjectType objType)
{
	GameObject* obj = nullptr;
	switch (objType)
	{
	case EGOT_Player:
		obj = new Player(*this);
		break;
	case EGOT_Building:
		obj = new Building(*this);
		break;
	case EGOT_Bomb:
		obj = new Bomb(*this);
		break;
	case EGOT_Item:
		obj = new Item(*this);
		break;
	default:
		break;
	}
	return obj;
}

void PlayScene::destroy(GameObject* obj)
{
	for (int w = 0; w < GRID_WIDTH; ++w) {
		for (int h = 0; h < GRID_HEIGHT; ++h) {
			auto& rObjects = mMapObject[w][h];
			auto  it = rObjects.begin(), end = rObjects.end();
			for(;it!=end;++it)
				if ((*it) == obj) {
					rObjects.erase(it);
					delete obj;
					return;
				}
			rObjects.clear();
		}
	}

}

inline vector<GameObject*>& PlayScene::getObject(int gridx, int gridy)
{
	return mMapObject[gridx][gridy];
}

Sprite * PlayScene::createGroundTile(const char * ani, size_t gx, size_t gy)
{
	AniData* grdAni = AnimationMgr::getAni("ground", ani);
	auto pGrd = Sprite::create(grdAni->fileName, grdAni->framesData[0]);
	pGrd->setAnchorPoint(Point::ZERO);
	pGrd->setPosition(Point(gx*GRID_SIZE, gy*GRID_SIZE));
	mGroundLayer->addChild(pGrd);
	return pGrd;
}
