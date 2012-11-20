/*
*
* ÎÄ¼þÃû³Æ	£º	PX2LanguageManager.hpp
*
*/

#ifndef PX2LANGUAGEMANAGER_HPP
#define PX2LANGUAGEMANAGER_HPP

#include "PX2UnityPre.hpp"

namespace PX2
{

	class LanguageManager
	{
	public:
		~LanguageManager ();

		static LanguageManager &GetSingleton ();

		bool Load (const char *filename);
		void SetLanguage (int index);
		std::string GetValue (std::string key);
		std::string GetValue (std::string key, int index);

	protected:
		LanguageManager ();

		int mLanguageIndex;
		std::map<std::string, std::vector<std::string> > mLanguages;
	};

#define PX2_LM LanguageManager::GetSingleton()

}

#endif