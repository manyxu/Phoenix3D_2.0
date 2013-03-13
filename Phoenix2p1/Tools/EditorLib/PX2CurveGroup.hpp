/*
*
* ÎÄ¼þÃû³Æ	£º	PX2CurveGroup.hpp
*
*/

#ifndef PX2CURVEGROUP_HPP
#define PX2CURVEGROUP_HPP

#include "PX2Curve.hpp"
#include "PX2EffectModule.hpp"

namespace PX2Editor
{

	class CurveGroup
	{
	public:
		enum CGType
		{
			CGT_FLOAT,
			CGT_FLOATRANGE,
			CGT_FLOAT3,
			CGT_FLOAT3RANGE,
			CGT_MAX_TYPE
		};
		CurveGroup (CGType t);
		~CurveGroup ();

		void SetCGType (CGType type) { mType = type; }
		CGType GetCGType () { return mType; }

		void SetClientData (int data) { mData = data; }
		int GetClientData () { return mData; }
		void SetClientDataPointer (void *data) { mDataPointer = data; }
		void *GetClientDataPointer () { return mDataPointer; }

		void SetName (std::string name);
		std::string GetName ();

		void SetVisible (bool show);
		void SetVisible (int index, bool show);

		void AddPoint (const PX2::APoint &pos);
		void DeletePoint (int index);
		int SetInVal (int index, float val);

		void UpdateCurve ();
		void UpdateCtrls ();
		void ReCreateCtrls ();

		CurvePtr mCurve0;
		CurvePtr mCurve1;
		CurvePtr mCurve2;
		CurvePtr mCurve3;
		CurvePtr mCurve4;
		CurvePtr mCurve5;
		PX2::EffectModulePtr mModule;

	protected:
		CurveGroup ();

		int mData;
		void *mDataPointer;
		CGType mType;
		std::string mName;
	};
	typedef PX2::Pointer0<CurveGroup> CurveGroupPtr;

}

#endif