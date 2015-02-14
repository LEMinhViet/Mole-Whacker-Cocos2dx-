#include "cocos2d.h"
#include "MouseManager.h"
#include "Mouse.h"
#include "GameScene.h"
#include "WhackAMole.h"
#include <iostream>
#include <vector> 

using namespace std;

USING_NS_CC;

MouseManager::MouseManager(Game* game, CCPoint origin, CCSize visibleSize, short type) 
{
	this->game = game;
	this->origin = origin;
	this->visibleSize = visibleSize;
	this->type = type;
}

void MouseManager::createMouses() 
{
	size_t count = 0;
	for (size_t i = 0; i < ROW; i++) 
	{
		if (i % 2 == 0) 
		{ 
			for (size_t j = 0; j < COLUMN + 1; j++) 
			{
				Mouse mouse(count, 
							ccp(origin.x + visibleSize.width / 8 + j * visibleSize.width / 4, 
								origin.y + (i + 1) * visibleSize.height / 6));
				game->addChild(mouse.createMouse(), 1);				
				mouses.push_back(mouse);
				order.push_back(count);
				count++;
			} 
		}
		else 
		{
			for (size_t j = 0; j < COLUMN; j++) 
			{
				Mouse mouse(count, 
							ccp(origin.x + (j + 1) * visibleSize.width / 4, 
								origin.y + (i + 1) * visibleSize.height / 6));
				game->addChild(mouse.createMouse(), 1);
				mouses.push_back(mouse);
				order.push_back(count);
				count++;
			}
		}
	}
}

void MouseManager::updateMouses() 
{
	nbMouseUp = 0;
	for (size_t i = 0; i < mouses.size(); i++) 
	{
		mouses[i].update();
		if (mouses[i].isUp())
		{
			nbMouseUp++;
		}
	}

	if (nbMouseUp < 3) 
	{
		random_shuffle(order.begin(), order.end());
		vector<int>::iterator it = order.begin();
		while (nbMouseUp < 3 && it != order.end())
		{
			if (!mouses[*it].isUp())
			{
				mouses[*it].setCountToUp(rand() % 48);
				nbMouseUp++;
			}
			it++;
		}
	}
}

void MouseManager::ccTouchesBegan(CCPoint location, CCEvent* event)
{
	for (vector<Mouse>::iterator it = mouses.begin(); it != mouses.end(); it++)
	{
		CCRect bounding = it->getSprMouse()->boundingBox();
		if (it->isUp() && bounding.containsPoint(location))
		{
			it->goDead();
			CCLog("Sprite Touched ; %f - %f vs %f - %f - %f - %f", location.x, location.y, it->getSprMouse()->boundingBox().getMinX(),
				it->getSprMouse()->boundingBox().getMaxX(), it->getSprMouse()->boundingBox().getMinY(),
				it->getSprMouse()->boundingBox().getMaxY());
			break;
		}
	}	
}