/*
*
* ÎÄ¼şÃû³Æ	£º	PX2LanguageManager.cpp
*
*/

#include "PX2LanguageManager.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2CSVParser.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
LanguageManager::~LanguageManager ()
{
}
//----------------------------------------------------------------------------
LanguageManager &LanguageManager::GetSingleton ()
{
	static LanguageManager man;
	return man;
}
//----------------------------------------------------------------------------
bool LanguageManager::Load (const char *filename)
{
	CSVParser csv;

	if (csv.Open(filename))
	{
		mLanguages.clear();
		
		// language start form 2
		for (int i=2; i<csv.GetRowsNum(); i++)
		{
			for (int j=1; j<csv.GetColsNum(); j++)
			{
				mLanguages[csv.GetData(i, 0)].push_back(csv.GetData(i, j));
			}
		}

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void LanguageManager::SetLanguage (int index)
{
	mLanguageIndex = index;
}
//----------------------------------------------------------------------------
std::string LanguageManager::GetValue (std::string key)
{
	if (mLanguageIndex < (int)mLanguages[key].size())
	{
		return mLanguages[key][mLanguageIndex];
	}

	assertion(false, "language key %s does not exist.", key.c_str());

	return "";
}
//----------------------------------------------------------------------------
std::string LanguageManager::GetValue (std::string key, int index)
{
	if (index < (int)mLanguages[key].size())
	{
		return mLanguages[key][index];
	}

	assertion(false, "language key %s does not exist.", key.c_str());

	return "";
}
//----------------------------------------------------------------------------
LanguageManager::LanguageManager ()
	:
mLanguageIndex(0)
{
}
//----------------------------------------------------------------------------