#ifndef __PLAY_LAYER_H__
#define __PLAY_LAYER_H__

#include "cocos2d.h"

struct GameLevel {
	int fieldSize;
	GameLevel();
};

class GameObject;

class PlayLayer : public cocos2d::CCLayer {
public:
	static PlayLayer* createWithLevel(GameLevel gameLevel);
	// CREATE_FUNC(PlayLayer);

	bool initWithLevel(GameLevel gameLevel);

	void playFadeInAnim(float delay);
	cocos2d::CCNode* getGameField() { return _gameField; }

	void addTile(GameObject* object);
	void removeTile(GameObject* object);
	bool hasTile(GameObject* object);

	cocos2d::CCPoint getCellCenter(int cellX, int cellY) const;
	void updateTileGrid(GameObject* object);

	void getCellInPoint(const cocos2d::CCPoint& point, int& cellX, int& cellY) const;
	bool fieldContainsCell(int cellX, int cellY);
	bool isCellEmpty(int x, int y);

	bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	bool isAnimationsEnabled() const { return _enableAnimations; }
	void setAnimationsEnabled(bool enableAnimations) { _enableAnimations = enableAnimations; }

	void selectCell(int x, int y);
protected:
	cocos2d::CCNode* _gameField;
	cocos2d::CCSpriteBatchNode* _objectsBatch;
	GameLevel _gameLevel;
private:
	void initGameField();

	bool _enableAnimations;

	std::vector<std::pair<int, int>> _selectedCells;

	std::vector<cocos2d::CCSprite*> _backTileSprites;
	std::vector<GameObject*> _allTiles;
};

#endif // !__PLAY_LAYER_H__