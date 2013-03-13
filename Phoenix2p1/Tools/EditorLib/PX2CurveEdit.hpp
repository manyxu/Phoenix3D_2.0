/*
*
* ÎÄ¼þÃû³Æ	£º	PX2CurveEdit.hpp
*
*/

#ifndef PX2CURVEEDIT_HPP
#define PX2CURVEEDIT_HPP

#include "PX2EditorLibPre.hpp"
#include "PX2CurveCtrl.hpp"
#include "PX2Curve.hpp"
#include "PX2EffectModule.hpp"
#include "PX2CurveGroup.hpp"
#include "PX2UICurveGroup.hpp"
#include "PX2UIFrame.hpp"

namespace PX2Editor
{

	class CurveEdit
	{
	public:
		CurveEdit ();
		~CurveEdit ();

		void UpdateAllCurves ();
		void SetCtrlsScale (float scaleX, float scaleZ);
		float GetCtrlsScaleX () { return mCtrlsScaleX; }
		float GetCtrlsScaleZ () { return mCtrlsScaleZ; }

		void GetInRange (float &inMin, float &inMax);
		void GetOutRange (float &outMin, float &outMax);

		int GetNumCurves ();
		Curve *GetCurve (int i);
		bool HasCurve (Curve *curve);
		void AddCurve (Curve *curve);
		void RemoveCurve (Curve *curve);
		void CreateAddCurve (PX2::EffectModule *module);
		void ReCreateAddCurve (PX2::EffectModule *module);
		bool HasCurveGroup (PX2::EffectModule *module);
		void RemoveGroup (PX2::EffectModule *module);
		void ClearGroup (PX2::UICurveGroup *uiGroup);
		void ClearAllGroups ();
		CurveGroup *GetCurveGroup (PX2::EffectModule *module);
		CurveGroup *GetCurveGroup (Curve *curve);
		void UpdateCurve (PX2::EffectModule *module);

		void SetActiveCurve (Curve *curve);
		Curve *GetActiveCurve () { return mActiveCurve; }
		CurveCtrl *TrySelectCurve (PX2::Movable *mov);
		void SetSelectedCurveCtrl (CurveCtrl *ctrl);
		CurveCtrl *GetSelectedCurveCtrl () { return mSelectedCurveCtrl; }

		void SetSelectedUICurveGroup (PX2::UICurveGroup *group);
		PX2::UICurveGroup *GetSelectedUICurveGroup () { return mSelectedCruveGroup; }

		PX2::VertexFormat *GetVertexFormat () { return mVFormat; }

		// CurveEditor Scene
		PX2::Node *GetCurveEditorScene () { return mCurveEditorScene; }

		// MainView Curves
		PX2::Node *GetMainViewScene () { return mMainViewScene; }

public_internal:
		PX2::Polysegment *CreatePoly (PX2::InterpCurveFloat *curve,
			PX2::Float3 color);
		void UpdatePoly (PX2::InterpCurveFloat *curve, PX2::Polysegment *p,
			PX2::Float3 color);
		PX2::Polysegment *CreatePoly(PX2::InterpCurveFloat3 *curve, int axis,
			PX2::Float3 color);
		void UpdatePoly (PX2::InterpCurveFloat3 *curve, PX2::Polysegment *p,
			int axis, PX2::Float3 color);

	protected:
		void AddGroup (CurveGroup *group);
		int GetNumGroups ();
		void RemoveGroup (CurveGroup *group);

		PX2::UICurveGroup *GetUICurveGroupFormUIView (PX2::UIFrame *frame, CurveGroup *group);

		float mCtrlsScaleX;
		float mCtrlsScaleZ;
		float mMaxRange;
		PX2::VertexFormatPtr mVFormat;
		std::vector<CurvePtr> mCurves;
		std::vector<CurveGroupPtr> mCurveGroups;
		PX2::UICurveGroupPtr mSelectedCruveGroup;
		CurvePtr mActiveCurve;
		CurveCtrlPtr mSelectedCurveCtrl;
		int mNumSamples;

		PX2::NodePtr mCurveEditorScene;
		PX2::NodePtr mMainViewScene;
	};

}

#endif