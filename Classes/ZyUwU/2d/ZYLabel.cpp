#include "ZYLabel.h"
#include "ZYEffect.h"

NS_ZY_BEGIN


//Static
ZYLabel::ZYLabel(cocos2d::TextHAlignment hAlignment, cocos2d::TextVAlignment vAlignment ): cocos2d::Label(hAlignment, vAlignment)
{

}

ZYLabel* ZYLabel::createWithTTF(const std::string& text, const std::string& fontFile, float fontSize, const cocos2d::Size& dimensions , cocos2d::TextHAlignment hAlignment , cocos2d::TextVAlignment vAlignment )
{
    auto pElement = new (std::nothrow) ZYLabel(hAlignment, vAlignment);
    if(pElement && pElement->cocos2d::Label::initWithTTF(text, fontFile, fontSize, dimensions, hAlignment, vAlignment))
    {
        pElement->autorelease();
        pElement->setName("ZYLABEL");
        return pElement;
    }
    CC_SAFE_DELETE(pElement);
    return nullptr;
}
float ZYLabel::getRotation() const
{
    if(_rotationZ_X == _rotationZ_Y)
    {
        return Node::getRotation();
    }
    else
        return _rotationZ_X;
}

void ZYLabel::fixGetRotation()
{
    if(_rotationZ_Y != _rotationZ_X) _rotationZ_Y = _rotationZ_X = 0;
}

ZYLabel* ZYLabel::createWithTTF(const TTFConfig& ttfConfig, const std::string& text,
                                  TextHAlignment hAlignment, int maxLineWidth)
{
    auto ret = new (std::nothrow) ZYLabel(hAlignment);

    if (ret && ret->initWithTTF(ttfConfig, text, hAlignment, maxLineWidth))
    {
        ret->autorelease();
        ret->setName("ZYLABEL");
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}
//// Public

//Virtual

void ZYLabel::log()
{

}

std::string ZYLabel::toString(int nTab)
{
    std::string ts;
    std::string tab = ZYSP_T(nTab);
    ts += (tab + " + Size: " + ZYSP_STS(getContentSize()));
    ts += (tab + " + Position: " + ZYSP_VTS(getPosition()));
    ts += (tab + " + Font Size: " + ZYSP_NTS(getTTFConfig().fontSize));
    return ts;
}

// Public

NS_ZY_END
