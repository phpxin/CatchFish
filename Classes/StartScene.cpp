#include "StartScene.h"
#include "BattleScene.h"

USING_NS_CC;

Scene* Start::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = Start::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Start::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto menuStart = MenuItemFont::create("Start game", CC_CALLBACK_1(Start::menuBattleCallback, this));
	menuStart->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	auto menuExit = MenuItemFont::create("Exit game", CC_CALLBACK_1(Start::menuCloseCallback, this));
	menuExit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
	
	Menu *mn = Menu::create(menuStart, menuExit, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);
    
    return true;
}

void Start::menuBattleCallback(Ref* pSender)
{
	auto scene = Battle::createScene();
	Director::getInstance()->replaceScene(scene);
}

void Start::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
