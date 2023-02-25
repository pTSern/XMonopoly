#pragma once

#include <android/log.h>

#define ZY_ASSERT_BREAK(__COND__, __RETURN_TYPE__)              \
if (!(cond)) {                                                  \
        __android_log_print(ANDROID_LOG_ERROR,                  \
                            "cocos2d-x assert",                 \
                            "%s function:%s line:%d",           \
                            __FILE__, __FUNCTION__, __LINE__);  \
    return __RETURN_TYPE__;                                     \
    }
