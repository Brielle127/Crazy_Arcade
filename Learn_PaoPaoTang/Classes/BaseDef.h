#ifndef _BASE_DEF_H_
#define _BASE_DEF_H_

static cocos2d::Size designResolutionSize = cocos2d::Size(1200, 900);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

enum EControlType
{
	ECT_NONE,
	ECT_UP, 
	ECT_DOWN,
	ECT_LEFT,
	ECT_RIGHT,
	ECT_PRESS,
	ECT_NUM
};

enum EPressState
{
	EPS_DOWN,
	EPS_UP
};
#endif // !_BASE_DEF_H_
