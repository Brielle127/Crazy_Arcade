///////////////////////////
///\file Head file for BaseDef.h
/// \brief 对象状态
///
/// \author 蓝楚迪
////////////////////////



#ifndef __BASE_DEF_H__
#define __BASE_DEF_H__

///窗口大小 
static cocos2d::Size designResolutionSize = cocos2d::Size(800, 600);
/*
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);
*/

/// 网格规模 
#define GRID_WIDTH 15
#define GRID_HEIGHT 13
#define GRID_SIZE 40

///\brief 按键方向类型
enum ControlType
{
	CT_NONE,   ///<enum value 无操作
	CT_UP,     ///<enum value 向上
	CT_DOWN,    ///<enum value 向下
	CT_LEFT,    ///<enum value 向左
	CT_RIGHT,    ///<enum value 向右
	CT_PRESS,    ///<enum value 按空格
	CT_NUM      ///<enum value     
};

 ///\brief 空格状态
enum PressState
{
	PS_DOWN,   ///<enum value 按下空格
	PS_UP        ///<enum value 空格回弹
};

///\brief 场景转换事件
enum SceneSwitchEvent
{
	SSE_Play,   ///<enum value 开始游戏
	SSE_Exit,    ///<enum value 结束游戏
	SSE_Back2Menu   ///<enum value 返回主菜单
};

///\brief 对象类型 
enum GameObjectType
{
	GOT_Player,    ///<enum value 角色
	GOT_Building,    ///<enum value 障碍物
	GOT_Bomb,     ///<enum value 泡泡
	GOT_Item,     ///<enum value 道具
	GOT_Num
};

///\brief角色逻辑状态 
enum PlayerLogicState
{
	PLS_NONE,   ///<enum value 无操作
	PLS_STAND,   ///<enum value 静止
	PLS_MOVE,     ///<enum value 移动
	PLS_WRAPPED,   ///<enum value 被泡泡包围
	PLS_DEAD,      ///<enum value 死亡
	PLS_NUM   
};

enum EPlayerMoveState
{
	EPMS_UP,        ///<enum value 向上
	EPMS_DOWN,      ///<enum value 向下
	EPMS_LEFT,      ///<enum value 向左
	EPMS_RIGHT      ///<enum value 向右
};

enum PlayerInput
{
	PI_NONE,    ///<enum value 非法动作请求
	PI_STOP,
	PI_MOVE,
//	PI_ATTACKED,///<enum value 受到攻击
	PI_KILL,     ///<enum value 炸弹爆炸
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
#endif // !__BASE_DEF_H__
