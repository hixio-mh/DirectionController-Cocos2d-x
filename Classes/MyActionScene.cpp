#include "MyActionScene.h"

USING_NS_CC;

bool MyAction::init()
{
	if (!Layer::create())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("bg.jpg");
	bg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(bg);

	sprite = Sprite::create("plane.png");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite);

	auto backMenuItem = MenuItemFont::create("Back", CC_CALLBACK_1(MyAction::backMenu,this));
	backMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(120, 100)));

	auto goMenuItem = MenuItemFont::create("Go", CC_CALLBACK_1(MyAction::goMenu, this));
	goMenuItem->setPosition(visibleSize.width / 2, 100);

	auto menu = Menu::create(backMenuItem, goMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	this->hiddenFlag = true;

	return true;
}

void MyAction::backMenu(Ref *pSender)
{
	auto sc = Help::createScene();
	auto reScene = TransitionSlideInL::create(1.0f, sc);
	Director::getInstance()->replaceScene(reScene);

}

void MyAction::goMenu(Ref *pSender)
{
	log("Tag = %i", this->getTag());

	Size size = Director::getInstance()->getVisibleSize();
	Vec2 p = Vec2(CCRANDOM_0_1() * size.width, CCRANDOM_0_1() * size.height);

	switch (this->getTag()){
		case PLACE_TAG:
			sprite->runAction(Place::create(p));
			break;
		case FLIPX_TAG:
			sprite->runAction(FlipX::create(true));
			break;
		case FLIPY_TAG:
			sprite->runAction(FlipY::create(true));
			break;
		case HIDE_SHOW_TAG:
			if (hiddenFlag){
				sprite->runAction(Hide::create());
				hiddenFlag = false;
			}
			else {
				sprite->runAction(Show::create());
				hiddenFlag = true;
			}
			break;
		case TOGGLE_TAG:
			sprite->runAction(ToggleVisibility::create());
			break;
		default:
			break;
	}
}