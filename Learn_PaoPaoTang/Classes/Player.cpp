#include "Player.h"
#include "PlayScene.h"

void Player::moveStateUpdate(float dt)
{
	// 上下左右的位移
	static int dirx[] = { 0,0,-1,1 };
	static int diry[] = { 1,-1,0,0 };
	// 步径大小
	float dx = dirx[mMoveState] * mSpeed * dt;
	float dy = diry[mMoveState] * mSpeed * dt;

	// 边界碰撞：限定玩家的移动范围
	const Point rPoint = mRenderObj.getPosition();
	const float nextPosX = rPoint.x + dx;
	const float nextPosY = rPoint.y + dy;

	if (nextPosX<GRID_SIZE / 2 || nextPosX>GRID_WIDTH*GRID_SIZE - GRID_SIZE / 2)
		return;
	if (nextPosY<1 || nextPosY>GRID_HEIGHT*GRID_SIZE - GRID_SIZE / 2-GRID_SIZE/4)
		return;

	int pgx = rPoint.x / GRID_SIZE;
	int pgy = rPoint.y / GRID_SIZE;
	pgx = dirx[mMoveState] + pgx;
	pgy = diry[mMoveState] + pgy;

	
	static int baTestFactorX[] = {				0,			 0, GRID_SIZE*1.5, -GRID_SIZE / 2 };
	static int baTestFactorY[] = { -GRID_SIZE / 4,GRID_SIZE + 1,			0,				0 };
	// 取得阻挡信息	
	bool ba = mScene.getBarrier(pgx, pgy);
	if (ba) {
		int bax = pgx*GRID_SIZE + baTestFactorX[mMoveState];
		int bay = pgx*GRID_SIZE + baTestFactorY[mMoveState]; // 从右向左走
		switch (mMoveState)
		{
		case PMS_UP:
			if (nextPosY > bay) {
				return;
			}
			break;
		case PMS_DOWN:
			if (nextPosY < bay) {
				return;
			}
			break;
		case PMS_LEFT:
			{
			if (nextPosX < bax)
			{
				return;
				}
			}
			break;
		case PMS_RIGHT:
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
