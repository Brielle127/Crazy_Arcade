///////////////////////////////////////////////////////////////////////////////
/// \file Buff.h
/// \brief ʵ��Buff��
/// 
/// 
///
/// \author ������
///////////////////////////////////////////////////////////////////////////////

#ifndef _BUFF_H_
#define _BUFF_H_

class Buff {
public:
	class Player* mPlayer;
	//virtual int getType() = 0; // buff����
	virtual void update(float dt) = 0;
	virtual void attach(class Player* pT) = 0;  // ���ӵ��������
	virtual void remove() = 0;
	virtual void compute() = 0;
};

class AtrributeBuff :public Buff {
public:
	class Player* mTarget;
	// Ӱ����������
	int popoNum;
	int popoStr;
	int roleSpeed;
	bool canKick;
	bool ignoreItem;   // ���Ե���
	bool ignoreStatic; // �����赲��
	//virtual int getType();
	virtual void update(float dt);
	virtual void attach(class Player* pT);
	virtual void remove();
	virtual void compute();
};
#endif // !_BUFF_H_
