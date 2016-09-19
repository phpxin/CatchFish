#include "BattleScene.h"
#include <cmath>
#include <iostream>
#include "Bullet.h"

USING_NS_CC;

Scene* Battle::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = Battle::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void Battle::createFish()
{
	Vector<SpriteFrame *> sfv;

	SpriteFrame *sf = SpriteFrame::create("fish1.png", Rect(0,0,55,26));
	sfv.pushBack(sf);

	SpriteFrame *sf1 = SpriteFrame::create("fish1.png", Rect(0, 36, 55, 26));
	sfv.pushBack(sf1);

	SpriteFrame *sf2 = SpriteFrame::create("fish1.png", Rect(0, 73, 55, 26));
	sfv.pushBack(sf2);

	SpriteFrame *sf3 = SpriteFrame::create("fish1.png", Rect(0, 110, 55, 26));
	sfv.pushBack(sf3);

	Animation *fishRun = Animation::create();
	fishRun->initWithSpriteFrames(sfv, 0.5);
	

	Animate *run = Animate::create(fishRun);
	//run->

	Sprite *fish = Sprite::create();
	fish->initWithSpriteFrame(sf);
	fish->setPosition(ccp(200, 200));
	this->addChild(fish);

	fish->runAction(RepeatForever::create(run));
	
}

// on "init" you need to initialize your instance
bool Battle::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(Battle::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    auto sprite = Sprite::create("game_bg_2_hd.jpg");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	sprite->setLocalZOrder(1);
    this->addChild(sprite, 0);


	// init touch event
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Battle::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Battle::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Battle::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// menus
	Texture2D *cache = Director::getInstance()->getTextureCache()->addImage("bottom.png");
	auto platform = Sprite::create();
	platform->setTexture(cache);
	platform->setTextureRect(Rect(0,0,765,72));
	platform->setPosition(Vec2(visibleSize.width / 2 - 45, 0 + platform->getContentSize().height / 2));
	platform->setLocalZOrder(2);
	this->addChild(platform);

	auto gunUpLevel = MenuItemImage::create();
	gunUpLevel->setNormalSpriteFrame(SpriteFrame::createWithTexture(cache, Rect(46,74,38,28)));
	gunUpLevel->setSelectedSpriteFrame(SpriteFrame::createWithTexture(cache, Rect(2, 74, 38, 28)));
	gunUpLevel->setCallback(CC_CALLBACK_1(Battle::gunUpLevelCallback, this));
	gunUpLevel->setScale(0.6);
	//gunUpLevel->setPosition(Vec2(visibleSize.width / 2 - 250, 15));
	gunUpLevel->setPosition(Vec2(0 - (gunUpLevel->getContentSize().width * 0.6 / 2), 0));

	auto gunSubLevel = MenuItemImage::create();
	gunSubLevel->setNormalSpriteFrame(SpriteFrame::createWithTexture(cache, Rect(134, 74, 38, 28)));
	gunSubLevel->setSelectedSpriteFrame(SpriteFrame::createWithTexture(cache, Rect(90, 74, 38, 28)));
	gunSubLevel->setCallback(CC_CALLBACK_1(Battle::gunSubLevelCallback, this));
	gunSubLevel->setScale(0.6);
	//gunSubLevel->setPosition(Vec2(visibleSize.width / 2 - 224, 15));
	gunSubLevel->setPosition(Vec2(0 + (gunSubLevel->getContentSize().width * 0.6 / 2), 0));

	auto gunMenu = Menu::create(gunUpLevel, gunSubLevel, NULL);
	//gunMenu->setPosition(Vec2::ZERO);
	gunMenu->setPosition(Vec2(visibleSize.width / 2 - 238, 13));
	//gunMenu->setScale(0.6);
	gunMenu->setLocalZOrder(3);
	this->addChild(gunMenu);

	// gun
	this->gun = Gun::createWithLevel(1);
	this->gun->setPosition(Vec2(visibleSize.width / 2, 10 + platform->getContentSize().height / 2));
	this->gun->setLocalZOrder(4);
	this->addChild(this->gun);


	auto ps = ParticleRain::create();
	ps->setPosition(Vec2(visibleSize.width/2, visibleSize.height));
	this->addChild(ps);

	this->createFish();

    return true;
}

void Battle::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){


}
void Battle::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
	//this->gun->setPosition(Vec2(touches[0]->getLocation().x, touches[0]->getLocation().y));


}

void Battle::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){

	float ax = this->gun->getPosition().x;
	float ay = this->gun->getPosition().y;

	float bx = touches[0]->getLocation().x;
	float by = touches[0]->getLocation().y;

	this->touch_x = bx;
	this->touch_y = by;

	if (by < ay)
		return;

	float sum = (bx - ax) / (by - ay);
	float ss = atan(sum);
	ss = ss * 180 / 3.14;

	float rot = this->gun->getRotation();
	float speed = (abs(ss - rot)) / 200;
	//this->gun->runAction(RotateTo::create(speed, ss));

	this->gun->stopAllActions();
	this->gun->runAction(Sequence::create(RotateTo::create(speed, ss), CallFuncN::create(CC_CALLBACK_1(Battle::gunMoveCallback, this)), NULL));
}

void Battle::gunMoveCallback(cocos2d::Ref* pSender){
	
	if (READY != this->gun->getStatus())
		return;

	auto bullet = Bullet::createWithLevel(this->gun->getLevel());
	bullet->setPosition(this->gun->getPosition());
	bullet->setRotation(this->gun->getRotation());
	bullet->setLocalZOrder(1);
	bullet->setDis(this->touch_x, this->touch_y);
	this->addChild(bullet);

	double _x = abs(this->gun->getPosition().x - this->touch_x);
	double _y = abs(this->gun->getPosition().y - this->touch_y);

	double _x_s = pow(_x, 2);
	double _y_s = pow(_y, 2);

	//long double _r = pow(_x_s + _y_s, 1 / 2);
	double _r = sqrt(_x_s + _y_s);
	auto buttle_to = MoveTo::create( _r/bullet->getSpeed(), cocos2d::Point(this->touch_x, this->touch_y));
	bullet->runAction(Sequence::create(buttle_to, CallFuncN::create(CC_CALLBACK_1(Bullet::bulletMoveCallback, bullet)), NULL));

}

void Battle::gunUpLevelCallback(cocos2d::Ref *pSender){
	this->gun->upLevel();
}

void Battle::gunSubLevelCallback(cocos2d::Ref *pSender){
	this->gun->subLevel();
}

void Battle::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
