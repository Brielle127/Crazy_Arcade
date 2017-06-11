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

#define ORIGIN_PLAYER_BOMB_NUM 3  // 默认初始炸弹数
#define ORIGIN_PLAYER_BOMB_STRENGTH 3 // 初始炸弹威力
#define ORIGIN_PLAYER_BOMB_SPEED 100  // 初始速度
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
	PLS_NONE,
	PLS_STAND,
	PLS_MOVE,
	PLS_WRAPPED,
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
enum PlayerMoveState
{
	PMS_UP,
	PMS_DOWN,
	PMS_LEFT,
	PMS_RIGHT
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

//// 道具种类
//enum ItemType 
//{
//	IT_POPO,			 // 水泡：可以增加炸弹数量
//	IT_STRENGTH_WATER,   // 力量水：增加炸弹威力
//	IT_ROLLER_SKATES,    // 旱冰鞋：角色的移动速度加快
//	IT_SPORTS_SHOE,       // 运动鞋：可以踢炸弹
//	IT_RED_EVIL,         // 红魔：使人物达到最快的速度，并且可以踢走炸弹
//	IT_RIDE,             // 坐骑
//	EI_NUM
//};
enum ItemType
{
	IT_NORMAL,
	IT_RIDE,
	IT_NUM
};

//// 道具影响的玩家属性
//enum ItemPropType
//{
//	IPT_POPO_NUM,//泡泡数量
//	IPT_POPO_STR,
//	IPT_PLAYER_SPEED,
//	IPT_KICK_POPO, // 踢炸弹
//	IPT_NUM
//};
#endif // !__BASE_DEF_H__
