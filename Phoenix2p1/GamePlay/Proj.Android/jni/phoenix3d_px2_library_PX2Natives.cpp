#include "phoenix3d_px2_library_PX2Natives.h"
#include "PX2Application.hpp"
#include "PX2JNI.hpp"
#include "PX2ResourceManager.hpp"
#include "GamePlayApp.hpp"

extern "C"
{

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIHelper::SetJavaVM(vm);

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL Java_phoenix3d_px2_library_PX2Natives_nativeOdle
  (JNIEnv *, jclass)
  {
  PX2::ApplicationBase::msApplication->OnIdle();
  }


JNIEXPORT void JNICALL Java_phoenix3d_px2_library_PX2Natives_nativeInit
  (JNIEnv *, jclass, jint, jint)
  {
  PX2::ApplicationBase::msAppInitlizeFun();
  PX2::ApplicationBase::msApplication->Initlize ();
  }


JNIEXPORT void JNICALL Java_phoenix3d_px2_library_PX2Natives_nativeOnPause
  (JNIEnv *, jclass)
  {
  }


JNIEXPORT void JNICALL Java_phoenix3d_px2_library_PX2Natives_nativeOnResume
  (JNIEnv *, jclass)
  {
  }


JNIEXPORT void JNICALL Java_phoenix3d_px2_library_PX2Natives_nativeTerm
  (JNIEnv *, jclass)
  {
  PX2::ApplicationBase::msAppTernamateFun();
  }
  
 JNIEXPORT void JNICALL Java_phoenix3d_px2_library_PX2Natives_nativeSetResourcePath
  (JNIEnv *env, jclass, jstring apkPath)
  {
  const char *str = env->GetStringUTFChars(apkPath, NULL);
  PX2::ResourceManager::SetResourcePath(str);
  env->ReleaseStringUTFChars(apkPath, str);
  }

 }