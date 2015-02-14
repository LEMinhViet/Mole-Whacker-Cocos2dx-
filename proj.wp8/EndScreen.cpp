#include "HelloWorldScene.h"
#include "GameScene.h"
#include "EndScreen.h"
#include "WhackAMole.h"
#include "cocos2d.h"
#include <iostream>

using namespace std;

USING_NS_CC;

// on "init" you need to initialize your instance
bool End::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	origin = CCDirector::sharedDirector()->getVisibleOrigin();


	//////////////////////////////////////////////////////////////////////////////////////////
	// Background
	sprGameBackground = CCSprite::create("Images/m_blackBg.png");
	sprGameBackground->setPosition(ccp(visibleSize.width / 2 + origin.x, sprGameBackground->getContentSize().height / 2 + origin.y));
	this->addChild(sprGameBackground, 2);

	sprGameResult = CCSprite::create("Images/g_result.png");
	sprGameResult->setPosition(ccp(visibleSize.width / 2 + origin.x, 0));
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(End::animationDone));
	sprGameResult->runAction(CCSequence::createWithTwoActions(CCEaseBackOut::create(CCMoveTo::create(0.5f, ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y))), callFunc));
	this->addChild(sprGameResult, 2);

	this->schedule(schedule_selector(End::update));

	return true;
}

void End::update(float dt)
{
}

void End::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
}

CCMenuItemSprite* End::createMenuButton(char* img, char* pressed_img, cocos2d::SEL_MenuHandler handler, float x, float y, float scale)
{
	CCMenuItemSprite *item = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(img),
													CCSprite::createWithSpriteFrameName(pressed_img),
													this,
													handler);
	if (x < 0) 
	{
		item->setScale(scale);
		item->setPosition(ccp(sprGameResult->getPositionX() + sprGameResult->getContentSize().width / 2 + item->getContentSize().width * x * scale,
			sprGameResult->getPositionY() - sprGameResult->getContentSize().height / 2 + item->getContentSize().height * y * scale));
	}
	else
	{
		item->setScale(scale);
		item->setPosition(ccp(sprGameResult->getPositionX() - sprGameResult->getContentSize().width / 2 + item->getContentSize().width * x * scale,
			sprGameResult->getPositionY() - sprGameResult->getContentSize().height / 2 + item->getContentSize().height * y * scale));
	}
	
	return item;
}

void End::pressOK(CCObject* pSender)
{
	Game::reset();

	CCTransitionScene* trans = CCTransitionSlideInR::create(0.3f, Game::scene());
	CCDirector::sharedDirector()->replaceScene(trans);
}

void End::pressReplay(CCObject* pSender)
{
	Game::reset();

	CCTransitionScene* trans = CCTransitionSlideInR::create(0.3f, HelloWorld::scene());
	CCDirector::sharedDirector()->replaceScene(trans);
}

void End::pressShare(CCObject* pSender)
{
	
}

void End::animationDone()
{
	CCMenuItemSprite* pOkItem = this->createMenuButton("okbutton-0.png",
												"okbutton-1.png",
												menu_selector(End::pressReplay),
												-2, 1, 1);
	CCMenuItemSprite* pShareItem = this->createMenuButton("shareButton-0.png",
												"shareButton-1.png",
												menu_selector(End::pressShare),
												2.2f, 1, 1);

	CCMenuItemSprite* pReplayItem = this->createMenuButton("replayButton-0.png",
												"replayButton-1.png",
												menu_selector(End::pressOK),
												2, 1, 1);

	CCMenu* pMenu = CCMenu::create(pOkItem, pShareItem, pReplayItem,  NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, 3);

	int score = 1000;
	char str[100];
	sprintf(str, "Score : %d", score);
	CCLabelBMFont* lblScore = CCLabelBMFont::create(str, "fonts/font.fnt", 720);
	lblScore->setPosition(ccp(sprGameResult->getPositionX(), sprGameResult->getPositionY()));
	lblScore->setScale(1.5f);
	addChild(lblScore, 3);

	vector<CCSprite*> sprStars;
	sprStars.push_back(CCSprite::createWithSpriteFrameName("star-1.png"));
	sprStars[0]->setPosition(ccp(sprGameResult->getPositionX() - sprStars[0]->getContentSize().width * 2, sprGameResult->getPositionY() - sprStars[0]->getContentSize().height * 2));
	addChild(sprStars[0], 4);

	sprStars.push_back(CCSprite::createWithSpriteFrameName("star-1.png"));
	sprStars[1]->setPosition(ccp(sprGameResult->getPositionX() - sprStars[1]->getContentSize().width, sprGameResult->getPositionY() - sprStars[1]->getContentSize().height * 2));
	addChild(sprStars[1], 4);

	sprStars.push_back(CCSprite::createWithSpriteFrameName("star-1.png"));
	sprStars[2]->setPosition(ccp(sprGameResult->getPositionX(), sprGameResult->getPositionY() - sprStars[2]->getContentSize().height * 2));
	addChild(sprStars[2], 4);

	sprStars.push_back(CCSprite::createWithSpriteFrameName("star-1.png"));
	sprStars[3]->setPosition(ccp(sprGameResult->getPositionX() + sprStars[3]->getContentSize().width, sprGameResult->getPositionY() - sprStars[3]->getContentSize().height * 2));
	addChild(sprStars[3], 4);

	sprStars.push_back(CCSprite::createWithSpriteFrameName("star-1.png"));
	sprStars[4]->setPosition(ccp(sprGameResult->getPositionX() + sprStars[4]->getContentSize().width * 2, sprGameResult->getPositionY() - sprStars[4]->getContentSize().height * 2));
	addChild(sprStars[4], 4);
}