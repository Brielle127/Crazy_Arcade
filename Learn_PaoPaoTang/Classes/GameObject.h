#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Animation.h"
#include "BaseDef.h"

class PlayScene;

class GameObject
{
	GameObjectType mType;
protected:
	RenderObj mRenderObj;
	PlayScene& mScene;
	int mGridX;
	int mGridY;
public:

	GameObject(PlayScene& rScene,GameObjectType type)
		:mScene(rScene),mType(type)
		,mGridX(-1),mGridY(-1)
	{}
	virtual ~GameObject(){}

	GameObjectType getType() { return mType; }
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

