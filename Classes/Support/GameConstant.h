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

static const std::string special_arena_spawn_key("SPAWN");
static const std::string special_arena_tax_key("TAX");
static const std::string special_arena_hospital_key("HOSPITAL");
static const std::string special_arena_shop_key("SHOP");
static const std::string special_arena_airport_key("AIRPORT");

static const std::string EVENT_FINISH_LOADED("event_loaded");

static const float magic_res_formula_base(1);
static const float magic_res_formula_factory(0.05f);

#define MRFB magic_res_formula_base
#define MRFF magic_res_formula_factory

static const float physic_res_formula_base(1);
static const float physic_res_formula_factory(0.05f);

#define PRFB physic_res_formula_base
#define PRFF physic_res_formula_factory

static const float animation_dilation_each_frame(0.125f);
static const float animation_move_time(0.25f);

static const std::string champion_animation_dir("champion/ani/");


static const float projectile_move_time(0.25f);

static const std::string property_icon("ui/button/self_remove/icon.png");
static const std::string property_front_icon("ui/button/self_remove/icon_front.png");
