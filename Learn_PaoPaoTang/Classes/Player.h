#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "GameObject.h"

#define PART_BODY  "body"
#define PART_EFX "dead"  // 目前只有一种特效：死亡
#define PART_RIDE "ride"

class Player;
typedef void(Player::*Method)();       // Player的无参无返回值成员函数
typedef void(Player::*UpdateMethod)(float); // 更新方法
struct StateMethod  // 状态方法
{
	Method enter;
	Method exit;
	UpdateMethod update;
	void init(Method en, Method ex, UpdateMethod up)
	{
		enter = en;
		exit = ex;
		update = up;
	}
};
class Player:public GameObject
{
	PlayerLogicState mState; // 角色当前状态
	float mSpeed;     // 速度
	int mMaxBombNum;  // 炸弹数量
	int mBombStrength;// 炸弹威力
	bool mIsRiding;   // 是否骑乘
	bool mTransTable[PLS_NUM][PLS_NUM]; // 状态转换表
	StateMethod states[PLS_NUM];
public:
	Player(PlayScene& rScene);

	virtual void load(const char* szName)
	{
		mRenderObj.setAni(PART_BODY, "role1", "walk_up");
	}
	virtual void update(float dt) 
	{
		(this->*states[PLS_STAND].update)(dt); // 调用成员函数
		// ...
		GameObject::update(dt);
	}
private: // 默认方法
	void defaultEnter() {}
	void  defaultExit() {}
	void defaultUpdate(float dt) {}
};


#endif // !_PALYER_H_
