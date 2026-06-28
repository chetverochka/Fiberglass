#include "MainMenuButtons.h"

USING_NS_CC;

MainMenuButton* MainMenuButton::create(const char* path) {
	return createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path));
}

MainMenuButton* MainMenuButton::createWithSpriteFrame(cocos2d::CCSpriteFrame* frame) {
	MainMenuButton* ret = new MainMenuButton();
	if (ret && ret->initWithFrame(frame)) {
		ret->autorelease();
	}
	else {
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void MainMenuButton::setCallback(cocos2d::CCObject* object, SEL_MenuHandler menuHandler) {
	m_pListener = object;
	m_pfnSelector = menuHandler;
}


bool MainMenuButton::initWithFrame(cocos2d::CCSpriteFrame* frame) {
	if (!CCMenuItemImage::init()) {
		return false;
	}

	setNormalSpriteFrame(frame);

	return true;
}
