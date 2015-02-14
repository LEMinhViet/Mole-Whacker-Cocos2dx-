#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "cocos2d.h"

class Mouse : public cocos2d::CCObject
{
private:
	short id;
	short type;
	short animation;
	short animationDead;

	short step;

	short countToDown;
	short countToUp;
	short countToHide;

	char str[100];
	
	cocos2d::CCPoint pos;
	cocos2d::CCSprite* sprMouse;

	void hideMiss();

	short getPower(short mouseType);
	short getHealth(short mouseType);
	short getScore(short mouseType);

public:
	static const short NB_MOUSE_TYPE = 13;

	static const short UP = 0;
	static const short DOWN = 1;
	static const short DEAD = 2;

	static const short WAIT_TO_UP = 0;
	static const short GO_UP = 1;
	static const short WAIT_TO_DOWN = 2;
	static const short GO_DOWN = 3;
	static const short GO_DEAD = 4;
	static const short GOING = 5;

	Mouse(short id, cocos2d::CCPoint pos);
	cocos2d::CCSprite* createMouse();
	cocos2d::CCSprite* Mouse::createMouseWithForeverAnimation(bool delay, int type);
	void createAnimationUP();
	void animationUPDone(Mouse* pSender);
	void createAnimationDOWN();
	void animationDOWNDone(Mouse* pSender);
	void createAnimationDEAD();
	void animationDEADDone(Mouse* pSender);
	void Mouse::createAnimationUPandDOWN(bool delay);
	void update();
	void changeType();

	bool isUp() { return step != WAIT_TO_UP || countToUp > 0; };
	
	short getTypeMouse();
	short getAnimation(short type);
	short getAnimationDead(short type);
	short getID();

	short getCountToUp() { return countToUp; };
	void setCountToUp(short value) { countToUp = value; };
	void goDead() {
		if (step != GOING) {
			step = GO_DEAD;		update();
		}
	};

	cocos2d::CCSprite* getSprMouse() { return sprMouse; };
};

#endif