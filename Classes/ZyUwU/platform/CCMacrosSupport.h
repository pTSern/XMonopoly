#pragma once

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    #define CC_FILEUTILS_GI cocos2d::FileUtils::getInstance()
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #define CC_FILEUTILS_GI cocos2d::FileUtilsAndroid::getInstance()
#endif

#define CC_DIRECTOR_GI cocos2d::Director::getInstance()
#define CCDR_GI CC_DIRECTOR_GI

//#define CC_FILEUTILS_GI cocos2d::FileUtils::getInstance()
#define CCFU_GI CC_FILEUTILS_GI

#define CC_DEVICE_GI cocos2d::backend::Device::getInstance()
#define CCDV_GI CC_DEVICE_GI

#define CC_UI_BUTTON_SMART_SET_TITLE_FONT_SIZE(__TARGET__, __REDUCTION__) __TARGET__->setTitleFontSize(__TARGET__->getContentSize().height - __REDUCTION__)
#define CCUB_SSTFP(__TARGET__, __REDUCTION__) CC_UI_BUTTON_SMART_SET_TITLE_FONT_SIZE(__TARGET__, __REDUCTION__)

#define CC_UI_BUTTON_SMART_SET_TITLE_FONT_SIZE_PERCENT(__TARGET__, __PERCENT__) __TARGET__->setTitleFontSize(__PERCENT__*__TARGET__->getContentSize().height)
#define CCUB_SSTFSP(__TARGET__, __PERCENT__) CC_UI_BUTTON_SMART_SET_TITLE_FONT_SIZE_PERCENT(__TARGET__, __PERCENT__)

#ifndef ZYASSERT_BREAK
#if COCOS2D_DEBUG > 0
    #if CC_ENABLE_SCRIPT_BINDING
    extern bool CC_DLL cc_assert_script_compatible(const char *msg);
    #define ZYASSERT_BREAK(__COND__, __MSG__, __RETURN_TYPE__) do {                           \
          if (!(__COND__)) {                                                               \
            if (!cc_assert_script_compatible(__MSG__) && strlen(__MSG__))                  \
              cocos2d::log("Assert failed: %s", __MSG__);                                  \
            CC_ASSERT(__COND__);                                                           \
            return __RETURN_TYPE__;                                                          \
          }                                                                                \
        } while (0)
    #else
    #define ZYASSERT_BREAK(__COND__, __RETURN_TYPE__) ZY_ASSERT_BREAK(__COND__, __RETURN_TYPE__)
    #endif
#else
    #define ZYASSERT_BREAK(__COND__, __MSG__)
#endif
#endif
