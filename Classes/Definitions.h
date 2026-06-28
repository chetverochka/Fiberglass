#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

/*

#define CREATE_INIT(__TYPE__, __FUNC_NAME__, __INITIALIZER__, ...)

static __TYPE__* __FUNC_NAME__() {
	__TYPE__* ret = new (std::nothrow) __TYPE__();
	if (ret && ret->__INITIALIZER__(__VA_ARGS__)) {
		ret->autorelease();
	}
	else {
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

*/

#define CREATE_INIT(__TYPE__, __FUNC_NAME__, __INITIALIZER__, ...)	\
static __TYPE__* __FUNC_NAME__() {									\
	__TYPE__* ret = new (std::nothrow) __TYPE__();					\
	if (ret && ret->__INITIALIZER__(__VA_ARGS__)) {					\
		ret->autorelease();											\
	}																\
	else {															\
		CC_SAFE_DELETE(ret);										\
	}																\
	return ret;														\
}

#include "CCDirector.h"

#define CC_SCREEN_SIZE cocos2d::CCDirector::sharedDirector()->getVisibleSize()
#define BMFNT_WHITE_40_FILENAME "BM_ForcedSquare_40px.fnt"
#define BMFNT_WHITE_40_PATH "fonts/BM_ForcedSquare_40px.fnt"
#define BMFNT_WHITE_64_PATH "fonts/BM_ForcedSquare_64px.fnt"
#define BMFNT_WHITE_64_FILENAME "BM_ForcedSquare_64px.fnt"

#endif // !__DEFINITIONS_H__