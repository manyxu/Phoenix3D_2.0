/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Curve.hpp
*
*/

#ifndef PX2EDITCURVE_HPP
#define PX2EDITCURVE_HPP

#include "PX2EditorLibPre.hpp"
#include "PX2CurveCtrl.hpp"

namespace PX2Editor
{

	// curves
	class Curve 
	{
	public:
		virtual ~Curve ();

		bool IsForInit () { return mIsForInit; };
		
		void SetClientData (int data) { mData = data; }
		int GetClientData () { return mData; }
		void SetClientDataPointer (void *data) { mDataPointer = data; }
		void *GetClientDataPointer () { return mDataPointer; }

		virtual void GetInRange (float &inMin, float &inMax);
		virtual void GetOutRange (float &outMin, float &outMax);
		virtual PX2::InterpCurveMode GetInterpMode (int index);

		virtual void AddPoint (float inVal, float outZ);
		virtual int SetInVal (int index, float val);
		virtual void DeletePoint (int index);
		virtual int GetNumPoints ();

		void SetVisible (bool show);

		PX2::Float3 GetCurveColor () { return mCurveColor; }
		PX2::Node *GetNode () { return mNode; }
		PX2::Polysegment *GetPoly () { return mPoly; }
		
		CurveCtrl *GetCtrl (int i);
		void SetCtrlsScale (float scaleX, float scaleZ);
		CurveCtrl *TrySelectCurve (PX2::Movable *mov);
		virtual void UpdateCurve ();
		virtual void UpdateCtrls ();
		virtual void ReCreateCtrls ();		

	protected:
		Curve ();
		Curve (bool isForInit);

		bool mIsForInit;
		std::vector<CurveCtrlPtr> mCtrls;
		int mData;
		void *mDataPointer;
		PX2::NodePtr mNode;
		PX2::Float3 mCurveColor;
		PX2::PolysegmentPtr mPoly;
	};
	typedef PX2::Pointer0<Curve> CurvePtr;

	class CurveFloat : public Curve
	{
	public:
		CurveFloat (PX2::InterpCurveFloat *curve, PX2::Float3 color,
			bool isForInit);
		virtual ~CurveFloat ();

		virtual void GetInRange (float &inMin, float &inMax);
		virtual void GetOutRange (float &outMin, float &outMax);
		virtual PX2::InterpCurveMode GetInterpMode (int index);

		virtual void AddPoint (float inVal, float outZ);
		virtual int SetInVal (int index, float val);
		virtual void DeletePoint (int index);
		virtual int GetNumPoints ();

		virtual void UpdateCurve ();
		virtual void UpdateCtrls ();
		virtual void ReCreateCtrls ();

	public_internal:
		PX2::InterpCurveFloat *mCurve;
	};
	typedef PX2::Pointer0<CurveFloat> CurveFloatPtr;

	class CurveFloat3 : public Curve
	{
	public:
		CurveFloat3 (PX2::InterpCurveFloat3 *curve, PX2::Float3 color,
			bool isForInit);
		virtual ~CurveFloat3 ();

	protected:
		PX2::InterpCurveFloat3 *mCurve;
	};
	typedef PX2::Pointer0<CurveFloat3> CurveFloat3Ptr;

	class CurveFloat3Axis : public Curve
	{
	public:
		CurveFloat3Axis (PX2::InterpCurveFloat3 *curve, int axis, 
			PX2::Float3 color, bool isForInit);
		virtual ~CurveFloat3Axis ();

		virtual void GetInRange (float &inMin, float &inMax);
		virtual void GetOutRange (float &outMin, float &outMax);
		virtual PX2::InterpCurveMode GetInterpMode (int index);

		virtual void AddPoint (float inVal, float outZ);
		virtual int SetInVal (int index, float val);
		virtual void DeletePoint (int index);
		virtual int GetNumPoints ();

		int GetAxis () { return mAxis; }

		virtual void UpdateCurve ();
		virtual void UpdateCtrls ();
		virtual void ReCreateCtrls ();

public_internal:
		PX2::InterpCurveFloat3 *mCurve;
		int mAxis;
	};
	typedef PX2::Pointer0<CurveFloat3Axis> CurveFloat3AxisPtr;

}

#endif