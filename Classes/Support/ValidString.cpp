#include "ValidString.h"

#include "external/json/document.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"

///] Constructor

ValidString::ValidString()
{

}

///] Static

std::string ValidString::getChampionName(const std::string& resourcePath)
{
    return resourcePath.substr(9, resourcePath.length() - 13);
}

std::string ValidString::getChampionAttackPath(const std::string& name)
{
    return name + champion_attack_tail_path;
}

std::string ValidString::getChampionIdlePath(const std::string& name)
{
    return name + champion_idle_tail_path;
}

std::string ValidString::getChampionDefendPath(const std::string& name)
{
    return name + champion_defend_tail_path;
}

std::string ValidString::getHalfPathOfChampion(const std::string& name)
{
    return champion_animation_dir + name;
}

std::string ValidString::getPngPath(const std::string& halfPath)
{
    return halfPath + file_format_png;
}

std::string ValidString::getPlistPath(const std::string& halfPath)
{
    return halfPath + file_format_plist;
}

std::string ValidString::getJsonPath(const std::string& halfPath)
{
    return halfPath + file_format_json;
}

int ValidString::getAttackIndexOfAnimation(const std::string& name)
{
    auto path = getJsonPath(champion_animation_dir + name);
    auto data = CCFU_GI->getStringFromFile(path);
    rapidjson::Document doc;
    doc.Parse(data.c_str());
    if(doc.HasParseError())
    {
        return 1;
    }
    const rapidjson::Value& value = doc[name.c_str()];
    return value[attack_index_string_in_json].GetInt();
}

int ValidString::numberFrames(const std::string& plist, const std::string& key)
{
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(plist);
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

Vector<SpriteFrame*> ValidString::generateFrames(const std::string& key, const int frameNum)
{
    Vector<SpriteFrame*> frames;

    for(int i = 0; i <= frameNum; i ++)
    {
        std::string frame_name = StringUtils::format((key + "_%d.png").c_str(), i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
        frames.pushBack(frame);
    }
    return frames;
}

Vector<SpriteFrame*> ValidString::generateFrames(const std::string& key, const std::string& plist)
{
    Vector<SpriteFrame*> frames;
    auto frameNum = numberFrames(plist, key);

    for(int i = 0; i <= frameNum; i ++)
    {
        std::string frame_name = StringUtils::format((key + "_%d.png").c_str(), i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name);
        frames.pushBack(frame);
    }
    return frames;
}
