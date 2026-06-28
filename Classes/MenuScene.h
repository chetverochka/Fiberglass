#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::CCLayer {
public:
	CREATE_FUNC(MenuScene);
	static cocos2d::CCScene* scene();

	bool init() override;
private:
	cocos2d::CCSprite* _gameLogo;

	void onPlayClicked(cocos2d::CCObject* sender);
	void onSettingsClicked(cocos2d::CCObject* sender);
};

#endif // !__MENU_SCENE_H__