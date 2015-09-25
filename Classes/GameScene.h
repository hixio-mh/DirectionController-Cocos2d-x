#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class Game : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	
	void logic(float t);



	void backToMenu(cocos2d::Ref *pSender);

	void goLeftCallBack(cocos2d::Ref *pLeft);

	void goRightCallBack(cocos2d::Ref *pRight);

	virtual bool onTouchBegan1(Touch *touch, Event *unused_event);

	virtual void onTouchMoved1(Touch *touch, Event *unused_event);

	virtual void onTouchEnded1(Touch *touch, Event *unused_event);

	virtual bool onTouchBegan2(Touch *touch, Event *unused_event);

	virtual void onTouchMoved2(Touch *touch, Event *unused_event);

	virtual void onTouchEnded2(Touch *touch, Event *unused_event);

	Vec2 getAngelePosition(double r, double angle);

	double getRad(Vec2 pos1, Vec2 pos2);

	void overStand();

	void runGame(float t);

	CREATE_FUNC(Game);


};

#endif