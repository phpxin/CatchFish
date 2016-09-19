#ifndef __Battle_SCENE_H__
#define __Battle_SCENE_H__

#include "cocos2d.h"
#include "Gun.h"

class Battle : public cocos2d::Layer
{
private:
	float touch_x;
	float touch_y;
	Gun *gun;

public:
	Battle() : touch_x(0.0), touch_y(0.0) {};

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	// gun up level
	void gunUpLevelCallback(cocos2d::Ref *pSender);
	void gunSubLevelCallback(cocos2d::Ref *pSender);

	void gunMoveCallback(cocos2d::Ref* pSender);

	void createFish();

	// touch event
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    // implement the "static create()" method manually
	CREATE_FUNC(Battle);
};

#endif // __Battle_SCENE_H__
