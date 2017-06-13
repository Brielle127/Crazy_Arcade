#include"Buff.h"
#include "Player.h"

void AtrributeBuff::update(float dt)
{

}

void AtrributeBuff::attach(Player * pT)
{
	mTarget = pT;
	// ...
	
}
 
void AtrributeBuff::compute()
{
	if (canKick)
		mTarget->setCanKickPopoEx(true);
	if (ignoreItem)
		mTarget->setIgnoreItemEx(true);
	if (ignoreStatic)
		mTarget->setIgnoreStaticEx(true);

	mTarget->setBombNumEx(popoNum + mTarget->getBombNum());
	mTarget->setStrEx(popoStr + mTarget->getStr());
	mTarget->setSpeedEx(roleSpeed + mTarget->getSpeed());
}

void AtrributeBuff::remove()
{
	delete this;
}
