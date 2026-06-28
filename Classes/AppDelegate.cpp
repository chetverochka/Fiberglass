#include "AppDelegate.h"
#include "MenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);


#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    pEGLView->setFrameSize(720, 1280);
    pEGLView->setFrameZoomFactor(0.6f);
#endif
    pEGLView->setDesignResolutionSize(720, 1280, ResolutionPolicy::kResolutionFixedWidth);

    CCSpriteFrameCache* framesCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    framesCache->addSpriteFramesWithFile("Spritesheet_1.plist");
    framesCache->addSpriteFramesWithFile("Spritesheet_2.plist");

    CCScene *pScene = MenuScene::scene();
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
