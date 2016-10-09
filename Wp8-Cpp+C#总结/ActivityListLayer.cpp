#include "ActivityListLayer.h"
#include "../../utils/http/ZCHttpUtils.h"
#include "../vip_layer/VipSalaryLayer.h"
#include "../overseas_trade_layer/OverseasTradeLayer.h"
#include "../treasure_map_layer/TreasureMapLayer.h"
#include "../soullayer/SoulTowerLayer.h"
#include "../god_general_gate_layer/GodGeneralGatePrepareLayer.h"
#include "../activities_layer/invite_layer/InviteLayer.h"
#include "../stone_gambling_layer/StoneGamblingLayer.h"
#include "../herothrone_layer/HeroThronePrepareLayer.h"
#include "../gem_layer/GemBattleStageLayer.h"
#include "../smash_layer/SmashLayer.h"
#include "../epic_layer/EpicLayer.h"
#include "../../object/GameSetting.h"
#include "../mingjiang_layer/MingJiangTuJianLayer.h"
#include "../treasure_island_layer/TreasureIslandLayer.h"
#include "../../network/http/ZCHttp.h"
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
#include "../elite_layer/EliteLayer.h"
#endif
#include "../menulayer/MenuLayer.h"
#include "../studfarm_layer/StudFarmLayer.h"
#include "../world_boss_layer/WorldBossLayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
#include "../../object/GameInfo.h"
#include "../../plugin/Configs.h"
#endif


bool SortActivityListItems( const ActivityListItem& v1, const ActivityListItem& v2)
{
    return v1.m_nOpenLevel < v2.m_nOpenLevel;
}


bool ActivityListLayer::init(const Json::Value& json_object){
	if (ZCDialog::init())
	{
        CCSprite* bg = CCSprite::create();
        bg->initWithFile(pop_bg_cube);
        bg->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2));
        addChild(bg);

		m_pTableView = zctech::CCTableView::create(this, CCSizeMake(580 , 450));
		m_pTableView->setDirection(zctech::kCCScrollViewDirectionVertical);
		m_pTableView->setPosition(ccp( 20 , 40));
		m_pTableView->setDelegate(this);
		m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        
        m_pTableView->setTouchPriority(getTouchPriority()-1);
		bg->addChild(m_pTableView);

		m_pTableView->setBounceable(false);

        
		CCSprite* activity_list_layer_img_txt = CCSprite::create(activitypop_flag);

		activity_list_layer_img_txt->setPosition(CCPointMake(bg->boundingBox().origin.x+ bg->boundingBox().size.width/2,bg->boundingBox().origin.y + bg->boundingBox().size.height));

		addChild(activity_list_layer_img_txt);

		
        CCSprite* img_btn_pop_close = CCSprite::create(pop_closebtn);
		CCSprite* normalSprite = CCSprite::createWithTexture(img_btn_pop_close->getTexture(),CCRectMake(0,0,img_btn_pop_close->getContentSize().width,img_btn_pop_close->getContentSize().height/2)) ;
		CCSprite* selectedSprite = CCSprite::createWithTexture(img_btn_pop_close->getTexture(),CCRectMake(0,img_btn_pop_close->getContentSize().height/2,img_btn_pop_close->getContentSize().width,img_btn_pop_close->getContentSize().height/2)) ;
		ZCButton* btn_pop_close = ZCButton::create(NULL,normalSprite,selectedSprite);
		btn_pop_close->setPosition(CCPointMake(bg->boundingBox().origin.x + bg->boundingBox().size.width - btn_pop_close->getContentSize().width/2   + 10 , bg->boundingBox().origin.y + bg->boundingBox().size.height -  btn_pop_close->getContentSize().height/2 + 10));
		btn_pop_close->setTag(BTN_POP_CLOSE_TAG);
		btn_pop_close->setTouchEndedCallback(this,callfuncND_selector(ActivityListLayer::clickCallback),btn_pop_close);
		btn_pop_close->setClickable(true);
        btn_pop_close->setTouchPriority(getTouchPriority());
		addChild(btn_pop_close);
        
        
        const Json::Value& v_list = json_object["list"];
        if (!v_list.isNull() && v_list.isObject())
        {
            Json::Value::Members members = v_list.getMemberNames();
            vector<string>::iterator iter =  members.begin();
            while(iter != members.end()){
                const Json::Value& v_item =  v_list[*iter];
                if (!v_item.isNull())
                {
                    string endtime;
                    JsonUtil::parseJsonValueToString(endtime, v_item["endtime"]);
                    string endtime2;
                    JsonUtil::parseJsonValueToString(endtime2, v_item["endtime2"]);
                    string starttime;
                    JsonUtil::parseJsonValueToString(starttime, v_item["starttime"]);
                    string starttime2;
                    JsonUtil::parseJsonValueToString(starttime2, v_item["starttime2"]);
                    int openlevel = JsonUtil::parseJsonValueToInt(v_item["openlevel"]);
                    int status = JsonUtil::parseJsonValueToInt(v_item["status"]);
                    
                    ActivityListItem activityListItem;
                    activityListItem.m_sStarttime = starttime;
                    activityListItem.m_sStarttime2 = starttime2;
                    activityListItem.m_sEndtime = endtime;
                    activityListItem.m_sEndtime2 = endtime2;
                    activityListItem.m_nStatus = status;
                    activityListItem.m_nOpenLevel = openlevel;  
                    activityListItem.m_sName = *iter; 
                    
                    if (strcmp("lottery", activityListItem.m_sName.c_str()) == 0 ) {  
                        activityListItem.m_nOrder = 1;   
                        activityListItem.m_nOpenLevel = 16;
                        if (GameUser::sharedGameUser()->getLevel() < 16) {  
                            activityListItem.m_nStatus = 0;
                        }
                    }else if (strcmp("treasure", activityListItem.m_sName.c_str()) == 0 ){ 
                        activityListItem.m_nOrder = 4;
                        activityListItem.m_nOpenLevel = 36;
                        if (GameUser::sharedGameUser()->getLevel() < 36) {
                            activityListItem.m_nStatus = 0;
                        }
                    }
                    else if (strcmp("dailytask", activityListItem.m_sName.c_str()) == 0 ){ 
                        activityListItem.m_nOrder = 7;
                        activityListItem.m_nOpenLevel = 41;
                        if (GameUser::sharedGameUser()->getLevel() < 41) {
                            activityListItem.m_nStatus = 0;
                        }
                    }
                    else if (strcmp("dailytrade", activityListItem.m_sName.c_str()) == 0 ){ 
                        activityListItem.m_nOrder = 11;
                        activityListItem.m_nOpenLevel = 61;
                        if (GameUser::sharedGameUser()->getLevel() < 61) {
                            activityListItem.m_nStatus = 0;
                        }
                    }
                    else if (strcmp("tower", activityListItem.m_sName.c_str()) == 0 ){  
                        activityListItem.m_nOrder = 10;
                        activityListItem.m_nOpenLevel = 51;
                        if (GameUser::sharedGameUser()->getLevel() < 51) {
                            activityListItem.m_nStatus = 0;
                        }
                    }
                    else if (strcmp("drink", activityListItem.m_sName.c_str()) == 0 ){ 
                        activityListItem.m_nOrder = 6;
                        activityListItem.m_nOpenLevel = 41;
                        if (GameUser::sharedGameUser()->getLevel() < 41) {
                            activityListItem.m_nStatus = 0;
                        }
                    }
                    else if (strcmp("boss", activityListItem.m_sName.c_str()) == 0 ){  
                        activityListItem.m_nOrder = 5;
                        activityListItem.m_nOpenLevel = 46;
                        if (GameUser::sharedGameUser()->getLevel() < 46) {
                            activityListItem.m_nStatus = 0;
                        }
                    }
                    else if (strcmp("generaltask", activityListItem.m_sName.c_str()) == 0 ){ 
                        activityListItem.m_nOrder = 12;
                        activityListItem.m_nOpenLevel = 71;
                        if (GameUser::sharedGameUser()->getLevel() < 71) {
                            activityListItem.m_nStatus = 0;
                        }
                    }
                    else if (strcmp("invitation", activityListItem.m_sName.c_str()) == 0 ){ 
                        activityListItem.m_nOrder = 8;
                        activityListItem.m_nOpenLevel = 50;
                        if (GameUser::sharedGameUser()->getLevel() < 50) {
                            activityListItem.m_nStatus = 0;
                        }
                    }
                    if (strcmp("logined", activityListItem.m_sName.c_str()) != 0 ) {  
						m_ActivityListItems.push_back(activityListItem);
                    } 
                    
                }
                iter++;
            }
            
            
            ActivityListItem activityListItem;
            activityListItem.m_nStatus = GameUser::sharedGameUser()->getLevel() < 31 ? 0 : 1;
            activityListItem.m_nOpenLevel = 31;
            activityListItem.m_sName = "instance";
            activityListItem.m_nOrder = 3;
            m_ActivityListItems.push_back(activityListItem);
            
            
                { 
                ActivityListItem activityListItem;
                activityListItem.m_nStatus = 1;
                activityListItem.m_nOpenLevel = 0;
                activityListItem.m_sName = "vipsalary";
                activityListItem.m_nOrder = 0;
                m_ActivityListItems.push_back(activityListItem);
                }
            
                {
                ActivityListItem activityListItem;
                activityListItem.m_nStatus = 1;
                activityListItem.m_nOpenLevel = 51;
                activityListItem.m_sName = "overseastrade";
                activityListItem.m_nOrder = 9;
                m_ActivityListItems.push_back(activityListItem);
                
                }
            
                {
                ActivityListItem activityListItem;
                activityListItem.m_nStatus = 1;
                activityListItem.m_nOpenLevel = 26;
                activityListItem.m_sName = "treasuremap";
                activityListItem.m_nOrder = 2;
                m_ActivityListItems.push_back(activityListItem);
                
                }

                {
                ActivityListItem activityListItem;
                activityListItem.m_nStatus = 1;
                activityListItem.m_nOpenLevel = 81;
                activityListItem.m_sName = "mingjiang";
                activityListItem.m_nOrder = 13;
                m_ActivityListItems.push_back(activityListItem);
                
                }
                {
                ActivityListItem activityListItem;
                activityListItem.m_nStatus = 1;
                activityListItem.m_nOpenLevel = 91;
                activityListItem.m_sName = "stone_gambling";
                activityListItem.m_nOrder = 14;
                m_ActivityListItems.push_back(activityListItem);
                }
            
                {
                    ActivityListItem activityListItem;
                    activityListItem.m_nStatus = 1;
                    activityListItem.m_nOpenLevel = 101;
                    activityListItem.m_sName = "herothrone";
                    activityListItem.m_nOrder = 15;
                    m_ActivityListItems.push_back(activityListItem);
                }
            
                {
                    ActivityListItem activityListItem;
                    activityListItem.m_nStatus = 1;
                    activityListItem.m_nOpenLevel = 120;
                    activityListItem.m_sName = "studfarm";
                    activityListItem.m_nOrder = 17;
                    m_ActivityListItems.push_back(activityListItem);
                }
            
                
                {
                    ActivityListItem activityListItem;
                    activityListItem.m_nStatus = 1;
                    activityListItem.m_nOpenLevel = 140;
                    activityListItem.m_sName = "gem";
                    activityListItem.m_nOrder = 18;
                    m_ActivityListItems.push_back(activityListItem);
                }
            
                
                {
                    ActivityListItem activityListItem;
                    activityListItem.m_nStatus = 1;
                    activityListItem.m_nOpenLevel = 150;
                    activityListItem.m_sName = "smash";
                    activityListItem.m_nOrder = 20;
                    m_ActivityListItems.push_back(activityListItem);
                }
            
                
                {
                    ActivityListItem activityListItem;
                    activityListItem.m_nStatus = 1;
                    activityListItem.m_nOpenLevel = 150;
                    activityListItem.m_sName = "epic";
                    activityListItem.m_nOrder = 22;
                    m_ActivityListItems.push_back(activityListItem);
                }
            
            sort(m_ActivityListItems.begin(), m_ActivityListItems.end(), SortActivityListItems); 
        }
        
        ZCLOGI("m_ActivityListItems.size()=%d" , m_ActivityListItems.size());
        
        
        for (int i = 0 ; i < m_ActivityListItems.size() ; i++) {
            ActivityListItem& item = m_ActivityListItems.at(i);
            
            
            zctech::CCTableViewCell *cell = new zctech::CCTableViewCell();
            cell->autorelease();
            cell->setContentSize(CCSize(580, 100));
            
            
            CCSprite* bg = CCSprite::create();
            bg->initWithFile(activitypop_list_bg);
            bg->setPosition(ccp(cell->getContentSize().width / 2 , cell->getContentSize().height / 2 ));
            bg->setTag(LIST_ITEM_BG_TAG);
            cell->addChild(bg);
            
            
            CCSprite* icon = CCSprite::create();
            icon->setPosition(ccp(60 , bg->getContentSize().height / 2 ));
            bg->addChild(icon);
            
            
            ZCLabelTTF* name_txt = ZCLabelTTF::create("", "", 24);
            name_txt->setColor(ccBLACK);
            name_txt->setAnchorPoint(ccp(0, 0.5f));
            name_txt->setPosition(ccp(110 +10, 70));
            
            
            ZCLabelTTF* description_txt = ZCLabelTTF::create("", "", 22);
            description_txt->setColor(ccc3(113,63,0));
            description_txt->setAnchorPoint(ccp(0, 0.5f));
            description_txt->setPosition(ccp(name_txt->boundingBox().origin.x, bg->getContentSize().height / 2 - 25));
            
            
            bg->addChild(name_txt);
            bg->addChild(description_txt);
            
            
            CCTexture2D* texture_middle = CCTextureCache::sharedTextureCache()->addImage(pop_btn_middle);
            ZCLabelTTF* btn_txt = ZCLabelTTF::create(DELIVER, "", 24);
            ZCButton* btn_go = ZCButton::create(btn_txt, CCSprite::createWithTexture(texture_middle, CCRect(0, 0, texture_middle->getContentSize().width, texture_middle->getContentSize().height / 2 )), CCSprite::createWithTexture(texture_middle, CCRect(0, texture_middle->getContentSize().height / 2 , texture_middle->getContentSize().width, texture_middle->getContentSize().height / 2 )) ,CCSprite::create(pop_btn_middle_disable));
            btn_go->setPosition(ccp(bg->getContentSize().width - btn_go->getContentSize().width / 2, icon->getPositionY()));
            btn_go->setUserData(&item); 
            btn_go->setTag(BTN_GO_TAG);
            btn_go->setSwallowsTouches(false);
            btn_go->setTouchPriority(getTouchPriority());
            bg->addChild(btn_go);
            
            bg->setUserData(btn_go);  
            
            
            if (item.m_nStatus==1) {
                btn_go->setEnable(true);
            }else{
                btn_go->setEnable(false);
            }
    
            
            if (strcmp("lottery", item.m_sName.c_str()) == 0 ) { 
                name_txt->setString(ACTIVITYPOP_TMPL_4);
                icon->initWithFile(activitypop_list_lottory);
                description_txt->setString(ACTIVITYPOP_TMPL_5);
                if (GameUser::sharedGameUser()->getLevel() < 16) {
                    btn_go->setEnable(false); 
                    btn_go->setString(LV_OPEN(16));
                }
                
            }else if (strcmp("treasure", item.m_sName.c_str()) == 0 ){ 
                name_txt->setString(ACTIVITYPOP_TMPL_13);
                icon->initWithFile(activitypop_list_treasure);
                description_txt->setString(ACTIVITYPOP_TMPL_14);
                if (GameUser::sharedGameUser()->getLevel() < 36) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(36));
                }
            }
            else if (strcmp("dailytask", item.m_sName.c_str()) == 0 ){  
                name_txt->setString(ACTIVITYPOP_TMPL_22);
                icon->initWithFile(activitypop_list_task);
                description_txt->setString(ACTIVITYPOP_TMPL_23);
                if (GameUser::sharedGameUser()->getLevel() < 41) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(41));
                }
            }
            else if (strcmp("dailytrade", item.m_sName.c_str()) == 0 ){  
                name_txt->setString(ACTIVITYPOP_TMPL_34);
                icon->initWithFile(activitypop_list_trade);
                description_txt->setString(ACTIVITYPOP_TMPL_35);
                if (GameUser::sharedGameUser()->getLevel() < 61) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(61));
                }
            }
            else if (strcmp("tower", item.m_sName.c_str()) == 0 ){ 
                name_txt->setString(SOULPOP_TMPL_2);
                icon->initWithFile(tower_icon);
                description_txt->setString(ACTIVITYPOP_TMPL_32);
                if (GameUser::sharedGameUser()->getLevel() < 51) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(51));
                }
            }
            else if (strcmp("drink", item.m_sName.c_str()) == 0 ){  
                name_txt->setString(ACTIVITYPOP_TMPL_19);
                icon->initWithFile(activitypop_list_drink);
                description_txt->setString(ACTIVITYPOP_TMPL_20);
                if (GameUser::sharedGameUser()->getLevel() < 41) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(41));
                }
            }
            else if (strcmp("boss", item.m_sName.c_str()) == 0 ){ 
                name_txt->setString(WORLD_BOSS);
                icon->initWithFile(activitypop_list_boss);
                description_txt->setString(ACTIVITYPOP_TMPL_17);
                
                
                ZCLabelTTF* time_txt = ZCLabelTTF::create((item.m_sStarttime + "-" + item.m_sEndtime + "\n" +  item.m_sStarttime2 + "-" + item.m_sEndtime2 ).c_str() , "", 18);
                time_txt->setAnchorPoint(ccp(0, 0.5f));
                time_txt->setPosition(ccp(230, name_txt->getPositionY()- 5));
                time_txt->setColor(ccc3(56,121,217));
                bg->addChild(time_txt);
                
                if (GameUser::sharedGameUser()->getLevel() < 46) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(46));
                }
            }
            else if(strcmp("generaltask", item.m_sName.c_str()) == 0 ){ 
                name_txt->setString(ACTIVITYPOP_TMPL_37);
                icon->initWithFile(activitypop_list_generaltask);
                description_txt->setString(ACTIVITYPOP_TMPL_38);
                if (GameUser::sharedGameUser()->getLevel() < 71) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(71));
                }
            }else if(strcmp("instance", item.m_sName.c_str()) == 0 ){ 
                name_txt->setString(MISSIONPOP_ELITE);
                icon->initWithFile(activitypop_list_elite);
                description_txt->setString(ACTIVITYPOP_TMPL_11);
                if (GameUser::sharedGameUser()->getLevel() < 31) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(31));
                }
            }else if(strcmp("vipsalary", item.m_sName.c_str()) == 0){
                name_txt->setString(ACTIVITYPOP_TMPL_1);
                icon->initWithFile(activitypop_list_vipreward);
                description_txt->setString(ACTIVITYPOP_TMPL_2);
                btn_go->setEnable(true);
            }else if(strcmp("overseastrade", item.m_sName.c_str()) == 0){ 
                name_txt->setString(ACTIVITYPOP_TMPL_28);
                icon->initWithFile(activitypop_list_overseastrade);
                description_txt->setString(ACTIVITYPOP_TMPL_29);
                if (GameUser::sharedGameUser()->getLevel() < item.m_nOpenLevel) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(item.m_nOpenLevel));
                }
            }else if(strcmp("treasuremap", item.m_sName.c_str()) == 0){  
                name_txt->setString(TREASUREMAP);
                icon->initWithFile(activitypop_list_treasuremap);
                description_txt->setString(ACTIVITYPOP_TMPL_8);
                if (GameUser::sharedGameUser()->getLevel() < item.m_nOpenLevel) {
                    btn_go->setEnable(false);
                    btn_go->setString( LV_OPEN(item.m_nOpenLevel));
                }
            }else if(strcmp("invitation", item.m_sName.c_str()) == 0){  
                name_txt->setString(ACTIVITYPOP_TMPL_25);
                icon->initWithFile(activitypop_list_invite);
                description_txt->setString(ACTIVITYPOP_TMPL_26);
                if (GameUser::sharedGameUser()->getLevel() < item.m_nOpenLevel) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(item.m_nOpenLevel));
                }
            }else if(strcmp("stone_gambling", item.m_sName.c_str()) == 0){ 
                name_txt->setString(ACTIVITYPOP_TMPL_43);
                
                #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                const string &channel = GameInfo::sharedGameInfo()->getChannel();
                if (channel.compare(CHANNEL_91_CODE) == 0) {
                    name_txt->setString("切石坊");
                    icon->initWithFile("pop/activitypop_list_slyz91.png");
                }else{
                    icon->initWithFile(activitypop_list_slyz);
                }
                #else
                icon->initWithFile(activitypop_list_slyz);
                #endif
                
                description_txt->setString(ACTIVITYPOP_TMPL_44);
                if (GameUser::sharedGameUser()->getLevel() < item.m_nOpenLevel) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(item.m_nOpenLevel));
                }
            }else if(strcmp("mingjiang", item.m_sName.c_str()) == 0){  
                name_txt->setString(HEROMANUALPOP_TMPL_1);
                icon->initWithFile(activitypop_list_heromanual);
                description_txt->setString(ACTIVITYPOP_TMPL_41);
                if (GameUser::sharedGameUser()->getLevel() < item.m_nOpenLevel) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(item.m_nOpenLevel));
                }
            }else if(strcmp("herothrone", item.m_sName.c_str()) == 0){  
                icon->initWithFile(activitypop_list_herothrone);
                name_txt->setString(ACTIVITYPOP_TMPL_46);
                description_txt->setString(ACTIVITYPOP_TMPL_47);
                if (GameUser::sharedGameUser()->getLevel() < item.m_nOpenLevel) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(item.m_nOpenLevel));
                }
            }else if(strcmp("gem" , item.m_sName.c_str()) == 0){ 
                icon->initWithFile(activitypop_list_sanctum);
                name_txt->setString(ACTIVITYPOP_TMPL_49);
                description_txt->setString(ACTIVITYPOP_TMPL_50);
                if (GameUser::sharedGameUser()->getLevel() < item.m_nOpenLevel) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(item.m_nOpenLevel));
                }
            }else if(strcmp("smash" , item.m_sName.c_str()) == 0){ 
                icon->initWithFile(activitypop_list_smash);
                name_txt->setString(ACTIVITYPOP_TMPL_52);
                description_txt->setString(ACTIVITYPOP_TMPL_56);
                if (GameUser::sharedGameUser()->getLevel() < item.m_nOpenLevel) {
                    btn_go->setEnable(false);
                    btn_go->setString(LV_OPEN(item.m_nOpenLevel));
                }
            }else if(strcmp("epic" , item.m_sName.c_str()) == 0){
                icon->initWithFile(activitypop_list_epic);  
                name_txt->setString(ACTIVITYPOP_TMPL_55);
                description_txt->setString(ACTIVITYPOP_TMPL_56);
                if (GameUser::sharedGameUser()->getLevel() < item.m_nOpenLevel) {
                    btn_go->setEnable(false);
                     btn_go->setString(LV_OPEN(item.m_nOpenLevel));
                }
            }else if(strcmp("studfarm" , item.m_sName.c_str()) == 0){  
                icon->initWithFile(activitypop_list_studfarm);
                name_txt->setString(I18n::sharedI18n()->getI18nString(MOUNTPOP_STUDFARM_BTN).c_str());
                description_txt->setString(I18n::sharedI18n()->getI18nString(ACTIVITYPOP_TMPL_59).c_str());
                if (GameUser::sharedGameUser()->getLevel() < item.m_nOpenLevel) {
                    btn_go->setEnable(false);
                     btn_go->setString(LV_OPEN(item.m_nOpenLevel));
                }
            }
            m_pArray->addObject(cell);
        }
        
        m_ListView_Rows = m_pArray->count(); 
        m_pTableView->reloadData(); 
        m_pTableView->scrollToFirstCell(); 
        
        
		return true;
	}
	return false;

}


void ActivityListLayer::clickCallback(CCNode* sender, void * param){
    CCNode* node = (CCNode*)param;
	CCAssert(node!=NULL , "node can not be NULL");
	switch(node->getTag()){
		case BTN_POP_CLOSE_TAG:
			this->removeFromParentAndCleanup(true);
			break;
	}
}


void ActivityListLayer::clickItemCallback(CCNode* sender, void * param){
    CCNode* node = (CCNode*)param; 
	CCAssert(node!=NULL , "node can not be NULL");
    
    if (node->getUserData()) {
        ActivityListItem* pActivityListItem = ((ActivityListItem*)node->getUserData()); 
        string activity_name = pActivityListItem->m_sName;
        
        if (strcmp("lottery", activity_name.c_str()) == 0 ) {  
            addChild(LotteryLayer::create());
        }else if (strcmp("treasure", activity_name.c_str()) == 0 ){  
            this->removeFromParentAndCleanup(true);  //?
            TreasureIslandLayer::create();
        }
        else if (strcmp("dailytask", activity_name.c_str()) == 0 ){  
            addChild(DailyMissionLayer::create());
        }
        else if (strcmp("dailytrade", activity_name.c_str()) == 0 ){ 
            addChild(BusinessLayer::create());
        }
        else if (strcmp("tower", activity_name.c_str()) == 0 ){ 
            this->removeFromParentAndCleanup(true);
            CCScene* pCCScene = CCScene::create();   //?
            pCCScene->addChild(SoulTowerLayer::create());
            CCDirector::sharedDirector()->pushScene(pCCScene);
        }
        else if (strcmp("drink", activity_name.c_str()) == 0 ){ 
            addChild(DrinkLayer::create());
        }
        else if (strcmp("boss", activity_name.c_str()) == 0 ){  
            MenuLayer::sharedMenuLayer()->addChild(WorldBossLayer::create());
        }
        else if(strcmp("generaltask", activity_name.c_str()) == 0 ){ 
            string url = GameUser::sharedGameUser()->getDomainServer() + "c=generaltask&m=index&token=" + GameUser::sharedGameUser()->getToken();
            ZCHttpUtils::doAsyncRequestUrl(url.c_str(), this, callfuncND_selector(ActivityListLayer::getGodGeneralGateInfoCallback));
        }
		else if(strcmp("instance", activity_name.c_str()) == 0 ){
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
            MenuLayer::sharedMenuLayer()->addChild(EliteLayer::create());
			ZCTOAST(WEIKAIFANG);
#endif
            
        }else if(strcmp("vipsalary", activity_name.c_str()) == 0){  //VIP工资
            string url = GameUser::sharedGameUser()->getDomainServer() + "c=vipwage&m=index&token=" + GameUser::sharedGameUser()->getToken();
            ZCHttpUtils::doAsyncRequestUrl(url.c_str(), this, callfuncND_selector(ActivityListLayer::getVipSalaryCallback) , NULL , ZCHttpRequestLoadingHeader);
        }else if(strcmp("overseastrade", activity_name.c_str()) == 0){ 
            string url = GameUser::sharedGameUser()->getDomainServer() + "c=overseastrade&m=index&token=" + GameUser::sharedGameUser()->getToken();
            ZCHttpUtils::doAsyncRequestUrl(url.c_str(), this, callfuncND_selector(ActivityListLayer::getOverseasTradeInfoCallback) , NULL , ZCHttpRequestLoadingHeader);
        }else if(strcmp("treasuremap", activity_name.c_str()) == 0){ 
            ZCHttpUtils::doAsyncRequestJustWithParameters("c=treasuremap&m=index", this, callfuncND_selector(ActivityListLayer::getTreasureMapInfoCallback)  , NULL , ZCHttpRequestLoadingHeader);
        }else if(strcmp("invitation", activity_name.c_str()) == 0){ 
            ZCHttpUtils::doAsyncRequestJustWithParameters("c=invitation&m=index", this, callfuncND_selector(ActivityListLayer::getInviteInfoCallback) , NULL , ZCHttpRequestLoadingHeader);
        }else if(strcmp("stone_gambling", activity_name.c_str()) == 0){ 
            addChild(StoneGamblingLayer::create());
        }
        else if (strcmp("mingjiang", activity_name.c_str()) == 0 ){ 
            addChild(MingJiangTuJianLayer::create());
        }
        else if (strcmp("herothrone", activity_name.c_str()) == 0 ){ 
            ZCHttpUtils::doAsyncRequestJustWithParameters("c=herothrone&m=index", this, callfuncND_selector(ActivityListLayer::getHeroThroneInfoCallback) , NULL , ZCHttpRequestLoadingHeader);
        }
        else if (strcmp("gem", activity_name.c_str()) == 0 ){ 
            CCScene* pCCScene = CCScene::create();
            pCCScene->addChild(GemBattleStageLayer::create());
            CCDirector::sharedDirector()->pushScene(pCCScene);
        }
        else if (strcmp("smash", activity_name.c_str()) == 0 ){ 
            addChild(SmashLayer::create());
        }
        else if (strcmp("epic", activity_name.c_str()) == 0 ){ 
            addChild(EpicLayer::create());
        }
        else if (strcmp("studfarm", activity_name.c_str()) == 0 ){  
            addChild(StudFarmLayer::create());
        }
        
        
    }
}


void ActivityListLayer::getHeroThroneInfoCallback(CCNode * , void* param){
    zc::ZCHttpResponse* response = (zc::ZCHttpResponse*)param;
	if (response && response->isSucceed())
	{
		string data(response->getResponseData()->begin(), response->getResponseData()->end());
		Json::Reader jsonReader;
		Json::Value json_object;
		if (jsonReader.parse(data.c_str(),json_object) && !json_object.isNull() && json_object.isObject()) {
			int status = JsonUtil::parseJsonValueToInt(json_object["status"]);
            switch (status) {
                case 1:
                    {
                        CCScene* pCCScene = CCScene::create();
                        HeroThronePrepareLayer* pHeroThronePrepareLayer = HeroThronePrepareLayer::create(json_object);
                        pCCScene->addChild(pHeroThronePrepareLayer);
                        CCDirector::sharedDirector()->replaceScene(pCCScene);
                    }
                    return;
                case 3:
                    ZCHttpUtils::doAsyncRequestJustWithParameters("c=herothrone&m=start", this, callfuncND_selector(HeroThronePrepareLayer::getStartInfoCallback),NULL,ZCHttpRequestLoadingHeader);
                    return;
                case -1:
                    ZCTOAST(LV_NOT_ENOUGH);
                    return;
                case 2:
                    ZCTOAST(LV_NOT_ENOUGH);
                    return;
                default:
                    ZCTOAST(UNDEFINED_ERROR);
                    return;
            }
		}
	}
    ZCTOAST(INTERNET_ERROR);
}


void ActivityListLayer::getGamblingInfoCallback(CCNode * , void* param){
    zc::ZCHttpResponse* response = (zc::ZCHttpResponse*)param;
	if (response && response->isSucceed())
	{
		string data(response->getResponseData()->begin(), response->getResponseData()->end());
		Json::Reader jsonReader;
		Json::Value json_object;
		if (jsonReader.parse(data.c_str(),json_object) && !json_object.isNull() && json_object.isObject()) {
			int status = JsonUtil::parseJsonValueToInt(json_object["status"]);
            switch (status) {
                case 1:
                    addChild(StoneGamblingLayer::create(json_object));
                    return;
                case -1:
                    ZCTOAST(LV_CAN_NOT_OPEN_FUNC);
                    return;
            }
		}
	}
    
    ZCTOAST(INTERNET_ERROR);
}


void ActivityListLayer::getInviteInfoCallback(CCNode * , void* param){
    zc::ZCHttpResponse* response = (zc::ZCHttpResponse*)param;
	if (response && response->isSucceed())
	{
		string data(response->getResponseData()->begin(), response->getResponseData()->end());
		Json::Reader jsonReader;
		Json::Value json_object;
		if (jsonReader.parse(data.c_str(),json_object) && !json_object.isNull() && json_object.isObject()) {
			int status = JsonUtil::parseJsonValueToInt(json_object["status"]);
            switch (status) {
                case 1:
                case 2:
                    addChild(InviteLayer::create(json_object));
                    return;
                default:
                    ZCTOAST(UNDEFINED_ERROR);
                    return;
            }
		}
	}
    
    ZCTOAST(INTERNET_ERROR);
}


void ActivityListLayer::getTreasureMapInfoCallback(CCNode * , void* param){
    zc::ZCHttpResponse* response = (zc::ZCHttpResponse*)param;
	if (response && response->isSucceed())
	{
		string data(response->getResponseData()->begin(), response->getResponseData()->end());
		Json::Reader jsonReader;
		Json::Value json_object;
		jsonReader.parse(data.c_str(),json_object);
		if ( !json_object.isNull() && json_object.isObject()) {
			int status = JsonUtil::parseJsonValueToInt(json_object["status"]);
            switch (status) {
                case 1:
                    addChild(TreasureMapLayer::create(json_object));
                    break;
                case 0:
                    ZCTOAST(WAIT_FOR_TREASUREMAP);
                    break;
                case -1:
                    ZCTOAST(ACTIVITY_CLOSED);
                    break;
                case -2:
                    ZCTOAST(GET_ACTIVITY_INFO_FAIL);
                    break;
                default:
                    ZCTOAST(UNDEFINED_ERROR);
                    break;
            }
		}else{
            this->removeChildByTag(kZCLayerLoadingHeader, true);
            ZCTOAST(INTERNET_ERROR);
        }
	}else {
        this->removeChildByTag(kZCLayerLoadingHeader, true);
		ZCTOAST(INTERNET_ERROR);
	}
    
}

void ActivityListLayer::getVipSalaryCallback(CCNode * , void* param){
    zc::ZCHttpResponse* response = (zc::ZCHttpResponse*)param;
	if (response && response->isSucceed())
	{
		string data(response->getResponseData()->begin(), response->getResponseData()->end());
		Json::Reader jsonReader;
		Json::Value json_object;
		jsonReader.parse(data.c_str(),json_object);
		if ( !json_object.isNull() && json_object.isObject()) {
			int status = JsonUtil::parseJsonValueToInt(json_object["status"]);
            switch (status) {
                case 1:
                    addChild(VipSalaryLayer::create(json_object));
                    break;
                case -2:
                    ZCTOAST(ACTIVITY_CLOSED);
                    break;
                default:
                    this->removeChildByTag(kZCLayerLoadingHeader, true);
                    ZCTOAST(NO_ACTIVITY);
                    break;
            }
		}else{
            this->removeChildByTag(kZCLayerLoadingHeader, true);
            ZCTOAST(INTERNET_ERROR);
        }
	}else {
        this->removeChildByTag(kZCLayerLoadingHeader, true);
		ZCTOAST(INTERNET_ERROR);
	}
}


void ActivityListLayer::getOverseasTradeInfoCallback(CCNode * , void* param){
    zc::ZCHttpResponse* response = (zc::ZCHttpResponse*)param;
	if (response && response->isSucceed())
	{
		string data(response->getResponseData()->begin(), response->getResponseData()->end());
		Json::Reader jsonReader;
		Json::Value json_object;
		jsonReader.parse(data.c_str(),json_object);
		if ( !json_object.isNull() && json_object.isObject()) {
			int status = JsonUtil::parseJsonValueToInt(json_object["status"]);
            switch (status) {
                case 1:
                    addChild(OverseasTradeLayer::create(json_object));
                    break;
                case 2:
                    ZCTOAST(NO_COUNTRY_NO_FUNC);
                    break;
                case 3:
                    ZCTOAST(LV_NOT_ENOUGH);
                    break;
                case -1:
                    ZCTOAST(GET_USER_INFO_FAIL);
                    break;
                case -2:
                    ZCTOAST(GET_TEAM_INFO_FAIL);
                    break;
                case -3:
                    ZCTOAST(TEAM_INFO_ERROR);
                    break;
                case -4:
                    ZCTOAST(GET_GOODS_INFO_FAIL);
                    break;
                default:
                    ZCTOAST(UNDEFINED_ERROR);
                    break;
            }
		}else{
            this->removeChildByTag(kZCLayerLoadingHeader, true);
        }
	}else {
        this->removeChildByTag(kZCLayerLoadingHeader, true);
		ZCTOAST(INTERNET_ERROR);
	}
}


void ActivityListLayer::removeLoadingHeaderFromNotification(CCObject*){
    this->removeChildByTag(kZCLayerLoadingHeader, true);
}


void ActivityListLayer::getGodGeneralGateInfoCallback(CCNode * , void* param){
    zc::ZCHttpResponse* response = (zc::ZCHttpResponse*)param;
	if (response && response->isSucceed())
	{
		string data(response->getResponseData()->begin(), response->getResponseData()->end());
		Json::Reader jsonReader;
		Json::Value json_object;
		jsonReader.parse(data.c_str(),json_object);
		if ( !json_object.isNull() && json_object.isObject()) {
			parseGodGeneralGateInfoJsonObject(json_object);
		}
	}else {
		ZCTOAST(INTERNET_ERROR);
	}
}
void ActivityListLayer::parseGodGeneralGateInfoJsonObject(const Json::Value& json_object){
    int status =JsonUtil::parseJsonValueToInt(json_object["status"]);
    switch (status) {
        case 1:
            {
                CCScene* pCCScene = CCScene::create();
                pCCScene->addChild(GodGeneralGatePrepareLayer::create(json_object));
                CCDirector::sharedDirector()->pushScene(pCCScene);
            }
            break;
            
        case -1:
            ZCTOAST(LV71_OPEN);
            break;
            
        case -2:
            ZCTOAST(GET_HERO_INFO_FAIL);
            break;
            
        default:
            ZCTOAST(UNDEFINED_ERROR);
            break;
    }
    
}

ActivityListLayer* ActivityListLayer::create(const Json::Value& json_object){
    ActivityListLayer* pActivityListLayer  = new ActivityListLayer;
    if(pActivityListLayer && pActivityListLayer->init(json_object)){
        pActivityListLayer->autorelease();
    }else{
        CC_SAFE_DELETE(pActivityListLayer);
    }
    return pActivityListLayer;
}


void ActivityListLayer::tableCellTouched(zctech::CCTableView* table, zctech::CCTableViewCell* cell){
    if (cell->getChildByTag(LIST_ITEM_BG_TAG) && cell->getChildByTag(LIST_ITEM_BG_TAG)->getUserData()) { 
        ZCButton* sp =  (ZCButton*)cell->getChildByTag(LIST_ITEM_BG_TAG)->getUserData(); 
        if(sp->getZCButtonState() == kZCButtonStateTrackingTouch){ 
            clickItemCallback(this, sp); 
        }
    }
}


cocos2d::CCSize ActivityListLayer::cellSizeForTable(zctech::CCTableView *table){
	CCSprite* bg = CCSprite::create(activitypop_list_bg);
	return CCSize(580, bg->getContentSize().height + 8);
}


zctech::CCTableViewCell* ActivityListLayer::tableCellAtIndex( zctech::CCTableView *table, unsigned int idx){
	return (zctech::CCTableViewCell*)m_pArray->objectAtIndex(idx);

}

unsigned int ActivityListLayer::numberOfCellsInTableView( zctech::CCTableView *table){
	return m_ListView_Rows;

}


