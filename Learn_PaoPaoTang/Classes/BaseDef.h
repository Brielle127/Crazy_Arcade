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

/* 键盘操作类型 */
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
	PS_NONE,
	PS_DOWN,
	PS_UP
};

/* 场景转换事件 */
enum SceneSwitchEvent
{
	SSE_Play,
	SSE_Replay,
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
	GOT_AI, // AI
	GOT_Num
};

/* 角色逻辑状态 */
enum PlayerLogicState
{
	PLS_NONE,
	PLS_STAND,
	PLS_MOVE,
	PLS_SURROUNDED,
	PLS_DEAD,
	PLS_NUM
};

enum PlayerInput
{
	PI_NONE,    // 非法动作请求
	PI_STOP,
	PI_MOVE,
//	PI_ATTACKED,// 受到攻击
	PI_KILL,     // 炸弹爆炸
	PI_NUM
};

/* 角色移动方向 */
enum PlayerDirection
{
	PD_UP,
	PD_DOWN,
	PD_LEFT,
	PD_RIGHT
};

/*炸弹状态*/
enum BombState
{
	BS_IDLE,// 读秒状态
	BS_EXPLODE // 爆炸状态
};

// 逻辑命令输入
enum OrderType {
	OT_SET_BOMB,// 放置炸弹

};

enum ItemType
{
	IT_NORMAL,
	IT_RIDE,
	IT_NUM
};

/*玩家属性*/
enum RolePropValue
{   
	RPV_NORMAL_POPO_NUM = 3,
	RPV_NORMAL_POPO_STR = 3,
	RPV_NORMAL_SPEED = 100,
	RPV_DEAD_TIME = 5, // 玩家死亡时间  
};

#endif 
