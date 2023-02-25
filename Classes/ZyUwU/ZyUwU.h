#pragma once

#define ZYUWU_VERSION 0x0

//All file includes here

//cocos2dx
#include "cocos2d.h"

//math
#include "ZyUwU/math/ZYFraction.h"
#include "ZyUwU/math/SmartAlgorithm.h"

//gacha
#include "ZyUwU/gacha/ZYGacha.h"

//platform
#include "ZyUwU/platform/ZYMacros.h"
#include "ZyUwU/platform/CCMacrosSupport.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "ZyUwU/platform/android/ZYPlatformDefine-android.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

//2d
#include "ZyUwU/2d/ZYSprite.h"
#include "ZyUwU/2d/ZYEffect.h"
#include "ZyUwU/2d/ZYLabel.h"

//base
#include "ZyUwU/base/ZYDirector.h"
#include "ZyUwU/base/ZYSupport.h"
//database

//ui

//audio

NS_ZY_BEGIN

static const char* zyuwuVversion();

NS_ZY_END

