#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME Monopoly)

project(${APP_NAME})

if(XCODE)
    if(NOT DEFINED CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET)
        SET (CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 8.0)
    endif()
endif()

if(NOT DEFINED BUILD_ENGINE_DONE) # to test PrC into root project
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
        Classes/AppDelegate.cpp

        Classes/GameObject/GameObject.cpp
        Classes/GameObject/Economy/Economy.cpp
        Classes/GameObject/XProperties.cpp
        Classes/GameObject/Economy/Manager/EconomyManager.cpp

        Classes/ZyUwU/ZyUwU.cpp
        Classes/ZyUwU/2d/ZYSprite.cpp
        Classes/ZyUwU/2d/ZYEffect.cpp
        Classes/ZyUwU/2d/ZYLabel.cpp
        Classes/ZyUwU/2d/ZYShaderHelper.cpp
        Classes/ZyUwU/2d/ZYSupport2D.cpp
        Classes/ZyUwU/2d/ZYAction.cpp
        Classes/ZyUwU/math/ZYFraction.cpp
        Classes/ZyUwU/math/SmartAlgorithm.cpp
        Classes/ZyUwU/gacha/ZYGacha.cpp
        Classes/ZyUwU/data-manager/ZYDatabase.cpp
        Classes/ZyUwU/data-manager/sqlite3.c
        Classes/ZyUwU/base/ZYNodeExtend.cpp
        Classes/ZyUwU/base/ZYDirector.cpp
        Classes/ZyUwU/base/ZYSupport.cpp
        Classes/ZyUwU/ui/ZYUI.cpp

        Classes/GameScene/LoginScene.cpp
        Classes/GameScene/MainMenu.cpp
        Classes/GameScene/BattleScene.cpp
        Classes/GameScene/ShopScene.cpp
        Classes/GameScene/MarketScene.cpp
        Classes/GameScene/GameOver.cpp

        Classes/LogManager/LogManager.cpp

        Classes/Dice/Dice.cpp

        Classes/GameMaster/GameMaster.cpp

        Classes/Audio/SoundManager.cpp

        Classes/Player/Player.cpp
        Classes/Player/UI/PlayerUI.cpp
        Classes/Player/ViewPoint/ViewPoint.cpp
        Classes/Player/Action/PlayerAction.cpp
        Classes/Player/Brain/AI/BotPlayer.cpp

        Classes/SelectHelper/SelectHelper.cpp

        Classes/Champion/Champion.cpp
        Classes/Champion/Mage/Mage.cpp

        Classes/ChampionInGame/ChampionInGame.cpp
        Classes/ChampionInGame/UI/ChampionUI.cpp
        Classes/ChampionInGame/UI/ChampionHUD.cpp

        Classes/Map/Map.cpp

        Classes/Statics/Statics.cpp
        Classes/Statics/Extension.cpp

        Classes/Skill/Skill.cpp
        Classes/Skill/Condition/Condition.cpp
        Classes/Skill/SkillCard/SkillCard.cpp
        Classes/Skill/SkillStatics/SkillStatics.cpp
        Classes/Skill/SkillInGame/SkillInGame.cpp
        Classes/Skill/SkillInGame/MoveBy/SkillMoveBy.cpp
        Classes/Skill/SkillManager/SkillManager.cpp
        Classes/Skill/SkillType/SkillType.cpp
        Classes/Skill/TargetType/TargetType.cpp
        Classes/Skill/TargetType/NoTarget/NoTarget.cpp
        Classes/Skill/TargetType/NoTarget/Toggle/Toggle.cpp
        Classes/Skill/TargetType/NoTarget/NormalCast/NormalCast.cpp
        Classes/Skill/TargetType/Factory/TargetTypeFactory.cpp

        Classes/GameEffect/Buff/Buff.cpp
        Classes/GameEffect/Debuff/Debuff.cpp
        Classes/GameEffect/GameEffect.cpp

        Classes/Support/Coordinate.cpp
        Classes/Support/ValidString.cpp

        Classes/Arena/Arena.cpp
        Classes/Arena/SpecialArena/SpecialArena.cpp
        Classes/Arena/Property/Property.cpp
        Classes/Arena/GlobalArena.cpp
        Classes/Arena/SpecialArena/Factory/Factory.cpp
        Classes/Arena/SpecialArena/Tax/Tax.cpp
        Classes/Arena/SpecialArena/Airport/Airport.cpp
        Classes/Arena/SpecialArena/Shop/Shop.cpp
        Classes/Arena/SpecialArena/Spawn/Spawn.cpp
        Classes/Arena/SpecialArena/Hospital/Hospital.cpp

        Classes/User/User.cpp
        Classes/User/Information/UserInformation.cpp
        Classes/User/Information/GameDetails.cpp
        Classes/User/UI/UserUI.cpp
        Classes/User/UI/IngameUI.cpp
        Classes/User/Audio/Audio.cpp
     )
list(APPEND GAME_HEADER
        Classes/AppDelegate.h

        Classes/GameObject/GameObject.h
        Classes/GameObject/AGameObject.h
        Classes/GameObject/XProperties.h
        Classes/GameObject/Economy/Manager/EconomyManager.h
        Classes/GameObject/Economy/Economy.h

        Classes/LogManager/LogManager.h

        Classes/ZyUwU/platform/ZYMacros.h
        Classes/ZyUwU/platform/CCMacrosSupport.h
        Classes/ZyUwU/platform/android/ZYPlatformDefine-android.h
        Classes/ZyUwU/ZyUwU.h
        Classes/ZyUwU/2d/ZYSprite.h
        Classes/ZyUwU/2d/ZYShaderHelper.h
        Classes/ZyUwU/2d/ZYEffect.h
        Classes/ZyUwU/2d/ZYLabel.h
        Classes/ZyUwU/2d/ZYSupport2D.h
        Classes/ZyUwU/2d/ZYAction.h
        Classes/ZyUwU/math/ZYFraction.h
        Classes/ZyUwU/math/SmartAlgorithm.h
        Classes/ZyUwU/gacha/ZYGacha.h
        Classes/ZyUwU/data-manager/ZYDatabase.h
        Classes/ZyUwU/data-manager/sqlite3.h
        Classes/ZyUwU/base/ZYDirector.h
        Classes/ZyUwU/base/ZYConstant.h
        Classes/ZyUwU/base/ZYNodeExtend.h
        Classes/ZyUwU/base/ZYSupport.h
        Classes/ZyUwU/ui/ZYUI.h

        Classes/GameScene/LoginScene.h
        Classes/GameScene/MainMenu.h
        Classes/GameScene/BattleScene.h
        Classes/GameScene/ShopScene.h
        Classes/GameScene/MarketScene.h
        Classes/GameScene/GameOver.h

        Classes/Dice/Dice.h

        Classes/GameMaster/GameMaster.h

        Classes/Audio/SoundManager.h

        Classes/Player/Player.h
        Classes/Player/UI/PlayerUI.h
        Classes/Player/ViewPoint/ViewPoint.h
        Classes/Player/Action/PlayerAction.h
        Classes/Player/Brain/AI/BotPlayer.h

        Classes/Champion/Champion.h
        Classes/Champion/Mage/Mage.h

        Classes/ChampionInGame/ChampionInGame.h
        Classes/ChampionInGame/Extension.h
        Classes/ChampionInGame/UI/ChampionUI.h
        Classes/ChampionInGame/UI/ChampionHUD.h

        Classes/Map/Map.h

        Classes/Statics/Statics.h
        Classes/Statics/Extension.h

        Classes/SelectHelper/SelectHelper.h

        Classes/Skill/Skill.h
        Classes/Skill/Condition/Condition.h
        Classes/Skill/SkillType/SkillType.h
        Classes/Skill/SummonType/SummonType.h
        Classes/Skill/TargetType/TargetType.h
        Classes/Skill/TriggerType/TriggerType.h
        Classes/Skill/SkillCard/SkillCard.h
        Classes/Skill/SkillStatics/SkillStatics.h
        Classes/Skill/SkillInGame/SkillInGame.h
        Classes/Skill/SkillInGame/MoveBy/SkillMoveBy.h
        Classes/Skill/SkillManager/SkillManager.h
        Classes/Skill/TargetType/NoTarget/NoTarget.h
        Classes/Skill/TargetType/NoTarget/Toggle/Toggle.h
        Classes/Skill/TargetType/NoTarget/NormalCast/NormalCast.h
        Classes/Skill/TargetType/Factory/TargetTypeFactory.h

        Classes/GameEffect/Buff/Buff.h
        Classes/GameEffect/Debuff/Debuff.h
        Classes/GameEffect/GameEffect.h

        Classes/ChampionSkill/ChampionSkill.h

        Classes/Support/Coordinate.h
        Classes/Support/Enum.h
        Classes/Support/ValidString.h
        Classes/Support/GameConstant.h
        Classes/Support/Macros.h

        Classes/Arena/Arena.h
        Classes/Arena/SpecialArena/SpecialArena.h
        Classes/Arena/Property/Property.h
        Classes/Arena/GlobalArena.h
        Classes/Arena/SpecialArena/Factory/Factory.h
        Classes/Arena/SpecialArena/Tax/Tax.h
        Classes/Arena/SpecialArena/Airport/Airport.h
        Classes/Arena/SpecialArena/Shop/Shop.h
        Classes/Arena/SpecialArena/Hospital/Hospital.h
        Classes/Arena/SpecialArena/Spawn/Spawn.h

        Classes/User/User.h
        Classes/User/Information/UserInformation.h
        Classes/User/Information/GameDetails.h
        Classes/User/UI/UserUI.h
        Classes/User/UI/IngameUI.h
        Classes/User/Audio/Audio.h
        Classes/User/Helper.h
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")

    if(MACOSX)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist")
    elseif(IOS)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/Info.plist")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif()

    # For code-signing, set the DEVELOPMENT_TEAM:
    #set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "GRLXXXX2K9")
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    cocos_get_resource_path(APP_RES_DIR ${APP_NAME})
    cocos_copy_target_res(${APP_NAME} LINK_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
