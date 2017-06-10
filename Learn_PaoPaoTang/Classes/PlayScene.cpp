#include "PlayScene.h"
#include "MenuSelectHandler.h"
#include "Player.h"  
#include "Building.h"
#include "Bomb.h"
#include "Item.h"
USING_NS_CC;

ControlType getControllType(EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
		return CT_UP;
	case  EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
		return CT_LEFT;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
		return CT_DOWN;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
		return CT_RIGHT;
	case EventKeyboard::KeyCode::KEY_SPACE:
		return CT_PRESS;
	}
	return CT_NONE;
}

bool isValidCT(ControlType ectType)
{
	switch (ectType)
	{
	case CT_UP:
	case CT_DOWN:
	case CT_LEFT:
	case CT_RIGHT:
	//case CT_PRESS:
		return true;
	}
	return false;
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


	setCurrentSceneFile("Scenes/test.xml");
	loadScene();
	
	// 注册键盘监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
			
		if (isValidCT(getControllType(keyCode))) {
			keys[keyCode] = true;
			ectTypes.push_back(getControllType(keyCode));

		}
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
			mPlayer.handleInput(CT_PRESS, PS_UP);
		else if (isValidCT(getControllType(keyCode))) {
			keys[keyCode] = false;
			for (auto i = ectTypes.begin() + ectTypes.size() - 1; i != ectTypes.begin(); --i)
				if (*i == getControllType(keyCode))
				{
					ectTypes.erase(i);
					break;
				}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, mObjectLayer);

	mPlayer.load("");
	mPlayer.setPosition(Point(100,100));
	mObjectLayer->addChild(mPlayer.getSprite());
	
}

void PlayScene::onExitScene()
{
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
	for (int w = 0; w < GRID_WIDTH; ++w) {
		for (int h = 0; h < GRID_HEIGHT; ++h) {
			auto& rObjects = mMapObject[w][h];
			for (int i = rObjects.size() - 1; i >= 0; --i) {
				auto obj = rObjects[i];
				if (obj->isNeedDestroy()) {
					destroy(obj);
				}
				else {
					obj->update(dt);
					mObjectLayer->reorderChild(obj->getSprite(), obj->getDepth());
				}
			}
		}
	}
	mObjectLayer->reorderChild(mPlayer.getSprite(), mPlayer.getDepth());
	mPlayer.update(dt);
	typedef EventKeyboard::KeyCode KC;
	if (ectTypes.empty())
	{
		mPlayer.handleInput(CT_NONE, PS_DOWN);
		mPlayer.handleInput(CT_NONE, PS_UP);
	}

	else
		switch (ectTypes.back())
		{
		case CT_UP:
			if (keys[KC::KEY_W] || keys[KC::KEY_CAPITAL_W])
				mPlayer.handleInput(CT_UP, PS_DOWN);
			else
				mPlayer.handleInput(CT_UP, PS_UP);
			break;
		case CT_DOWN:
			if (keys[KC::KEY_S] || keys[KC::KEY_CAPITAL_S])
				mPlayer.handleInput(CT_DOWN, PS_DOWN);
			else
				mPlayer.handleInput(CT_DOWN, PS_UP);
			break;
		case CT_LEFT:
			if (keys[KC::KEY_A] || keys[KC::KEY_CAPITAL_A])
				mPlayer.handleInput(CT_LEFT, PS_DOWN);
			else
				mPlayer.handleInput(CT_LEFT, PS_UP);
			break; 
		case CT_RIGHT:
			if (keys[KC::KEY_D] || keys[KC::KEY_CAPITAL_D])
				mPlayer.handleInput(CT_RIGHT, PS_DOWN);
			else
				mPlayer.handleInput(CT_RIGHT, PS_UP);
			break;
		default:
			mPlayer.handleInput(CT_NONE, PS_DOWN);
			mPlayer.handleInput(CT_NONE, PS_UP);
			break;
		}
}


void PlayScene::setCurrentSceneFile(const char * szFile)
{
	mCurrentFile = szFile;
}

// 加载场景
void PlayScene::loadScene()
{
	TiXmlDocument doc;
	if (doc.LoadFile(mCurrentFile.c_str())) {
		map<size_t, bool> usedMap; // 地图网格被占用情况
		auto root = doc.RootElement();
		auto grounds = root->FirstChildElement();
		auto defaultAni = grounds->Attribute("defaultAni"); // 默认背景

		// 加载背景
		auto ground = grounds->FirstChildElement();
		while (ground) {
			auto ani = ground->Attribute("ani");
			string tiles = ground->Attribute("tiles");
			auto idx = tiles.find_first_of(',');
			while (idx) {
				string sub = tiles.substr(0, idx);
				int gridIdx = atoi(sub.c_str());
				int gx, gy;
				gx = gridIdx % GRID_WIDTH;
				gy = gridIdx / GRID_WIDTH;
				createGroundTile(ani, gx, gy);
				usedMap[gridIdx] = true;
				tiles = tiles.substr(idx + 1, tiles.length());
				idx = tiles.find_first_of(',');
				if (idx == size_t(-1))
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

		// 加载building
		auto buildings = grounds->NextSiblingElement();
		if (buildings) {
			auto building = buildings->FirstChildElement();
			while (building) {
				int gridx = atoi(building->Attribute("gridX"));
				int gridy = atoi(building->Attribute("gridY"));
				auto name = building->Attribute("name");

				// 创建building对象
				auto obj = (Building*)createObject(GOT_Building);
				obj->load(name);
				obj->setPosition(Point(gridx*GRID_SIZE, gridy*GRID_SIZE));
				obj->setGrid(gridx, gridy);
				obj->init();
				(mMapObject[gridx][gridy]).push_back(obj);
				mObjectLayer->addChild(obj->getSprite());

				// 下一节点
				building = building->NextSiblingElement();
			}
		}
	}

}

GameObject * PlayScene::createObject(GameObjectType objType)
{
	GameObject* obj = nullptr;
	switch (objType)
	{
	case GOT_Player:
		obj = new Player(*this);
		break;
	case GOT_Building:
		obj = new Building(*this);
		break;
	case GOT_Bomb:
		obj = new Bomb(*this);
		break;
	case GOT_Item:
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
			for(auto  it = rObjects.begin();it!=rObjects.end();++it)
				if ((*it) == obj) {
					obj->getSprite()->removeAllChildrenWithCleanup(true);
					delete obj;
					rObjects.erase(it);
					return;
				}
		}
	}

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
