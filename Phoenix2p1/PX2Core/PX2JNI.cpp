/*
*
* ÎÄ¼þÃû³Æ	£º	PX2JNI.cpp
*
*/

#ifndef __ANDROID__

#include "PX2Assert.hpp"
using namespace PX2;
using namespace std;

#define JAVAVM JNIHelper::GetJavaVM()

extern "C"
{

	//----------------------------------------------------------------------------
	static bool GetEnv_ (JNIEnv **env)
	{
		if (JAVAVM->GetEnv((void**)env, JNI_VERSION_1_4) != JNI_OK)
		{
			assertion(false, "Failed to get the environment using GetEnv()");
			return false;
		}

		if (JAVAVM->AttachCurrentThread(env, 0) < 0)
		{
			assertion(false, 
				"Failed to get the environment using AttachCurrentThread()");
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------------------
	static jclass GetClassID_(const char *className, JNIEnv *env)
	{
		JNIEnv *envTemp = env;
		jclass ret = 0;

		if (!envTemp)
		{
			if (!GetEnv(&envTemp))
			{
				return 0;
			}
		}

		ret = envTemp->FindClass(className);
		if (!ret)
		{
			assertion(false, "Failed to find class of %s\n", className);
			return 0;
		}

		return ret;
	}
	//----------------------------------------------------------------------------
	static bool GetStaticMethodInfo_(cocos2d::JNIMethodInfo &methodinfo, 
		const char *className, const char *methodName, const char *paramCode)
	{
		jmethodID methodID = 0;
		JNIEnv *envTemp = 0;

		if (!GetEnv(&envTemp))
			return false;

		jclass classID = GetClassID_(className, envTemp);
		methodID = envTemp->GetStaticMethodID(classID, methodName, paramCode);
		if (!methodID)
		{
			assertion(false, "Failed to find static method id of %s", methodName);
			return false;
		}

		methodinfo.classID = classID;
		methodinfo.env = envTemp;
		methodinfo.methodID = methodID;

		return true;
	}
	//----------------------------------------------------------------------------
	static bool GetMethodInfo_(cocos2d::JNIMethodInfo &methodinfo,
		const char *className, const char *methodName, const char *paramCode)
	{
		jmethodID methodID = 0;
		JNIEnv *envTemp = 0;

		if (!GetEnv(&envTemp))
			return false;

		jclass classID = GetClassID_(className, envTemp);
		methodID = envTemp->GetMethodID(classID, methodName, paramCode);
		if (!methodID)
		{
			assertion(false, "Failed to find method id of %s", methodName);
			return false;
		}

		methodinfo.classID = classID;
		methodinfo.env = envTemp;
		methodinfo.methodID = methodID;

		return true;
	}
	//----------------------------------------------------------------------------
	static string JString2string_(jstring jstr)
	{
		JNIEnv *env = 0;

		jboolean isCopy;
		if (!GetEnv(&env))
		{
			return "";
		}

		const char* chars = env->GetStringUTFChars(jstr, &isCopy);
		string ret(chars);
		if (isCopy)
		{
			env->ReleaseStringUTFChars(jstr, chars);
		}

		return ret;
	}
	//----------------------------------------------------------------------------

}

//----------------------------------------------------------------------------
JavaVM *JNIHelper::msJavaVM = 0;
//----------------------------------------------------------------------------
JavaVM *JNIHelper::GetJavaVM()
{
	return msJavaVM;
}
//----------------------------------------------------------------------------
void JNIHelper::SetJavaVM(JavaVM *javaVM)
{
	msJavaVM = javaVM;
}
//----------------------------------------------------------------------------
jclass JNIHelper::GetClassID(const char *className, JNIEnv *env)
{
	return GetClassID_(className, env);
}
//----------------------------------------------------------------------------
bool JNIHelper::GetStaticMethodInfo(JNIMethodInfo &methodinfo,
	const char *className, const char *methodName, const char *paramCode)
{
	return GetStaticMethodInfo_(methodinfo, className, methodName, paramCode);
}
//----------------------------------------------------------------------------
bool JNIHelper::GetMethodInfo(JNIMethodInfo &methodinfo, const char *className,
	const char *methodName, const char *paramCode)
{
	return GetMethodInfo_(methodinfo, className, methodName, paramCode);
}
//----------------------------------------------------------------------------
string JNIHelper::JString2string(jstring str)
{
	return JString2string_(str);
}
//----------------------------------------------------------------------------

#endif