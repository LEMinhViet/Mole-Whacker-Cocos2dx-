#include "cocos2d.h"
#include "LoadingScene.h"
#include <iostream>

using namespace std;

USING_NS_CC;

CCScene* Loading::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	Loading *layer = new Loading();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void Loading::onEnter(void)
{
	CCLayer::onEnter();

	CCSprite *sprLogo = CCSprite::create("Images/Logo.jpg");
	sprLogo->setAnchorPoint(CCPointZero);
	sprLogo->setPosition(CCPointZero);
	this->addChild(sprLogo, 0);

	this->runAction(CCCallFunc::create(this, callfunc_selector(Loading::startLoading)));
}

void Loading::startLoading(void)
{
	this->prepareLists();
	this->startImageLoading();
}

void Loading::endLoading(void)
{
	CCTransitionScene* trans = CCTransitionFade::create(0.3f, HelloWorld::createScene());
	CCDirector::sharedDirector()->replaceScene(trans);
}

void Loading::prepareLists(void)
{
	this->prepareImageList();
	this->prepareAtlasList();
}

void Loading::prepareImageList(void)
{
	vector<string> imageList;

	imageList.push_back("Images/endMenu.png");
	imageList.push_back("Images/g_mouses.png");
	imageList.push_back("Images/main_menu_buttons.png");
	imageList.push_back("Images/inGame_Elements.png");
	imageList.push_back("Images/m_Texts.png");
	imageList.push_back("Images/gauss.png");

	this->asyncImageLoader = new AsyncImageLoader(imageList, this,
		callfuncI_selector(Loading::onImageLoaded), callfuncB_selector(Loading::onImageLoadingFinished));
}

void Loading::prepareAtlasList(void)
{
	vector<string> atlasList;

	atlasList.push_back("Images/endMenu.plist");
	atlasList.push_back("Images/g_mouses.plist");
	atlasList.push_back("Images/main_menu_buttons.plist");
	atlasList.push_back("Images/inGame_Elements.plist");
	atlasList.push_back("Images/m_Texts.plist");
	atlasList.push_back("Images/gauss.plist");

	this->asyncAtlasLoader = new AsyncAtlasLoader(atlasList, this,
		callfunc_selector(Loading::onAtlasLoaded), callfunc_selector(Loading::onAtlasLoadingFinished));
}

void Loading::updateProgress(void)
{
}

void Loading::startImageLoading(void)
{
	this->asyncImageLoader->start();
}

void Loading::onImageLoaded(int index)
{
	this->updateProgress();
}

void Loading::onImageLoadingFinished(bool successful)
{
	if (!successful)
	{
		// show error
		return;
	}

	this->startAtlasLoading();
}

void Loading::startAtlasLoading(void)
{
	this->asyncAtlasLoader->start();
}

void Loading::onAtlasLoaded(void)
{
	this->updateProgress();
}

void Loading::onAtlasLoadingFinished(void)
{
	this->endLoading();
}