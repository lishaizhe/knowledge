#ifndef __XAMLPAGEMGR__
#define __XAMLPAGEMGR__

#include "cocos2d.h"
#include "../cocos2dx/platform/winrt/CCWinRTUtils.h"
#include "CCLableTTFEX.h"
using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

namespace PhoneDirect3DXamlAppComponent
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class IWebCallback
	{
	public:
		virtual void ExecWeb(Platform::String^ URL);
	};
	public ref class BroswerEventHelper sealed
	{
	public:
		BroswerEventHelper();
		static void SetCallback(IWebCallback^ Callback);
		static void callWebBroswer(Platform::String^ url);
	};

	/*Input*/
	public interface class IInputCallback
	{
	public:
		virtual void ExecInput();
	};
	public ref class InputEventHelper sealed
	{
	public:
		InputEventHelper();
		static void SetCallback(IInputCallback^ Callback);
		static void callInputXAML();
	};

}
#endif

class XamlPageMgr : public CCObject
{
	CCLableTTFEXDelegate* m_InputLableDelegate;
public:
	static XamlPageMgr* _inst;
	static XamlPageMgr* getInst();

	void onOpenWebXamlPage(std::string Url);
	void onPurchaseDone(CCObject* pObj);

	void onOpenInputXamlPage(CCLableTTFEXDelegate* _delegate);
	void onInputDone(CCObject* pObj);
};

#endif

