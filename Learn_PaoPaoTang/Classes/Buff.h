#ifndef _BUFF_H_
#define _BUFF_H_

class Buff {
public:
	class Player* mPlayer;
	//virtual int getType() = 0; // buff类型
	virtual void update(float dt) = 0;
	virtual void attach(class Player* pT) = 0;  // 附加到玩家身上
	virtual void remove() = 0;
};

class AtrributeBuff :public Buff {
public:
	class Player* mTarget;
	// 影响的玩家属性
	int popoNum;
	int popoStr;
	int roleSpeed;
	bool canKick;
	bool ignoreItem;   // 忽略道具
	bool ignoreStatic; // 忽略阻挡物
	//virtual int getType();
	virtual void update(float dt);
	virtual void attach(class Player* pT);
	virtual void remove();
private:
	void compute();
};
#endif // !_BUFF_H_
