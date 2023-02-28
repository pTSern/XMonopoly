#include "ZYSupport.h"
#include "ZyUwU/2d/ZYLabel.h"

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

std::string ZYSupport::tabString(int nTab)
{
    if (0 > nTab || nTab > 10) nTab = 2;
    std::string tab = "\n";
    for (int i = 0; i < nTab; i++) tab += "\t";
    return tab;
}

std::string ZYSupport::numberToString(float fNum)
{
    if(this->isInt(fNum)) return this->shorterDecimal(fNum, 0);
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
//Virtual

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
//protected

NS_ZY_END
