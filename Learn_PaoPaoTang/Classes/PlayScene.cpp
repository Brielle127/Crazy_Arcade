#include "PlayScene.h"
#include "MenuSelectHandler.h"

USING_NS_CC;

CRenderObj* pRenderObj = nullptr; // 用于测试代码

CPlayScene::CPlayScene()
	:mGroundLayer(nullptr)
	, mObjectLayer(nullptr)
	, mUILayer(nullptr)
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
void CPlayScene::onEnterScene()
{
	/*处理缩放*/

	Sprite* pBG = Sprite::create("pic/BG.png");	 // 游戏场景背景
	pBG->setAnchorPoint(Point::ZERO);
	pBG->setPosition(Point(-20, -40));
	mGroundLayer->addChild(pBG,0);

	/*返回主菜单按钮*/
	auto back_label = Label::createWithSystemFont(CStringTableMgr::getString("main_menu"), "Arial", 24);
	auto back_labelItem = MenuItemLabel::create(back_label, CC_CALLBACK_1(CMenuSelectHandler::onMenu_Back2Menu, CMenuSelectHandler::sharedHandler()));
	back_labelItem->setPosition(designResolutionSize.width-80,25);

	Menu* menu = Menu::create(back_labelItem, NULL);
	menu->setPosition(Point::ZERO);
	mUILayer->addChild(menu, 1);
	
	//测试代码
	pRenderObj = new (CRenderObj)();
	pRenderObj->addPart("root",Point::ZERO);
	pRenderObj->addPart("head", Point(0, 71));

	pRenderObj->setAni(0, "oasis", "root");
	pRenderObj->setAni("head", "oasis", "head");

	mObjectLayer->addChild(pRenderObj->sprite);
	pRenderObj->sprite->setPosition(Point(designResolutionSize.width/2,designResolutionSize.height/2));
	setCurrentSceneFile("Scenes/test.xml");
	loadScene();
}

void CPlayScene::onExitScene()
{
	//mSceneLayer->removeAllChildrenWithCleanup(true);
	mGroundLayer->removeAllChildrenWithCleanup(true);
	mObjectLayer->removeAllChildrenWithCleanup(true);
	mUILayer->removeAllChildrenWithCleanup(true);
}

void CPlayScene::onUpdate(float dt)
{
	pRenderObj->update(dt);
}

void CPlayScene::setCurrentSceneFile(const char * szFile)
{
	mCurrentFile = szFile;
}

void CPlayScene::loadScene()
{
	TiXmlDocument doc;
	if (doc.LoadFile(mCurrentFile.c_str())) {
		map<size_t, bool> usedMap; // 记录地图网格被占用情况
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

}

Sprite * CPlayScene::createGroundTile(const char * ani, size_t gx, size_t gy)
{
	CAniData* grdAni = CAnimationMgr::getAni("ground", ani);
	auto pGrd = Sprite::create(grdAni->fileName, grdAni->framesData[0]);
	pGrd->setAnchorPoint(Point::ZERO);
	pGrd->setPosition(Point(gx*GRID_SIZE, gy*GRID_SIZE));
	mGroundLayer->addChild(pGrd);
	return pGrd;
}
