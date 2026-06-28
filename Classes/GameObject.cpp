#include "GameObject.h"
#include "PlayLayer.h"

USING_NS_CC;

std::string GameObject::getObjectFrame(ObjectType type) {
	char frameName[50];
	switch (type)
	{
	case OBJECT_SQUARE:
		return "SquareTile.png";
	case OBJECT_CIRCLE:
		return "CircleTile.png";
	case OBJECT_TRIANGLE:
		return "TriangleTile.png";
	case OBJECT_STAR:
		return "StarTile.png";
	}
	return "";
}

GameObject* GameObject::createWithType(ObjectType type) {
	GameObject* ret = new GameObject();
	if (ret && ret->initWithType(type)) {
		ret->autorelease();
	}
	else {
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

GameObject* GameObject::createRandom() {
	ObjectType types[4] = {
		OBJECT_SQUARE,
		OBJECT_CIRCLE,
		OBJECT_TRIANGLE,
		OBJECT_STAR
	};
	const int count = sizeof(types) / sizeof(types[0]);
	return GameObject::createWithType(types[abs(rand() % count)]);
}

bool GameObject::initWithType(ObjectType objectType) {
	if (!CCSprite::init()) {
		return false;
	}

	_type = objectType;

	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCSpriteFrame* objectFrame = frameCache->spriteFrameByName(getObjectFrame(objectType).c_str());
	setDisplayFrame(objectFrame);

	_cellX = 0;
	_cellY = 0;
	_gameParent = NULL;

	return true;
}

void GameObject::setCell(int x, int y) {
	_cellX = x;
	_cellY = y;

	if (getGame()) {
		getGame()->updateTileGrid(this);
	}
}

void GameObject::onEnterGame() {
}

void GameObject::onExitGame() {

}