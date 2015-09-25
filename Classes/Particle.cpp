#include "Particle.h"
#include "HelloWorldScene.h"

USING_NS_CC;


Scene* Part::createScene()
{
	auto scene = Scene::create();

	auto layer = Part::create();

	scene->addChild(layer);

	return scene;
}

bool Part::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//setBG
	auto sprite = Sprite::create("desktop.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	//set backMenuItem
	auto backMenuItem = MenuItemFont::create("Back", CC_CALLBACK_1(Part::backItem, this));
	backMenuItem->setPosition(Vec2(origin.x + visibleSize.width - backMenuItem->getContentSize().width / 2,
		origin.y + backMenuItem->getContentSize().height / 2));

	auto menu = Menu::create(backMenuItem,/* placeLable, flipXLable, flipYLable, hideLable, toggleLable,*/ NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}
void Part::backMenu(cocos2d::Ref * pSender)
{
	auto Hello = HelloWorld::createScene();
	auto action = TransitionCrossFade::create(1.0f, Hello);

	Director::getInstance()->replaceScene(action);
}