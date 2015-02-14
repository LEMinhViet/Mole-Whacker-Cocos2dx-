#include "GameScene.h"
#include "PauseScreen.h"
#include "EndScreen.h"
#include "WhackAMole.h"
#include "MouseManager.h"
#include "DataManager.h"
#include <iostream>

using namespace std;

USING_NS_CC;

int Game::health = MAX_HEALTH;
int Game::power = 0;
int Game::score = 0;
int Game::combo = 0;

CCScene* Game::scene()
{
    // 'scene' is an autorelease object
	CCScene* scene = CCScene::create();
    
    // 'layer' is an autorelease object
	Game *layer = Game::create();

	layer->setTouchEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(layer, 0);

	// add layer as a child to scene
	scene->addChild(layer, 1, GAME_LAYER);

	scene->setTag(WhackAMole::kGameScene);

	// return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
	char keyName[] = "score";
	//DataManager::setObjectForKey(keyName, ccs("123456"));
	CCLog("SCORE : %s", DataManager::getObjectForKey(keyName)->getCString());

	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }


	// Set some values
	deltaTime = 0;
	iType = COUNT_DOWN_LAYER;
	
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    origin = CCDirector::sharedDirector()->getVisibleOrigin();

	this->mouseManager = new MouseManager (this, origin, visibleSize, 0);
	this->mouseManager->createMouses();
		
	//////////////////////////////////////////////////////////////////////////////////////////
	// 2. Pause Layer
	CCMenuItemSprite *pPauseItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("pauseButton-0.png"),
															CCSprite::createWithSpriteFrameName("pauseButton-1.png"),
															this,
															menu_selector(Game::pressPause));
	pPauseItem->setPosition(ccp(origin.x + pPauseItem->getContentSize().width, origin.y + visibleSize.height - pPauseItem->getContentSize().height));
	this->addChild(pPauseItem, 5);

	pMenu = CCMenu::create(pPauseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 5);
	
	//////////////////////////////////////////////////////////////////////////////////////////
    // 3. GAME background
    sprGameSky = CCSprite::create("Images/g_sky.jpg");
	sprGameSky->setPosition(ccp(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height - sprGameSky->getContentSize().height / 2));
	this->addChild(sprGameSky, 0);

	sprGameBackground = CCSprite::create("Images/g_bg.png");
	sprGameBackground->setPosition(ccp(visibleSize.width / 2 + origin.x, sprGameBackground->getContentSize().height / 2 + origin.y));
	this->addChild(sprGameBackground, 0);	

	//////////////////////////////////////////////////////////////////////////////////////////
	// 4. GAUSS 
	sprGaussFg = CCSprite::createWithSpriteFrameName("gaussFg.png");
	sprGaussFg->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + sprGaussFg->getContentSize().height / 2));
	this->addChild(sprGaussFg, 2);

	sprHealthBg = CCSprite::createWithSpriteFrameName("healthBg.png");
	procHealth = CCProgressTimer::create(sprHealthBg);
	procHealth->setPosition(ccp(origin.x + visibleSize.width / 2 - sprHealthBg->getContentSize().width, origin.y + sprGaussFg->getContentSize().height * 0.25));
	procHealth->setType(CCProgressTimerType::kCCProgressTimerTypeBar);
	procHealth->setAnchorPoint(ccp(0, 0));
	procHealth->setMidpoint(ccp(0, 0));
	procHealth->setBarChangeRate(ccp(1, 0));
	procHealth->setPercentage(Game::health);
	this->addChild(procHealth, 1);

	sprPowerBg = CCSprite::createWithSpriteFrameName("powerBg.png");
	procPower = CCProgressTimer::create(sprPowerBg);
	procPower->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + sprGaussFg->getContentSize().height * 0.25));
	procPower->setType(CCProgressTimerType::kCCProgressTimerTypeBar);
	procPower->setAnchorPoint(ccp(0, 0));
	procPower->setMidpoint(ccp(0, 0));
	procPower->setBarChangeRate(ccp(1, 0));
	procPower->setPercentage(Game::power);
	this->addChild(procPower, 1);
	
	//////////////////////////////////////////////////////////////////////////////////////////
	// 5. INFOS
	lblScore = CCLabelBMFont::create("Score : 0", "fonts/font.fnt", 720);
	lblScore->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - lblScore->getContentSize().height * 2));
	lblScore->setScale(1.0f);
	this->addChild(lblScore, 3);

	lblCombo = CCLabelBMFont::create("COMBO x ", "fonts/font.fnt", 720);
	lblCombo->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - lblCombo->getContentSize().height * 4));
	lblCombo->setVisible(false);
	lblCombo->setScale(1.2f);
	this->addChild(lblCombo, 3);
	
	//////////////////////////////////////////////////////////////////////////////////////////
	// 6. COUNT DOWN Layer
	update(0);
	resume();

	this->schedule(schedule_selector(Game::update));
    
    return true;
}

void Game::update(float dt) 
{
	if (iType == GAME_LAYER)
	{
		this->mouseManager->updateMouses();
		updateGaussBar();

		if (Game::health <= 0)
		{
			end();
		}
	}
}

void Game::start()
{
	iType = GAME_LAYER;
	this->removeChild(sprCountDown);

	this->setTouchEnabled(true);
}

void Game::resume()
{
	iType = COUNT_DOWN_LAYER;
	sprCountDown = CCSprite::createWithSpriteFrameName("3.png");
	CCArray* animFrames = CCArray::createWithCapacity(4);

	animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("3.png"));
	animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("2.png"));
	animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("1.png"));
	animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("fight.png"));

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 1.0f);
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Game::start));
	sprCountDown->runAction(CCSequence::createWithTwoActions(CCAnimate::create(animation), callFunc));
	sprCountDown->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(sprCountDown, 6);
}

void Game::end()
{
	End* endLayer = End::create();
	CCDirector::sharedDirector()->getRunningScene()->addChild(endLayer, 5, END_LAYER);
	iType = END_LAYER;

	this->setTouchEnabled(false);
}

void Game::reset()
{
	Game::health = MAX_HEALTH;
	Game::power = 0;
	Game::score = 0;
	Game::combo = 0;
}

void Game::updateGaussBar()
{
	procHealth->setPercentage(Game::health);
	procPower->setPercentage(Game::power);
}

int Game::getType()
{
	return iType;
}

void Game::setType(int value)
{
	iType = value;
}

void Game::pressPause(cocos2d::CCObject* pSender)
{
	if (iType == COUNT_DOWN_LAYER) 
	{
		this->removeChild(sprCountDown);
	}
	
	Pause* pauseLayer = Pause::create();
	CCDirector::sharedDirector()->getRunningScene()->addChild(pauseLayer, 5, PAUSE_LAYER);
	iType = PAUSE_LAYER;

	this->setTouchEnabled(false);
}

void Game::ccTouchesBegan(CCSet* touches, CCEvent* event)
{	
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	this->mouseManager->ccTouchesBegan(location, event);
	
	// Effect
	showTouchEffect(location);

	// Stats
	udpateComboText();
	updateScoreText();
}

void Game::showTouchEffect(CCPoint location)
{
	// HAMMER ANIMATION
	CCSprite* sprHammer = CCSprite::createWithSpriteFrameName("hammer_0.png");
	CCArray* animFrames = CCArray::createWithCapacity(3);

	animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hammer_0.png"));
	animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hammer_1.png"));
	animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hammer_2.png"));

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.05f);
	CCCallFuncND* callFuncND = CCCallFuncND::create(this, callfuncND_selector(Game::hideEffect), (void*)sprHammer);
	sprHammer->runAction(CCSequence::createWithTwoActions(CCAnimate::create(animation), callFuncND));
	sprHammer->setPosition(location);
	this->addChild(sprHammer, 5);

	// EFFECT ANIMATION
	CCSprite* sprEffect = CCSprite::createWithSpriteFrameName("hitEffect-0.png");
	animFrames = CCArray::createWithCapacity(5);

	animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hitEffect-0.png"));
	animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hitEffect-1.png"));
	animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hitEffect-2.png"));
	animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hitEffect-3.png"));
	animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hitEffect-4.png"));

	animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
	callFuncND = CCCallFuncND::create(this, callfuncND_selector(Game::hideEffect), (void*)sprEffect);
	sprEffect->runAction(CCSequence::createWithTwoActions(CCAnimate::create(animation), callFuncND));
	sprEffect->setPosition(location);
	this->addChild(sprEffect, 4);
}

void Game::udpateComboText()
{
	if (combo > 1)
	{
		sprintf(strCombo, "COMBO x %d", combo);
		lblCombo->setString(strCombo);
		lblCombo->runAction(CCSequence::createWithTwoActions(CCScaleTo::create(0.25f, 1.4f), CCScaleTo::create(0.15f, 1.0f)));
		lblCombo->setVisible(true);
	}
	else
	{
		lblCombo->setVisible(false);
	}
}

void Game::updateScoreText()
{	
	sprintf(strScore, "Score : %d", score);
	lblScore->setString(strScore);
}

void Game::hideHammer(CCNode* pSender, void* sprHammer)
{
	this->removeChild((CCSprite*)sprHammer);
}

void Game::hideEffect(CCNode* pSender, void* sprEffect)
{
	this->removeChild((CCSprite*)sprEffect);
}