#include "HelpScreen.h"
#include "WhackAMole.h"
#include "Mouse.h"
#include <iostream>

using namespace std;

USING_NS_CC;

CCScene* Help::scene()
{
	CCScene *scene = CCScene::create();

	Help *layer = Help::create();

	scene->addChild(layer);

	scene->setTag(WhackAMole::kHelpScene);

	return scene;
}


bool Help::init()
{
	////////////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	origin = CCDirector::sharedDirector()->getVisibleOrigin();

	///////////////////////////////////
	// 2. Background
	sprMenuBackground = CCSprite::create("Images/m_bg.png");
	sprMenuBackground->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprMenuBackground, 0);

	sprMenuLogo = CCSprite::create("Images/help.png");
	sprMenuLogo->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - sprMenuLogo->getContentSize().height));
	this->addChild(sprMenuLogo, 0);

	sprMenuHelp = CCSprite::create("Images/h_content.png");
	sprMenuHelp->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + sprMenuHelp->getContentSize().height / 24));
	this->addChild(sprMenuHelp);

	return true;
}
