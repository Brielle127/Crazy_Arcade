#include "Item.h"
#include "PlayScene.h"
#include "Player.h"
void Item::update(float dt)
{
	if (mNeedDestroy)
		return;
	// 
	auto player = mScene.getPlayer();
	auto& rPoint = player->getPosition(); // ���λ��
	auto& rItemPos = this->getPosition(); // ����λ��

	float dx = rPoint.x - (rItemPos.x + GRID_SIZE / 2);
	float dy = rPoint.y - rItemPos.y;

	const float range = GRID_SIZE / 3; // �������ߵķ�Χ
	if (dx*dx + dy*dy < range*range) {
		mNeedDestroy = true;
		switch (mInfo->type)
		{
		case IT_NORMAL: // ��ͨ����
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
		case IT_RIDE:  // ����
			player->ride(mInfo);
			break;
		default:
			return;
		}
	}
	GameObject::update(dt);
}
