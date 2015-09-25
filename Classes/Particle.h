#ifndef __PARTICLE_SCENE_H__
#define __PARTICLE_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class Particle : public cocos2d::Layer
{

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void backMenu(cocos2d::Ref * pSender);

	CREATE_FUNC(Particle);
}



#endif
