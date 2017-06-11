#include "Building.h"

void Building::beAttacked()
{
	if (mDestroyEnable) {
		destroy(); // ±»´Ý»Ù
		mNeedDestroy = true;
	}
}
