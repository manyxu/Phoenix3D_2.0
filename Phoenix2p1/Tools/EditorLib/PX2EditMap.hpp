/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditMap.hpp
*
*/

#ifndef PX2EDITMAP_HPP
#define PX2EDITMAP_HPP

#include "PX2EditorLibPre.hpp"
#include "PX2Scene.hpp"
#include "PX2Actor.hpp"

namespace PX2Editor
{

	class EditMap
	{
	public:
		EditMap ();
		~EditMap ();

		void NewScene ();
		bool LoadScene (std::string pathname);
		std::string GetLoadedScenePath () { return mLoadedScenePath; }
		bool SaveScene (std::string pathname);
		bool SaveSceneAs (std::string pathname);
		PX2::Scene *GetScene () { return mScene; }

		void AddActor (PX2::Actor *actor);
		void RemoveActor (PX2::Actor *actor);
		void RemoveSelection ();

	protected:
		PX2::ScenePtr mScene;
		std::string mLoadedScenePath;

		PX2::VertexFormatPtr mVertexFormat;
	};

}

#endif