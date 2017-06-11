#include "Bomb.h"

void Bomb::explosion()
{
	mRenderObj.removePart("p0");
	mRenderObj.removePart("p1");
	mRenderObj.setAnchorPoint(Point::ZERO);
	mRenderObj.setPosition(Point(mGridX*GRID_SIZE, mGridY*GRID_SIZE));

	mRenderObj.addPart("middle", Point::ZERO);
	mRenderObj.setAni("middle", "Explosion", "middle");
	static char buf[256];

	// 向上
	for (int i = 0; i < mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX, mGridY + idx)) // 存在阻挡
			break;
		sprintf(buf, "part_up%d", i);
		mRenderObj.addPart(buf, Point(0, GRID_SIZE*idx));
		
		if (i == mLength - 1) // 上边界
			mRenderObj.setAni(buf, "Explosion", "up");
		else
			mRenderObj.setAni(buf, "Explosion", "up_m");
	}
	
	// 向下
	for (int i = 0; i<mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX, mGridY - idx)) // 存在阻挡
			break;
		sprintf(buf, "part_down%d", i);
		mRenderObj.addPart(buf, Point(0, -GRID_SIZE*idx));
		mRenderObj.setAni(buf, "Explosion", "left");

		if (i == mLength - 1)  // 下边界
			mRenderObj.setAni(buf, "Explosion", "down");
		else
			mRenderObj.setAni(buf, "Explosion", "down_m");
		
	}
	// 向左
	for (int i = 0; i<mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX-idx, mGridY)) // 存在阻挡
			break;
		sprintf(buf, "part_left%d", i);
		mRenderObj.addPart(buf, Point( -GRID_SIZE*idx,0));
		if (i == mLength - 1)  
			mRenderObj.setAni(buf, "Explosion", "left");
		else
			mRenderObj.setAni(buf, "Explosion", "left_m");
	}
	// 向右
	for (int i = 0; i<mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX+idx, mGridY)) // 存在阻挡
			break;
		sprintf(buf, "part_right%d", i);
		mRenderObj.addPart(buf, Point(GRID_SIZE*idx,0));
		if (i == mLength - 1)  
			mRenderObj.setAni(buf, "Explosion", "right");
		else
			mRenderObj.setAni(buf, "Explosion", "right_m");
	}
}

void Bomb::attack()
{
	// 向上
	for (int i = 0; i < mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX, mGridY + idx)) { // 存在阻挡
			auto& rVec = mScene.getObject(mGridX, mGridY + idx);
			for (size_t m = 0; m < rVec.size(); ++m) {
				rVec[m]->beAttacked();
			}
			break;
		}
	}


	// 向下
	for (int i = 0; i < mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX, mGridY - idx)) {
			auto& rVec = mScene.getObject(mGridX, mGridY - idx);
			for (size_t m = 0; m < rVec.size(); ++m) {
				rVec[m]->beAttacked();
			}
			break;
		}
	}
	// 向左
	for (int i = 0; i < mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX - idx, mGridY)) {
			auto& rVec = mScene.getObject(mGridX - idx, mGridY);
			for (size_t m = 0; m < rVec.size(); ++m) {
				rVec[m]->beAttacked();
			}
			break;
		}
	}
	// 向右
	for (int i = 0; i < mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX + idx, mGridY)) {
			auto& rVec = mScene.getObject(mGridX + idx, mGridY);
			for (size_t m = 0; m < rVec.size(); ++m) {
				rVec[m]->beAttacked();
			}
			break;
		}
	}
}

