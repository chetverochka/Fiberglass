#include "PlayLayer.h"
#include "Definitions.h"
#include "BackgroundLayer.h"
#include "GameObject.h"

USING_NS_CC;

GameLevel::GameLevel() 
	: fieldSize(10)
{

}

#define CELL_SIZE 100.f
#define GAME_FIELD_TAG 1
#define TILE_PARENT_NODE _objectsBatch

PlayLayer* PlayLayer::createWithLevel(GameLevel gameLevel) {
	PlayLayer* ret = new PlayLayer();
	if (ret && ret->initWithLevel(gameLevel)) {
		ret->autorelease();
	}
	else {
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool PlayLayer::initWithLevel(GameLevel gameLevel) {
	if (!CCLayer::init()) {
		return false;
	}
	_gameLevel = gameLevel;
	_enableAnimations = false;

	addChild(BackgroundLayer::create(), -1);
	initGameField();

	setTouchEnabled(true);
	setTouchMode(ccTouchesMode::kCCTouchesOneByOne);

	return true;
}

void PlayLayer::playFadeInAnim(float delay) {

	const int fieldSize = _gameLevel.fieldSize;


	for (int i = 0; i < _backTileSprites.size(); i++) {
		CCSprite* backTile = _backTileSprites[i];
		backTile->setScale(0.f);

		CCArray* seq = CCArray::create();
		seq->addObject(CCDelayTime::create(delay + (i + i % fieldSize) * 0.01));
		seq->addObject(CCEaseExponentialOut::create(CCScaleTo::create(0.6f, 1.f)));

		backTile->runAction(CCSequence::create(seq));
	}
}

void PlayLayer::initGameField() {
	const int fieldSize = abs(_gameLevel.fieldSize);

	CCSize fieldDimensions;
	fieldDimensions.width = fieldSize * CELL_SIZE;
	fieldDimensions.height = fieldSize * CELL_SIZE;

	_gameField = CCNode::create();
	_gameField->setContentSize(fieldDimensions);
	_gameField->setAnchorPoint(ccp(0.5, 0.5));
	_gameField->setPosition(ccp(CC_SCREEN_SIZE.width / 2, CC_SCREEN_SIZE.height / 2));
	_gameField->setTag(GAME_FIELD_TAG);
	
	const float scale = (fmin(CC_SCREEN_SIZE.width, CC_SCREEN_SIZE.height) - 40.f) / (fieldSize * CELL_SIZE);
	_gameField->setScale(scale);

	addChild(_gameField);

	_backTileSprites.clear();

	int rowIndex = 0, columnIndex = 0;
	for (int i = 0; i < pow(fieldSize, 2); i++) {
		CCSprite* backTile = CCSprite::createWithSpriteFrameName("BackTile.png");
		_gameField->addChild(backTile, -1);

		columnIndex = i % fieldSize;
		rowIndex = ceil(i / fieldSize);
		
		backTile->setPosition(ccp(
			CELL_SIZE / 2 + columnIndex * CELL_SIZE,
			fieldDimensions.height - CELL_SIZE / 2 - rowIndex * CELL_SIZE
		));
		_backTileSprites.push_back(backTile);
	}

	_objectsBatch = CCSpriteBatchNode::create("Spritesheet_2.png");
	_objectsBatch->setAnchorPoint(ccp(0, 0));
	_objectsBatch->setPosition(ccp(0, 0));
	_gameField->addChild(_objectsBatch, 0);
}

void PlayLayer::addTile(GameObject* object) {
	if (hasTile(object) || object->getParent() || _allTiles.size() >= pow(_gameLevel.fieldSize, 2)) {
		CCAssert(false, "PlayLayer::addTile");
	}
	_allTiles.push_back(object);

	object->setGame(this);
	object->onEnterGame();

	TILE_PARENT_NODE->addChild(object);

	updateTileGrid(object);
}

void PlayLayer::removeTile(GameObject* object) {
	if (!hasTile(object) || object->getParent() != TILE_PARENT_NODE) {
		CCAssert(false, "PlayLayer::removeTile");
	}
	object->onExitGame();
	object->setGame(NULL);

	_allTiles.erase(std::find(_allTiles.begin(), _allTiles.end(), object));

	TILE_PARENT_NODE->removeChild(object, true);
}

bool PlayLayer::hasTile(GameObject* object) {
	return object->getGame() == this;
}

CCPoint PlayLayer::getCellCenter(int cellX, int cellY) const {
	CCPoint absolutePos;
	absolutePos.x = CELL_SIZE / 2 + (cellX - 1) * CELL_SIZE;
	absolutePos.y = _gameField->getContentSize().height - CELL_SIZE / 2 - (cellY - 1) * CELL_SIZE;
	return absolutePos;
}

void PlayLayer::updateTileGrid(GameObject* object) {
	CCPoint cellCenter = getCellCenter(object->getCellX(), object->getCellY());

	object->setPosition(cellCenter);
}

void PlayLayer::getCellInPoint(const CCPoint& point, int& cellX, int& cellY) const {
	const CCPoint convertedPoint = _gameField->convertToNodeSpace(point);
	
	cellX = std::floor(convertedPoint.x / CELL_SIZE) + 1;
	cellY = std::floor((_gameField->getContentSize().height - convertedPoint.y) / CELL_SIZE) + 1;
}

bool PlayLayer::fieldContainsCell(int cellX, int cellY) {
	return cellX >= 1 && cellY >= 1 && cellX <= _gameLevel.fieldSize && cellY <= _gameLevel.fieldSize;
}

bool PlayLayer::isCellEmpty(int x, int y) {
	for (int i = 0; i < _allTiles.size(); i++) {
		if (_allTiles[i]->getCellX() == _allTiles[i]->getCellY()) {
			return false;
		}
	}
	return true;
}

bool PlayLayer::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
	const CCPoint touchLocation = touch->getLocation();

	if (_gameField->boundingBox().containsPoint(touchLocation)) {
		
		return true;
	}
	else {
		return false;
	}
}

void PlayLayer::selectCell(int x, int y) { // TODO: rename to swithCellState(int x, int y);
	
}