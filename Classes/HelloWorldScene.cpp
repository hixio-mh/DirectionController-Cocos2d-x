#include "HelloWorldScene.h"
#include "HelpScene.h"
#include "GameScene.h"
#include "cocostudio\CocoStudio.h"

using namespace cocostudio;
USING_NS_CC;

Scene* HelloWorld::createScene()
{

    auto scene = Scene::create();

    auto layer = HelloWorld::create();


    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	auto helpMenuItem = MenuItemFont::create("Help", CC_CALLBACK_1(HelloWorld::helpMenuCallBack, this));
	auto gameMenuItem = MenuItemFont::create("Game", CC_CALLBACK_1(HelloWorld::gameMenuCallBack, this));
	/*
	//开关按钮的实现
	auto toggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::menuItemCallBack, this),
													MenuItemFont::create("On"),MenuItemFont::create("Off"),NULL);

	toggleMenuItem->setPosition(Vec2(480, 50));

	*/
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1);

    auto menu1 = Menu::create(helpMenuItem,gameMenuItem, NULL);
	menu1->alignItemsVertically();
    this->addChild(menu1, 1);


    auto label = Label::createWithTTF("Simple Game", "fonts/Marker Felt.ttf", 24);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);


    auto sprite = Sprite::create("bg1.jpg");
	sprite->setScale(1.1);
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);

	/*
	auto JoyStick_base = Sprite::create("JoyStick-base.png", Rect( 104, 104 ,  100, 100 ));
	JoyStick_base->setPosition(Vec2(100,100));
	this->addChild(JoyStick_base, 0);

	
	auto cache = Director::getInstance()->getTextureCache()->addImage("JoyStick-base.png");
	auto Joy = Sprite::create();
	Joy->setTexture(cache);
	Joy->setTextureRect(Rect(50, 50, 50, 50));
	Joy->setPosition(Vec2(600, 200));
	this->addChild(Joy, 0);
    */
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuItemCallBack(Ref* pSender)
{

}

void HelloWorld::helpMenuCallBack(Ref* pSender)
{
	auto help = Help::createScene();
	auto action = TransitionFadeDown::create(0.5f, help);

	Director::getInstance()->pushScene(action);
}

void HelloWorld::gameMenuCallBack(Ref* pSender)
{
	auto game = Game::createScene();
	auto action = TransitionFadeDown::create(0.5f, game);

	Director::getInstance()->pushScene(action);
}
