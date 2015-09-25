#ifndef _MYACTION_SCENE_H__
#define _MYACTION_SCENE_H__

#include "cocos2d.h"
#include "HelpScene.h"

class MyAction:public cocos2d::Layer
{
	bool hiddenFlag;
	cocos2d::Sprite *sprite;

public:
	
	static cocos2d::Scene *createScene();
	virtual bool init();

	CREATE_FUNC(MyAction);

	void goMenu(cocos2d::Ref *pSender);
	void backMenu(cocos2d::Ref *pSender);

};

#endif   //_MYACTION_SCENE_H__