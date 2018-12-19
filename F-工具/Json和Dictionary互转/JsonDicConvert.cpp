//
//  JsonDicConvert.cpp
//  AgainstZ
//
//  Created by admin on 2018/11/20.
//

#include "JsonDicConvert.hpp"


char* JDConvert::strFromDic(CCDictionary* dic){
    cJSON* json = cJSON_CreateObject();
    convertDicToJson(dic, json);
    char* jsonStr = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return jsonStr;
}

void JDConvert::convertDicToJson(CCDictionary* dic, cJSON* json){
    DictElement* element = nullptr;
    CCDICT_FOREACH(dic, element){
        Ref* object = element->getObject();
        cJSON* jsonItem = getObjJson(object);
        cJSON_AddItemToObject(json, element->getStrKey(), jsonItem);//添加一个对象到json
    }
}

void JDConvert::convertArrayToJson(CCArray * array, cJSON * json){
    CCObject* obj;
    CCARRAY_FOREACH(array, obj){
        cJSON* jsonItem = getObjJson(obj);
        cJSON_AddItemToArray(json, jsonItem);//添加一个对象到json中的array
    }
}

cJSON* JDConvert::getObjJson(CCObject* obj){
    std::string name = typeid(*obj).name();
    if (name.find("Dictionary") != std::string::npos){
        cJSON* json = cJSON_CreateObject();
        convertDicToJson((CCDictionary *)obj, json);
        return json;
    }else if (name.find("Array") != std::string::npos){
        cJSON* json = cJSON_CreateArray();
        convertArrayToJson(dynamic_cast<CCArray*>(obj), json);
        return json;
    }else if (name.find("String") != std::string::npos){
        CCString * s = (CCString *)obj;
        cJSON* json = cJSON_CreateString(s->getCString());
        return json;
    }else if (name.find("Integer") != std::string::npos){
        CCInteger * i = (CCInteger *)obj;
        cJSON* json = cJSON_CreateNumber(i->getValue());
        return json;
    }else if (name.find("Bool") != std::string::npos){
        CCBool* b = (CCBool*)obj;
        cJSON* json = nullptr;
        if (b->getValue()){
            json = cJSON_CreateTrue();
        }else{
            json = cJSON_CreateFalse();
        }
        return json;
    }
    return nullptr;
}

CCDictionary* JDConvert::dicFromStr(std::string jsonStr){
    CCDictionary* pDic = CCDictionary::create();
    cJSON* json = cJSON_Parse(jsonStr.c_str());
    convertJsonToDictionary(json, pDic);
    cJSON_Delete(json);
    return pDic;
}

void JDConvert::convertJsonToDictionary(cJSON *json, CCDictionary *dictionary){
    dictionary->removeAllObjects();
    cJSON* j = json->child;
    while (j) {
        std::string key = j->string;
        CCObject* obj = getJsonObject(j);
        dictionary->setObject(obj, key);
        j = j->next;
    }
}

void JDConvert::convertJsonToArray(cJSON * json, CCArray * array){
    array->removeAllObjects();
    int size = cJSON_GetArraySize(json);
    for (int i = 0; i < size; ++i){
        cJSON* jsonItem = cJSON_GetArrayItem(json, i);
        CCObject* obj = getJsonObject(jsonItem);
        array->addObject(obj);
    }
}

CCObject* JDConvert::getJsonObject(cJSON *json){
    if (json->type == cJSON_Object){
        CCDictionary* dic = CCDictionary::create();
        convertJsonToDictionary(json, dic);
        return dic;
    }else if (json->type == cJSON_Array){
        CCArray* array = CCArray::create();
        convertJsonToArray(json, array);
        return array;
    }else if (json->type == cJSON_String){
        CCString* str = CCString::create(json->valuestring);
        return str;
    }else if (json->type == cJSON_Number){
        CCDouble* d = CCDouble::create(json->valuedouble);
        return d;
    }else if (json->type == cJSON_True){
        return CCBool::create(true);
    }else if (json->type == cJSON_False){
        return CCBool::create(false);
    }
    return nullptr;
}
