#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#define GAME_LAYER 1
#define PAUSE_LAYER 2
#define COUNT_DOWN_LAYER 3
#define END_LAYER 4


#include "cocos2d.h"

class MouseManager;

class Game : public cocos2d::CCLayer
{
private:
	int deltaTime;
	char strCombo[100];
	char strScore[100];

	cocos2d::CCMenu* pMenu;
	cocos2d::CCSprite* sprGameBackground;
	cocos2d::CCSprite* sprGameSky;
	cocos2d::CCSprite* sprCountDown;
	cocos2d::CCSprite* sprGaussFg;
	cocos2d::CCSprite* sprHealthBg;
	cocos2d::CCSprite* sprPowerBg;

	cocos2d::CCProgressTimer* procHealth;
	cocos2d::CCProgressTimer* procPower;

	cocos2d::CCLabelBMFont* lblScore;
	cocos2d::CCLabelBMFont* lblCombo;

	MouseManager* mouseManager;

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
	static void reset();

	static const int RUSH = 0;
	static const int LEVEL = 1;

	static const int MAX_POWER = 100;
	static const int MAX_HEALTH = 100;

	static int health;
	static int power;
	static int score;
	static int combo;
	
	int iType;
	int getType();
	void setType(int value);

	cocos2d::CCSize visibleSize;
    cocos2d::CCPoint origin;

	void update(float dt);
	void start();
	void resume();
	void end();
	
	void pressPause(cocos2d::CCObject* pSender);
	void updateGaussBar();

	void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

	void showTouchEffect(cocos2d::CCPoint location);
	void hideHammer(cocos2d::CCNode* pSender, void* sprHammer);
	void hideEffect(cocos2d::CCNode* pSender, void* sprEffect);
	void udpateComboText();
	void updateScoreText();

	// implement the "static node()" method manually
	CREATE_FUNC(Game);
};

#endif // __GAME_SCENE_H__
