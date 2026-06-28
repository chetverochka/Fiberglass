#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "cocos2d.h"

enum ObjectType {
	OBJECT_SQUARE,
	OBJECT_CIRCLE,
	OBJECT_TRIANGLE,
	OBJECT_STAR
};

class PlayLayer;

class GameObject : public cocos2d::CCSprite {
public:
	static std::string getObjectFrame(ObjectType type);
	static GameObject* createWithType(ObjectType type);
	static GameObject* createRandom();

	bool initWithType(ObjectType objectType);

	void setCell(int x, int y);
	void setCellX(int x) { setCell(x, _cellY); }
	void setCellY(int y) { setCell(_cellX, y); }

	void getCell(int& x, int& y) const { x = _cellX; y = _cellY; }
	const int& getCellX() const { return _cellX; }
	const int& getCellY() const { return _cellY; }

	void setGame(PlayLayer* field) { _gameParent = field; }
	PlayLayer* getGame() const { return _gameParent; }

	void onEnterGame();
	void onExitGame();
private:
	ObjectType _type;

	int _cellX;
	int _cellY;

	PlayLayer* _gameParent;

private:  // CC_SYNTHESIZE ZONE
private:  // CC_SYNTHESIZE ZONE
};

#endif // !__GAME_OBJECT_H__