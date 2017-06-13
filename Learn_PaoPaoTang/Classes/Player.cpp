#include "Player.h"
#include "PlayScene.h"
#include "Bomb.h"
Player::Player(PlayScene & rScene)
	:GameObject(rScene, GOT_Player)
	, mState(PLS_STAND)
	,mIsRiding(false)
	,mRideInfo(nullptr)
	,mRoleInfo(nullptr)
	,mCurrentUsedBombNum(0)
{
	memset(&mAttri, 0, sizeof(BaseAttri));
	memset(&mAttriEx, 0, sizeof(BaseAttri));
	mRenderObj.addPart(PART_BODY, Point::ZERO);
	mRenderObj.addPart(PART_EFX, Point::ZERO);
	mRenderObj.addPart(PART_RIDE, Point::ZERO);
	memset(mTransTable, PLS_NONE, sizeof(mTransTable));

	// ����Ĭ������Ĳ�������
	mTransTable[PI_KILL][PLS_STAND] = PLS_WRAPPED; // ��ֹ״̬+ը����ը->�����ݰ���
	mTransTable[PI_MOVE][PLS_STAND] = PLS_MOVE;    // ��ֹ״̬+�����ƶ�->�ƶ�״̬

	mTransTable[PI_MOVE][PLS_MOVE] = PLS_MOVE;
	mTransTable[PI_KILL][PLS_MOVE] = PLS_WRAPPED;
	mTransTable[PI_STOP][PLS_MOVE] = PLS_STAND;

	// ������ߡ�
	mTransTable[PI_KILL][PLS_WRAPPED] = PLS_DEAD;

	// ��ʼ��Ĭ�Ϸ���
	states[PLS_STAND].init(&Player::standStateEnter, &Player::defaultExit, &Player::defaultUpdate, &Player::moveAndStandOrderHandler);
	states[PLS_MOVE].init(&Player::moveStateEnter, &Player::defaultExit, &Player::moveStateUpdate, &Player::moveAndStandOrderHandler);
	states[PLS_WRAPPED].init(&Player::defaultEnter, &Player::defaultExit, &Player::defaultUpdate, &Player::defaultOrderHandler);
	states[PLS_DEAD].init(&Player::defaultEnter, &Player::defaultExit, &Player::defaultUpdate, &Player::defaultOrderHandler);
}

// �������
void Player::ride(ItemInfo * rideInfo)
{
	mRideInfo = rideInfo;
	mIsRiding = true;
	mRenderObj.setAni(PART_BODY, mRoleInfo->group.c_str(), getCurrentAni(mDirection));
	mRenderObj.modifyPartOffset(PART_BODY, Point(-mRenderObj.getSize()->size.width / 2, rideInfo->ridePointY));
	
	auto ani = getRideAni(mDirection);
	mRenderObj.setAni(PART_RIDE, rideInfo->rideGroup.c_str(), ani);
	mRenderObj.modifyPartOffset(PART_RIDE, Point(-rideInfo->ridePointX, 0));
}

void Player::handleInput(ControlType ectType, PressState epState)
{
	switch (epState)
	{
	case PS_DOWN:
		handleDown(ectType);
		break;
	case PS_UP:
		handleUp(ectType);
		break;
	default:
		return;
	}
}

void Player::handleDown(ControlType ectType) // ������̰����¼�
{
	switch (ectType)
	{
	case CT_PRESS: // �ո����ը��
	{

	}
	break;
	case CT_UP:
	case CT_DOWN:
	case CT_LEFT:
	case CT_RIGHT:
	{

		static PlayerDirection getMoveState[] = { PD_UP,PD_DOWN,PD_LEFT,PD_RIGHT };
		mTransParam.nextDirection = getMoveState[ectType - CT_UP];
		PlayerLogicState s = mTransTable[PI_MOVE][mState];  // �����ƶ�
		if (s != PLS_NONE)
			changeState(s);
	}
	break;
	default:
		return;

	}
}

void Player::handleUp(ControlType ectType)
{
	switch (ectType)
	{
	case CT_PRESS: // �ո����ը��
	{
		(this->*states[mState].orderHandler)(OT_SET_BOMB, nullptr);
	}
	break;
	case CT_LEFT:
	case CT_RIGHT:
	case CT_UP:
	case CT_DOWN:
	{
		PlayerLogicState s = mTransTable[PI_STOP][mState];  // ����ͣ��
		if (s != PLS_NONE)
			changeState(s);
	}
	break;
	default:
		return;

	}
}

// �л�״̬
void Player::changeState(PlayerLogicState nextState)
{
	// �˳���ǰ״̬
	StateMethod rCurrent = states[mState];
	(this->*rCurrent.exit)();

	mState = nextState;
	StateMethod rNext = states[nextState];
	(this->*rNext.enter)();
}

void Player::standStateEnter()
{
	auto pAniName = getCurrentAni(mDirection);
	if (pAniName) {
		mRenderObj.setAni(PART_BODY, mRoleInfo->group.c_str(), pAniName);
		move_flag = false;
		
		if (mIsRiding) {
			auto ani = getRideAni(mTransParam.nextDirection);
			mRenderObj.setAni(PART_RIDE, mRideInfo->rideGroup.c_str(), ani);
			mRenderObj.modifyPartOffset(PART_RIDE, Point(-mRideInfo->ridePointX, 0));
		}
	}
}

// �л�����
void Player::moveStateEnter()
{
	
	auto pAniName = getCurrentAni(mTransParam.nextDirection);
	if (pAniName) {
		if (mDirection != mTransParam.nextDirection || !move_flag) { // �ı䷽���ı��ƶ�״̬
			mRenderObj.setAni(PART_BODY, mRoleInfo->group.c_str(), pAniName);
			if (mIsRiding) { // ���ﶯ��ת��
				auto ani = getRideAni(mTransParam.nextDirection);
				mRenderObj.setAni(PART_RIDE, mRideInfo->rideGroup.c_str(), ani);
				mRenderObj.modifyPartOffset(PART_RIDE, Point(-mRideInfo->ridePointX, 0));
			}
			move_flag = true;
		}
		mDirection = mTransParam.nextDirection;
	}
}

void Player::moveStateUpdate(float dt)
{
	// �������ҵ�λ��
	static int dirx[] = { 0,0,-1,1 };
	static int diry[] = { 1,-1,0,0 };
	// ������С
	float dx = dirx[mDirection] * getSpeed() * dt;
	float dy = diry[mDirection] * getSpeed() * dt;

	// �߽���ײ���޶���ҵ��ƶ���Χ
	auto& rPoint = mRenderObj.getPosition(); // ��ǰλ��
	float nextPosX = rPoint.x + dx;
	float nextPosY = rPoint.y + dy;

	// �߽��ж�
	if (nextPosX<GRID_SIZE / 2 || nextPosX>GRID_WIDTH*GRID_SIZE - GRID_SIZE / 2)
		return;
	if (nextPosY<0 || nextPosY>GRID_HEIGHT*GRID_SIZE - GRID_SIZE / 2)
		return;

	/*if (mScene.getBarrier(nextPosX / GRID_SIZE, nextPosY / GRID_SIZE))
	return;*/

	// �������λ��
	int pgx = rPoint.x / GRID_SIZE;
	int pgy = rPoint.y / GRID_SIZE;

	// �����������
	int newx = (int(rPoint.x / GRID_SIZE))*GRID_SIZE + GRID_SIZE / 2;
	int newy = (int(rPoint.y / GRID_SIZE))*GRID_SIZE + GRID_SIZE / 2;

	if (mDirection == PD_LEFT || mDirection == PD_RIGHT) { // �����ƶ�����������赲
		if (pgy > 0 && pgy < GRID_HEIGHT)// �߽粻������
		{
			if (rPoint.y + dy > 0 || rPoint.y + dy < GRID_HEIGHT*GRID_SIZE - GRID_SIZE / 2)
				if (mScene.getBarrier(pgx, pgy - 1, getIgnoreStatic()) && rPoint.y < newy - GRID_SIZE / 2)
				{
					((Point&)rPoint).y = newy;
					pgy = rPoint.y / GRID_SIZE;
					nextPosY = rPoint.y - GRID_SIZE / 2 + dy;
				}        // ����λ��
				else if (mScene.getBarrier(pgx, pgy + 1, getIgnoreStatic()) && rPoint.y > newy )
				{
					((Point&)rPoint).y = newy;
					pgy = rPoint.y / GRID_SIZE;
					nextPosY = rPoint.y + dy;
				}
		}
	}                                    // 
	else if (pgx > 0 && pgx < GRID_WIDTH)// �߽粻������ 
	{
		if ((mScene.getBarrier(pgx - 1, pgy, getIgnoreStatic()) && (rPoint.x < newx)) ||
			(mScene.getBarrier(pgx + 1, pgy, getIgnoreStatic()) && (rPoint.x > newx))) {
			((Point&)rPoint).x = (int(rPoint.x / GRID_SIZE))*GRID_SIZE + GRID_SIZE / 2;
			pgx = rPoint.x / GRID_SIZE;
			if (rPoint.x + dx > GRID_SIZE / 2 || rPoint.x + dx < GRID_WIDTH*GRID_SIZE - GRID_SIZE / 2)
				nextPosX = rPoint.x + dx;
		}
	}

	pgx += dirx[mDirection];
	pgy += diry[mDirection];

	static int baTestFactorX[] = { 0,			 0, int(GRID_SIZE*1.5), -GRID_SIZE / 2 };
	static int baTestFactorY[] = { -GRID_SIZE / 2,GRID_SIZE + 1,			0,				0 };

	if (pgy<GRID_HEIGHT)
		if (mScene.getBarrier(pgx, pgy,getIgnoreStatic())) {                       // ��һλ���赲��	
			auto& rObjs = mScene.getObject(pgx, pgy);
			for (size_t i = 0; i < rObjs.size(); ++i) {
				auto popo = rObjs[i];
				if (popo->getType() == GOT_Bomb) {
					if (getCanKickPopo())
						((Bomb*)popo)->beKicked(dirx[mDirection], diry[mDirection]);
					break;
				}
			}
			int bax = pgx*GRID_SIZE + baTestFactorX[mDirection];//  ��һ������
			int bay = pgy*GRID_SIZE + baTestFactorY[mDirection]; 
			switch (mDirection)
			{
			case PD_UP:
				if (nextPosY > bay) {
					return;
				}
				break;
			case PD_DOWN:
				if (nextPosY < bay) {
					return;
				}
				break;
			case PD_LEFT:
			{
				if (nextPosX < bax)
				{
					return;
				}
			}
			break;
			case PD_RIGHT:
				if (nextPosX > bax)
				{
					return;
				}
				break;
			default:
				return;
			}
		}
	mRenderObj.setPosition(Point(nextPosX, nextPosY));
}

void Player::moveAndStandOrderHandler(OrderType type, void * data)
{
	switch (type)
	{
	case OT_SET_BOMB:
	{
		if (mCurrentUsedBombNum >= getBombNum())
			return;

		auto& rPoint = this->getPosition();
		int gridx = rPoint.x / GRID_SIZE, gridy = rPoint.y / GRID_SIZE;
	
		if (mScene.getBarrier(gridx, gridy))
			return;

		Bomb* obj = (Bomb*)mScene.createObject(GOT_Bomb);
		obj->setStrLen(getStr());
		obj->setRelatedPtr(&mCurrentUsedBombNum);
		obj->setGrid(gridx, gridy);
		mScene.addObj(obj, gridx, gridy);
		mCurrentUsedBombNum++;  // ��һ��ը���ݼ�����
	}
	break;
	default:
		break;
	}
}

const char * Player::getCurrentAni(PlayerDirection dir)
{
	static const char* moveAnis[] = { "walk_up","walk_down","walk_left","walk_right" };
	static const char* standAnis[] = { "stand_up","stand_down","stand_left","stand_right" };
	static const char* rideAnis[] = { "ride_up","ride_down","ride_left","ride_right" }; 
	switch (dir)
	{
	case PD_UP:
	case PD_DOWN:
	case PD_LEFT:
	case PD_RIGHT:
		if (mIsRiding) {
			return rideAnis[dir];
		}
		else {
			if (mState == PLS_MOVE) {
				return moveAnis[dir];
			}
			else if (mState == PLS_STAND) {
				return standAnis[dir];
			}
			return nullptr;
		}
		break;
	default:
		return nullptr;
	}
}

const char * Player::getRideAni(PlayerDirection dir)
{
	if (!mIsRiding)
		return nullptr;
	static const char* moveAnis[] = { "walk_up","walk_down","walk_left","walk_right" };
	static const char* standAnis[] = { "stand_up","stand_down","stand_left","stand_right" };
	switch (dir)
	{
	case PD_UP:
	case PD_DOWN:
	case PD_LEFT:
	case PD_RIGHT:
		if (mState == PLS_MOVE) {
			return moveAnis[dir];
		}
		else if (mState == PLS_STAND) {
			return standAnis[dir];
		}
	default:
		return nullptr;
	}
}
