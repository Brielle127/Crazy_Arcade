#include "Building.h"

void Building::beAttacked()
{
	if (mDestroyEnable) {
		destroy(); // ���ݻ�
		mNeedDestroy = true;
	}
}
