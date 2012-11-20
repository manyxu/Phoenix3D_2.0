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

namespace PX2Editor
{

	class EditSystem : public PX2::Singleton<EditSystem>
	{
	public:
		EditSystem ();
		~EditSystem ();

		bool Initlize ();
		bool Terminate ();

		EditMap *GetEditMap ();
		ActorSelection *GetSelection ();

		enum EditMode
		{
			EM_NONE,
			EM_SELECT,
			EM_TRANSLATE,
			EM_ROLATE,
			EM_SCALE,
			EM_MAX_MODE
		};
		void SetEditMode (EditMode mode);
		EditMode GetEditMode ();

	protected:
		EditMap *mEditMap;
		ActorSelection *mSelection;
		PX2::NodePtr mHelpScene;
		EditMode mEditMode;
	};

#include "PX2EditSystem.inl"

}

#endif