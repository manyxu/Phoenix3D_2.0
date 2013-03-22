/*
*
* ÎÄ¼þÃû³Æ	£º	PX2InterpCurveRotateCtrl.hpp
*
*/

#ifndef PX2INTERPCURVEROTATECTRL_HPP
#define PX2INTERPCURVEROTATECTRL_HPP

#include "PX2Controller.hpp"
#include "PX2InterpCurve.hpp"

namespace PX2
{

	class InterpCurveRotateController : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(InterpCurveRotateController);

	public:
		InterpCurveRotateController (const Float3 &initRotate);
		virtual ~InterpCurveRotateController ();

		virtual bool Update (double applicationTime);

	public:
		Float3 mInitRotate;
		InterpCurveFloat3 mRotates;
	};

	PX2_REGISTER_STREAM(InterpCurveRotateController);
	typedef Pointer0<InterpCurveRotateController> InterpCurveRotateControllerPtr;

}

#endif