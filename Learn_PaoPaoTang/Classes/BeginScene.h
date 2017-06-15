///////////////////////////////////////////////////////////////////////////////
/// \file BeginScene.h
/// \brief  µœ÷BeginScene¿‡
/// 
/// 
///
/// \author ¿∂≥˛µœ 
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

	virtual void onEnterScene();
	virtual void onExitScene();
	
};

#endif // !BEGIN_SCENE_H
