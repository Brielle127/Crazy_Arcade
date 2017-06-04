#ifndef __BASE_DEF_H__
#define __BASE_DEF_H__

/* 窗口大小 */
static cocos2d::Size designResolutionSize = cocos2d::Size(800, 600);
/*
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);
*/

/* 网格规模 */
#define GRID_WIDTH 15
#define GRID_HEIGHT 13
#define GRID_SIZE 40

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

enum ESceneSwitchEvent
{
	ESSE_Play,
	ESSE_Exit,
	ESSE_Back2Menu
};

/* 对象类型 */
enum EGameObjectType
{
	EGOT_Player,   
	EGOT_Building, 
	EGOT_Bomb,     
	EGOT_Item,
	EGOT_Num
};

/* 角色逻辑状态 */
enum EPlayerLogicState
{
	EPLS_STAND,
	EPLS_MOVE,
	EPLS_WRAPPED,
	EPLS_DEAD,
	EPLS_NUM
};

enum EPlayerMoveState
{
	EPMS_UP,
	EPMS_DOWN,
	EPMS_LEFT,
	EPMS_RIGHT
};
#endif // !__BASE_DEF_H__
