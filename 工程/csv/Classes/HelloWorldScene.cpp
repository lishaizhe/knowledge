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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CSVReaderController.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto size = Director::getInstance()->getVisibleSize();

    std::vector<csvdata> tmp = CSVReaderController::getInst()->readCSV("timecsv.csv");
    
    auto blank_image = Sprite::create("blank_image.png");
    blank_image->setAnchorPoint(Vec2(0.5f, 0.5f));
    blank_image->setPosition(Vec2(size.width/2, size.height/2));
    addChild(blank_image);
    
    auto _addFont =[=](std::string data, std::string fontname, int fontsize, Vec2 pos){
        auto bsize = blank_image->getContentSize();
        auto lab = CCLabelTTF::create(data, fontname, fontsize);
        lab->setColor(Color3B::BLACK);
        lab->setPosition(bsize.width*pos.x, bsize.height*pos.y);
        blank_image->addChild(lab);
    };
    for (int i = 0; i < 1; ++i){
        //月份
        _addFont(tmp[i].month, "Arial.ttf", 30, Vec2(0.1, 0.85));
        //农历
        _addFont("农历", "Arial.ttf", 30, Vec2(0.8, 0.85));
        //农历日期
        _addFont(tmp[i].calendar, "Arial.ttf", 30, Vec2(0.8, 0.8));
        //月份中第几天
        _addFont(tmp[i].date, "Arial.ttf", 30, Vec2(0.4, 0.75));
        //周几
        _addFont(tmp[i].week, "Arial.ttf", 30, Vec2(0.6, 0.75));
        //宜
        _addFont(tmp[i].cando, "Arial.ttf", 30, Vec2(0.5, 0.5));
        //书语
        _addFont(tmp[i].list, "Arial.ttf", 30, Vec2(0.5, 0.35));
        //书籍
        _addFont(tmp[i].book, "Arial.ttf", 30, Vec2(0.5, 0.25));
    }
    
    auto blank_size = blank_image->getContentSize();
    RenderTexture* render = RenderTexture::create(blank_size.width, blank_size.height);
    render->setPosition(Vec2(size.width/2, size.height/2));
    addChild(render);
    scheduleOnce([=](float t){
        render->begin();
        blank_image->visit();
        render->end();
        std::string writepath = FileUtils::getInstance()->getWritablePath();
        render->saveToFile("abc.png", Image::Format::PNG);
    }, 2.0, "123");
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
