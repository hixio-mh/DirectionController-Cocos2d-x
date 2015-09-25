#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"



class Help : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuItemBackToMain(cocos2d::Ref* pSender);

	virtual void onAcceleration(cocos2d::Acceleration *acc,cocos2d::Event *event);

	virtual void onEnter();
	virtual void onExit();
	virtual void cleanup();

	CREATE_FUNC(Help);
};

#endif // __HELLOWORLD_SCENE_H__
