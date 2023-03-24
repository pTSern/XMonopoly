#pragma once

#include "ZyUwU/platform/ZYMacros.h"
#include "ZYConstant.h"
#include "cocos2d.h"
#include "iomanip"

USING_NS_CC;

NS_ZY_BEGIN

#define ZY_SUPPORT_GI zy::ZYSupport::getInstance()

#define ZY_SP_NUMBER_TO_STRING(__NUM__) zy::ZYSupport::getInstance()->numberToString(__NUM__)
#define ZYSP_NTS(__NUM__) ZY_SP_NUMBER_TO_STRING(__NUM__)

#define ZY_SP_SIZE_TO_STRING(__SIZE__) zy::ZYSupport::getInstance()->sizeToString(__SIZE__)
#define ZYSP_STS(__SIZE__) ZY_SP_SIZE_TO_STRING(__SIZE__)

#define ZY_SP_VEC2_TO_STRING(__VEC2__) zy::ZYSupport::getInstance()->vec2ToString(__VEC2__)
#define ZYSP_VTS(__VEC2__) ZY_SP_VEC2_TO_STRING(__VEC2__)

#define ZY_SP_NO_NUMBER_STRING(__STRING__) zy::ZYSupport::getInstance()->noNumberString(__STRING__)
#define ZYSP_NNS(__STRING__) ZY_SP_NO_NUMBER_STRING(__STRING__)

#define ZY_SP_TAB(__NUM__) zy::ZYSupport::getInstance()->tabString(__NUM__);
#define ZYSP_T(__NUM__) ZY_SP_TAB(__NUM__)

#define ZY_SP_FIT_STRING_IN_SIZE(__LABEL__, __STRING__, __BORDER_SIZE__, __MIN_FONT_SIZE__) zy::ZYSupport::getInstance()->fitStringInSize(__LABEL__, __STRING__, __BORDER_SIZE__, __MIN_FONT_SIZE__)
#define ZYSP_FSIS(__LABEL__, __STRING__, __BORDER_SIZE__, __MIN_FONT_SIZE__) ZY_SP_FIT_STRING_IN_SIZE(__LABEL__, __STRING__, __BORDER_SIZE__, __MIN_FONT_SIZE__)

#define ZY_SP_SHORTER_DECIMAL(__NUM__, __LENGTH__) zy::ZYSupport::getInstance()->shorterDecimal(__NUM__, __LENGTH__)
#define ZYSP_SD(__NUM__, __LENGTH__) ZY_SP_SHORTER_DECIMAL(__NUM__, __LENGTH__)

#define ZY_SP_COLOR3B_TO_COLOR4F(__COLOR4F__) ZY_SUPPORT_GI->convert4FTo3B(__COLOR4F__)
#define ZYSP_3BT4F(__COLOR4F__) ZY_SP_COLOR3B_TO_COLOR4F(__COLOR4F__)

#define ZY_SP_SMART_ROUNDING_FLOAT(__NUM__, __LENGTH__) ZY_SUPPORT_GI->smartRoundingFloat(__NUM__, __LENGTH__)
#define ZYSP_SRF(__NUM__, __LENGTH__) ZY_SP_SMART_ROUNDING_FLOAT(__NUM__, __LENGTH__)

#define PI 3.14159265359

class ZYLabel;
BEGIN_CREATE_INSTANCE_REFCLASS(ZYSupport, cocos2d::Ref)

public:
    std::string shorterDecimal(float fNum, int nLength);
    std::string numberToString(float fNum);
    std::string sizeToString(cocos2d::Size size);
    std::string vec2ToString(cocos2d::Point vec2);
    std::string noNumberString(std::string sText);
    std::string tabString(int nTab = 2);
    std::string smartRoundingFloat(float num, int length);
    void fitStringInSize(zy::ZYLabel* pLabel, std::string str, cocos2d::Size borderSize, int nMinFontSize = 14);

public:
    bool isInt(float fNum);
    bool isOdd(int nNum);

public:
    float radToDegree(float fRad);
    float degreeToRad(float fDegree);

public:
    const Color3B& convert4FTo3B(const Color4F& color);

END_CREATE_INSTANCE_REFCLASS

NS_ZY_END
