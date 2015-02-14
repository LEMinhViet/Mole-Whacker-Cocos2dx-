#include "cocos2d.h"
#include <vector>

using namespace cocos2d;
using namespace std;

USING_NS_CC;

// thêm hai selector cần dùng
typedef void (CCObject::*SEL_CallFuncI)(int);
typedef void (CCObject::*SEL_CallFuncB)(bool);

#define callfuncI_selector(_func_) (SEL_CallFuncI)(&_func_)
#define callfuncB_selector(_func_) (SEL_CallFuncB)(&_func_)

class AsyncImageLoader : public CCObject
{
protected:
	vector imageList(false);
	int imageIndex;

	bool running;

	CCObject *callbackTarget;
	SEL_CallFuncI onImageLoaded;
	SEL_CallFuncB onImageLoadingFinished;

public:
	AsyncImageLoader(const vector &imageList,
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
			this->addImageAsyncCallback(this); // truyền this làm cờ hiệu
		}
	}

	void stop(void)
	{
		this->running = false;
	}

	inline const vector & getImageList(void) const
	{
		return this->imageList;
	}

	inline int getImageIndex(void) const
	{
		return this->imageIndex;
	}

private:
	// được gọi mỗi khi nạp xong một hình
	void addImageAsyncCallback(void *textureObject)
	{
		if (!textureObject)
		{
			// nạp không được, kết thúc
			(this->callbackTarget->*this->onImageLoadingFinished)(false);
		}
		else
		{
			// đã nạp được hình
			if (textureObject != this)
				(this->callbackTarget->*this->onImageLoaded)(this->imageIndex);

			// nếu bị gọi dừng giữa chừng
			if (!this->running)
				return;

			// xong hết danh sách chưa?
			if (++this->imageIndex == this->imageList.size())
				(this->callbackTarget->*this->onImageLoadingFinished)(true);
			else
				CCTextureCache::sharedTextureCache()->addImageAsync(this->imageList[this->imageIndex].c_str(),
				this, callfuncO_selector(AsyncImageLoader::addImageAsyncCallback));
		}
	}
};
