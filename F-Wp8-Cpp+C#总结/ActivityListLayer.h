#ifndef SanGuo_ActivityListLayer_h
#define SanGuo_ActivityListLayer_h


#include "../../base/baselayer/ZCLayerColor.h"
#include "../../views/listview/ZCListView.h"
#include "../drinklayer/DrinkLayer.h"
#include "../lotterylayer/LotteryLayer.h"
#include "../businesslayer/BusinessLayer.h"
#include "ActivityListItem.h"
#include "../daily_mission_layer/DailyMissionLayer.h"
#include "../../views/ScrollView/CCTableView.h"
#include "../../dialogs/ZCDialog.h"
#include <algorithm>
#include "../../EventTypes.h"

class ActivityListLayer : public ZCDialog ,public CCTableViewDelegate , public CCTableViewDataSource  {
private:
	enum TAG{
		BTN_POP_CLOSE_TAG = kCCMenuHandlerPriority,
		BTN_GO_TAG,
		LIST_ITEM_BG_TAG,
		LAYER_TAG,
	};


	int m_ListView_Rows;
	zctech::CCTableView* m_pTableView;
    vector<ActivityListItem> m_ActivityListItems;
    void clickCallback(CCNode* sender, void * param);
    void clickItemCallback(CCNode* sender, void * param);

    void getGodGeneralGateInfoCallback(CCNode * , void* param);
	void parseGodGeneralGateInfoJsonObject(const Json::Value& json_object);

    void getInstanceServerCallback(CCNode * , void* param);
    void getVipSalaryCallback(CCNode * , void* param);
    
    void getOverseasTradeInfoCallback(CCNode * , void* param);
    void getTreasureMapInfoCallback(CCNode * , void* param);
    
    void getInviteInfoCallback(CCNode * , void* param);
    void getGamblingInfoCallback(CCNode * , void* param);
    
	virtual void scrollViewDidScroll(zctech::CCScrollView* view) {ZCLOGI("scrollViewDidScroll");};
	virtual void scrollViewDidZoom(zctech::CCScrollView* view) {};
	virtual void tableCellTouched(zctech::CCTableView* table, zctech::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(zctech::CCTableView *table);
	virtual zctech::CCTableViewCell* tableCellAtIndex( zctech::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView( zctech::CCTableView *table);

    
    CCArray* m_pArray;
    
public:
    void getHeroThroneInfoCallback(CCNode * , void* param);
    
	ActivityListLayer():m_ListView_Rows(0)
	,m_pTableView(NULL)
    ,m_pArray(CCArray::create()){
        CC_SAFE_RETAIN(m_pArray);
        CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ActivityListLayer::removeLoadingHeaderFromNotification), EVENT_REMOVE_LOADING_HEADER , NULL);
    }
    ~ActivityListLayer(){
        CC_SAFE_RELEASE_NULL(m_pArray);
        CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_REMOVE_LOADING_HEADER);
    }
    
    
    void removeLoadingHeaderFromNotification(CCObject*);
    
	bool init(const Json::Value& json_object);
//	void onEnter();
//	void onExit();
//    
    static ActivityListLayer* create(const Json::Value& json_object);

};


#endif