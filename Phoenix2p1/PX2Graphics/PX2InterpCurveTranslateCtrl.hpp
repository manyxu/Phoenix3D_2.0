/*
*
* ÎÄ¼þÃû³Æ	£º	PX2InterpCurveTransCtrl.hpp
*
*/

#ifndef PX2INTERPCURVETRANSLATECTRL_HPP
#define PX2INTERPCURVETRANSLATECTRL_HPP

#include "PX2Controller.hpp"
#include "PX2InterpCurve.hpp"

namespace PX2
{

	class InterpCurveTranslateController : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(InterpCurveTranslateController);

	public:
		InterpCurveTranslateController (const Float3 &trans);
		virtual ~InterpCurveTranslateController ();

		virtual bool Update (double applicationTime);

	public:
		Float3 mInitTrans;
		InterpCurveFloat3 mTranslates;
	};

	PX2_REGISTER_STREAM(InterpCurveTranslateController);
	typedef Pointer0<InterpCurveTranslateController> InterpCurveTranslateControllerPtr;

}

#endif