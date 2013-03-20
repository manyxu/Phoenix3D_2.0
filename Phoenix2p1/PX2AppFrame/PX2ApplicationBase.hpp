/*
*
* 文件名称	：	PX2ApplicationBase.hpp
*
*/

#ifndef PX2APPLICATIONBASE_HPP
#define PX2APPLICATIONBASE_HPP

#include "PX2AppFramePre.hpp"
#include "PX2ScriptEventHandler.hpp"

namespace PX2
{

	class ApplicationBase : public EventHandler
	{
	protected:
		ApplicationBase ();
	public:
		virtual ~ApplicationBase ();

		// App
		static ApplicationBase* msApplication;

		// system use
		static bool IsInitlized ();
		bool Initlize ();
		bool Ternamate ();
		void ResetRenderStates ();
		virtual bool OnInitlize ();
		virtual bool OnTernamate ();

		virtual void WillEnterForeground ();
		virtual void DidEnterBackground ();

		void SetSize (int width, int height);
		int GetWidth ();
		int GetHeight ();

		virtual void OnIdle ();
		virtual bool OnResume();
		virtual bool OnPause();

		virtual void DoEnter ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

		// Enteries
		typedef bool (*AppInitlizeFun)();
		static AppInitlizeFun msAppInitlizeFun;
		typedef bool (*AppTernamateFun)();
		static AppTernamateFun msAppTernamateFun;
		typedef int (*EntryPoint)(int numArguments, char** arguments);
		static EntryPoint msEntry;

		virtual int Main (int numArguments, char** arguments);

	protected:
		virtual bool OnInitlizeApp () = 0;
		virtual bool OnTernamateApp () = 0;
		void DrawInfo (int x, int y);

		static bool msIsInitlized;
	
		// 渲染相关
		// 窗口参数
		std::string mWindowTitle;
		int mXPosition, mYPosition, mWidth, mHeight;
		bool mAllowResize;

		Texture::Format mColorFormat;
		Texture::Format mDepthStencilFormat;
		int mNumMultisamples;
		Float4 mClearColor;
		Renderer* mRenderer;
		CameraPtr mCamera;

		EventWorld *mEventWorld;
		InputEventAdapter *mInputEventAdapter;
		GraphicsRoot *mRoot;
		ResourceManager *mResMan;
		ScriptManager *mScriptMan;
		ScriptEventHandlerPtr mScriptEventHandler;
		GameManager *mGameMan;
		UIManager *mUIManager;
		Project *mProject;
		
		float mApplicationTime;
		float mLastApplicationTime;
		bool mIsTimeInited;
		float mElapsedTime;

		UIStaticTextPtr mFrameText;
		float mFrameRate;
		int mNumFrames;
		float mFrameTime;

		UIStaticTextPtr mCurTotalMemory; // 兆
		UIStaticTextPtr mMaxTotalMemory;
		UIStaticTextPtr mDebugText;
	};

}

#endif