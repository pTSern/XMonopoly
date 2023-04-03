/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AppDelegate.h"
#include "GameScene/MainMenu.h"
#include "GameScene/BattleScene.h"
#include "ZyUwU/data-manager/ZYDatabase.h"

//#define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("PrC", cocos2d::Rect(0, 0, zy::designResolutionSize.width, zy::designResolutionSize.height));
#else
        glview = GLViewImpl::create("PrC");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 144);

    // Set the design resolution
    auto frameSize = glview->getFrameSize();
    glview->setDesignResolutionSize(zy::designResolutionSize.width, zy::designResolutionSize.height, ResolutionPolicy::EXACT_FIT);

    // if the frame's height is larger than the height of medium size.

    if (frameSize.height > zy::largeResolutionSize.height)
    {
        director->setContentScaleFactor(MIN((zy::supperResolutionSize.height/zy::designResolutionSize.height), (zy::supperResolutionSize.width/zy::designResolutionSize.width)));
        zy::ZYDirector::getInstance()->setResolutionName("SUPPER");
    }
    else if (frameSize.height > zy::mediumResolutionSize.height)
    {
        director->setContentScaleFactor(MIN((zy::largeResolutionSize.height/zy::designResolutionSize.height), (zy::largeResolutionSize.width/zy::designResolutionSize.width)));
        zy::ZYDirector::getInstance()->setResolutionName("LARGER");
    }
    // if the frame's height is larger than the height of small size.
    if (frameSize.height > zy::smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(zy::mediumResolutionSize.height/zy::designResolutionSize.height, zy::mediumResolutionSize.width/zy::designResolutionSize.width));
        zy::ZYDirector::getInstance()->setResolutionName("MEDIUM");
    }
    // if the frame's height is larger than the height of larger size

    // if the frame's height is smaller than the height of medium size.
    else
    {        
        //director->setContentScaleFactor(MIN(zy::smallResolutionSize.height/zy::designResolutionSize.height, zy::smallResolutionSize.width/zy::designResolutionSize.width));
        zy::ZYDirector::getInstance()->setResolutionName("SMALL");
    }
    register_all_packages();

    // init the database file loc
    ZYDB_GI->init("database.db");

    // create a scene. it's an autorelease object
    auto scene = MainMenuScene::createScene();

    // run
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#endif
}
