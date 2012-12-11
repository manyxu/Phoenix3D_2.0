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
		bool LoadScene (const char *pathname);
		std::string GetLoadedScenePath () { return mLoadedScenePath; }
		bool SaveScene (const char *pathname);
		bool SaveSceneAs (const char *pathname);
		PX2::Scene *GetScene () { return mScene; }

		void CreateBox (PX2::APoint pos);
		void CreateSphere (PX2::APoint pos);
		void AddModelActor ( PX2::Movable *mov, PX2::APoint pos);
		void CreateTerrain (std::string name, int terrainSize, int pageSize,
			float gridSpacing);

		void AddActor (PX2::Actor *actor);
		void RemoveActor (PX2::Actor *actor);

		void CloneShare (PX2::Actor *actor, PX2::APoint pos);
		void CloneData (PX2::Actor *actor, PX2::APoint pos);

	protected:
		PX2::ScenePtr mScene;
		std::string mLoadedScenePath;

		PX2::VertexFormatPtr mVertexFormat;
	};

}

#endif