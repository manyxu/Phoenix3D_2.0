#include "phoenix3d_px2_library_PX2Renderer.h"
#include "PX2Application.hpp"
#include "PX2JNI.hpp"
#include "GamePlayApp.hpp"

extern "C"
{

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIHelper::SetJavaVM(vm);

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL Java_phoenix3d_px2_library_PX2Renderer_nativeOdle
  (JNIEnv *, jclass)
  {
  PX2::ApplicationBase::msApplication->OnIdle();
  }


JNIEXPORT void JNICALL Java_phoenix3d_px2_library_PX2Renderer_nativeInit
  (JNIEnv *, jclass, jint, jint)
  {
  PX2::ApplicationBase::msAppInitlizeFun();
  PX2::ApplicationBase::msApplication->Initlize ();
  }


JNIEXPORT void JNICALL Java_phoenix3d_px2_library_PX2Renderer_nativeOnPause
  (JNIEnv *, jclass)
  {
  }


JNIEXPORT void JNICALL Java_phoenix3d_px2_library_PX2Renderer_nativeOnResume
  (JNIEnv *, jclass)
  {
  }


JNIEXPORT void JNICALL Java_phoenix3d_px2_library_PX2Renderer_nativeTerm
  (JNIEnv *, jclass)
  {
  PX2::ApplicationBase::msAppTernamateFun();
  }

 }