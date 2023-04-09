#include "ZYSupport.h"
#include "ZyUwU/2d/ZYLabel.h"
#include "ZYDirector.h"

NS_ZY_BEGIN

//

ZYSupport* ZYSupport::sp_pInstance = nullptr;

ZYSupport::ZYSupport()
{

}

//// Public

bool ZYSupport::isInt(float fNum)
{
    return (fNum - (int)fNum) == 0;
}

std::string ZYSupport::shorterDecimal(float fNum, int nLength)
{
   std::stringstream stream;
   stream << std::fixed << std::setprecision(nLength) << fNum;
    return stream.str();
}

std::string ZYSupport::smartRoundingFloat(float num, int length)
{
    double rounded_num = std::round(num * std::pow(10, length)) / std::pow(10, length);
    std::stringstream stream;
    auto str = shorterDecimal(rounded_num, length);
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);

    if(str.back() == '.') str.pop_back();

    return str;
}

std::string ZYSupport::tabString(int nTab)
{
    if (0 > nTab || nTab > 10) nTab = 2;
    std::string tab = "\n";
    for (int i = 0; i < nTab; i++) tab += "\t";
    return tab;
}

std::string ZYSupport::numberToString(float fNum)
{
    if(this->isInt(fNum)) return this->shorterDecimal(fNum, 1);
    return this->shorterDecimal(fNum, sgc_nDefaultFloatLength);
}

std::string ZYSupport::noNumberString(std::string sText)
{
    sText.erase(std::remove_if(sText.begin(), sText.end(), ::isdigit), sText.end());
    return sText;
}


std::string ZYSupport::sizeToString(cocos2d::Size size)
{
    return "(" + ZYSP_NTS(size.width) + " - " + ZYSP_NTS(size.height) + ")";
}

std::string ZYSupport::vec2ToString(cocos2d::Point vec2)
{
    return "(" + ZYSP_NTS(vec2.x) + ", " + ZYSP_NTS(vec2.y) + ")";
}

float ZYSupport::radToDegree(float fRad)
{
    return fRad*180/PI;
}

float ZYSupport::degreeToRad(float fDegree)
{
    return fDegree*PI/180;
}

bool ZYSupport::isOdd(int nNum)
{
    return (nNum%2==1);
}

void ZYSupport::fitStringInSize(zy::ZYLabel* pLabel, std::string text, cocos2d::Size borderSize, int nMinFontSize)
{
    pLabel->setMaxLineWidth(borderSize.width - 2);
    pLabel->setString(text);
    bool isBreak = false;
    bool isRerun = false;
    auto _c = pLabel->getTTFConfig();
    TTFConfig new_c(_c);
    std::string str;
    while(!isBreak)
    {
        if(pLabel->getContentSize().height > borderSize.height)
        {
            new_c.fontSize--;
            if(new_c.fontSize < nMinFontSize)
            {
                str = pLabel->getString();
                str.erase(str.end() - (int)(str.length()*0.1), str.end());
                str.insert(str.length(), "...");
                isBreak = true;
                isRerun = true;
                CCLOG("X1");
            }
            else pLabel->setTTFConfig(new_c);
            CCLOG("X2");
        }
        else isBreak = true;
    }
    if(isRerun) fitStringInSize(pLabel, str, borderSize, nMinFontSize);
}

void ZYSupport::floatingNotify(Node* target, const std::string& message, const TTFConfig& ttf, const Color3B& color, const Point& position, const int& order, const float& duration, bool isLock)
{
    if(target)
    {
        auto dim_layer = LayerColor::create(Color4B::BLACK);
        target->addChild(dim_layer, order);
        dim_layer->setOpacity(dim_layer->getOpacity()/2);

        auto label = ZYLabel::createWithTTF(ttf, message, TextHAlignment::CENTER, ZYDR_TGVS.width/4*3);
        label->setColor(color);
        label->setPosition(position);
        target->addChild(label, order + 1);

        const float _duration = 0.75f;

        if(!isLock)
        {
            label->setScale(0);                 ///< Make the label to be very small

            ///v Create actions for label
            auto scale_to = ScaleTo::create(_duration, 1.0f);   ///< Scale to 1 - the true size
            auto delay = DelayTime::create(duration);
            auto fade = FadeOut::create(_duration/3);
            auto remove = RemoveSelf::create(true);
            auto label_seq = Sequence::create(scale_to, delay, fade, remove, nullptr);
            auto dim_seq = Sequence::create(DelayTime::create(duration + _duration*2), remove->clone(), nullptr);
            ///^ End create actions

            label->runAction(label_seq);
            dim_layer->runAction(dim_seq);
        }
    }
}
///] Virtual

bool ZYSupport::init()
{
    return true;
}

std::string ZYSupport::toString(int nTab)
{
    std::string ts;
    return ts;
}

void ZYSupport::log()
{

}

///] protected

const Color3B& ZYSupport::convert4FTo3B(const Color4F& color)
{
    const auto color3 = Color3B(color.r * 250.0f, color.g * 250.0f, color.b * 250.0f);
    return color3;
}

NS_ZY_END
