#pragma once

#include "../ChampionInGame.h"

USING_NS_ALL;

/**
*   This is a test-champion
*/
BEGIN_CREATE_REFCLASS(TesterBot, ChampionInGame)

public:
    static TesterBot* createWithProperties(Champion *pChamp, ChampionUI *pUI, Dice* pDice, SkillManager* vSkillDeck);
    virtual void startTurn();
    void chooseSkill();

END_CREATE_REFCLASS