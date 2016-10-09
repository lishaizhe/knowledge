#ifndef __CCLABLETTFEX__
#define __CCLABLETTFEX__

#include "cocos2d.h"
using namespace cocos2d;

class CCLableTTFEXDelegate
{
public:
	virtual void onSetString(const char* text) = 0;
};

class CCLableTTFEX : public CCLabelTTF, public CCTouchDelegate, public CCLableTTFEXDelegate
{
	bool m_bTouchInside;
public:
	CCLableTTFEX();
	static CCLableTTFEX * create(const char *string, const char *fontName, float fontSize,int nPriority,
                               const CCSize& dimensions, CCTextAlignment hAlignment, 
                               CCVerticalTextAlignment vAlignment);

	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);

	virtual void onSetString(const char* text);
};


#endif
