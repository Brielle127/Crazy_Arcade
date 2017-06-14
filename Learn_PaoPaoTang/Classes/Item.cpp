#include "PlayScene.h"
#include "Item.h"
#include "Player.h"
#include "Buff.h"
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
		if (player->getIgnoreItem())  // 忽略道具
			return;
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

			player->setCanKickPopo(mInfo->canKick);
			player->setIgnoreItem(mInfo->ignoreItem);
			player->setIgnoreStatic(mInfo->ignoreStatic);
		}
		break;
		case IT_RIDE:  // 坐骑
		{
			AtrributeBuff* pBuff = new AtrributeBuff();
			pBuff->canKick = mInfo->canKick;
			pBuff->ignoreItem = mInfo->ignoreItem;
			pBuff->ignoreStatic = mInfo->ignoreStatic;
			pBuff->popoNum = mInfo->popoNum;
			pBuff->popoStr = mInfo->popoStr;
			pBuff->roleSpeed = mInfo->roleSpeed;

			player->addBuff(pBuff);
			player->ride(mInfo);
		}
		break;
		default:
			return;
		}
	}
	GameObject::update(dt);
}
