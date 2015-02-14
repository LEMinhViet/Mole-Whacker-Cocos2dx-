#include "HelloWorldScene.h"
#include "WhackAMole.h"
#include "Mouse.h"
#include "GameScene.h"
#include "HelpScreen.h"
#include <iostream>

using namespace std;

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
	
	// add layer as a child to scene
    scene->addChild(layer);

	scene->setTag(WhackAMole::kMenuScene); 

	// return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	srand(time(NULL));
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	iState = MENU;
    
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	//////////////////////////////////////////////////////////////////////////////////////////
    // 2. Create some Buttons. a button is an autorelease object
	pRateItem = createMenuButton("btn_Rate.png",
								"btn_Rate_Selected.png", 
								menu_selector(HelloWorld::showRate),
								0.2f,
								0.2f,
								0.4f);
	pRushItem = createMenuButton("btn_Play.png",
								"btn_Play_Selected.png", 
								menu_selector(HelloWorld::showRushGame),
								0.5f,
								0.2f,
								0.8f);
	pHelpItem = createMenuButton("btn_Help.png",
								"btn_Help_Selected.png",
								menu_selector(HelloWorld::showHelp),
								0.81f,
								0.2f,
								0.6f);

    // create menu, it's an autorelease object
	pMenu = CCMenu::create(pRateItem, pRushItem, pHelpItem, NULL);
    pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

    //////////////////////////////////////////////////////////////////////////////////////////
    // 3. Menu background
    sprMenuBackground = CCSprite::create("Images/m_bg.png");
	sprMenuBackground->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprMenuBackground, 0);

	sprMenuLogo = CCSprite::create("Images/m_logo.png");
	sprMenuLogo->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - sprMenuLogo->getContentSize().height * 0.75));
	sprMenuLogo->setScale(0);
	sprMenuLogo->runAction(CCScaleTo::create(1.0f, 1.0f));
	this->addChild(sprMenuLogo);

	// Some Animations 
	Mouse rateMouse(-1, ccp(pRateItem->getPositionX(), pRateItem->getPositionY() + pRateItem->getContentSize().height * 3 / 2));
	this->addChild(rateMouse.createMouseWithForeverAnimation(false, 12), 3);

	Mouse rushMouse(-1, ccp(pRushItem->getPositionX(), pRushItem->getPositionY() + pRushItem->getContentSize().height * 3 / 2));
	this->addChild(rushMouse.createMouseWithForeverAnimation(true, -1), 3);

	Mouse helpMouse(-1, ccp(pHelpItem->getPositionX(), pHelpItem->getPositionY() + pHelpItem->getContentSize().height * 3 / 2));
	this->addChild(helpMouse.createMouseWithForeverAnimation(false, 3), 3);

	// Some Infos
	lblInfo = CCLabelBMFont::create("Ubiduck 2014 - v1.0", "fonts/font.fnt", 720);
	lblInfo->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + lblInfo->getContentSize().height));
	lblInfo->setScale(1.0f);
	this->addChild(lblInfo, 3);
	
	best = 1000;
	sprintf(str, "Best : %d", best);
	lblRushScore = CCLabelBMFont::create(str, "fonts/font.fnt", 720);
	lblRushScore->setPosition(ccp(pRushItem->getPositionX(), pRushItem->getPositionY() - pRushItem->getContentSize().height * 0.75));
	this->addChild(lblRushScore, 3);

	this->schedule(schedule_selector(HelloWorld::update));
    
    return true;
}

CCMenuItemSprite *HelloWorld::createMenuButton(char* img, char* pressed_img, cocos2d::SEL_MenuHandler handler, float x, float y, float scale)
{
	CCMenuItemSprite *item = CCMenuItemSprite::create(
										CCSprite::createWithSpriteFrameName(img), 
										CCSprite::createWithSpriteFrameName(pressed_img), 
										this,
										handler);
	item->setScale(scale);

	item->setPosition(ccp(origin.x + visibleSize.width * x, origin.y + visibleSize.height * y));
	
	return item;
}

void HelloWorld::update (float dt) 
{

}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::showRate(CCObject* pSender)
{
	CCTransitionScene* trans = CCTransitionSlideInL::create(0.3f, Game::scene());
	CCDirector::sharedDirector()->replaceScene(trans);
}

void HelloWorld::showRushGame(CCObject* pSender)
{
	CCTransitionScene* trans = CCTransitionSlideInL::create(0.3f, Game::scene());
	CCDirector::sharedDirector()->replaceScene(trans);
}

void HelloWorld::showHelp(CCObject* pSender)
{
	CCTransitionScene* trans = CCTransitionSlideInL::create(0.3f, Help::scene());
	CCDirector::sharedDirector()->replaceScene(trans);
}
