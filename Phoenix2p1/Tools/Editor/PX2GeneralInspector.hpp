/*
*
* ÎÄ¼þÃû³Æ	£º	PX2GeneralInspector.hpp
*
*/

#ifndef PX2GENERALINSPECTOR_HPP
#define PX2GENERALINSPECTOR_HPP

#include "PX2EditorPre.hpp"
#include "PX2GeneralPropertyGrid.hpp"

namespace PX2Editor
{

	class GeneralInspector : public wxScrolledWindow
	{
	public:
		GeneralInspector (wxWindow *parent);
		~GeneralInspector ();

		void OnSize(wxSizeEvent& e);

		void SetType (int type);

	protected:
		DECLARE_EVENT_TABLE()

		GeneralInspector ();

		GeneralPropertyGrid *mGeneralPropertyGrid;
		int mType;
		bool mInitSized;
	};

}

#endif