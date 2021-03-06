/*
*
* �ļ�����	��	PX2EMFloatProperty.hpp
*
*/

#ifndef PX2EMFLOATPROPERTY_HPP
#define PX2EMFLOATPROPERTY_HPP

#include "PX2EditorPre.hpp"
#include "PX2Property.hpp"

namespace PX2Editor
{

	class EMFloatProperty : public Property
	{
	public:
		EMFloatProperty (PropertyPage *parent, std::string name, 
			PX2::InterpCurvePointFloat *point, bool isForInit);
		virtual ~EMFloatProperty ();

		virtual void OnChange (wxPropertyGridEvent &event);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		bool mIsForInit;
		wxPGProperty *mPropertyInVal;
		wxPGProperty *mPropertyOutVal;
		wxPGProperty *mPropertyArriveTangent;
		wxPGProperty *mPropertyLeaveTangent;
		wxPGProperty *mInterpMode;
	
		PX2::InterpCurvePointFloat *mPoint;
	};
}

#endif