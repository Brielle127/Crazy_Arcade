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

	// ����
	for (int i = 0; i < mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX, mGridY + idx)) // �����赲
			break;
		sprintf(buf, "part_up%d", i);
		mRenderObj.addPart(buf, Point(0, GRID_SIZE*idx));
		
		if (i == mLength - 1) // �ϱ߽�
			mRenderObj.setAni(buf, "Explosion", "up");
		else
			mRenderObj.setAni(buf, "Explosion", "up_m");
	}
	
	// ����
	for (int i = 0; i<mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX, mGridY - idx)) // �����赲
			break;
		sprintf(buf, "part_down%d", i);
		mRenderObj.addPart(buf, Point(0, -GRID_SIZE*idx));
		mRenderObj.setAni(buf, "Explosion", "left");

		if (i == mLength - 1)  // �±߽�
			mRenderObj.setAni(buf, "Explosion", "down");
		else
			mRenderObj.setAni(buf, "Explosion", "down_m");
		
	}
	// ����
	for (int i = 0; i<mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX-idx, mGridY)) // �����赲
			break;
		sprintf(buf, "part_left%d", i);
		mRenderObj.addPart(buf, Point( -GRID_SIZE*idx,0));
		if (i == mLength - 1)  
			mRenderObj.setAni(buf, "Explosion", "left");
		else
			mRenderObj.setAni(buf, "Explosion", "left_m");
	}
	// ����
	for (int i = 0; i<mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX+idx, mGridY)) // �����赲
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
	// ����
	for (int i = 0; i < mLength; ++i) {
		int idx = i + 1;
		if (mScene.getBarrier(mGridX, mGridY + idx)) { // �����赲
			auto& rVec = mScene.getObject(mGridX, mGridY + idx);
			for (size_t m = 0; m < rVec.size(); ++m) {
				rVec[m]->beAttacked();
			}
			break;
		}
	}


	// ����
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
	// ����
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
	// ����
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

