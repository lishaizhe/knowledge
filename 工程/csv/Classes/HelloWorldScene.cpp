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

void HelloWorld::_addFontTTF(std::string data, std::string fontname, int fontsize, Vec2 pos){
    auto bsize = blank_image->getContentSize();
    auto lab = Label::createWithTTF(data, fontname, fontsize);
    lab->enableBold();
    lab->setColor(Color3B::BLACK);
    lab->setPosition(bsize.width*pos.x, bsize.height*pos.y);
    blank_image->addChild(lab);
};

void HelloWorld::_addFontSys(std::string data, std::string fontname, int fontsize, Vec2 pos, Vec2 anchorPos, TextHAlignment alignment, Size dimension){
    auto bsize = blank_image->getContentSize();
    auto lab = Label::createWithSystemFont(data, fontname, fontsize);
    lab->enableBold();
    lab->setAnchorPoint(anchorPos);
    lab->setColor(Color3B::BLACK);
    lab->setDimensions(dimension.width, dimension.height);
    lab->setPosition(bsize.width*pos.x, bsize.height*pos.y);
    blank_image->addChild(lab);
};

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

    tmp = CSVReaderController::getInst()->readCSV("timecsv.csv");
    
    blank_image = Sprite::create("blank_image.png");
    blank_image->setAnchorPoint(Vec2(0.5f, 0.5f));
    blank_image->setPosition(Vec2(size.width/2-128, size.height/2));
    addChild(blank_image);
    
    auto blank_size = blank_image->getContentSize();
    render = RenderTexture::create(blank_size.width, blank_size.height);
//    render->setPosition(Vec2(size.width/2, size.height/2));
    addChild(render);
    
    _changemap["JANUARY"] = "一 月";
    _changemap["FEBRUARY"] = "二 月";
    _changemap["MARCH"] = "三 月";
    _changemap["APRIL"] = "四 月";
    _changemap["MAY"] = "五 月";
    _changemap["JUNE"] = "六 月";
    _changemap["JULY"] = "七 月";
    _changemap["AUGUST"] = "八 月";
    _changemap["SEPTEMBER"] = "九 月";
    _changemap["OCTOBER"] = "十 月";
    _changemap["NOVEMBER"] = "十一 月";
    _changemap["DECEMBER"] = "十二 月";
    
    std::string writepath = FileUtils::getInstance()->getWritablePath();
    cocos2d::log(">> %s", writepath.c_str());
    m_lamb = [this](int i){
        blank_image->removeAllChildrenWithCleanup(true);
        //月份
        _addFontSys(_changemap[tmp[i].month], "Arial.ttf", 50, Vec2(0.15, 0.87), Vec2(0, 0.5));
        //农历
        _addFontSys("农     历", "Arial.ttf", 40, Vec2(0.8, 0.875), Vec2(1, 0.5));
        //农历日期
        _addFontSys(tmp[i].calendar, "Arial.ttf", 40, Vec2(0.8, 0.855), Vec2(1, 0.5));
        //月份中第几天
        _addFontTTF(tmp[i].date, "elephant.otf", 300, Vec2(0.38, 0.68));
        //周几
        std::string strWeek = "星\n期\n"+tmp[i].week;
        _addFontSys(strWeek, "Arial.ttf", 95, Vec2(0.6, 0.66));
        //计划
        _addFontSys(tmp[i].list, "Arial.ttf", 55, Vec2(0.5, 0.5));
        //书语
        _addFontSys(tmp[i].summary, "Arial.ttf", 45, Vec2(0.5, 0.3), Vec2(0.5, 0.5), TextHAlignment::LEFT, Size(800, 0));
        //书籍
        std::string strBook = "——" + tmp[i].book;
        _addFontSys(strBook, "Arial.ttf", 40, Vec2(0.82, 0.22), Vec2(1, 0.5));
        
        render->clear(0, 0, 0, 0);
        render->begin();
        blank_image->visit();
        render->end();
        
        render->saveToFile(strBook+"123.png", Image::Format::PNG);
        cocos2d::log(">>>> %d", i);
    };
    
    schedule([this](float t){
        if (m_index >= 2){
            MessageBox("done", "make");
            this->unschedule("update");
            return;
        }
        m_lamb(m_index);
        m_index++;
    }, 5.0f, CC_REPEAT_FOREVER, 1.5, "update");
    
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
