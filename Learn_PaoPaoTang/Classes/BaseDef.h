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
	GOT_Num
};

/* ��ɫ�߼�״̬ */
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
	PI_NONE,    // �Ƿ���������
	PI_STOP,
	PI_MOVE,
//	PI_ATTACKED,// �ܵ�����
	PI_KILL,     // ը����ը
	PI_NUM
};

/* ��ɫ�ƶ����� */
enum PlayerMoveState
{
	PMS_UP,
	PMS_DOWN,
	PMS_LEFT,
	PMS_RIGHT
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

#endif // !__BASE_DEF_H__
