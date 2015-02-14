#ifndef __MOUSE_MANAGER_H__
#define __MOUSE_MANAGER_H__

#include "cocos2d.h"
#include "Mouse.h"
#include <vector>  

using namespace std;

class Game;

class MouseManager
{
private:
	static const short ROW = 4;
	static const short COLUMN = 3;

	short nb;
	short type;
	short typeMouse;
	short nbMouseUp;

	cocos2d::CCSize visibleSize;
    cocos2d::CCPoint origin;

	Game* game;
	vector<Mouse> mouses;
	vector<int> order;

public:
	MouseManager(Game* game, cocos2d::CCPoint origin, cocos2d::CCSize visibleSize, short type);
	void createMouses();
	void updateMouses();
	void ccTouchesBegan(cocos2d::CCPoint location, cocos2d::CCEvent* event);
};

#endif