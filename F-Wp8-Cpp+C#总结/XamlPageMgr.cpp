#include "XamlPageMgr.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
namespace PhoneDirect3DXamlAppComponent
{
	BroswerEventHelper::BroswerEventHelper(void)
	{}

	IWebCallback^ _webCallback = nullptr;

	void BroswerEventHelper::SetCallback(IWebCallback^ callback)
	{
		_webCallback = callback;
	}

	void BroswerEventHelper::callWebBroswer(Platform::String^ url)
	{
		if(_webCallback != nullptr)
		{
			_webCallback->ExecWeb(url);
		}
	}

	/***/

	InputEventHelper::InputEventHelper(void)
	{}

	IInputCallback^ _InputCallback = nullptr;

	void InputEventHelper::SetCallback(IInputCallback^ callback)
	{
		_InputCallback = callback;
	}

	void InputEventHelper::callInputXAML()
	{
		if(_InputCallback != nullptr)
		{
			_InputCallback->ExecInput();
		}
	}


}
using namespace PhoneDirect3DXamlAppComponent;
#endif






XamlPageMgr* XamlPageMgr::_inst = NULL;

XamlPageMgr* XamlPageMgr::getInst()
{
	if(!_inst)
	{
		_inst = new XamlPageMgr();
		_inst->m_InputLableDelegate = NULL;
		CCNotificationCenter::sharedNotificationCenter()->addObserver(_inst,callfuncO_selector(XamlPageMgr::onPurchaseDone),"onPurchaseDone",NULL);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(_inst,callfuncO_selector(XamlPageMgr::onInputDone),"onInputDone",NULL);
	}
	return _inst;
}

void XamlPageMgr::onPurchaseDone(CCObject* pObj)
{
	OutputDebugStringA("++++Test++++");
}

void XamlPageMgr::onOpenWebXamlPage(std::string Url)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	std::wstring _szUniURL = CCUtf8ToUnicode(Url.c_str());
	Platform::String^ _szPlatFormURL = ref new Platform::String(_szUniURL.c_str());
	BroswerEventHelper^ helper = ref new BroswerEventHelper();
	helper->callWebBroswer(_szPlatFormURL);
#endif
}


void XamlPageMgr::onOpenInputXamlPage(CCLableTTFEXDelegate* _delegate)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	m_InputLableDelegate = _delegate;
	InputEventHelper^ helper = ref new InputEventHelper();
	helper->callInputXAML();
#endif
}

void XamlPageMgr::onInputDone(CCObject* pObj)
{
	CCString* pString = (CCString*)pObj;
	m_InputLableDelegate->onSetString(pString->getCString());
}