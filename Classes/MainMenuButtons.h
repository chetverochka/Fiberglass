#ifndef __MAIN_MENU_BUTTONS_H__
#define __MAIN_MENU_BUTTONS_H__

#include "cocos2d.h"

class MainMenuButton : public cocos2d::CCMenuItemImage {
public:
	static MainMenuButton* create(const char* path);
	static MainMenuButton* createWithSpriteFrame(cocos2d::CCSpriteFrame* frame);

	void setCallback(cocos2d::CCObject* object, cocos2d::SEL_MenuHandler menuHandler);

protected:
	virtual bool initWithFrame(cocos2d::CCSpriteFrame* frame);


	
};

#endif // !__MAIN_MENU_BUTTONS_H__