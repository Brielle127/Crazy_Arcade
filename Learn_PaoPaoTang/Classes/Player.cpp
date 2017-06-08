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
	const Point rPoint = mRenderObj.getPosition(); // 当前位置
	float nextPosX = rPoint.x + dx;
	float nextPosY = rPoint.y + dy;

	// 边界判定
	if (nextPosX<GRID_SIZE / 2 || nextPosX>GRID_WIDTH*GRID_SIZE - GRID_SIZE / 2)
		return;
	if (nextPosY<1 || nextPosY>GRID_HEIGHT*GRID_SIZE - GRID_SIZE / 2-GRID_SIZE/4)
		return;

	// 计算格子位置
	int pgx = rPoint.x / GRID_SIZE;
	int pgy = rPoint.y / GRID_SIZE;
	pgx = dirx[mMoveState] + pgx;
	pgy = diry[mMoveState] + pgy;

	
	if (mMoveState == PMS_LEFT || mMoveState == PMS_RIGHT) {// 左右移动：检查上下阻挡,修正位置
		bool ba = mScene.getBarrier(pgx, pgy - 1) || mScene.getBarrier(pgx, pgy + 1);
		if (ba) {

		((Point&) rPoint).y = int(rPoint.y / GRID_SIZE)*GRID_SIZE + GRID_SIZE / 2;
		pgy = rPoint.y / GRID_SIZE;
		nextPosY = rPoint.y + dy; // 修正位置
		}
	}
	else { // 上下移动
		bool ba = mScene.getBarrier(pgx-1, pgy) || mScene.getBarrier(pgx+1, pgy);
		if (ba) {
		((Point&)rPoint).x = int(rPoint.x / GRID_SIZE)*GRID_SIZE + GRID_SIZE / 2;
		pgx = rPoint.x / GRID_SIZE;
		nextPosX = rPoint.x + dx;
		}
	}
	static int baTestFactorX[] = {				0,			 0, int(GRID_SIZE*1.5), -GRID_SIZE / 2 };
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
