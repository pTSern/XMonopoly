#pragma once

#include "../ZyUwU/ZyUwU.h"
#include "Support/GameConstant.h"
#include "User/Helper.h"
#include "Support/Coordinate.h"
//#include "Arena/Factory/ArenaFactory.h"

USING_NS_ALL;

#define MAP_MNG_GI MapManager::getInstance()

#define LOAD_LAYER(__TILE_MAP__, __LAYER_CONSTANT__, __LAYER_MAP__) \
do {                                                                   \
	auto ret = __TILE_MAP__->getLayer(__LAYER_CONSTANT__.g_sLayerId);\
	if(ret)      \
    {                                                                  \
        __LAYER_MAP__[__LAYER_CONSTANT__.g_sLayerId] = __TILE_MAP__->getLayer(__LAYER_CONSTANT__.g_sLayerId); \
        __LAYER_MAP__[__LAYER_CONSTANT__.g_sLayerId]->setVisible(__LAYER_CONSTANT__.g_bIsVisible);\
    }\
} while(0);	\

class Arena;
class Player;
class HospitalArena;
class SpawnArena;
BEGIN_CREATE_INSTANCE_REFCLASS(MapManager, cocos2d::Node)

public:
    void generateGameBoard();
	cocos2d::TMXTiledMap* getTileMap();
	cocos2d::TMXLayer* getLayer(std::string sLayerId);
	void loadTileMap(std::string sMapName);
	cocos2d::Point getPosition();
	void setPosition(cocos2d::Point pos);
	void setAnchorPoint(cocos2d::Point anchor);

	void loadMapFromFile(std::string sFileName);

	void config();
	void setScale(cocos2d::Point cScale);

	CREATE_GET_FUNC(getAngleHorizonInRad, float, p_fAngleHorizon);
	CREATE_GET_FUNC(getAngleHorizon, float, ZY_SUPPORT_GI->radToDegree(p_fAngleHorizon));
	CREATE_GET_FUNC(getAngleVerticalInRad, float, p_fAngleVertical);
	CREATE_GET_FUNC(getAngleVertical, float, ZY_SUPPORT_GI->radToDegree(p_fAngleVertical));
	CREATE_GET_FUNC(getArenaGroup, cocos2d::TMXObjectGroup*, p_pArenaGroup);
	CREATE_GET_FUNC(getWorldSize, Size, p_world);
	CREATE_GET_FUNC(getObjectTileSize, Size, p_objectTileSize);
	CREATE_GET_FUNC(getTrueObjectTileSize, Size, p_tObjectTile);
	CREATE_GET_FUNC(getTrueWorldSize, Size, p_tWorld);
	CREATE_GET_FUNC(getArenas, std::vector<Arena*>, p_vArenas);
	CREATE_SET_GET_FUNC(setClientPlayer, getClientPlayer, Player*, p_pClientPlayer);
	CREATE_GET_FUNC(getHospitalCoord, Coordinate, p_hospital);
	Arena* getArenaByCoord(Coordinate coord);

	/**
	* Check if input position is contact to a collision object
	* 
	* @pragma: position need to be checked 
	* @return: TRUE -> Contaced to a collision object
	* @return: FALSE -> NO Contact happen
	*/
	cocos2d::Size getMapPixelSize();
	//void drawRectOnArena();
    void revoke();
	virtual void update(float dt);
    void generateArenas();
    Size getTrueObjectSize(const Size& objectSize);
	Size getTrueObjectSize(const float& width, const float &height);
	Point getTrueObjectPoint(const Point& objectPoint);
	Point getTrueObjectPoint(const float& xx, const float &yy);
	bool onTouch(Touch *touch, Event *event);
	bool endTouch(Touch *touch, Event *event);

protected:
    void generatePropertyArenas(ValueMap obj);
    void generateSpecialArenas(ValueMap obj);
	void createTaxArena(ValueMap obj);
	void createHospitalArena(ValueMap obj);
	void createShopArena(ValueMap obj);
	void createAirPortArena(ValueMap obj);
	void createSpawnArena(ValueMap obj);

private:
	//DrawNode *p_pRect;
	cocos2d::TMXTiledMap* p_pTileMap;						///< the tiled map
    std::map<std::string, cocos2d::TMXLayer*> p_mLayers;	///< array of layer of the map
	cocos2d::TMXObjectGroup* p_pArenaGroup;					///< the arena's group-object of the map
	float p_fAngleHorizon, p_fAngleVertical;				///< the horizon and vertical angel of the map, see document for more details
    Size p_tObjectTile, p_tWorld;							///< the true object tile size and map size base on cocos2dx's pixel
	Size p_objectTileSize, p_world;							///< the object tile size and map size base on tile's pixel
    std::vector<Arena*> p_vArenas;							///< array of Arena in the map
	Player* p_pClientPlayer;								///< weak reference to the client player, most use for selecting arena

	Coordinate p_hospital;

END_CREATE_INSTANCE_REFCLASS;
