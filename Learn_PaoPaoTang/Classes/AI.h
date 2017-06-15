///////////////////////////////////////////////////////////////////////////////
/// \file AI.h
/// \brief ÊµÏÖAIÀà
/// 
/// 
///
/// \author À¶³þµÏ
///////////////////////////////////////////////////////////////////////////////

#ifndef _AI_H_
#define _AI_H_
#include "Player.h"

class AIPlayer :public Player 
{
public:
	AIPlayer(PlayScene& rScene):Player(rScene)
	{
		mType = GOT_AI;
	}
public:
	virtual void update(float dt)
	{
		//...
		Player::update(dt);
	}
};

#endif // !AI

