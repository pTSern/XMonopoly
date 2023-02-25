#pragma once

#include "ZyUwU/platform/ZYMacros.h"
#include "cocos2d.h"

NS_ZY_BEGIN

static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size smallResolutionSize = cocos2d::Size(1280, 720);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2560, 1440);
static cocos2d::Size supperResolutionSize = cocos2d::Size(2880,1620);

static const int sgc_nDefaultFloatLength = 5;

static const int sgc_nMaxRateDenominator = 10000000;

NS_ZY_END