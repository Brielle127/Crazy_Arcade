#include"PlayTool.h"
#include"Player.h"

bool PlayTools::IntersectPlayer(Rect player) {
	if (PlayTool->getBoundingBox().intersectsRect(player))
		return true;
	else
		return false;
}

Sprite* PlayTools::GeneratePlayTool(std::string png) {
	
	PlayTool = Sprite::create(png);
	///ToolLayer->addChild(PlayTool);
	PlayTool->setAnchorPoint(Point::ZERO);
	PlayTool->setPosition(Point(300, 250));
	return PlayTool;
}

Vec2* PlayTools::GeneratePosition() {
	//ToolPosition=
	return ToolPosition;
}

Vec2* PlayTools::TurnUp() {
	
	return ToolPosition;
}