#pragma once

#include "ZyUwU/ZyUwU.h"
#include "GlobalArena.h"
#include "GameObject/GameObject.h"
#include "Support/Coordinate.h"
#include "GameEffect/GameEffect.h"
#include "Support/GameConstant.h"
#include "Map/Map.h"
#include "Player/Player.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(Arena, GameObject)

public:
    struct SortArena
    {
        inline bool operator() (Arena* l, Arena* r)
        {
            return l->getCoordinate().g_nIndex < r->getCoordinate().g_nIndex;
        }
    };
public:
    enum class Type
    {
        ARENA = 0,
        PROPERTY,
        SPECIAL
    };
    void setCoordinate(Coordinate &coord);
    void autoSortChampion();
    void autoRotate();
    void autoSetPosition();

    Point getMoveAblePosition();

    CREATE_GET_FUNC(getCoordinate, Coordinate, m_Coord);
    CREATE_GET_FUNC(getChampionInArena, std::vector<ChampionInGame*>, m_vChampions);
    CREATE_GET_FUNC(getEffectLayer, std::vector<GameEffect*>, m_vEffectLayer);
    CREATE_GET_FUNC(getNumberChampionInArena, int, m_vChampions.size());

    CREATE_GET_FUNC(getLeftPoint, Point, m_Left);
    CREATE_GET_FUNC(getRightPoint, Point, m_Right);
    CREATE_GET_FUNC(getTopPoint, Point, m_Top);
    CREATE_GET_FUNC(getBottomPoint, Point, m_Bottom);
    CREATE_GET_FUNC(getRectColor, Color4F, m_cColor);
    CREATE_GET_FUNC(getType, Type, m_eType);

    void setRectColor(Color4F color);

    void addChampion(ChampionInGame *pChamp, bool callOnLand = false);
    void removeChampion(ChampionInGame *pChamp);

    void addIcon(ZYSprite *pSprite);
    void addIcon(std::string sSprite);

    void setTitle(std::string text);
    void setRectPoint(Point cLeft, Size cSize);
    void setRectPoint(float xx, float yy, float width, float height);
    void addDrawRectOrder();
    void reduceDrawRectOrder();

    void drawRect();
    void revokeRect();

    bool isContainPoint(Point point);

    Point getMiddlePoint();

public:
    virtual void update(float dt);
    virtual void onLand(ChampionInGame *pChamp);
    virtual ~Arena();
    virtual void config();
    virtual bool initWithProperties(const std::string& sTitle, Coordinate &coord, Size rectSize, Point left);

protected:
    Point m_Left, m_Top, m_Right, m_Bottom;
    Color4F m_cColor;
    DrawNode* m_pRect;
    int m_nDrawRectOrder;
    bool m_bIsDrewRect;
    Type m_eType;

    Coordinate m_Coord;

    Size m_Size;
    bool m_bIsBuyAble;

    ZYLabel* m_pTitle;

    std::vector<GameEffect*> m_vEffectLayer;
    std::vector<ZYSprite*> m_vIcons;
    std::vector<ChampionInGame*> m_vChampions;

private:

END_CREATE_REFCLASS


