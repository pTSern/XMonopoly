#pragma once

#include "ZyUwU/platform/ZYMacros.h"
#include "ZyUwU/base/ZYSupport.h"
#include "cocos2d.h"
#include "ZYShaderHelper.h"

NS_ZY_BEGIN

class ZYEffect;
class ZYLabel : public cocos2d::Label
{
public:
    static ZYLabel* createWithTTF(const std::string& text, const std::string& fontFile, float fontSize,
                                  const cocos2d::Size& dimensions = cocos2d::Size::ZERO,
                                  cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
                                  cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);
    static ZYLabel* createWithTTF(const TTFConfig& ttfConfig, const std::string& text,
                                TextHAlignment hAlignment = TextHAlignment::LEFT, int maxLineWidth = 0);
public:
    virtual void log();
    virtual std::string toString(int nTab = 2);

private:
    ZYLabel(TextHAlignment hAlignment = TextHAlignment::LEFT,
            TextVAlignment vAlignment = TextVAlignment::TOP);
};

NS_ZY_END
