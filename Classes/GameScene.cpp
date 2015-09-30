#include "GameScene.h"
#include "HelloWorldScene.h"
#include "math\CCMath.h"
#include "cocostudio\CocoStudio.h"

using namespace cocostudio;
USING_NS_CC;

//ö��   ����TAG
typedef enum
{
	ALICE_TAG = 1000,
	YAOGAN_TAG = 9007,
	YAOPOINT_TAG,
	XIA_TAG

}HERO_TAG;

auto PI = 3.1415;
//����
auto R_Direction = "";
//����
auto R_Action = "hold";
//�ƶ��ٶ�
auto R_speed = 7;

Scene* Game::createScene()
{
	auto scene = Scene::create();

	auto layer = Game::create();

	scene->addChild(layer);

	return scene;
}

bool Game::init()
{
	if (!Layer::create())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//setBG
	auto gameBg = Sprite::create("bg3.jpg");
	gameBg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(gameBg, 0);

	//set menuItem
	auto backMenuItem = MenuItemFont::create("Back", CC_CALLBACK_1(Game::backToMenu, this));
	backMenuItem->setPosition(Vec2(origin.x + visibleSize.width - backMenuItem->getContentSize().width / 2,
		origin.y + backMenuItem->getContentSize().height / 2));

	auto menu = Menu::create(backMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1);

	//set controlItem
	auto leftItem = MenuItemImage::create("left.png", "left02.png", CC_CALLBACK_1(Game::goLeftCallBack, this));
	auto rightItem = MenuItemImage::create("right.png", "right02.png", CC_CALLBACK_1(Game::goRightCallBack, this));

	auto controlMenu = Menu::create(leftItem,rightItem,  NULL);
	controlMenu->setPosition(Vec2(100,100));
	controlMenu->alignItemsHorizontally();
	this->addChild(controlMenu, 1);


	
	
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Export/kakaxi.ExportJson");
	auto arm = Armature::create("kakaxi");
	arm->setScale(0.8);
	arm->getAnimation()->play("run");
	arm->setPosition(Point(visibleSize.width*0.2, visibleSize.height*0.7));
	this->addChild(arm, 4,XIA_TAG);
	
	//add sprites
	auto alice = Sprite::create("alice.png");
	alice->setScale(0.1);
	alice->setPosition(Vec2(200, 200));
	this->addChild(alice,3,ALICE_TAG);



	//ҡ�˼���
	auto listener_YaoGan = EventListenerTouchOneByOne::create();
	listener_YaoGan->setSwallowTouches(true);

	listener_YaoGan->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan1, this);
	listener_YaoGan->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved1, this);
	listener_YaoGan->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded1, this);

	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(listener_YaoGan, this);

	//���Ǽ���
	auto listener_Role = EventListenerTouchOneByOne::create();
	listener_Role->setSwallowTouches(true);

	listener_Role->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan2, this);
	listener_Role->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved2, this);
	listener_Role->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded2, this);

	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(listener_Role, this);

	//this->schedule(schedule_selector(Game::logic), 1);
	overStand();
	
	this->schedule(schedule_selector(Game::runGame), 0.03);

	return true;
}

//�ƶ����ص�

void Game::overStand() 
{
	auto hero = (Armature *)getChildByTag(XIA_TAG);
	if ( true)
		{
			hero->getAnimation()->play("hold");
		}
}

void Game::runGame(float t){
	auto hero = (Armature *)getChildByTag(XIA_TAG);
if (R_Action == "run")
{
	if (hero != NULL)
	{
		if (hero->getAnimation()->getCurrentMovementID() != "run")
		{
			hero->getAnimation()->play("run");
		}

		auto p_hero_old = hero->getPosition();
		if (R_Direction == "right")
		{
			hero->setScaleX(-1);
			hero->setPosition(p_hero_old.x + R_speed, p_hero_old.y);
		}
		else if (R_Direction == "up")
		{
			hero->setPosition(p_hero_old.x, p_hero_old.y + R_speed);

		}
		else if (R_Direction == "left")
		{
			hero->setScaleX(1);
			hero->setPosition(p_hero_old.x - R_speed, p_hero_old.y);

		}
		else if (R_Direction == "down")
		{
			hero->setPosition(p_hero_old.x, p_hero_old.y - R_speed);

		}
		else if (R_Direction == "left_up")
		{
			hero->setScaleX(1);
			hero->setPosition(p_hero_old.x - R_speed, p_hero_old.y + R_speed);

		}
		else if (R_Direction == "left_down")
		{
			hero->setScaleX(1);
			log("left down");
			hero->setPosition(p_hero_old.x - R_speed, p_hero_old.y - R_speed);
//--
		}
		else if (R_Direction == "right_up")
		{
			hero->setScaleX(-1);
			hero->setPosition(p_hero_old.x + R_speed, p_hero_old.y + R_speed);
		}
		else if (R_Direction == "right_down")
		{
			hero->setScaleX(-1);
			hero->setPosition(p_hero_old.x + R_speed, p_hero_old.y - R_speed);

		}
	}
}
}


void Game::backToMenu(Ref *pSender)
{
	auto sc = HelloWorld::createScene();

	auto reScene = TransitionCrossFade::create(1.0f, sc);

	Director::getInstance()->replaceScene(reScene);

}


//ҡ�˴����ص�����

bool Game::onTouchBegan1(Touch *touch, Event *event){

	//this->getChildByTag(10)->runAction(MoveBy::create(0.5, Vec2(10, 0)));
	//ҡ�˴���
	auto target = event->getCurrentTarget();

	auto location = target->convertToNodeSpace(touch->getLocation());

		auto yaogan = Sprite::create("yaoganBg.png");
	
	yaogan->setPosition(location.x,location.y);
	this->addChild(yaogan,3,YAOGAN_TAG);

	//����ҡ�˵�
	auto yaoPoint = Sprite::create("yaogan.png");
	yaoPoint->setPosition(location.x, location.y);
	this->addChild(yaoPoint, 4,YAOPOINT_TAG);

	return true;
}

void Game::onTouchMoved1(Touch *touch, Event *event){
	//�Ȼ�ȡҡ�˵��ҡ�˱����ľ������
	auto target = event->getCurrentTarget();
	auto sp_dian = target->getChildByTag(YAOPOINT_TAG);
	auto sp_yaoganBg = target->getChildByTag(YAOGAN_TAG);
	auto sp_hero = target->getChildByTag(XIA_TAG);

	//ҡ����
	if (sp_dian != NULL && sp_yaoganBg != NULL)
	{
		auto p_dian = sp_yaoganBg->getPosition();
		auto bg_width = sp_yaoganBg->getContentSize().width*0.5;

		auto point = touch->getLocation();
		auto p_rad = this->getRad(p_dian, point);

		//��������Բ��֮��ľ���
		auto juli = sqrt(pow((p_dian.x - point.x), 2) + pow((p_dian.y - point.y),2));
		
		//���벻�����뾶
		if (juli >= bg_width)
		{
			auto re = getAngelePosition(bg_width, p_rad);
			sp_dian->setPosition(re.x+p_dian.x,  re.y+p_dian.y);
		}
		else{
			auto delta = touch->getDelta();
			
			
			auto x = sp_dian->getPosition().x + delta.x;
			auto y = sp_dian->getPosition().y + delta.y;
			sp_dian->setPosition(x, y);
		}


		//�жϷ��� ---�˷���
		auto move_x = (int)(p_dian.x - point.x);
		auto move_y = (int)(p_dian.y - point.y);

		if (move_x >= 10 && move_y <= -10){
			//����
			R_Direction = "left_up";
		}
		else if (move_x >= 10 && move_y >= 10){
			//����
			R_Direction = "left_down";
		}
		else if (move_x <= -10 && move_y <= -10){
			//����
			R_Direction = "right_up";
		}
		else if (move_x <= -10 && move_y >= 10){
			//����
			R_Direction = "right_down";
		}
		else if (move_x > -10 && move_x < 10 && move_y > 0){
			//��
			R_Direction = "down";
		}
		else if (move_x > -10 && move_x < 10 && move_y < 0){
			//��
			R_Direction = "up";
		}
		else if (move_x > 0 && move_y < 10 && move_y > -10){
			//��
			R_Direction = "left";
		}
		else if (move_x < 0 && move_y < 10 && move_y > -10){
			//��
			R_Direction = "right";
		}
		R_Action = "run";
		//log("R_Direction>>>" + R_Direction);
	}


}


void Game::onTouchEnded1(Touch *touch, Event *event){

	auto target = event->getCurrentTarget();
	if (target->getChildByTag(YAOPOINT_TAG) != NULL)
	{
		target->removeChildByTag(YAOPOINT_TAG);
	}
	if (target->getChildByTag(YAOGAN_TAG) != NULL)
	{
		target->removeChildByTag(YAOGAN_TAG);
	}

	R_Action = "hold";

	auto sp_hero = (Armature *)target->getChildByTag(XIA_TAG);
	sp_hero->getAnimation()->play("hold");
	//sp_hero->ge;
	//this->getChildByTag(10)->stopAction(MoveBy::create(0.5, Vec2(10, 0)));
}


//�ж������ļн�
double Game::getRad(Vec2 pos1, Vec2 pos2)
{
		   auto px1 = pos1.x;
		   auto py1 = pos1.y;
		   auto px2 = pos2.x;
		   auto py2 = pos2.y;

		   //�õ�����x�ľ���
		   auto x = px2 - px1;
		   //�õ�����y�ľ���
		   auto y = py1 - py2;
		   //���б�߳���
		   auto xie = sqrt(pow(x, 2) + pow(y, 2));
		   //�õ�����Ƕȵ�����ֵ(ͨ�����Ǻ����еĵ���Ƕ�����ֵ=б��/б��)
		   auto cosAngle = x / xie;
		   //ͨ�������Ҷ����ȡ���ڽǶȵĻ���
		   auto rad = acos(cosAngle);
		   //ע�⣺��������λ��Y����<ҡ�˵�Y���꣬����Ҫȥ��ֵ-0~-180
		   if (py2 < py1)
		   {
			   rad = -rad;
		   }
		   return rad;
}
//��ȡ�뾶����

Vec2 Game::getAngelePosition(double r, double angle){
	Vec2 re;
	re.x = r*cos(angle);
	re.y = r*sin(angle);
		return re;
}




//���Ǽ���
bool Game::onTouchBegan2(Touch *touch, Event *event)
{
	auto target =static_cast<Armature *>(event->getCurrentTarget());
	auto locationInNode = target->convertToNodeSpace(touch->getLocation());
	auto s = target->getContentSize();
	auto rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode))
	{
		
		target->setOpacity(180);
		target->getAnimation()->play("run");
		return true;
	}
	return false;
 }
void Game::onTouchMoved2(Touch *touch, Event *event) {
	auto target = static_cast<Sprite *>(event->getCurrentTarget());
	auto delta = touch->getDelta();
	auto x = target->getPosition().x + delta.x;
	auto y = target->getPosition().y + delta.y;
	target->setPosition(x, y);
}


void Game::onTouchEnded2(Touch *touch, Event *event) {
	auto target = static_cast<Armature *>(event->getCurrentTarget());
	target->setOpacity(255);
	target->getAnimation()->play("hold");

}



void Game::goLeftCallBack(Ref *pLeft)
{
	//this->getChildByTag(11)->runAction(FlipX::create(true));

	//this->getChildByTag(11)->runAction(Repeat::create(MoveBy::create(0.5, Vec2(-20, 0)),5));
	//this->getChildByTag(11)->runAction(Repeat::create(Animate::create(AnimationCache::getInstance()
	//	->getAnimation("walk")),5));
}

void Game::goRightCallBack(Ref *pSender)
{

	//this->getChildByTag(10)->runAction(FlipX::create(false));
	//this->getChildByTag(10)->runAction(Repeat::create(MoveBy::create(0.5, Vec2(20, 0)), 5));
	//this->getChildByTag(10)->runAction(MoveBy::create(0.5, Vec2(10, 0)));

}