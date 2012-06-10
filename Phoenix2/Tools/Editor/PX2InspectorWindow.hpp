/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Inspector.hpp
*
* 版本		:	1.0 (2011/11/01)
*
* 作者		：	more
*
*/

#ifndef PX2INSPECTORWINDOW_HPP
#define PX2INSPECTORWINDOW_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class TerrainInspector;
	class ModelInspector;
	class TextureConvertPane;
	class TexturePropertyGrid;
	class EffectInspector;
	class LightInspector;
	class EnvironmentPanel;
	class SoundPanel;

	class InspectorWindow : public wxWindow, public PX2::EventHandler
	{
	public:
		InspectorWindow (wxWindow *parent);
		~InspectorWindow ();

		void SetObject (PX2::Object *object);

		enum InspecWinType
		{
			IWT_TERRAIN,
			IWT_MODELACTOR,
			IWT_TEXCONVERT,
			IWT_TEXTURE,
			IWT_LIGHT,
			IWT_EFFECT,
			IWT_ENVIRONMENT,
			IWT_SOUND,
			IWT_MAX_TYPE
		};

		void SwitchToWindow (InspecWinType type);

		void HideAllWindow ();

		void OnSize(wxSizeEvent& e);

		// 事件
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()

		void OnSetObject (PX2::Object *object);

		PX2::ObjectPtr mObject;

		InspecWinType mInspecWinType;
		TerrainInspector *mTerInspec;
		ModelInspector *mModelInspec;
		TexturePropertyGrid *mTextureInspec;
		TextureConvertPane *mTexConInspec;
		EffectInspector *mEffectInspec;
		EnvironmentPanel *mEnviInspec;
		LightInspector *mLightInspec;
		SoundPanel *mSoundInspec;

		wxWindow *mCurrentWindow;
		std::map<InspecWinType, wxWindow*> mWindows;
	};

}

#endif