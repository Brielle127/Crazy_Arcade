///////////////////////////////////////////////////////////////////////////////
/// \file BeginScene.h
/// \brief Head file for class BeginScene
/// 
/// 
///
/// \author 易春含
///////////////////////////////////////////////////////////////////////////////

#ifndef BEGIN_SCENE_H
#define BEGIN_SCENE_H
#include"BaseScene.h"

class BeginScene :public BaseScene
{
public:
	BeginScene()
	{

	}

	virtual void onEnterScene();  ///进入场景
	virtual void onExitScene();    ///退出场景
	
};

#endif // !BEGIN_SCENE_H
