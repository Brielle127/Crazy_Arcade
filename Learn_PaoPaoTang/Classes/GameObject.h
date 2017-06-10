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
	/* ����λ�� */
	void setGrid(int gridx, int gridy) { mGridX = gridx; mGridY = gridy; }
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
	virtual void update(float dt)
	{
		//log("GameObject::update");
		mRenderObj.update(dt);// ������ʾ����
	}

	virtual Sprite* getSprite() { return mRenderObj.sprite; }
};

#endif // !_GAME_OBJECT_H_

