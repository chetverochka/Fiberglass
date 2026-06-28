#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"

class PlayLayer;

class PlayScene : public cocos2d::CCScene {
public:
	static PlayScene* create(int level);
	bool init(int level);
	void onEnter();


private:
	void goBack(cocos2d::CCObject* sender);

	int _level;
	PlayLayer* _playLayer;
	cocos2d::CCLabelBMFont* _levelLabel;
	cocos2d::CCProgressTimer* _pointsBar;
};

#endif //!__PLAY_SCENE_H__