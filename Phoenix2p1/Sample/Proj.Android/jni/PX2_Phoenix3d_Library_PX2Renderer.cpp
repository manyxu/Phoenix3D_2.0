
#include "PX2_Phoenix3d_Library_PX2Renderer.h"
#include "PX2Application.hpp"
#include "SampleApp.hpp"

//----------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_PX2_Phoenix3d_Library_PX2Renderer_nativeOdle
  (JNIEnv *, jclass)
{   
	PX2::ApplicationBase::msApplication->OnIdle();
}
//----------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_PX2_Phoenix3d_Library_PX2Renderer_nativeInit
  (JNIEnv *, jclass, jint, jint)
{	
	PX2::ApplicationBase::msAppInitlizeFun();
	PX2::ApplicationBase::msApplication->Initlize ();
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
	PX2::ApplicationBase::msAppTernamateFun();
}
//----------------------------------------------------------------------------