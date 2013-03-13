/*
*
* ÎÄ¼þÃû³Æ	£º	PX2GeneralPropertyGrid.hpp
*
*/

#ifndef PX2GENERALPROPERTYGRID_HPP
#define PX2GENERALPROPERTYGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"

namespace PX2Editor
{

	class GeneralPropertyGrid : public ObjectPropertyGrid
	{
	public:
		GeneralPropertyGrid (wxWindow *parent);
		virtual ~GeneralPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(GeneralPropertyGrid)

		void SetType (int type);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()

		GeneralPropertyGrid ();
		void RefreshOnProject ();
		void RefreshOnScene ();
		void RefreshOnUI ();

		int mType;

		// Project
		std::string mProjName;
		int mProjWidth;
		int mProjHeight;
		PX2::Float3 mProjColor;
		bool mIsShowProjectInfo;

		bool mIsShowSceneBound;
		bool mIsSceneWired;
		bool mIsShowGrid;

		bool mIsShowUI;
		bool mIsUIWired;
		float mUICameraPercent;
		bool mIsShowUIRange;
	};

}

#endif

