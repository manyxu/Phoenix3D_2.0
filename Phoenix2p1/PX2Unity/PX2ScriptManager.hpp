/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ScriptManager.hpp
*
*/

#ifndef PX2SCRIPTMANAGER_HPP
#define PX2SCRIPTMANAGER_HPP

#include "PX2UnityPre.hpp"

namespace PX2
{

	class ScriptManager : public Singleton<ScriptManager>
	{
	public:
		ScriptManager ();
		virtual ~ScriptManager ();

		enum ScriptType
		{
			ST_LUA,
			ST_MAX_TYPE
		};
		static ScriptManager *Create (ScriptType type);
		ScriptType GetScriptType ();

		virtual bool CallString (const char *str) = 0;
		virtual bool CallFile (const char *filename) = 0;
		virtual bool CallBuffer (const char *buffer, unsigned long size) = 0;
		virtual void SetUserTypePointer (const char *luaName, const char *className,
			void *ptr) = 0;

	protected:
		ScriptType mType;
	};

	#define PX2_SM ScriptManager::GetSingleton()

}

#endif