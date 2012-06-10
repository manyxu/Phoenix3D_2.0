/*
*
* 文件名称	：	PX2DLLMain.cpp
*
*/

#include "PX2Max9ClassDesc.hpp"

static int sControlsInit = FALSE;
static PX2::GraphicsRoot *sRoot = 0;
static PX2::ResourceManager *sResMan = 0;
//----------------------------------------------------------------------------
BOOL WINAPI DllMain (HINSTANCE instance, ULONG dwReason, LPVOID)
{
	// 这个函数被调用时，由Windows DLL被加载
	if (!sControlsInit) 
	{
		sControlsInit = true;

		// Max初始化
		InitCustomControls(instance); // max 常用控件
		InitCommonControls(); // windows控件
	}

	switch (dwReason) 
	{
	case DLL_PROCESS_ATTACH:
		PX2Max8ClassDesc::msInstance = instance;

#ifdef PX2_USE_MEMORY
		PX2::Memory::Initialize();
#endif

		InitCustomControls(instance);
		InitCommonControls();

		sRoot = new0 PX2::GraphicsRoot();
		sRoot->Initlize();

		sResMan = new0 PX2::ResourceManager();
		break;
	case DLL_PROCESS_DETACH:
		sRoot->Terminate();
		delete0(sRoot);

		delete0(sResMan);
#ifdef PX2_USE_MEMORY
		PX2::Memory::Terminate("Max9ToTd_MemoryReport.txt");
#endif
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}
//----------------------------------------------------------------------------
__declspec(dllexport) const TCHAR* LibDescription ()
{
	// 这个函数返回一个字符串描述这个DLL。用户如果没有这个DLL可以通过此获得。
	return "Phoenix2 3DMax Plugin";
}
//----------------------------------------------------------------------------
__declspec(dllexport) int LibNumberClasses ()
{
	// 函数返回在这个DLL里插件类的个数。
	return 1;
}
//----------------------------------------------------------------------------
__declspec(dllexport) ClassDesc* LibClassDesc (int i)
{
	// 这个函数这个导出插件的描述类
	(void)i;
	return &PX2Max8ClassDesc::TheClassDesc;
}
//----------------------------------------------------------------------------
__declspec(dllexport) ULONG LibVersion ()
{
	// 函数返回一个预定义的常量标识Max系统编译的版本号。这个让系统运行时捕获
	// 正确的DLL。
	return VERSION_3DSMAX;
}
//----------------------------------------------------------------------------