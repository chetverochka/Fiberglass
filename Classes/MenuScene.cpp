#include "MenuScene.h"
#include "MainMenuButtons.h"
#include "PlayScene.h"
#include "BackgroundLayer.h"

USING_NS_CC;

CCScene* MenuScene::scene() {
	CCScene* ret = CCScene::create();
	if (ret) {
		ret->addChild(MenuScene::create());
	}
	return ret;
}

bool MenuScene::init() {
	if (!CCLayer::init()) {
		return false;
	}

	const CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	addChild(BackgroundLayer::create(), -1);

	_gameLogo = CCSprite::createWithSpriteFrameName("Fiberglass_logo.png");
	addChild(_gameLogo);

	_gameLogo->setPosition(ccp(
		visibleSize.width / 2, 
		visibleSize.height - _gameLogo->getContentSize().height / 2 - 100.f));


	CCMenu* menuButtons = CCMenu::create();
	menuButtons->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

	CCMenuItem* playButton = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrameName("PlayButton.png"), 
		NULL,
		this, 
		menu_selector(MenuScene::onPlayClicked));
	CCMenuItem* settingsButton = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrameName("SettingsButton.png"),
		NULL,
		this,
		menu_selector(MenuScene::onSettingsClicked));

	menuButtons->addChild(playButton);
	menuButtons->addChild(settingsButton);
	menuButtons->alignItemsVerticallyWithPadding(49.f);

	addChild(menuButtons);

	return true;
}

void MenuScene::onPlayClicked(cocos2d::CCObject* sender) {
	CCScene* scene = PlayScene::create(1);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5f, scene));
}

void MenuScene::onSettingsClicked(cocos2d::CCObject* sender) {

}