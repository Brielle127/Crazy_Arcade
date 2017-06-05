#include "Player.h"

Player::Player(PlayScene & rScene)
	:GameObject(rScene, GOT_Player)
	, mState(PLS_STAND)
	, mSpeed(0)
	, mMaxBombNum(0)
	, mBombStrength(0)
	, mIsRiding(0)
{
	mRenderObj.addPart(PART_BODY, Point::ZERO);
	mRenderObj.addPart(PART_EFX, Point::ZERO);
	mRenderObj.addPart(PART_RIDE, Point::ZERO);

	memset(mTransTable, 0, sizeof(mTransTable));

	// 设置默认允许的操作……

	// 初始化默认方法
	states[PLS_STAND].init(&Player::defaultEnter, &Player::defaultExit, &Player::defaultUpdate, &Player::standHandleInput);
	states[PLS_MOVE].init(&Player::defaultEnter, &Player::defaultExit, &Player::defaultUpdate, &Player::moveHandleInput);
	states[PLS_WRAPPED].init(&Player::defaultEnter, &Player::defaultExit, &Player::defaultUpdate, &Player::defaultHandleInput);
	states[PLS_DEAD].init(&Player::defaultEnter, &Player::defaultExit, &Player::defaultUpdate, &Player::defaultHandleInput);
}
