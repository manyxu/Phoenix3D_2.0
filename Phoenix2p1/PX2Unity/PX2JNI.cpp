/*
*
* ÎÄ¼þÃû³Æ	£º	PX2JNI.cpp
*
*/

#ifdef __ANDROID__
#include "PX2JNI.hpp"
#include "PX2Assert.hpp"
#include "PX2Log.hpp"
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
			assertion(false, "Failed to get the environment using GetEnv_()");
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
			if (!GetEnv_(&envTemp))
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
	static bool GetStaticMethodInfo_(JNIMethodInfo &methodinfo, 
		const char *className, const char *methodName, const char *paramCode)
	{
		jmethodID methodID = 0;
		JNIEnv *envTemp = 0;

		if (!GetEnv_(&envTemp))
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
	static bool GetMethodInfo_(JNIMethodInfo &methodinfo,
		const char *className, const char *methodName, const char *paramCode)
	{
		jmethodID methodID = 0;
		JNIEnv *envTemp = 0;

		if (!GetEnv_(&envTemp))
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
		if (!GetEnv_(&env))
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

//----------------------------------------------------------------------------
extern "C"
{

	const char *GetPackageNameJNI()
	{
		JNIMethodInfo t;

		if (JNIHelper::GetStaticMethodInfo(t,
			"phoenix3d/px2/library/PX2Activity",
			"GetPX2PackageName",
			"()Ljava/lang/String;"))
		{
			jstring jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);

			std::string str = JNIHelper::JString2string(jstr);

			t.env->DeleteLocalRef(jstr);

			PX2_LOG_INFO("package name is %s\n", str.c_str());

			return str.c_str();
		}

		return 0;
	}

	const char *GetCurrentLanguageJNI()
	{
		JNIMethodInfo t;

		if (JNIHelper::GetStaticMethodInfo(t,
			"phoenix3d/px2/library/PX2Activity",
			"GetCurrentLanguage",
			"()Ljava/lang/String;"))
		{
			jstring jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);

			std::string str = JNIHelper::JString2string(jstr);

			t.env->DeleteLocalRef(jstr);

			PX2_LOG_INFO("language name %s\n", str.c_str());

			return str.c_str();
		}

		return 0;
	}

}
//----------------------------------------------------------------------------


#endif