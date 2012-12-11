/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditSystem.hpp
*
*/

#ifndef PX2EDITSYSTEM_HPP
#define PX2EDITSYSTEM_HPP

#include "PX2EditorLibPre.hpp"
#include "PX2EditMap.hpp"
#include "PX2ActorSelection.hpp"
#include "PX2EditCommand.hpp"
#include "PX2TerrainEdit.hpp"

namespace PX2Editor
{

	class EditSystem : public PX2::Singleton<EditSystem>
	{
	public:
		EditSystem ();
		~EditSystem ();

		bool Initlize ();
		bool Terminate ();
		void Update (double elapsedSeconds);

		EditCommandManager *GetCM ();
		TerrainEdit *GetTerrainEdit ();
		EditMap *GetEditMap ();
		ActorSelection *GetSelection ();
		PX2::Node *GetHelpScene ();

		void EnableSelectEdit (bool enable);
		bool IsSelectEditEnable ();
		enum EditMode
		{
			EM_NONE,
			EM_SELECT,
			EM_TRANSLATE,
			EM_ROLATE,
			EM_SCALE,
			EM_TERRAIN,
			EM_MAX_MODE
		};
		void SetEditMode (EditMode mode);
		EditMode GetEditMode ();

		// PreView Object
		void SetPreViewObject (PX2::Object *obj);
		PX2::Object *GetPreViewObject ();

		// Selected Resource
		void SetSelectedResource (PX2::Object *obj);
		void SetSelectedResourceName (std::string name);
		PX2::Object *GetSelectedResource ();
		std::string GetSelectedResourceName ();

		PX2::TriMesh *GetXYPlane ();
		PX2::TriMesh *GetXZPlane ();
		PX2::TriMesh *GetYZPlane ();

	protected:
		EditCommandManager *mCM;
		TerrainEdit *mTerrainEdit;
		EditMap *mEditMap;
		ActorSelection *mSelection;
		PX2::NodePtr mHelpScene;
		bool mSelectEditEnable;
		EditMode mEditMode;
		PX2::ObjectPtr mPreViewObject;
		PX2::ObjectPtr mSelectedResource;
		std::string mSelectedResourceName;

		PX2::TriMeshPtr mXYPlane;
		PX2::TriMeshPtr mXZPlane;
		PX2::TriMeshPtr mYZPlane;
	};

#include "PX2EditSystem.inl"

}

#endif