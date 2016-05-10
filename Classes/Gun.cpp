#include "Gun.h"

USING_NS_CC;

void Gun::upLevel(){

	if (this->level >= GUN_TOP_LEVEL)
		return;

	int _level = this->level + 1;
	this->setLevel(_level);
}

void Gun::subLevel(){
	if (this->level <= 1)
		return;

	int _level = this->level - 1;
	this->setLevel(_level);
}

void Gun::setLevel(int _level){

	if (this->status != READY)
	{
		return;
	}
	
	this->status = LOADING;

	this->level = _level;
	this->runAction(Sequence::create(ScaleTo::create(0.5, 0.2), 
		CallFuncN::create(CC_CALLBACK_1(Gun::setLevelCallback, this)), 
		ScaleTo::create(0.5, 1), 
		CallFuncN::create(CC_CALLBACK_1(Gun::setReadyCallback, this)), 
		NULL));

}

GUN_STATUS Gun::getStatus()
{
	return this->status;
}

void Gun::setReadyCallback(cocos2d::Ref *pSender){
	this->status = READY;
}

void Gun::setLevelCallback(cocos2d::Ref *pSender){
	
	Texture2D *cache_gun = NULL;
	switch (this->level)
	{
	case 1:
		cache_gun = Director::getInstance()->getTextureCache()->addImage("cannon1.png");
		this->setTexture(cache_gun);
		this->setTextureRect(Rect(12, 0, 54, 66));
		break;
	case 2:
		cache_gun = Director::getInstance()->getTextureCache()->addImage("cannon2.png");
		this->setTexture(cache_gun);
		this->setTextureRect(Rect(12, 0, 54, 66));
		break;
	case 3:
		cache_gun = Director::getInstance()->getTextureCache()->addImage("cannon3.png");
		this->setTexture(cache_gun);
		this->setTextureRect(Rect(12, 0, 54, 66));
		break;
	case 4:
		cache_gun = Director::getInstance()->getTextureCache()->addImage("cannon4.png");
		this->setTexture(cache_gun);
		this->setTextureRect(Rect(12, 0, 54, 70));
		break;
	case 5:
		cache_gun = Director::getInstance()->getTextureCache()->addImage("cannon5.png");
		this->setTexture(cache_gun);
		this->setTextureRect(Rect(12, 0, 54, 70));
		break;
	case 6:
		cache_gun = Director::getInstance()->getTextureCache()->addImage("cannon6.png");
		this->setTexture(cache_gun);
		this->setTextureRect(Rect(12, 0, 54, 78));
		break;
	case 7:
		cache_gun = Director::getInstance()->getTextureCache()->addImage("cannon7.png");
		this->setTexture(cache_gun);
		this->setTextureRect(Rect(12, 0, 54, 80));
		break;
	default:
		break;
	}
}

int Gun::getLevel(){
	return this->level;
}

Gun* Gun::createWithLevel(int _level){
	Gun *gun = new Gun();

	if (gun && gun->init())
	{
		gun->setLevel(_level);

		gun->autorelease();
		return gun;
	}
	CC_SAFE_DELETE(gun);
	return nullptr;
}