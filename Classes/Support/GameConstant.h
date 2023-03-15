#pragma once

#include "../ZyUwU/ZyUwU.h"

USING_NS_ALL;

class LayerConstant
{
public:
    LayerConstant(std::string sLayerId, bool bIsVisible)
    {
        g_sLayerId = sLayerId;
        g_bIsVisible = bIsVisible;
    }
    std::string g_sLayerId;
    bool g_bIsVisible;
};

static const LayerConstant metaLayer = LayerConstant("meta", false);
static const LayerConstant backgroundLayer = LayerConstant("background", true);

static const std::string globalFont("fonts/arial.ttf");

static const std::string obj_property("property");
static const std::string obj_special("special");
static const std::string obj_square("square");
static const std::string sr_button_default("ui/button/self_remove/default.png");
static const std::string sr_button_clicked("ui/button/self_remove/clicked.png");
static const std::string sr_button_disable("ui/button/self_remove/disable.png");
static const char* sr_background("ui/button/self_remove/background.png");
static const TTFConfig defaultTTFConfig(globalFont, 18);
