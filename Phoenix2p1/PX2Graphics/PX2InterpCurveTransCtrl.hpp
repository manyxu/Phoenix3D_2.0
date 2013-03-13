/*
*
* ÎÄ¼þÃû³Æ	£º	PX2InterpCurveTransCtrl.hpp
*
*/

#ifndef PX2INTERPCURVETRANSCTRL_HPP
#define PX2INTERPCURVETRANSCTRL_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2TransformController.hpp"
#include "PX2InterpCurve.hpp"

namespace PX2
{

	class InterpCurveTransController : public TransformController
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(InterpCurveTransController);

	public:
		InterpCurveTransController (const Transform& localTransform);
		virtual ~InterpCurveTransController ();

		virtual bool Update (double applicationTime);

	public:
		InterpCurveFloat3 mScales;
		InterpCurveFloat3 mRotates;
		InterpCurveFloat3 mTrans;
	};

	PX2_REGISTER_STREAM(InterpCurveTransController);
	typedef Pointer0<InterpCurveTransController> InterpCurveTransControllerPtr;
#include "PX2InterpCurveTransCtrl.inl"

}

#endif