//
//  JsonDicConvert.hpp
//  AgainstZ
//
//  Created by admin on 2018/11/20.
//

/*
 目的很明显就是Dictionary和json之间的互换
 实现起来也比较简单
 Dictionary=>json
    遍历字典，依次通过typeid(xx).name的形式获取当前是什么类型的数据,依次通过 cJSON_Create的形式创建对象并通过cJSON_AddItemToObject  cJSON_AddItemToArray 的形式插入到json中即可
 
 json=>Dictionary
    遍历json  while(json->child) 的形式
    通过json->string 获取json的对象key， 通过json->type 获取是什么格式类型的。依次塞入Dictionary
 
 在其中存在一个打印的输出cJSON_PrintUnformatted【不带格式的输出】
                     cJSON_Print  【带格式的输出】
 */

//使用的是cJson库  https://github.com/DaveGamble/cJSON

#ifndef JsonDicConvert_hpp
#define JsonDicConvert_hpp


#include "cocos2d.h"
#include "cJSON.h"
using namespace cocos2d;

namespace JDConvert {
    //转JSON
    char* strFromDic(CCDictionary* dic);
    void convertDicToJson(CCDictionary* dic, cJSON* json);
    void convertArrayToJson(CCArray* array, cJSON* json);
    cJSON* getObjJson(CCObject* obj);
    
    //转Dictionary
    CCDictionary* dicFromStr(std::string jsonStr);
    void convertJsonToDictionary(cJSON *json, CCDictionary *dictionary);
    void convertJsonToArray(cJSON * json, CCArray * array);
    CCObject* getJsonObject(cJSON *json);
}

#endif /* JsonDicConvert_hpp */
