/*
*
* ÎÄ¼þÃû³Æ	£º	PX2JNI.hpp
*
*/

#ifndef PX2JNI_HPP
#define PX2JNI_HPP

#ifdef __ANDROID__

#include "PX2CorePre.hpp"
#include <jni.h>

namespace PX2
{

	struct JNIMethodInfo
	{
		JNIEnv *env;
		jclass classID;
		jmethodID methodID;
	};

	class JNIHelper
	{
	public:
		static void SetJavaVM (JavaVM *vm);
		static JavaVM *GetJavaVM ();
		static jclass GetClassID (const char *className, JNIEnv *env=0);
		static bool GetStaticMethodInfo (JNIMethodInfo &methodinfo,
			const char *className, const char *methodName, 
			const char *paramCode);
		static bool GetMethodInfo (JNIMethodInfo &methodinfo,
			const char *className, const char *methodName, 
			const char *paramCode);
		static std::string JString2string (jstring str);

	private:
		static JavaVM *msJavaVM;
	};

}

extern "C"
{
	extern const char* GetCurrentLanguageJNI();
	extern const char* GetPackageNameJNI();
}

#endif

#endif
