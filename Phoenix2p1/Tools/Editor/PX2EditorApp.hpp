/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditorApp.hpp
*
*/

#ifndef PX2EDITORAPP_HPP
#define PX2EDITORAPP_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class MainFrame;
	class ControllerManager;

	class EditorApp : public wxApp, public PX2::Singleton<EditorApp>
	{
	public:
		EditorApp ();
		~EditorApp ();

		virtual bool OnInit ();
		virtual int OnExit();

	protected:
		void AddHandlers ();

		MainFrame *mMainFrame;
	};

	DECLARE_APP(EditorApp)
}

#endif