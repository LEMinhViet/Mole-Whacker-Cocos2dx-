#ifndef __HELP_SCREEN_H__
#define __HELP_SCREEN_H__

#include "cocos2d.h"

class Help : public cocos2d::CCLayer
{
private:
	cocos2d::CCSprite* sprMenuBackground;
	cocos2d::CCSprite* sprMenuLogo;
	cocos2d::CCSprite* sprMenuHelp;

	cocos2d::CCSpriteBatchNode* _mouseBatchNode;

public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	cocos2d::CCLabelBMFont *lblInfo;

	cocos2d::CCSize visibleSize;
	cocos2d::CCPoint origin;

	CREATE_FUNC(Help);
};

#endif // __HELP_SCREEN_H__