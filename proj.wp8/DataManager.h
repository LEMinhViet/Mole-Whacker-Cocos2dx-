#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

class DataManager
{
public:
	static CCString* getObjectForKey(const char* key);
	static void setObjectForKey(const char* key, CCString *obj);
};

#endif