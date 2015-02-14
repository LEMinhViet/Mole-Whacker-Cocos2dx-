#ifndef __ASYNCLOADERS_H__
#define __ASYNCLOADERS_H__

#include <thread>
#include <mutex>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

typedef void (CCObject::*SEL_CallFuncI)(int);
typedef void (CCObject::*SEL_CallFuncB)(bool);

#define callfuncI_selector(_func_) (SEL_CallFuncI)(&_func_)
#define callfuncB_selector(_func_) (SEL_CallFuncB)(&_func_)

class AsyncImageLoader : public CCObject
{
protected:
	vector<string> imageList;
	size_t imageIndex;

	bool running;

	CCObject *callbackTarget;
	SEL_CallFuncI onImageLoaded;
	SEL_CallFuncB onImageLoadingFinished;

public:
	AsyncImageLoader(const vector<string> &imageList,
		CCObject *callbackTarget, SEL_CallFuncI onImageLoaded, SEL_CallFuncB onImageLoadingFinished)
		: running(false),
		callbackTarget(callbackTarget), onImageLoaded(onImageLoaded), onImageLoadingFinished(onImageLoadingFinished)
	{
		this->imageList = imageList;
		this->imageIndex = -1;
	}

	void start(void)
	{
		if (!this->running)
		{
			this->running = true;
			this->addImageAsyncCallback(this);
		}
	}

	void stop(void)
	{
		this->running = false;
	}

	inline const vector<string> & getImageList(void) const
	{
		return this->imageList;
	}

	inline int getImageIndex(void) const
	{
		return this->imageIndex;
	}

private:
	void addImageAsyncCallback(void *textureObject)
	{
		if (!textureObject)
		{
			(this->callbackTarget->*this->onImageLoadingFinished)(false);
		}
		else
		{
			if (textureObject != this) 
				(this->callbackTarget->*this->onImageLoaded)(this->imageIndex);

			if (!this->running) 
				return;

			if (++this->imageIndex == this->imageList.size() ) 
				(this->callbackTarget->*this->onImageLoadingFinished)(true);
			else 
				CCTextureCache::sharedTextureCache()->addImageAsync(this->imageList[this->imageIndex].c_str(),
					this, callfuncO_selector(AsyncImageLoader::addImageAsyncCallback));
		}
	}
};

class AsyncAtlasLoader : public CCObject
{
protected:
	vector<string> atlasList;
	size_t atlasIndex;

	thread thread;
	mutex mutex;

	bool running;
	bool recentAtlasLoaded;
	bool atlasLoadingEnded;

	CCObject *callbackTarget;
	SEL_CallFunc onAtlasLoaded;
	SEL_CallFunc onAtlasLoadingFinished;

public:
	AsyncAtlasLoader(const vector<string> &atlasList,
		CCObject *callbackTarget, SEL_CallFunc onAtlasLoaded, SEL_CallFunc onAtlasLoadingFinished)
		:
		running(false), recentAtlasLoaded(false), atlasLoadingEnded(false),
		callbackTarget(callbackTarget),
		onAtlasLoaded(onAtlasLoaded), onAtlasLoadingFinished(onAtlasLoadingFinished)
	{
		this->atlasList = atlasList;
		this->atlasIndex = -1;
	}

	inline const vector<string> & getAtlasList(void) const
	{
		return this->atlasList;
	}

	inline int getAtlasIndex(void) const
	{
		return this->atlasIndex;
	}

	void start(void)
	{
		if (!this->running)
		{
			CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);

			this->running = true;
			this->thread = std::thread(AsyncAtlasLoader::run, this);
		}
	}

	void stop(void)
	{
		if (this->running)
		{
			this->mutex.lock();
			this->running = false;
			this->mutex.unlock();

			this->thread.join();

			CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
		}
	}

	void update(float dt)
	{
		(void)dt;

		if (this->recentAtlasLoaded)
		{
			this->mutex.lock();

			this->recentAtlasLoaded = false;
			(this->callbackTarget->*this->onAtlasLoaded)();

			this->mutex.unlock();
		}

		if (this->atlasLoadingEnded)
		{
			this->mutex.lock();

			this->atlasLoadingEnded = false;
			(this->callbackTarget->*this->onAtlasLoadingFinished)();

			this->running = false;
			this->mutex.unlock();
		}
	}

private:
	static void *run(void *arg)
	{
		auto This = reinterpret_cast<AsyncAtlasLoader *>(arg);
		while (true)
		{
			This->mutex.lock();
			if (This->running == false)
			{
				This->mutex.unlock();
				break;
			}
			This->mutex.unlock();
			
			if (++This->atlasIndex >= This->atlasList.size())
			{
				This->atlasLoadingEnded = true;
			}
			else
			{
				CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(This->atlasList[This->atlasIndex].c_str());
				This->recentAtlasLoaded = true;
			}
		}

		return nullptr;
	}
};

#endif//__ASYNCLOADERS_H__
