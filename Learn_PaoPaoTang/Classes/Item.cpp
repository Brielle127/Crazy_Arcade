#include "Item.h"
#include "PlayScene.h"
#include "Player.h"
void Item::update(float dt)
{
	if (mNeedDestroy)
		return;
	// 
	auto player = mScene.getPlayer();
	auto& rPoint = player->getPosition(); // 玩家位置
	auto& rItemPos = this->getPosition(); // 道具位置

	float dx = rPoint.x - (rItemPos.x + GRID_SIZE / 2);
	float dy = rPoint.y - rItemPos.y;

	const float range = GRID_SIZE / 3; // 触碰道具的范围
	if (dx*dx + dy*dy < range*range) {
		mNeedDestroy = true;
		switch (mInfo->type)
		{
		case IT_NORMAL: // 普通道具
		{
			int num = player->getBombNum() + mInfo->popoNum;
			player->setBombNum(num);

			int str = player->getStr() + mInfo->popoStr;
			player->setStr(str);

			int speed = player->getSpeed() + mInfo->roleSpeed;
			player->setSpeed(speed);

			if (mInfo->canKick)
				player->setCanKickPopo(true);
		}
		break;
		case IT_RIDE:  // 坐骑
			player->ride(mInfo);
			break;
		default:
			return;
		}
	}
	GameObject::update(dt);
}
