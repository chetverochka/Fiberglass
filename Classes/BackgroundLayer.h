#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::CCLayer {
public:
	CREATE_FUNC(BackgroundLayer);

	bool init() override;
};

#endif // !__BACKGROUND_LAYER_H__