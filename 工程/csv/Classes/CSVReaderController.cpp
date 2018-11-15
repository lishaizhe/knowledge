//
//  CSVReaderController.cpp
//  AgainstZ
//
//  Created by admin on 2018/11/15.
//

#include "CSVReaderController.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

CSVReaderController* CSVReaderController::getInst(){
    static CSVReaderController _inst;
    return &_inst;
}

string Trim(string& str)
{
    str.erase(0,str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
    return str;
}

std::vector<csvdata> CSVReaderController::readCSV(const string &filepath){
    std::string _filepath = FileUtils::sharedFileUtils()->fullPathForFilename(filepath);
    ifstream fin(_filepath);
    string line;
    while (getline(fin, line)) {
        istringstream sin(line);
        vector<string> fields;
        string field;
        while (getline(sin, field, ';')) {
            fields.push_back(field);
        }
        csvdata _data;
        _data.id = Trim(fields[0]);
        _data.month = Trim(fields[1]);
        _data.date = Trim(fields[2]);
        _data.eweek = Trim(fields[3]);
        _data.week = Trim(fields[4]);
        _data.attribute = Trim(fields[5]);
        _data.book = Trim(fields[6]);
        _data.list = Trim(fields[7]);
        _data.summary = Trim(fields[8]);
        _data.note = Trim(fields[9]);
        _data.cando = Trim(fields[10]);
        _data.calendar = Trim(fields[11]);
        m_datalist.push_back(_data);
    }
    
    sortDataList();
    return m_datalist;
}


void CSVReaderController::sortDataList(){
    std::map<std::string, int> _sort_month;
    _sort_month["JANUARY"] = 1;
    _sort_month["FEBRUARY"] = 2;
    _sort_month["MARCH"] = 3;
    _sort_month["APRIL"] = 4;
    _sort_month["MAY"] = 5;
    _sort_month["JUNE"] = 6;
    _sort_month["JULY"] = 7;
    _sort_month["AUGUST"] = 8;
    _sort_month["SEPTEMBER"] = 9;
    _sort_month["OCTOBER"] = 10;
    _sort_month["NOVEMBER"] = 11;
    _sort_month["DECEMBER"] = 12;
    
    sort(m_datalist.begin(), m_datalist.end(), [&](const csvdata& data1, const csvdata& data2){
        if (_sort_month[data1.month] == _sort_month[data2.month]){
            return atoi(data1.date.c_str()) < atoi(data2.date.c_str());
        }else{
            return _sort_month[data1.month] < _sort_month[data2.month];
        }
    });
}
