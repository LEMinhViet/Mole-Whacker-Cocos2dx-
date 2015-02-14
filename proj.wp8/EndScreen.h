#ifndef __END_SCENE_H__
#define __END_SCENE_H__

#include "cocos2d.h"

class End : public cocos2d::CCLayer
{
private:
	cocos2d::CCSize visibleSize;
	cocos2d::CCPoint origin;

	cocos2d::CCSprite* sprGameBackground;
	cocos2d::CCSprite* sprGameResult;

	cocos2d::CCSpriteBatchNode* _endBatchNode;

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event); 
	
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	void update(float dt);
	void pressOK(cocos2d::CCObject* pSender);
	void pressReplay(cocos2d::CCObject* pSender);
	void pressShare(cocos2d::CCObject* pSender);
	void animationDone();

	cocos2d::CCMenuItemSprite* createMenuButton(char* img, char* pressed_img, cocos2d::SEL_MenuHandler handler, float x, float y, float scale);

	// implement the "static node()" method manually
	CREATE_FUNC(End);
};

#endif // __END_SCENE_H__
