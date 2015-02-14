#include "PauseScreen.h"
#include "GameScene.h"
#include "WhackAMole.h"
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include <iostream>

using namespace std;

USING_NS_CC;

// on "init" you need to initialize your instance
bool Pause::init()
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
	this->addChild(sprGameBackground, 5);

	CCMenuItemSprite *pResumeItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("resumeButton-0.png"),
													CCSprite::createWithSpriteFrameName("resumeButton-1.png"),
													this,
													menu_selector(Pause::pressMenu));
	pResumeItem->setPosition(ccp(origin.x + pResumeItem->getContentSize().width, origin.y + visibleSize.height - pResumeItem->getContentSize().height));

	CCMenuItemSprite *pNewItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("replay.png"),
															CCSprite::createWithSpriteFrameName("replay.png"),
															this,
															menu_selector(Pause::pressNew));
	pNewItem->setPosition(ccp(origin.x + pNewItem->getContentSize().width * 0.7, origin.y + pNewItem->getContentSize().height * 2));
	pNewItem->setScale(1.5f, 1.5f);

	CCMenuItemSprite *pExitItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("exit.png"),
															CCSprite::createWithSpriteFrameName("exit.png"),
															this,
															menu_selector(Pause::pressExit));
	pExitItem->setPosition(ccp(origin.x + visibleSize.width - pExitItem->getContentSize().width * 0.6, origin.y + pExitItem->getContentSize().height * 2));
	pExitItem->setScale(1.5f, 1.5f);

	pMenu = CCMenu::create(pResumeItem, pNewItem, pExitItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 5);
	
	this->schedule(schedule_selector(Pause::update));

	return true;
}

void Pause::update(float dt)
{
}

void Pause::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
}

void Pause::pressMenu(cocos2d::CCObject* pSender)
{
	Game::reset();

	CCDirector::sharedDirector()->getRunningScene()->removeChild(this);
	CCNode* node = CCDirector::sharedDirector()->getRunningScene()->getChildByTag(GAME_LAYER);
	Game* game = dynamic_cast<Game*>(node);
	game->resume();
}

void Pause::pressNew(cocos2d::CCObject* pSender)
{
	Game::reset();

	CCTransitionScene* trans = CCTransitionSlideInR::create(0.3f, Game::scene());
	CCDirector::sharedDirector()->replaceScene(trans);
}

void Pause::pressExit(cocos2d::CCObject* pSender)
{
	// TODO save game
	CCTransitionScene* trans = CCTransitionSlideInR::create(0.3f, HelloWorld::scene());
	CCDirector::sharedDirector()->replaceScene(trans);
}