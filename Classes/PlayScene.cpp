#include "PlayScene.h"
#include "Definitions.h"
#include "PlayLayer.h"
#include "MenuScene.h"
#include "GameObject.h"

USING_NS_CC;

PlayScene* PlayScene::create(int level) {
	PlayScene* ret = new PlayScene();
	if (ret && ret->init(level)) {
		ret->autorelease();
	}
	else {
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool PlayScene::init(int level) {
	if (!CCScene::init()) {
		return false;
	}

	_level = level;

	CCMenuItem* pauseButton = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrameName("PauseButton.png"),
		CCSprite::createWithSpriteFrameName("PauseButton.png"),
		this,
		menu_selector(PlayScene::goBack)
	);
	CCMenu* pauseMenu = CCMenu::createWithItem(pauseButton);
	addChild(pauseMenu, 1);

	pauseMenu->setPosition(ccp(
		pauseButton->getContentSize().width/2 + 20.f, 
		CC_SCREEN_SIZE.height - pauseButton->getContentSize().height/2 - 20.f
		));

	const int fieldSize = 7;

	GameLevel gameLevel;
	gameLevel.fieldSize = fieldSize;

	_playLayer = PlayLayer::createWithLevel(gameLevel);
	addChild(_playLayer);

	CCSprite* levelLabelDeco = CCSprite::createWithSpriteFrameName("LevelLabelFill.png");
	levelLabelDeco->setPosition(ccp(
		CC_SCREEN_SIZE.width - levelLabelDeco->getContentSize().width/2,
		pauseMenu->getPositionY()
	));
	addChild(levelLabelDeco, 1);

	_levelLabel = CCLabelBMFont::create("Level 1", BMFNT_WHITE_64_PATH);
	_levelLabel->setPosition(ccp(
		CC_SCREEN_SIZE.width/2,
		pauseMenu->getPositionY() - 8
	));
	addChild(_levelLabel, 1);

	// init points progress bar
	CCSprite* progressBarSprite = CCSprite::createWithSpriteFrameName("GameProgressBar.png");
	_pointsBar = CCProgressTimer::create(progressBarSprite);
	_pointsBar->setAnchorPoint(ccp(0.5, 0.5));
	CCNode* gameField = _playLayer->getGameField();
	_pointsBar->setPosition(ccp(
		gameField->getPositionX(),
		gameField->boundingBox().getMinY() - progressBarSprite->getContentSize().height / 2 - 50.f
	));
	_pointsBar->setType(CCProgressTimerType::kCCProgressTimerTypeBar);
	_pointsBar->setBarChangeRate(ccp(1,0));
	_pointsBar->setMidpoint(ccp(0.0f, 0.5f));
	_pointsBar->setPercentage(0);
	_pointsBar->runAction(CCEaseExponentialOut::create(CCProgressTo::create(3.f, 100)));
	addChild(_pointsBar, 1);


	int initialObjectsCount = 0;
	if (initialObjectsCount <= 3) {
		initialObjectsCount = 5;
	}

	for (int i = 0; i < initialObjectsCount; i++) {
		GameObject* object = GameObject::createRandom();
		object->setCell(rand() % 6 + 1, rand() % 6 + 1);
		_playLayer->addTile(object);
	}

	return true;
}

void PlayScene::onEnter() {
	CCScene::onEnter();
	_playLayer->playFadeInAnim(0.2f);
}

void PlayScene::goBack(CCObject* sender) {
	CCScene* scene = MenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(0.5f, scene));
}