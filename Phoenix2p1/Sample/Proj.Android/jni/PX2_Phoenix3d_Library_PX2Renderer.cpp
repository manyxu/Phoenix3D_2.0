
#include "PX2_Phoenix3d_Library_PX2Renderer.h"
#include "PX2Application.hpp"

//----------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_PX2_Phoenix3d_Library_PX2Renderer_nativeOdle
  (JNIEnv *, jclass)
{
	PX2::Application::msApplication->OnIdle();
}
//----------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_PX2_Phoenix3d_Library_PX2Renderer_nativeInit
  (JNIEnv *, jclass, jint, jint)
{
	PX2::Application::msAppInitlizeFun();
}
//----------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_PX2_Phoenix3d_Library_PX2Renderer_nativeOnPause
  (JNIEnv *, jclass)
{

}
//----------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_PX2_Phoenix3d_Library_PX2Renderer_nativeOnResume
  (JNIEnv *, jclass)
{

}
//----------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_PX2_Phoenix3d_Library_PX2Renderer_nativeTerm
	(JNIEnv *, jclass)
{
//	Application::msAppTernamateFun();
}
//----------------------------------------------------------------------------