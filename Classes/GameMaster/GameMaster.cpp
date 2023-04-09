#include "GameMaster.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Player/Player.h"
#include "Player/UI/PlayerUI.h"
#include "Map/Map.h"
#include "Statics/Statics.h"

#include "external/json/document.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"

using namespace rapidjson;

//#include "Skill/SkillStatics/SkillStatics.h"

GameMaster* GameMaster::sp_pInstance = nullptr;

//// Constructor

GameMaster::GameMaster() :
m_pIsTurnChampion(nullptr),
m_pMarkIsTurnChampion_UP(nullptr), m_pMarkIsTurnChampion_DOWN(nullptr),
m_nChampionIsTurnIndex(-1), m_nRound(0),
m_pRunningScene(nullptr), m_pBattleLayer(nullptr),
m_pClient(nullptr), m_pMap(nullptr), p_bLockEndGame(false),
m_pClientUI(nullptr), p_nBitmask(0)
{

}

void GameMaster::revoke()
{
    //CC_SAFE_RELEASE_NULL(m_pMarkIsTurnChampion_UP);
    //CC_SAFE_RELEASE_NULL(m_pMarkIsTurnChampion_DOWN);
    m_pIsTurnChampion = nullptr;
    m_pClientUI = nullptr;

    for(auto &child: m_vList)
    {
        child = nullptr;
    }
    m_vList.clear();

    m_pRunningScene = nullptr;
    m_pBattleLayer = nullptr;
    p_bLockEndGame = false;
    p_nBitmask = 0;

    CC_SAFE_RELEASE_NULL(m_pMap);
    this->scheduleUpdate();
}

//// Public

bool GameMaster::init()
{
    m_pMarkIsTurnChampion_UP = ZYSprite::create("champion/up.png");
    m_pMarkIsTurnChampion_DOWN = ZYSprite::create("champion/down.png");

    this->addChild(m_pMarkIsTurnChampion_UP);
    this->addChild(m_pMarkIsTurnChampion_DOWN);
    this->scheduleUpdate();
    return true;
}
void GameMaster::generateMap(const std::string& tileMap)
{
    m_pMap = MapManager::create();
    m_pMap->loadTileMap(tileMap);
    m_pMap->setPosition(Point(ZYDR_TGVS.width/2, (ZYDR_TGVS.height + m_pMap->getContentSize().height/2)/2));
    addChild(m_pMap);
    m_pMap->generateArenas();
}

int GameMaster::getBitMask()
{
    p_nBitmask ++;
    return p_nBitmask;
}

void GameMaster::setClientPlayer(Player* target)
{
    if(target)
    {
        //m_pClientUI = PlayerUI::createClientUI();
        target->setIsClient(true);
        //target->addChild(m_pClientUI, 5);
        m_pClient = target;
    }
}

void GameMaster::log()
{

}

void GameMaster::setRunningScene(Scene* var, Layer* layer,ui::Widget::ccWidgetTouchCallback callback)
{
    this->m_pRunningScene = var;
    this->m_pEndGameCallback = callback;
    this->m_pBattleLayer = layer;
}

std::string GameMaster::toString(int nTab)
{
    std::string ts;
    return ts;
}

void GameMaster::setIsTurnChampion(ChampionInGame* champion)
{
    this->m_pIsTurnChampion = champion;
}

void GameMaster::markChampion()
{
    if(m_pIsTurnChampion)
    {
        this->m_pMarkIsTurnChampion_UP->setPosition(Point(m_pIsTurnChampion->getIcon()->getPosition().x, m_pIsTurnChampion->getIcon()->getContentPositionMiddleTop().y + 2*m_pMarkIsTurnChampion_UP->getContentSize().height/3));
        this->m_pMarkIsTurnChampion_DOWN->setPosition(m_pIsTurnChampion->getIcon()->getContentPositionMiddleBottom());
        auto color = m_pIsTurnChampion->getOwner()->getTheColor();
        auto color3b = ZYSP_3BT4F(m_pIsTurnChampion->getOwner()->getTheColor());
        this->m_pMarkIsTurnChampion_UP->setColor(color3b);
        this->m_pMarkIsTurnChampion_DOWN->setColor(color3b);
    }
}

void GameMaster::update(float dt)
{
    this->markChampion();
}

void GameMaster::calculateNewTurn()
{
    std::sort(m_vList.begin(), m_vList.end(), ChampionInGame::SortChampion());
    CCLOG("CALL CALCULATE NEW TURN");
    int next_index = 0;
    if(m_nChampionIsTurnIndex + 1 <= m_vList.size() - 1)
    {
        next_index = m_nChampionIsTurnIndex + 1;
    }
    //if(m_vList[next_index]->isValidTurn())
    {
        m_nRound ++;
        m_pIsTurnChampion = m_vList[next_index];
        m_nChampionIsTurnIndex = next_index;
        CCLOG("INDEX: %d", m_nChampionIsTurnIndex);
        m_pIsTurnChampion->startTurn();
    }
}

void GameMaster::addChampList(std::vector<ChampionInGame*> list)
{
    for(auto &x : list)
    {
        m_vList.push_back(x);
    }
}

void GameMaster::endGame(bool bIsClient)
{
    if(!p_bLockEndGame)
    {
        auto ttf = defaultTTFConfig;
        ttf.fontSize = 50;
        ttf.bold = true;
        auto color = Color3B::BLUE;
        std::string str= "YOU WIN";
        if(bIsClient)
        {
            color = Color3B::RED;
            str = "YOU LOSE";
        }
        floatingNotify(str, ttf, color, ZYDR_TGVS/2, 2, true);
        m_pBattleLayer->getEventDispatcher()->removeAllEventListeners();

        auto button = ui::Button::create(sr_button_default, sr_button_clicked);
        button->setTitleText("CONTINUE");
        CCUB_SSTFSP(button, 0.8);
        button->addTouchEventListener(m_pEndGameCallback);
        button->setPosition(Point(ZYDR_TGVS.width/2, ZYDR_TGVS.height/4));
        m_pBattleLayer->addChild(button);
        button->setGlobalZOrder(7);
        p_bLockEndGame = true;
    }
}
void GameMaster::floatingNotify(const std::string& message, const TTFConfig& ttf, const Color3B& color, const Point& position, const float& duration, bool isLock)
{
    ZYSP_GI->floatingNotify(m_pBattleLayer, message, ttf, color, position, 5, duration, isLock);
}

void GameMaster::floatingNotify(const std::string& message)
{
    auto ttf = defaultTTFConfig;
    ttf.fontSize = 50;
    floatingNotify(message, ttf, Color3B::BLACK, ZYDR_TGVS/2);
}

float GameMaster::magicDmgCalculator(Statics* defender, SkillStatics* attacker, Point pos)
{
    float mr = defender->getMagicResistance() - attacker->getMagicPieInNum();
    float mrToDc = Fraction::fastPercent(MRFB - (MRFF * mr)/(MRFB + MRFF * abs(mr)));
    // Total magic resistance in decimal (0.xxx)
    float totalMrInDc = mrToDc * (1 - attacker->getTheMagicPiercing().getPcAmount());
    // Run gacha if this crit

    bool isCrit = critStar(pos, attacker->getMagicCritRate());
    // Run crit

    // Total magic damage
    float totalMd = (isCrit*attacker->getMagicCritDmgMul() + 1) * attacker->getMagicDmg();
    float causeDmg = (1 - totalMrInDc) * totalMd;

    return causeDmg;
}

float GameMaster::physicDmgCalculator(Statics* defender, SkillStatics* attacker, Point pos)
{
    float ar = defender->getArmor() - attacker->getPhysicPieInNum();
    float arToDc = Fraction::fastPercent(PRFB - (PRFF * ar)/(PRFB + PRFF * abs(ar)));
    // Total armor resistance in decimal (0.xxx)
    float totalArInDc = arToDc * (1 - attacker->getThePhysicPiercing().getPcAmount());
    // Run gacha if this crit

    bool isCrit = critStar(pos, attacker->getPhysicCritRate());
    // Run crit

    // Total magic damage
    float totalMd = (isCrit*attacker->getPhysicCritDmgMul() + 1) * attacker->getPhysicDmg();
    float causeDmg = (1 - totalArInDc) * totalMd;

    return causeDmg;
}

float GameMaster::totalDmgCalculator(Statics* defender, SkillStatics* attacker, Point pos)
{
    return magicDmgCalculator(defender, attacker, pos) + physicDmgCalculator(defender, attacker, pos);
}

float GameMaster::attackScene(ChampionInGame* attacker, std::vector<ChampionInGame*>& defenders)
{
    if(defenders.empty())
    {
        return 0;
    }
    float total_delay = 0;
    Vector<FiniteTimeAction*> vec;
    for(auto&x : defenders)
    {
        auto delay = attackScene(attacker, x, true);
        total_delay += delay;
        vec.pushBack(Sequence::create(CallFunc::create([&, attacker, x](){
            attackScene(attacker, x);
        }), DelayTime::create(delay), nullptr));
    }
    auto seq = Sequence::create(vec);
    runAction(seq);
    return total_delay;
}

float GameMaster::attackScene(ChampionInGame* attacker, ChampionInGame* defender, bool isPreCalculate)
{
    auto path = attacker->getIcon()->getResourceName();
    auto name = path.substr(9, path.length() - 13);
    auto path_name = name + "_attack";
    auto half_path = champion_animation_dir + std::string(path_name);
    auto ani_path = half_path + ".png";
    auto ani_plist = half_path + ".plist";

    int num = numberFrames(ani_plist, path_name);
    auto total_delay = (num + 1) * animation_dilation_each_frame + animation_move_time;

    if(isPreCalculate) return total_delay;

    auto def_path = defender->getIcon()->getResourceName();
    auto def_name = (def_path.substr(9, def_path.length() -13) + "_def");
    auto ani_def_path = "champion/ani/" + def_name += ".png";

    auto dim = LayerColor::create(Color4B::BLACK);
    m_pBattleLayer->addChild(dim, 9);
    dim->setOpacity(225);

    auto atk =  ZYSprite::create(path);
    atk->setFlippedX(true);
    m_pBattleLayer->addChild(atk, 11);

    auto def = defender->getIcon()->clone();
    m_pBattleLayer->addChild(def, 10);

    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile(ani_plist);

    Vector<SpriteFrame*> frames;
    for (int i = 0; i <= num; i++) {
        std::string frameName = StringUtils::format((path_name + "_%d.png").c_str(), i);
        auto frame = cache->getSpriteFrameByName(frameName);
        frames.pushBack(frame);
    }

    auto animation = Animation::createWithSpriteFrames(frames, animation_dilation_each_frame);
    auto animate = Animate::create(animation);

    def->setPosition(Point(ZYDR_TGVS.width/3, ZYDR_TGVS.height/2));
    auto targetPos = Point( def->getContentPositionMiddleRight().x + atk->getContentSize().width/2,def->getPositionY());
    atk->setPosition(Point(ZYDR_TGVS.width/3*2, ZYDR_TGVS.height/2));

    auto delay = DelayTime::create(total_delay);
    auto rm = RemoveSelf::create(true);
    auto mt = MoveTo::create(animation_move_time, targetPos);

    auto cb = CallFunc::create([&, ani_def_path, def]()
                               {
                                    def->replaceTexture(ani_def_path);
                               });

    auto index = getAttackIndexInAnimation(name);
    auto dim_sq = Sequence::create(DelayTime::create(animation_move_time + animation_dilation_each_frame), DelayTime::create((num) * animation_dilation_each_frame), rm,  nullptr);
    auto def_sq = Sequence::create(DelayTime::create(animation_move_time + animation_dilation_each_frame*index), cb, DelayTime::create((num - index + 1) * animation_dilation_each_frame), rm->clone(), nullptr);
    auto atk_sq = Sequence::create(mt, animate, rm->clone(), nullptr);

    atk->runAction(atk_sq);
    def->runAction(def_sq);
    dim->runAction(dim_sq);

    return total_delay;
}

const int GameMaster::getAttackIndexInAnimation(const std::string& name)
{
    auto path = champion_animation_dir + std::string(name) + ".json";
    auto data = CCFU_GI->getStringFromFile(path);
    Document doc;
    doc.Parse(data.c_str());
    if(doc.HasParseError())
    {
        CCLOG("ERROR");
        return 1;
    }
    const rapidjson::Value& value = doc[name.c_str()];
    return value["attack_index"].GetInt();
}

bool GameMaster::critStar(Point pos, float chance)
{
    if(ZYGC_GI->runGacha(chance))
    {
        this->critStar(pos);
        return true;
    }
    return false;
}

void GameMaster::critStar(Point pos)
{

}

int GameMaster::numberFrames(const std::string& path, const std::string& key)
{
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(path);
    int numFrames = 0;
    ValueMap& framesDict = dict["frames"].asValueMap();
    for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter) {
        std::string skey = iter->first;
        if (skey.find(key) == 0) {
            numFrames++;
        }
    }

    return numFrames-1;
}
