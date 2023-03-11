#include "Arena.h"

//// Constructor

Arena::Arena() :
m_Coord(Dir::NE, 0),
m_pTitle(nullptr), m_pRect(nullptr),
m_cColor(Color4F::RED), m_nDrawRectOrder(0), m_bIsDrewRect(false),
m_Left(0,0), m_Top(0,0), m_Right(0,0), m_Bottom(0,0)
{
    m_vEffectLayer.reserve(2);
    m_vIcons.reserve(2);
    m_vChampions.reserve(2);
}

Arena::~Arena()
{
    CC_SAFE_RELEASE(m_pTitle);
    CC_SAFE_RELEASE(m_pRect);
    for(auto &effect : m_vEffectLayer)
    {
        CC_SAFE_RELEASE(effect);
    }
    for(auto &sprite : m_vIcons)
    {
        CC_SAFE_RELEASE(sprite);
    }
    for(auto &champs : m_vChampions)
    {
        CC_SAFE_RELEASE(champs);
    }
}
//// Public

//Virtual

bool Arena::init()
{
    //initWithProperties("DARK", Coordinate(Dir::NE, 0), Size(0,0));
    return true;
}

void Arena::log()
{
    ZY_EZ_LOG;
}

std::string Arena::toString(int nTab)
{
    std::string ts = GameObject::toString(nTab);
    std::string tab = ZY_SP_TAB(nTab);
    ZY_TSHNP(ts, tab, nTab, " Coordinate: ", m_Coord);
    ts += tab + " + Size: " + ZY_SP_NUMBER_TO_STRING(m_Size.width) + " - " + ZY_SP_NUMBER_TO_STRING(m_Size.height);
    ts += tab + " + Is Buyable: " + ZY_SP_NUMBER_TO_STRING((int)m_bIsBuyAble);
    ts += tab + " + Left: " + ZYSP_VTS(m_Left);
    ts += tab + " + Right: " + ZYSP_VTS(m_Right);
    ts += tab + " + Top: " + ZYSP_VTS(m_Top);
    ts += tab + " + Bot: " + ZYSP_VTS(m_Bottom);

    ZY_TSHV(ts, tab, nTab, " + Effect Layer ", m_vEffectLayer);
    ZY_TSHV(ts, tab, nTab, " + Champions ", m_vChampions);

    for(int i = 0; i < m_vChampions.size(); i++){
        ts += tab + " + Champions [" + ZY_SP_NUMBER_TO_STRING(i) + "]" +
                m_vChampions[i]->toString();
    }

    return ts;
}

void Arena::config()
{
    //int x = (1 - ((int)m_Coord.g_bIsFlip * 2));
    m_pTitle->setColor(Color3B::BLACK);
    m_pTitle->setHorizontalAlignment(TextHAlignment::CENTER);
    m_pTitle->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    this->addChild(m_pRect);
    this->addChild(m_pTitle, 1);
}

bool Arena::initWithProperties(const std::string& sTitle, Coordinate &coord, Size rectSize, Point left)
{
    this->setRectPoint(left, rectSize);
    m_pRect = DrawNode::create();

    TTFConfig ttfConfig(globalFont, 20, GlyphCollection::DYNAMIC,nullptr,false , 0, false, true);
    m_pTitle = ZYLabel::createWithTTF(ttfConfig, sTitle);
    Size size = Size(m_Left.distance(m_Bottom), m_Left.distance(m_Bottom));
    ZYSP_FSIS(m_pTitle, sTitle, size, 14);
    m_Coord = coord;

    return true;
}

void Arena::update(float dt)
{
    //if(!m_vChampions.empty())
    //{
    //    this->autoSortChampion();
    //}
    //this->autoRotate();
    //this->autoSetPosition();
    if(m_nDrawRectOrder >= 1 && !m_bIsDrewRect)
    {
        m_bIsDrewRect = true;
        this->drawRect();
    }
    else if(m_nDrawRectOrder <= 0 && m_bIsDrewRect)
    {
        m_bIsDrewRect = false;
        this->revokeRect();
    }
}

void Arena::onLand(ChampionInGame *pChamp)
{
    ////Cast effect to lander
    for(auto &x : m_vEffectLayer)
    {
        //Cast effect
    }
}
//public

void Arena::setCoordinate(Coordinate &coord)
{
    if(m_Coord.g_eDir == coord.g_eDir && m_Coord.g_nIndex == coord.g_nIndex)
    {
        return;
    }
    m_Coord.g_eDir = coord.g_eDir;
}

void Arena::autoSortChampion()
{
    auto n = this->getNumberChampionInArena();
    if(n <= 0) return;
    auto midLeftBot = m_Left.getMidpoint(m_Bottom);
    auto midTopRight = m_Top.getMidpoint(m_Right);
    for(int i = 0; i < n; i++)
    {
        m_vChampions[i]->setPosition((i+1)*(midTopRight + midLeftBot)/(n+1));
    }
}

void Arena::autoRotate()
{

}

void Arena::autoSetPosition()
{
}

Point Arena::getMoveAblePosition()
{
    auto n = this->getNumberChampionInArena();
    if(n<=0) {
        return getMiddlePoint();
    }
    auto midLeftBot = m_Left.getMidpoint(m_Bottom);
    auto midTopRight = m_Top.getMidpoint(m_Right);

    auto x =  Point((n)*(midTopRight + midLeftBot)/(n+1));
    CCLOG("%s", ZYSP_VTS(x).c_str());
    return x;
}

void Arena::addChampion(ChampionInGame *pChamp)
{
    //this->autoSortChampion();
    m_vChampions.push_back(pChamp);
}

void Arena::removeChampion(ChampionInGame *pChamp)
{
    for (auto x = 0; x < m_vChampions.size(); x ++ )
    {
        if(m_vChampions[x] == pChamp)
        {
            m_vChampions.erase(m_vChampions.begin() + x);
            break;
        }
    }
    //this->autoSortChampion();
}

void Arena::setTitle(std::string text)
{
    m_pTitle->setString(text);
}

void Arena::addDrawRectOrder()
{
    m_nDrawRectOrder++;
}

void Arena::reduceDrawRectOrder()
{
    m_nDrawRectOrder--;
}

void Arena::setRectPoint(Point cLeft, Size cSize)
{
    this->setRectPoint(cLeft.x, cLeft.y, cSize.width, cSize.height);
}

void Arena::setRectPoint(float xx, float yy, float width, float height)
{
    auto ah = MAP_MNG_GI->getAngleHorizonInRad();

    this->m_Left = Point(xx, yy);
    this->m_Top = Point(xx + height*cos(ah), yy +height*sin(ah));
    this->m_Right = Point(xx + height*cos(ah) + width*cos(ah), yy - width*sin(ah) + height*sin(ah));
    this->m_Bottom = Point(xx + width*cos(ah), yy - width*sin(ah));
}

void Arena::drawRect()
{
    if(!m_pRect) m_pRect = DrawNode::create();
    m_pRect->drawRect(m_Left, m_Top, m_Right, m_Bottom, m_cColor);
}

void Arena::revokeRect()
{
    m_pRect->clear();
}

bool Arena::isContainPoint(Point point)
{
    if(SmartAlgorithm::checkPointOnLine(m_Left, m_Top, point)) return true;
    if(SmartAlgorithm::checkPointOnLine(m_Top, m_Right, point)) return true;
    if(SmartAlgorithm::checkPointOnLine(m_Right, m_Bottom, point)) return true;
    if(SmartAlgorithm::checkPointOnLine(m_Bottom, m_Left, point)) return true;
    return false;
}

Point Arena::getMiddlePoint()
{
    auto midLeftBot = m_Left.getMidpoint(m_Bottom);
    auto midTopRight = m_Top.getMidpoint(m_Right);
    return midLeftBot.getMidpoint(midTopRight);
}

//Virtual
