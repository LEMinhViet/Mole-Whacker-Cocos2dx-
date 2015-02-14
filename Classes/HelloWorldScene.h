#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
private:

	// States
	static const int MENU = 0;
	static const int INFO = 1;
	static const int MODE = 2;
	
	int iState;
	int best;
	char str[10];

	cocos2d::CCLabelBMFont *lblInfo;
	cocos2d::CCLabelBMFont *lblRushScore;

	cocos2d::CCMenu* pMenu;
	cocos2d::CCSprite* sprMenuBackground;
	cocos2d::CCSprite* sprMenuLogo;
	cocos2d::CCSprite* sprMenuPicture; 

	cocos2d::CCSpriteBatchNode* _gameBatchNode;
	cocos2d::CCSpriteBatchNode* _mouseBatchNode;

	cocos2d::CCMenuItemSprite* pRushItem;
	cocos2d::CCMenuItemSprite* pRateItem;
	cocos2d::CCMenuItemSprite* pHelpItem;
    
	cocos2d::CCMenuItemSprite *createMenuButton(char* img, 
												char* pressed_img, 
												cocos2d::SEL_MenuHandler, 
												float x, 
												float y,
												float scale);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	cocos2d::CCSize visibleSize;
    cocos2d::CCPoint origin;

	// a selector callback
    void menuCloseCallback(CCObject* pSender);
	void HelloWorld::showRate(CCObject* pSender);
	void HelloWorld::showRushGame(CCObject* pSender);
	void HelloWorld::showHelp(CCObject* pSender);

	void update(float dt);

	// implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
