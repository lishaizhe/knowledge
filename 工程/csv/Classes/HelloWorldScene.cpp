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

Label* HelloWorld::_addFontSys(std::string data, std::string fontname, int fontsize, Vec2 pos, Vec2 anchorPos, TextHAlignment alignment, Size dimension, Color3B color, int highlight){
    auto bsize = blank_image->getContentSize();
    auto lab = Label::createWithTTF(data, fontname, fontsize);
    lab->enableBold();
    lab->setAnchorPoint(anchorPos);
    lab->setColor(color);
    lab->setDimensions(dimension.width, dimension.height);
    lab->setPosition(bsize.width*pos.x, bsize.height*pos.y);
    if (highlight != 0){
        lab->setLineHeight(highlight);
    }
    blank_image->addChild(lab);
    return lab;
};

std::string HelloWorld::getBottomTitle(std::string week){
    if (week.compare("一") == 0){
        return "蓝色学习日计划:";
    }else if (week.compare("二") == 0){
        return "红色热血日计划:";
    }else if (week.compare("三") == 0){
        return "绿色乐活日计划:";
    }else if (week.compare("四") == 0){
        return "白色思考日计划:";
    }else if (week.compare("五") == 0){
        return "黄色能量日计划:";
    }else if (week.compare("六") == 0){
        return "周六随心日计划:";
    }else if (week.compare("日") == 0){
        return "周日缤纷日计划:";
    }
    return "";
}

void splitWord(const string & word, vector<string> & characters)
{
    size_t num = word.size();
    int i = 0;
    while(i < num)
    {
        int size = 1;
        if(word[i] & 0x80)
        {
            char temp = word[i];
            temp <<= 1;
            do{
                temp <<= 1;
                ++size;
            }while(temp & 0x80);
        }
        string subWord;
        subWord = word.substr(i, size);
        characters.push_back(subWord);
        i += size;
    }
}

void HelloWorld::drawCircle(Vec2 pos){
    auto blank_size = blank_image->getContentSize();
    Sprite* circle = Sprite::create("blank_circle.png");
    circle->setPosition(Vec2(blank_size.width*pos.x, blank_size.height*pos.y));
    blank_image->addChild(circle);
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
        _addFontSys(_changemap[tmp[i].month], "SimHei.ttf", 50, Vec2(0.15, 0.87), Vec2(0, 0.5));
        //农历
        _addFontSys("农    历", "SimHei.ttf", 40, Vec2(0.8, 0.875), Vec2(1, 0.5));
        //农历日期
        _addFontSys(tmp[i].calendar, "SimHei.ttf", 40, Vec2(0.8, 0.855), Vec2(1, 0.5));
        //月份中第几天
        float _PosX = 0.49;
        std::vector<std::string> _vec_date;
        splitWord(tmp[i].date, _vec_date);
//        splitWord("22", _vec_date);
        if (_vec_date.size() == 1){
            _addFontSys(_vec_date[0], "ELEPHNT.TTF", 300, Vec2(_PosX, 0.66), Vec2(1, 0.5));
            _PosX+=0.03;
        }else{
            _PosX = 0.35;
            if (_vec_date[0] == "1"){
                _PosX = 0.36;
            }
            auto lab = _addFontSys(_vec_date[0], "ELEPHNT.TTF", 300, Vec2(_PosX, 0.66), Vec2(0.5, 0.5));
            lab->setScaleX(0.9);
            _PosX = 0.5;
            auto lab2 = _addFontSys(_vec_date[1], "ELEPHNT.TTF", 300, Vec2(_PosX, 0.66), Vec2(0.5, 0.5));
            lab2->setScaleX(0.9);
            _PosX+=0.09;
        }
        
        auto blank_size = blank_image->getContentSize();
        auto mid_line = Sprite::create("middle_bar.png");
        mid_line->setPosition(Vec2(blank_size.width*_PosX, blank_size.height*0.66));
        blank_image->addChild(mid_line);
        _PosX += 0.08;
        //周几
        std::string strWeek = "星期"+tmp[i].week;
        std::vector<std::string> _vec_week;
        splitWord(strWeek, _vec_week);
        _addFontSys(_vec_week[0], "SimHei.ttf", 95, Vec2(_PosX, 0.71));
        _addFontSys(_vec_week[1], "SimHei.ttf", 95, Vec2(_PosX, 0.66));
        _addFontSys(_vec_week[2], "SimHei.ttf", 95, Vec2(_PosX, 0.61)); //0.6
        _PosX += 0.15;
        //节气
        std::vector<std::string> _vec_note;
        splitWord(tmp[i].note, _vec_note);
        if (_vec_note.size() == 3){
            drawCircle(Vec2(_PosX, 0.71));
            _addFontSys(_vec_note[0], "SimHei.ttf", 70, Vec2(_PosX, 0.71),Vec2(0.5, 0.5),TextHAlignment::CENTER,Size::ZERO,Color3B::WHITE);
            drawCircle(Vec2(_PosX, 0.66));
            _addFontSys(_vec_note[1], "SimHei.ttf", 70, Vec2(_PosX, 0.66),Vec2(0.5, 0.5),TextHAlignment::CENTER,Size::ZERO,Color3B::WHITE);
            drawCircle(Vec2(_PosX, 0.61));
            _addFontSys(_vec_note[2], "SimHei.ttf", 70, Vec2(_PosX, 0.61),Vec2(0.5, 0.5),TextHAlignment::CENTER,Size::ZERO,Color3B::WHITE);
        }else if (_vec_note.size() == 2){
            drawCircle(Vec2(_PosX, 0.69));
            _addFontSys(_vec_note[0], "SimHei.ttf", 70, Vec2(_PosX, 0.69),Vec2(0.5, 0.5),TextHAlignment::CENTER,Size::ZERO,Color3B::WHITE);
            drawCircle(Vec2(_PosX, 0.63));
            _addFontSys(_vec_note[1], "SimHei.ttf", 70, Vec2(_PosX, 0.63),Vec2(0.5, 0.5),TextHAlignment::CENTER,Size::ZERO,Color3B::WHITE); //0.75
        }

    
        //计划
        _addFontSys(tmp[i].list, "STXINWEI.TTF", 160, Vec2(0.5, 0.5));
        //书语
        _addFontSys(tmp[i].summary, "FZXBSK--GBK1-0.TTF", 45, Vec2(0.5, 0.3), Vec2(0.5, 0.5), TextHAlignment::LEFT, Size(800, 0), Color3B::BLACK, 70);
        //书籍
        std::string strBook = "——" + tmp[i].book;
        auto labBook = _addFontSys(strBook, "FZXBSK--GBK1-0.TTF", 40, Vec2(0.82, 0.22), Vec2(1, 0.5));
        if (labBook->getBoundingBox().size.width > 780){
            labBook->setScale(780.0f/labBook->getBoundingBox().size.width);
        }
        //能量日计划
        _addFontSys(getBottomTitle(tmp[i].week), "FZXBSK--GBK1-0.TTF", 32, Vec2(0.15, 0.051), Vec2(0, 0.5));
        
        
        drawBattery(i);
        
        render->clear(0, 0, 0, 0);
        render->begin();
        blank_image->visit();
        render->end();

        std::string strIndex = _changemap[tmp[i].month] + tmp[i].date+".png";
        render->saveToFile(strIndex.c_str(), Image::Format::PNG);
        cocos2d::log(">>>> %d", i);
    };
    
    schedule([this](float t){
        if (m_index >= 31){
            MessageBox("done", "make");
            this->unschedule("update");
            return;
        }
        m_lamb(m_index);
        m_index++;
    }, 1.0f, CC_REPEAT_FOREVER, 1.5, "update");
    
    return true;
}

void HelloWorld::drawBattery(int index){
    std::map<int, Sprite*> _list;
    _list.clear();
    auto blank_size = blank_image->getContentSize();
    int _count = getBatteryPieceCount(index);
    for (int i = 0; i < _count; ++i){
        Sprite* item = Sprite::create("blank_triangle.png");
        item->setPosition(Vec2(blank_size.width*(0.835-0.015*i), blank_size.height*0.054));
        blank_image->addChild(item);
        _list.insert(std::make_pair(i, item));
    }
    if (_list.size() > 0){
        float opa = getLastBatteryOpacity(index);
        _list[_list.size()-1]->setOpacity(opa);
    }
}

int HelloWorld::getBatteryPieceCount(int index){
    return ceil((float)(365-index)/73);
}

float HelloWorld::getLastBatteryOpacity(int index){
    return 255 - 255.0/73 * (index%73);
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
