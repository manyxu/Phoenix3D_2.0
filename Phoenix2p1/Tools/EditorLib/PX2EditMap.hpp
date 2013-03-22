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

		void NewProject (const char *pathname, const char *projName, int width, int height);
		bool LoadProject (const char *pathname);
		bool SaveProject ();
		bool SaveProjectAs (const char *pathname);
		void CloseProject ();
		std::string GetProjectFilePath () { return mProjectFilePath; }

		void NewScene ();
		bool LoadScene (const char *pathname);
		bool SaveScene (const char *pathname);
		bool SaveSceneAs (const char *pathname);
		void CloseScene ();

		void CreateBox (PX2::APoint pos);
		void CreateSphere (PX2::APoint pos);
		void CreateEffect (PX2::APoint pos);
		PX2::Movable *CreateParticlesToEffect (PX2::Node *node);
		void AddModelActor (PX2::Movable *mov, PX2::APoint pos);
		void CreateTerrain (std::string name, int terrainSize, int pageSize,
			float gridSpacing);
		void CreateSky ();
		void CreateUIFrame (PX2::Node *parent, PX2::Float2 posScreen);
		void CreateUIPicBox (PX2::Node *parent, PX2::Float2 posScreen,
			const std::string &filename="");
		void CreateUIAnimPicBox(PX2::Node *parent, PX2::Float2 posScreen,
			const std::string &texPack="");
		void CreateUIStaticText (PX2::Node *parent, PX2::Float2 posScreen,
			const std::string &filename="");
		void CreateUIButton (PX2::Node *parent, PX2::Float2 posScreen);

		void CreateCurveScaleCtrl (PX2::Movable *mov);
		void CreateCurveRotateCtrl (PX2::Movable *mov);
		void CreateCurveTranslateCtrl (PX2::Movable *mov);

		void AddActor (PX2::Actor *actor);
		void RemoveActor (PX2::Actor *actor);
		bool RemoveUI (PX2::Object *obj);
		bool RemoveCtrl (PX2::Object *obj);

		void CloneShare (PX2::Actor *actor, PX2::APoint pos);
		void CloneData (PX2::Actor *actor, PX2::APoint pos);

	protected:
		std::string mProjectFilePath;
		PX2::ScenePtr mScene;
		PX2::VertexFormatPtr mVertexFormat;
	};

}

#endif