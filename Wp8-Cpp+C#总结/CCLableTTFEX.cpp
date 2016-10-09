#include "CCLableTTFEX.h"
#include "XamlPageMgr.h"


CCLableTTFEX::CCLableTTFEX()
{
	m_bTouchInside = false;
}

CCLableTTFEX* CCLableTTFEX::create(const char *string, const char *fontName, float fontSize,int nPriority,
                               const CCSize& dimensions, CCTextAlignment hAlignment, 
                               CCVerticalTextAlignment vAlignment)
{
	CCLableTTFEX *pRet = new CCLableTTFEX();
    if(pRet && pRet->initWithString(string, fontName, fontSize, dimensions, hAlignment, vAlignment))
    {
        pRet->autorelease();
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(pRet,nPriority,true);
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCLableTTFEX::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	CCRect rect = this->boundingBox();
	rect.origin = CCPointZero;
	CCPoint pos = this->convertTouchToNodeSpace(pTouch);
	if(rect.containsPoint(pos))
		m_bTouchInside = true;
	else
		m_bTouchInside = false;
	return m_bTouchInside;
}

void CCLableTTFEX::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	bool _TouchInside = false;
	CCRect rect = this->boundingBox();
	rect.origin = CCPointZero;
	CCPoint pos = this->convertTouchToNodeSpace(pTouch);
	if(rect.containsPoint(pos))
		_TouchInside = true;
	
	if(_TouchInside && m_bTouchInside)
	{
		//call xaml
		XamlPageMgr::getInst()->onOpenInputXamlPage(this);
	}
}


void CCLableTTFEX::onSetString(const char* text)
{
	this->setString(text);
}