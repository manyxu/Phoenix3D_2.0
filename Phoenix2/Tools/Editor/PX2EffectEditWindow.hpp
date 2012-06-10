/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EffectEditWindow.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2EFFECTEDITWINDOW_HPP
#define PX2EFFECTEDITWINDOW_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class EffectEditTimeLineWindow;

	class EffectEditWindow : public wxPanel, public PX2::EventHandler
	{
	public:
		EffectEditWindow ();
		EffectEditWindow (wxWindow* parent);
		virtual ~EffectEditWindow ();

		DECLARE_DYNAMIC_CLASS(EffectEditWindow);

		void OnEffectListbox (wxCommandEvent& event);
		void OnSize (wxSizeEvent &e);
		void OnNew (wxCommandEvent &e);
		void OnOpen (wxCommandEvent &e);
		void OnDelete (wxCommandEvent &e);
		void OnSave (wxCommandEvent &e);
		void OnSaveAs (wxCommandEvent &e);
		void OnDeleteEffectItem (wxCommandEvent &e);
		void OnNewParticleEmitter (wxCommandEvent &e);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()

		void NewEffectEditNode (std::string name);
		void LoadEffectEditNode ();
		bool LoadEffectNode (std::string pathname);
		void DeleteEffectEditNode (PX2::EffectNode *node);
		bool SaveEffectEditNode ();
		bool SaveEffectNode (std::string pathname, PX2::EffectNode *node);
		void SaveAsEffectEditNode (std::string path);
		void DeleteEffectItemOnNode (PX2::EffectNode *node, PX2::Movable *object);
		void NewParticleEmitterOnNode (PX2::EffectNode *node, std::string name);

		PX2::EffectNode *GetSelectedEffectNode ();
		void OnSelectEffectNode (PX2::EffectNode *node);

		wxToolBar* mToolbar;
		wxListBox* mEffectList;
		EffectEditTimeLineWindow *mEffectEditTimeLine;

		class EffectNodeData 
		{
		public:
			EffectNodeData () {}
			EffectNodeData (PX2::EffectNode *node)
			{
				mNode = node;
				mPath = "";
			}
			~EffectNodeData ()
			{
				mNode = 0;
				mPath = "";
			}

			PX2::EffectNodePtr mNode;
			std::string mPath;
		};
		std::vector<EffectNodeData> mEffectNodes;
	};

}

#endif