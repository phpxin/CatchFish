#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"


class Bullet : public cocos2d::Sprite
{
private:
	int level;
public:
	float dis_x;
	float dis_y;
	Bullet(int _level) :dis_x(0), dis_y(0), level(_level){}
	static Bullet *createWithLevel(int _level);
	void setDis(float x, float y);
	void bulletMoveCallback(cocos2d::Ref* pSender);
	virtual bool init() override;
	double getSpeed();
};

#endif // __BULLET_H__