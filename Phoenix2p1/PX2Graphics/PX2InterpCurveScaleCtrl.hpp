/*
*
* ÎÄ¼þÃû³Æ	£º	PX2InterpCurveTransCtrl.hpp
*
*/

#ifndef PX2INTERPCURVESCALESCTRL_HPP
#define PX2INTERPCURVESCALESCTRL_HPP

#include "PX2Controller.hpp"
#include "PX2InterpCurve.hpp"

namespace PX2
{

	class InterpCurveScaleController : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(InterpCurveScaleController);

	public:
		InterpCurveScaleController (const Float3 &initScale);
		virtual ~InterpCurveScaleController ();

		virtual bool Update (double applicationTime);

	public:
		Float3 mInitScale;
		InterpCurveFloat3 mScales;
	};

	PX2_REGISTER_STREAM(InterpCurveScaleController);
	typedef Pointer0<InterpCurveScaleController> InterpCurveScaleControllerPtr;

}

#endif