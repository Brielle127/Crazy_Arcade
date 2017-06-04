#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Animation.h"
#include "BaseDef.h"
class CPlayScene;

class CGameObject
{
	EGameObjectType mType;
protected:
	CRenderObj mRenderObj;
	CPlayScene& mScene;
	int mGridX;
	int mGridY;
public:
	CGameObject(CPlayScene& rScene,EGameObjectType type)
		:mScene(rScene),mType(type)
		,mGridX(-1),mGridY(-1)
	{}
	virtual ~CGameObject(){}

	EGameObjectType getType() { return mType; }
	/* 设置位置 */
	void setGrid(int gridx, int gridy) { mGridX = gridx; mGridY = gridy; }
public:
	virtual float getDepth() { return -mRenderObj.sprite->getPositionY(); }
	virtual void load(const char* szName) = 0;
	virtual void update(float dt)
	{
		mRenderObj.update(dt);// 更新显示内容
	}

	virtual Sprite* getSprite() { return mRenderObj.sprite; }
};

#endif // !_GAME_OBJECT_H_

