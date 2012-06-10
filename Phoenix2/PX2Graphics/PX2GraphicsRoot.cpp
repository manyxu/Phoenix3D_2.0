/*
*
* 文件名称	：	PX2GraphicsRoot.cpp
*
*/

#include "PX2GraphicsRoot.hpp"
#include "PX2Environment.hpp"
using namespace PX2;

std::string GraphicsRoot::PX2Path;
//----------------------------------------------------------------------------
GraphicsRoot::GraphicsRoot ()
{
}
//----------------------------------------------------------------------------
GraphicsRoot::~GraphicsRoot ()
{
}
//----------------------------------------------------------------------------
bool GraphicsRoot::Initlize ()
{
	// 你需要创建PX2_PATH环境变量，应用程序依赖于此查找各种资源文件。
	PX2Path = Environment::GetVariable("PX2_PATH");
	//if (PX2Path == "")
	//{
	//	assertion(false, "Please set the PX2_PATH environment variable.\n");
	//	FILE* ofile = fopen("ApplicationError.txt", "w");
	//	fprintf(ofile, "Please set the PX2_PATH environment variable.\n");
	//	fclose(ofile);
	//	//return false;
	//}
	//PX2Path += "/";

	InitTerm::ExecuteInitializers();

	std::string directory;

	// 应用程序当前目录
	Environment::InsertDirectory("/");

	// Camera
#ifdef PX2_USE_DX9
	// DirectX使用深度在区间[0,1]内的矩阵。
	Camera::SetDefaultDepthType(Camera::PM_DEPTH_ZERO_TO_ONE);
#endif

#ifdef PX2_USE_OPENGL
	// OpenGL使用深度在区间[-1,1]内的矩阵。
	Camera::SetDefaultDepthType(Camera::PM_DEPTH_MINUS_ONE_TO_ONE);
#endif

	return true;
}
//-----------------------------------------------------------------------------
bool GraphicsRoot::Terminate ()
{
	Environment::RemoveAllDirectories();

	InitTerm::ExecuteTerminators();

	return true;
}
//----------------------------------------------------------------------------
void GraphicsRoot::AddLight (Light *light)
{
	bool bIn = false;
	for (int i=0; i<(int)mAllLights.size(); i++)
	{
		if (light == mAllLights[i])
			bIn = true;
	}

	if (!bIn)
	{
		mAllLights.push_back(light);
	}
}
//----------------------------------------------------------------------------
void GraphicsRoot::RemoveLight (Light *light)
{
	std::vector<Pointer0<Light> >::iterator it = mAllLights.begin();
	for (; it!=mAllLights.end(); it++)
	{
		if (*it == light)
		{
			mAllLights.erase(it);
			return;
		}
	}
}
//----------------------------------------------------------------------------
void GraphicsRoot::ClearAllLights ()
{
	mAllLights.clear();
}
//----------------------------------------------------------------------------
int GraphicsRoot::GetNumLights ()
{
	return (int)mAllLights.size();
}
//----------------------------------------------------------------------------
Light *GraphicsRoot::GetLight (int index)
{
	int numLights = (int)mAllLights.size();
	if (index>=0 && index<numLights)
	{
		return mAllLights[index];
	}

	return 0;
}
//----------------------------------------------------------------------------