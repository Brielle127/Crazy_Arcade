#ifndef __BASE_DEF_H__
#define __BASE_DEF_H__

/* ���ڴ�С */
static cocos2d::Size designResolutionSize = cocos2d::Size(800, 600);
/*
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);
*/

/* �����ģ */
#define GRID_WIDTH 15
#define GRID_HEIGHT 13
#define GRID_SIZE 40

/* ���̲������� */
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

/* ����ת���¼� */
enum SceneSwitchEvent
{
	SSE_Play,
	SSE_Replay,
	SSE_Exit,
	SSE_Back2Menu
};

/* �������� */
enum GameObjectType
{
	GOT_Player,   
	GOT_Building, 
	GOT_Bomb,     
	GOT_Item,
	GOT_AI, // AI
	GOT_Num
};

/* ��ɫ�߼�״̬ */
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
	PI_NONE,    // �Ƿ���������
	PI_STOP,
	PI_MOVE,
//	PI_ATTACKED,// �ܵ�����
	PI_KILL,     // ը����ը
	PI_NUM
};

/* ��ɫ�ƶ����� */
enum PlayerDirection
{
	PD_UP,
	PD_DOWN,
	PD_LEFT,
	PD_RIGHT
};

/*ը��״̬*/
enum BombState
{
	BS_IDLE,// ����״̬
	BS_EXPLODE // ��ը״̬
};

// �߼���������
enum OrderType {
	OT_SET_BOMB,// ����ը��

};

enum ItemType
{
	IT_NORMAL,
	IT_RIDE,
	IT_NUM
};

/*�������*/
enum RolePropValue
{   
	RPV_NORMAL_POPO_NUM = 3,
	RPV_NORMAL_POPO_STR = 3,
	RPV_NORMAL_SPEED = 100,
	RPV_DEAD_TIME = 5, // �������ʱ��  
};

#endif 
