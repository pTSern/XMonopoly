#include "ZYGacha.h"
NS_ZY_BEGIN

//

GachaItem::GachaItem()
{

}

bool GachaItem::init()
{
    return true;
}

void GachaItem::log()
{
    ZY_EZ_LOG;
}

std::string GachaItem::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);

    ts += tab + " + Rate - Amount - Type: " + ZY_SP_NUMBER_TO_STRING(m_nRate) + " - " + ZY_SP_NUMBER_TO_STRING(m_nAmount) + " - " + m_sItemType;

    return ts;
}

GachaItem* GachaItem::createWithProperties(int nRate, int nAmount, std::string sItemType)
{
    auto p = GachaItem::create();
    p->setRate(nRate);
    p->setAmount(nAmount);
    p->setItemType(sItemType);

    return p;
}
std::vector<GachaItem*> GachaItem::createItemList(GachaItem *pItem, ...)
{
    va_list args;
    va_start(args, pItem);
    std::vector<GachaItem*> vList;

    if(pItem)
    {
        vList.push_back(pItem);
        GachaItem *pElement = va_arg(args, GachaItem*);
        while(pElement)
        {
            vList.push_back(pElement);
            pElement = va_arg(args, GachaItem*);
        }
    }

    va_end(args);

    return vList;
}

std::vector<GachaItem*> ZYGacha::generateSuccessList(std::vector<GachaItem *> vList, int nRollTime)
{
    int nTotalRate = 0;
    int nTotalRoll = 0;
    int nVecIndex = 0;

    std::vector<GachaItem*> vSList;
    if(vList.size() < 0) return vSList;

    for(int i = 0; i < vList.size(); i ++)
    {
        nTotalRate+= vList[i]->getRate();
    }
    
    while (nTotalRoll < nRollTime)
    {
        bool bIsFinish = false;
        while(!bIsFinish)
        {
            if(ZYGacha::getInstance()->runGacha(Fraction::toFloat(vList[nVecIndex]->getRate(), nTotalRate)))
            {
                bIsFinish = true;
                nTotalRoll++;
                vSList.push_back(vList[nVecIndex]);
                nVecIndex = 0;
                break;
            }
            nVecIndex++;
            if(nVecIndex >= vList.size()) nVecIndex = 0;
        }
        bIsFinish = false;
    }

    return vSList;

}

//

ZYGacha* ZYGacha::sp_pInstance = nullptr;

ZYGacha::ZYGacha()
{

}



bool ZYGacha::runGacha(float fRate, bool bIsPercent)
{
    if (!bIsPercent) fRate /= 100;

    if (fRate >= 1) return true;
    if (fRate <= 0) return false;

    int nRate = sgc_nMaxRateDenominator * fRate;

    Fraction frac = Fraction::fastShortCut(nRate, sgc_nMaxRateDenominator);
    int luckyNumber = cocos2d::random(1, frac.getDenominator());

  //  CCLOG("-----BEGIN-----");
  //  frac.log();
  //  CCLOG("%d", luckyNumber);
  //  CCLOG("------END------");

    if ( frac.getNumerator() * 2 <= frac.getDenominator() && luckyNumber % 2 == 0 && luckyNumber <= frac.getNumerator() * 2)
    {
        return true;
    }

    if (frac.getNumerator() * 2 > frac.getDenominator())
    {
        if (luckyNumber % 2 == 0)
        {
            return true;
        }
        else if (luckyNumber % 2 != 0 && luckyNumber <= (frac.getNumerator() - (frac.getDenominator() / 2)) - 1)
        {
            return true;
        }
    }

    return false;
}

//Virutal

bool ZYGacha::init()
{
    return true;
}

void ZYGacha::log()
{

}

std::string ZYGacha::toString(int nTab)
{
    std::string ts;
    return ts;
}


NS_ZY_END