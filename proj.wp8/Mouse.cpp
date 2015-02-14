#include "Mouse.h"
#include "GameScene.h"
#include "cocos2d.h"

using namespace std;

USING_NS_CC;

Mouse::Mouse(short id, CCPoint pos) 
{
	this->id = id;
	this->type = getTypeMouse();
	this->animation = getAnimation(type);
	this->animationDead = getAnimationDead(type);
	this->pos = pos;
}

cocos2d::CCSprite* Mouse::createMouse() 
{
	sprintf(str, "mouse_%d-0-0.png", type);
	sprMouse = CCSprite::createWithSpriteFrameName(str);
	sprMouse->setPosition(pos);

	step = WAIT_TO_UP;
	return sprMouse;
}

cocos2d::CCSprite* Mouse::createMouseWithForeverAnimation(bool delay, int newType)
{
	if (newType != -1) 
	{ 
		type = newType;		
		animation = getAnimation(type);
		animationDead = getAnimationDead(type);
		sprintf(str, "mouse_%d-0-0.png", newType); 
	}
	else			sprintf(str, "mouse_%d-0-0.png", type);
	
	sprMouse = CCSprite::createWithSpriteFrameName(str);
	sprMouse->setPosition(pos);
	createAnimationUPandDOWN(delay);
	return sprMouse;
}

void Mouse::createAnimationUPandDOWN(bool delay)
{
	CCArray* animFrames = CCArray::createWithCapacity(animation);
	for (int i = 0; i < animation; i++)
	{
		sprintf(str, "mouse_%d-0-%d.png", type, i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animFrames->addObject(frame);
	}

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
	if (delay) 
	{
		sprMouse->runAction(CCRepeatForever::create(CCSequence::create(CCDelayTime::create(4), 
																	   CCAnimate::create(animation),
																	   CCDelayTime::create(4),
																	   CCAnimate::create(animation)->reverse(),
																	   NULL)));
	}
	else
	{
		sprMouse->runAction(CCRepeatForever::create(CCSequence::create(CCAnimate::create(animation),
																	   CCDelayTime::create(4),
																	   CCAnimate::create(animation)->reverse(),
																	   CCDelayTime::create(4),
																	   NULL)));
	}
}

void Mouse::createAnimationUP() 
{
	CCArray* animFrames = CCArray::createWithCapacity(animation);
	for (int i = 0; i < animation; i++)
	{
		sprintf(str, "mouse_%d-0-%d.png", type, i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animFrames->addObject(frame);
	}

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.025f);
	CCCallFuncN* callFunc = CCCallFuncN::create(this, callfuncN_selector(Mouse::animationUPDone));
	sprMouse->runAction(CCSequence::createWithTwoActions(CCAnimate::create(animation), callFunc));
	
}

void Mouse::animationUPDone(Mouse* pSender)
{
	step = WAIT_TO_DOWN;
	countToDown = 120;
}

void Mouse::createAnimationDOWN() 
{
	// Down Animation
	CCArray* animFrames = CCArray::createWithCapacity(animation);
	for (int i = animation - 1; i >= 0; i--)
	{
		sprintf(str, "mouse_%d-0-%d.png", type, i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animFrames->addObject(frame);
	}

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.025f);
	CCCallFuncN* callFunc = CCCallFuncN::create(this, callfuncN_selector(Mouse::animationDOWNDone));
	sprMouse->runAction(CCSequence::createWithTwoActions(CCAnimate::create(animation), callFunc));

	// Lost heath
	Game::health -= getHealth(type);
	Game::combo = 0;
}

void Mouse::animationDOWNDone(Mouse* pSender)
{
	step = WAIT_TO_UP;
	changeType();

	// Miss effect
	CCSprite* sprMiss = CCSprite::createWithSpriteFrameName("miss.png");
	sprMiss->setPosition(ccp(sprMouse->getContentSize().width / 2, sprMouse->getContentSize().height / 2));
	sprMouse->addChild(sprMiss);

	countToHide = 45;
}

void Mouse::createAnimationDEAD() 
{
	CCArray* animFrames = CCArray::createWithCapacity(animationDead);
	for (int i = 0; i < animationDead; i++)
	{
		sprintf(str, "mouse_%d_dead-0-%d.png", type, i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animFrames->addObject(frame);
	}

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);
	CCCallFuncN* callFunc = CCCallFuncN::create(this, callfuncN_selector(Mouse::animationDEADDone));
	sprMouse->runAction(CCSequence::createWithTwoActions(CCAnimate::create(animation), callFunc));

	Game::power += getPower(type);
	Game::score += getScore(type);
	Game::combo++;
}

void Mouse::animationDEADDone(Mouse* pSender)
{
	step = WAIT_TO_UP;
	changeType();
}

void Mouse::update() 
{
	if (step == WAIT_TO_UP) 
	{
		if (countToUp > 0)
		{
			countToUp--;
			if (countToUp == 0)
			{
				step = GO_UP;
				sprMouse->removeAllChildren();
			}
		}
		
		if (countToHide > 0)
		{
			countToHide--;
			if (countToHide == 0)
			{
				sprMouse->removeAllChildren();
			}
		}
	} 
	else if (step == GO_UP) 
	{
		step = GOING;
		createAnimationUP();
	}
	else if (step == WAIT_TO_DOWN)
	{
		countToDown--;
		if (countToDown == 0)
		{
			step = GO_DOWN;
		}
	}
	else if (step == GO_DOWN) 
	{
		step = GOING;
		createAnimationDOWN();
	}
	else if (step == GO_DEAD)
	{
		step = GOING;
		createAnimationDEAD();
	}
	else if(step == GOING)
	{

	}
}

void Mouse::hideMiss()
{
	sprMouse->removeAllChildren();
}

void Mouse::changeType()
{
	this->type = getTypeMouse();
	this->animation = getAnimation(type);
	this->animationDead = getAnimationDead(type);
}

short Mouse::getPower(short mouseType)
{
	return 5;
}

short Mouse::getHealth(short mouseType)
{
	return 5;
}

short Mouse::getScore(short mouseType)
{
	return 5;
}

short Mouse::getTypeMouse()
{
	return rand() % NB_MOUSE_TYPE + 1;
}

short Mouse::getAnimation(short type)
{
	switch (type)
	{
	case 11:
	case 13:
		return 7;
	default:
		return 6;
	}
}

short Mouse::getAnimationDead(short type)
{
	switch (type)
	{
	case 11:
	case 13:
		return 9;
	default:
		return 4;
	}
}

short Mouse::getID() 
{
	return id;
}