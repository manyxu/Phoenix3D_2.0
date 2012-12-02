/*
*
* ÎÄ¼þÃû³Æ	£º	PX2GameManager.hpp
*
*/

#ifndef PX2GAMEMANAGER_HPP
#define PX2GAMEMANAGER_HPP

#include "PX2GamePre.hpp"
#include "PX2Singleton.hpp"

namespace PX2
{

	class GameManager : public Singleton<GameManager>
	{
	public:
		GameManager ();
		~GameManager ();

		bool LoadBoost (const char *filename);
		int GetBoostWidth () const;
		int GetBoostHeight () const;
		std::string GetMapName () const;

	private:
		int mBoostWidth;
		int mBoostHeight;
		std::string mMapName;
	};

#include "PX2GameManager.inl"

}

#endif