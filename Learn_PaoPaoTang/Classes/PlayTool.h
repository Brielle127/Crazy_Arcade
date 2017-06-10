#include"cocos2d.h"
#include<string>
#include"Player.h"

USING_NS_CC;

class PlayTools {

	Sprite* PlayTool;
	Vec2* ToolPosition;
	//static Layer* ToolLayer;
public:
	//PlayTools();
	Vec2* GeneratePosition();
	//static Layer* getToolLayer() { return ToolLayer; };
	Sprite* GeneratePlayTool(std::string png);
	Sprite* gettool() { return PlayTool; };
	//virtual Vec2 TurnUp();
	Vec2* TurnUp();
	bool IntersectPlayer(Rect player);
};

class ToolShoe:public PlayTools
{
public:

private:
	//virtual Vec2 TurnUp();
};

