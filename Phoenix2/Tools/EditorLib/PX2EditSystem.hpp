/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EditorSystem.hpp
*
* 版本		:	1.0 (2011/05/01)
*
* 作者		：	more
*
*/

#ifndef PX2EDITSYSTEM_HPP
#define PX2EDITSYSTEM_HPP

#include "PX2EditorLibPrerequisites.hpp"

namespace PX2Editor
{

	class EditMap;
	class TerrainEdit;
	class EffectEdit;

	class EditSystem : public PX2::Singleton<EditSystem>
	{
	public:
		EditSystem ();
		~EditSystem ();

		// init shutdown
		bool Initlize ();
		bool Terminate ();

		// edit mode
		enum EditMode
		{
			EM_NONE,
			EM_SELECT,
			EM_TRANSLATE,
			EM_ROLATE,
			EM_SCALE,
			EM_TERRAIN_HEIGHT,
			EM_TERRAIN_TEXTURE,
			EM_EFFECT,
			EM_TEXTURECONVERT,
			EM_PHYSICSPLAY,
			EM_MAX_MODE
		};

		void SetEditMode (EditMode mode);
		EditMode GetEditMode ();

		// help scene
		PX2::Node *GetHelpScene () { return mHelpScene; }

		// PreView Object
		void SetPreViewObject (PX2::Object *obj);
		PX2::Object *GetPreViewObject ();

		// Selected Resource
		void SetSelectedResource (PX2::Object *obj);
		void SetSelectedResourceName (std::string name);
		PX2::Object *GetSelectedResource ();
		std::string GetSelectedResourceName ();

		// other
		PX2::EventWorld *GetEventWorld () { return mEditorEventWorld; }
		EditMap *GetEditMap () { return mEditMap; }
		TerrainEdit *GetTerrainEdit () { return mTerrainEdit; }
		EffectEdit *GetEffectEdit () { return mEffectEdit; }

	protected:
		PX2::EventWorld *mEditorEventWorld;
		EditMode mMode;
		EditMap *mEditMap;
		TerrainEdit *mTerrainEdit;
		EffectEdit *mEffectEdit;
		PX2::NodePtr mHelpScene;
		PX2::ObjectPtr mPreViewObject;
		PX2::ObjectPtr mSelectedResource;
		std::string mSelectedResourceName;
	};
}

#endif