#include <string>
#include "Bullet.h"

USING_NS_CC;

using namespace std;

void Bullet::setDis(float x, float y){
	this->dis_x = x;
	this->dis_y = y;
}

Bullet* Bullet::createWithLevel(int _level){
	Bullet *bt = new Bullet(_level);

	if (bt && bt->init())
	{
		bt->autorelease();
		
		return bt;
	}
	CC_SAFE_DELETE(bt);
	return nullptr;
}

bool Bullet::init(){
	
	char buf[100];
	sprintf(buf,"bullet%d.png", this->level);
	return this->initWithFile(string(buf));
	
}

double Bullet::getSpeed()
{
	//可以根据等级动态返回速度，暂时不需要

	return 500;
}

void Bullet::bulletMoveCallback(cocos2d::Ref* pSender){

	Sprite *_sp = (Sprite *)pSender;

	Texture2D *cache_gun = Director::getInstance()->getTextureCache()->addImage("web.png");
	auto web = Sprite::create();
	web->setTexture(cache_gun);
	switch (this->level){
	case 2:
		web->setTextureRect(Rect(14,408, 110, 112));
		break;
	case 3:
		web->setTextureRect(Rect(178, 370, 124, 124));
		break;
	case 4:
		web->setTextureRect(Rect(250, 198, 150, 144));
		break;
	case 5:
		web->setTextureRect(Rect(0, 242, 162, 154));
		break;
	case 6:
		web->setTextureRect(Rect(244, 0, 178, 180));
		break;
	case 7:
		web->setTextureRect(Rect(20, 20, 198, 202));
		break;
	default:
		web->setTextureRect(Rect(330, 374, 91, 86));
		break;
	}
	web->setPosition(_sp->getPosition());
	web->setLocalZOrder(4);
	this->getParent()->addChild(web);

	this->removeFromParent();
}