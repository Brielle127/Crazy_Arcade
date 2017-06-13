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

enum RolePropValue
{   // ��������
	//RPV_MIN_POPO_NUM=3,   
	PRV_NORMAL_POPO_NUM=3,
	//RPV_MAX_POPO_NUM=10,

	//RPV_MIN_POPO_STR=3,
	RPV_NORMAL_POPO_STR=3,
	//RPV_MAX_POPO_STR=10,

	//RPV_MIN_SPEED=50,
	RPV_NORMAL_SPEED=100,
	//RPV_MAX_SPEED=200,
};
//// ��������
//enum ItemType 
//{
//	IT_POPO,			 // ˮ�ݣ���������ը������
//	IT_STRENGTH_WATER,   // ����ˮ������ը������
//	IT_ROLLER_SKATES,    // ����Ь����ɫ���ƶ��ٶȼӿ�
//	IT_SPORTS_SHOE,       // �˶�Ь��������ը��
//	IT_RED_EVIL,         // ��ħ��ʹ����ﵽ�����ٶȣ����ҿ�������ը��
//	IT_RIDE,             // ����
//	EI_NUM
//};

//// ����Ӱ����������
//enum ItemPropType
//{
//	IPT_POPO_NUM,//��������
//	IPT_POPO_STR,
//	IPT_PLAYER_SPEED,
//	IPT_KICK_POPO, // ��ը��
//	IPT_NUM
//};
#endif 
