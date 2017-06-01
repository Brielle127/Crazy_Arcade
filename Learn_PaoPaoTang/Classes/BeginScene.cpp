#include"BeginScene.h"
#include"BaseDef.h"
#include"MenuSelectHandler.h"
#include"GameUtils.h"
#include"tinyxml.h"

#include<xstring>
using namespace std;
USING_NS_CC;

CBeginScene::CBeginScene()
{

}


void CBeginScene::onEnterScene()
{
	// 创建菜单
	auto image = MenuItemImage::create(
		"play.png","CloseNormal.png", CC_CALLBACK_1(CMenuSelectHandler::beginScene_PlayItem, CMenuSelectHandler::sharedHandler()));
	image->setPosition(designResolutionSize.width / 2, designResolutionSize.height / 2);
	wstring exit = L"退出游戏";
	string exit2; 
	GameUtils::WStrToUTF8(exit2, exit);
	auto label = Label::create(exit2, "Arial", 24);
	auto labelItem = MenuItemLabel::create(label);
	labelItem->setPosition(designResolutionSize.width / 2, designResolutionSize.height / 2-140);

	Menu* menu = Menu::create(image, labelItem, NULL);
	menu->setPosition(Vec2::ZERO);
	mSceneLayer->addChild(menu,1);
	
}

