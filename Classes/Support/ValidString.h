#pragma once

#include "ZyUwU/ZyUwU.h"

#include "GameConstant.h"

class ValidString
{
public:
    static std::string getChampionName(const std::string& resourcePath);
    static std::string getChampionAttackPath(const std::string& name);
    static std::string getChampionIdlePath(const std::string& name);
    static std::string getChampionDefendPath(const std::string& name);
    static std::string getHalfPathOfChampion(const std::string& pathName);
    static std::string getPngPath(const std::string& halfPath);
    static std::string getPlistPath(const std::string& halfPath);
    static std::string getJsonPath(const std::string& halfPath);

    static int getAttackIndexOfAnimation(const std::string& name);
    static int numberFrames(const std::string& plist, const std::string& key);
    static Vector<SpriteFrame*> generateFrames(const std::string& key, const int framesNum);
    static Vector<SpriteFrame*> generateFrames(const std::string& key, const std::string& plist);
private:
    ValidString();
};