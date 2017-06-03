#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "cocos2d.h"
USING_NS_CC;
#include <vector>
using namespace std;

struct CAniData
{
	// 动画名
	string name;
	// 动画资源文件
	string fileName;
	// 帧率
	int fps;
	// 动画帧数据
	vector<Rect> framesData;
};

/*渲染对象*/
class CRenderObj
{
	float currentElapsed;
public:
	Sprite* sprite;
	int currentFrame;
	CAniData* currentAniData;
	CRenderObj()
		:currentFrame(0),
		currentElapsed(0),
		currentAniData(nullptr)
	{
		sprite = Sprite::create();
		
		/*测试代码*/
		currentAniData = new (CAniData)();
		currentAniData->name = "";
		currentAniData->fps = 4;
		currentAniData->fileName = "Pic/Role2.png";
		int width = 336 / 6;
		int height = 268/4;
		currentAniData->framesData.reserve(6);
		for (int i = 0; i < 6; i++)
		{
			currentAniData->framesData.push_back(Rect(width*i,height*1,width,height));
		}

		auto pTexture = Director::getInstance()->getTextureCache()->addImage(currentAniData->fileName);
		sprite->setTexture(pTexture);
		sprite->setTextureRect(currentAniData->framesData[0]); 
	}
	void update(float dt)
	{
		if (currentAniData) {
			if (currentAniData->framesData.size() == 1) // 处理只有1帧的动画
				return;
			currentElapsed += dt;
			currentFrame = currentElapsed*currentAniData->fps;
			currentFrame %= currentAniData->framesData.size();
			sprite->setTextureRect(currentAniData->framesData[currentFrame]);
		}

	}
		
};
#endif // !_ANIMATION_H_
