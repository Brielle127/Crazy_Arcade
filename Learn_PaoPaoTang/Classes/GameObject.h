#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Animation.h"
#include "BaseDef.h"
//#include "PlayScene.h"
class PlayScene;

class GameObject
{
protected:
	GameObjectType mType;
	RenderObj mRenderObj;
	PlayScene& mScene;
	int mGridX;
	int mGridY;
	bool mNeedDestroy;
public:

	GameObject(PlayScene& rScene,GameObjectType type)
		:mScene(rScene),mType(type)
		,mGridX(-1),mGridY(-1)
		,mNeedDestroy(false)
	{}
	virtual ~GameObject(){}

	GameObjectType getType() { return mType; }
	bool isNeedDestroy() { return mNeedDestroy; }
	/* 设置位置 */
	virtual void setGrid(int gridx, int gridy) { mGridX = gridx; mGridY = gridy; }
	virtual void setPosition(const Point& rPoint)
	{
		mRenderObj.setPosition(rPoint);
	}

	const Point& getPosition()
	{
		return mRenderObj.getPosition();
	}

public:
	virtual float getDepth() { return -mRenderObj.getPosition().y; }
	virtual void load(const char* szName) = 0;
	virtual void beAttacked() = 0;  // 受到炸弹的攻击
	virtual void update(float dt)
	{
		//log("GameObject::update");
		mRenderObj.update(dt);// 更新显示内容
	}

	virtual Sprite* getSprite() { return mRenderObj.sprite; }
};

#endif // !_GAME_OBJECT_H_
