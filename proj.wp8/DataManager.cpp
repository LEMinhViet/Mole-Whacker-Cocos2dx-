#include "DataManager.h"

USING_NS_CC;

CCString* DataManager::getObjectForKey(const char* key) {
	string value = CCUserDefault::sharedUserDefault()->getStringForKey(key, "");
	CCString *pRet = CCString::create("");
	pRet->m_sString = value;
	return pRet;
}

void DataManager::setObjectForKey(const char* key, CCString *obj) {
	CCUserDefault::sharedUserDefault()->setStringForKey(key, obj->getCString());
	CCUserDefault::sharedUserDefault()->flush();
}