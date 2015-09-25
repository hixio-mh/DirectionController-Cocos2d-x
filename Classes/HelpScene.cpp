#include "HelpScene.h"
#include "HelloWorldScene.h"
#include "cocostudio\CocoStudio.h"

using namespace cocostudio;
using namespace CocosDenshion;
USING_NS_CC;

Scene* Help::createScene()
{
	auto scene = Scene::create();

	auto layer = Help::create();

	scene->addChild(layer);

	return scene;
}

bool Help::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//setBG
	auto sprite = Sprite::create("bg3.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	//set backMenuItem
	auto backMenuItem = MenuItemFont::create("Back", CC_CALLBACK_1(Help::menuItemBackToMain, this));
	backMenuItem->setPosition(Vec2(origin.x + visibleSize.width - backMenuItem->getContentSize().width / 2,
		origin.y + backMenuItem->getContentSize().height / 2));
	
	auto menu = Menu::create(backMenuItem,/* placeLable, flipXLable, flipYLable, hideLable, toggleLable,*/ NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto alice = Sprite::create("alice.png");
	alice->setScale(0.1);
	alice->setPosition(Vec2(200, 200));
	this->addChild(alice, 3,100);

	//auto particleSystem = ParticleFlower::create();
	//auto particleSystem = ParticleFire::create();
	//auto particleSystem = ParticleSmoke::create();
	//auto particleSystem = ParticleSun::create();
	//auto particleSystem = ParticleSnow::create();
	//auto particleSystem = ParticleExplosion::create();
	//auto particleSystem = ParticleFireworks::create();
	//auto particleSystem = ParticleGalaxy::create();
	//auto particleSystem = ParticleMeteor::create();
	//auto particleSystem = ParticleSpiral::create();
	auto particleSystem = ParticleRain::create();
	particleSystem->setPosition(Director::getInstance()->convertToGL(Vec2(270,380)));
	this->addChild(particleSystem);


	SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3",true);

	return true;
}

void Help::onEnter()
{
	Layer::onEnter();
	setAccelerometerEnabled(true);
}

void Help::onAcceleration(Acceleration *acc, Event *event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto hero = (Sprite *)this->getChildByTag(100);
	Size s = hero->getContentSize();
	Vec2 p0 = hero->getPosition();

	float p1x = p0.x + acc->x * 30;
	if ((p1x - s.width / 2) < 0){
		p1x = s.width / 2;
	}
	if ((p1x + s.width / 2) > visibleSize.width){
		p1x = visibleSize.width - s.width / 2;
	}
	float p1y = p0.y + acc->y * 30;
	if ((p1y - s.height / 2) < 0){
		p1y = s.height / 2;
	}
	if ((p1y + s.height / 2) > visibleSize.height){
		p1y = visibleSize.height - s.height / 2;
	}
	hero->runAction(Place::create(Vec2(p1x, p1y)));
}

void Help::onExit(){
	Layer::onExit();

}
void Help::cleanup(){
	Layer::cleanup();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("bgm.mp3");
}

//»Øµ÷º¯Êý

void Help::menuItemBackToMain(cocos2d::Ref* pSender)
{
	auto Hello = HelloWorld::createScene();
	auto action = TransitionCrossFade::create(1.0f, Hello);

	Director::getInstance()->replaceScene(action);
	SimpleAudioEngine::getInstance()->playEffect("effect.wav");
	
	
}

