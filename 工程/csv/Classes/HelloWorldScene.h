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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CSVReaderController.hpp"
using namespace cocos2d;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    int m_index{0};
    std::function<void(int)> m_lamb;
    std::vector<csvdata> tmp;
    std::map<std::string, std::string> _changemap;
    Sprite* blank_image;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    std::string getBottomTitle(std::string week);
    void drawBattery(int index);
    int getBatteryPieceCount(int index);
    float getLastBatteryOpacity(int index);
    
    void drawCircle(Vec2 pos);
    
    void _addFontTTF(std::string data, std::string fontname, int fontsize, Vec2 pos);
    void _addFontSys(std::string data, std::string fontname, int fontsize, Vec2 pos, Vec2 anchorPos=Vec2(0.5, 0.5), TextHAlignment alignment = TextHAlignment::CENTER, Size dimension = Size::ZERO, Color3B color = Color3B::BLACK, int highlight =0);
    RenderTexture* render;
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
