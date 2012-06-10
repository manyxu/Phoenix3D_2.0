/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EditMap.hpp
*
* 版本		:	1.0 (2011/05/01)
*
* 作者		：	more
*
*/

#ifndef PX2EDITMAP_HPP
#define PX2EDITMAP_HPP

#include "PX2EditorLibPrerequisites.hpp"

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
		
		void NewAndAddTerrain (std::string name,int terrainSize, int pageSize,
			float gridSpacing);
		void NewAndAddCube (std::string name);
		void NewAndAddSphere (std::string name);
		void NewAndAddPlane (std::string name);
		void NewAndAddLight (std::string name, PX2::APoint pos, PX2::Light::Type type);
		void NewAndAddModel (PX2::APoint pos);
		void NewAndAddSound (PX2::APoint pos);

		// 物理测试用
		void FireACube (PX2::APoint pos, PX2::AVector dir, float strength);

		void AddActor (PX2::Actor *actor);
		void RemoveActor (PX2::Actor *actor);
		void RemoveSelection ();

		PX2::RawTerrainActor *GetTerrainActor ();

		void SetDrawPhysics (bool draw);
		bool IsPhysicsDraw ();

	protected:
		PX2::ScenePtr mScene;
		PX2::RawTerrainActorPtr mTerrainActor;
		std::string mLoadedScenePath;
		PX2::VertexFormatPtr mVertexFormat;

		bool mDrawPhysics;
	};

}

#endif