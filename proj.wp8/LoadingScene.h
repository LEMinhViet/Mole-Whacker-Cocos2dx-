#include "cocos2d.h"
#include "AsyncLoaders.h"
#include "HelloWorldScene.h"

using namespace std;

USING_NS_CC;

class AsyncImageLoader;
class AsyncAtlasLoader;

class Loading : public CCLayer
{
protected:
	AsyncImageLoader *asyncImageLoader;
	AsyncAtlasLoader *asyncAtlasLoader;

public:
	static CCScene* scene();
	void onEnter(void);

protected:
	void startLoading(void);
	void endLoading(void);
	void prepareLists(void);
	void prepareImageList(void);
	void prepareAtlasList(void);
	void updateProgress(void);
	void startImageLoading(void);
	void onImageLoaded(int index);
	void onImageLoadingFinished(bool successful);
	void startAtlasLoading(void);
	void onAtlasLoaded(void);
	void onAtlasLoadingFinished(void);
};
