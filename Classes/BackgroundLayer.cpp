#include "BackgroundLayer.h"

USING_NS_CC;

bool BackgroundLayer::init() {
	if (!CCLayer::init()) {
		return false;
	}

	const CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* backgroundSprite = CCSprite::create("MenuBackground.png");
	backgroundSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	backgroundSprite->setScale(visibleSize.height / backgroundSprite->getContentSize().height);
	addChild(backgroundSprite, -1);

	return true;
}