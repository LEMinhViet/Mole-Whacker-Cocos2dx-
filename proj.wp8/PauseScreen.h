#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"

#define GAME_LAYER 1

class Pause : public cocos2d::CCLayer
{
private:
	cocos2d::CCSize visibleSize;
	cocos2d::CCPoint origin;

	cocos2d::CCMenu* pMenu;
	cocos2d::CCSprite* sprGameBackground;
	cocos2d::CCSprite* sprGameResult;

	cocos2d::CCSpriteBatchNode* _pauseBatchNode;

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

	void update(float dt);
	void pressMenu(cocos2d::CCObject* pSender);
	void pressNew(cocos2d::CCObject* pSender);
	void pressExit(cocos2d::CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(Pause);
};

#endif // __PAUSE_SCENE_H__
