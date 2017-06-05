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

enum ControlType
{
	CT_NONE,
	CT_UP, 
	CT_DOWN,
	CT_LEFT,
	CT_RIGHT,
	CT_PRESS,
	CT_NUM
};

enum PressState
{
	PS_DOWN,
	PS_UP
};

/* 场景转换事件 */
enum SceneSwitchEvent
{
	SSE_Play,
	SSE_Exit,
	SSE_Back2Menu
};

/* 对象类型 */
enum GameObjectType
{
	GOT_Player,   
	GOT_Building, 
	GOT_Bomb,     
	GOT_Item,
	GOT_Num
};

/* 角色逻辑状态 */
enum PlayerLogicState
{
	PLS_STAND,
	PLS_MOVE,
	PLS_WRAPPED,
	PLS_DEAD,
	PLS_NUM
};

#endif // !__BASE_DEF_H__
