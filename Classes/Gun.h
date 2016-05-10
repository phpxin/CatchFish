#ifndef __GUN_H__
#define __GUN_H__

#include "cocos2d.h"
#include "Bullet.h"
#define GUN_TOP_LEVEL 7

enum GUN_STATUS{READY=1,LOADING=2};

class Gun : public cocos2d::Sprite
{
private:
	int level;
	GUN_STATUS status;
public:
	Gun() :level(0),status(READY){}
	static Gun* createWithLevel(int _level);
	void setLevel(int _level);
	void upLevel();
	void subLevel();
	void setLevelCallback(cocos2d::Ref *pSender);
	void setReadyCallback(cocos2d::Ref *pSender);
	GUN_STATUS getStatus();
	int getLevel();

	friend class Bullet;
};

#endif // __GUN_H__