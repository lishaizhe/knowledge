//
//  CSVReaderController.hpp
//  AgainstZ
//
//  Created by admin on 2018/11/15.
//

#ifndef CSVReaderController_hpp
#define CSVReaderController_hpp

#include "cocos2d.h"
#include <iostream>
using namespace std;
using namespace cocos2d;

class csvdata{
public:
    std::string id{""};         //日期
    std::string month{""};      //月份
    std::string date{""};       //月份内第几天
    std::string eweek{""};      //周几[英]
    std::string week{""};       //周几
    std::string attribute{""};  //属性
    std::string book{""};       //图书
    std::string list{""};       //
    std::string summary{""};
    std::string note{""};
    std::string cando{""};
    std::string calendar{""};
};

class CSVReaderController{
public:
    std::vector<csvdata> m_datalist;
    static CSVReaderController* getInst();
    std::vector<csvdata> readCSV(const std::string& filepath);
    void sortDataList();
};

#endif /* CSVReaderController_hpp */
