/*
*
* ÎÄ¼þÃû³Æ	£º	PX2CurveEdit.cpp
*
*/

#include "PX2CurveEdit.hpp"
#include "PX2UIManager.hpp"
using namespace PX2Editor;
using namespace PX2;

CurveEdit::CurveEdit ()
	:
mNumSamples(512),
mCtrlsScaleX(1.0f),
mCtrlsScaleZ(1.0f),
mMaxRange(99999.0f),
mSelectedCruveGroup(0)
{
	mVFormat = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT3, 0);

	mCurveEditorScene = new0 Node();
	mMainViewScene = new0 Node();
}
//----------------------------------------------------------------------------
CurveEdit::~CurveEdit ()
{
}
//----------------------------------------------------------------------------
void CurveEdit::GetInRange (float &inMin, float &inMax)
{
	for (int i=0; i<(int)mCurves.size(); i++)
	{
		if (mCurves[i])
		{
			mCurves[i]->GetInRange(inMin, inMax);
		}
	}
}
//----------------------------------------------------------------------------
void CurveEdit::GetOutRange (float &outMin, float &outMax)
{
	for (int i=0; i<(int)mCurves.size(); i++)
	{
		if (mCurves[i])
		{
			mCurves[i]->GetOutRange(outMin, outMax);
		}
	}
}
//----------------------------------------------------------------------------
void CurveEdit::UpdateAllCurves ()
{
	for (int i=0; i<(int)mCurves.size(); i++)
	{
		if (mCurves[i])
		{
			mCurves[i]->UpdateCurve();
			mCurves[i]->UpdateCtrls();
		}
	}
}
//----------------------------------------------------------------------------
void CurveEdit::SetCtrlsScale (float scaleX, float scaleZ)
{
	mCtrlsScaleX = scaleX;
	mCtrlsScaleZ = scaleZ;

	for (int i=0; i<(int)mCurves.size(); i++)
	{
		if (mCurves[i])
		{
			mCurves[i]->SetCtrlsScale(scaleX, scaleZ);
		}
	}
}
//----------------------------------------------------------------------------
int CurveEdit::GetNumCurves ()
{
	return (int)mCurves.size();
}
//----------------------------------------------------------------------------
Curve *CurveEdit::GetCurve (int i)
{
	if (0<=i && i<(int)mCurves.size())
		return mCurves[i];

	return 0;
}
//----------------------------------------------------------------------------
bool CurveEdit::HasCurve (Curve *curve)
{
	for (int i=0; i<(int)mCurves.size(); i++)
	{
		if (curve == mCurves[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void CurveEdit::AddCurve (Curve *curve)
{
	if (!curve)
		return;

	if (!HasCurve(curve))
	{
		mCurves.push_back(curve);

		mCurveEditorScene->AttachChild(curve->GetNode());
	}
}
//----------------------------------------------------------------------------
void CurveEdit::RemoveCurve (Curve *curve)
{
	if (!curve)
		return;

	std::vector<CurvePtr>::iterator it = mCurves.begin();
	for (; it!=mCurves.end(); it++)
	{
		if (curve == *it)
		{
			mCurveEditorScene->DetachChild(curve->GetNode());

			mCurves.erase(it);
			return;
		}
	}
}
//----------------------------------------------------------------------------
void CurveEdit::CreateAddCurve (PX2::EffectModule *module)
{
	if (HasCurveGroup(module))
		return;

	EffectModule::ModuleType moduleType = module->GetModuleType();
	bool isRange = module->IsRange();
	CurveGroup *group = 0;
	if (EffectModule::MT_FLOAT == moduleType && !isRange)
	{
		CurvePtr curve = new0 CurveFloat(&(module->GetCurveFloatMin()),
			Float3::RED, module->IsForInit());
		AddCurve(curve);
		curve->SetClientDataPointer(module);
		group = new0 CurveGroup(CurveGroup::CGT_FLOAT);
		group->mCurve0 = curve;
		group->mModule = module;
		group->SetName(module->GetName());
		group->SetClientDataPointer(module);
		AddGroup(group);
	}
	else if (EffectModule::MT_FLOAT==moduleType && isRange)
	{
		CurvePtr curve0 = new0 CurveFloat(&(module->GetCurveFloatMin()),
			Float3::RED, module->IsForInit());
		CurvePtr curve1 = new0 CurveFloat(&(module->GetCurveFloatMax()),
			Float3::GREEN, module->IsForInit());
		AddCurve(curve0);
		AddCurve(curve1);
		curve0->SetClientDataPointer(module);
		curve1->SetClientDataPointer(module);
		group = new0 CurveGroup(CurveGroup::CGT_FLOATRANGE);
		group->mCurve0 = curve0;
		group->mCurve1 = curve1;
		group->mModule = module;
		group->SetName(module->GetName());
		group->SetClientDataPointer(module);
		AddGroup(group);
	}
	else if (EffectModule::MT_FLOAT3 == moduleType && !isRange)
	{
		CurvePtr curve0= new0 CurveFloat3Axis(&(module->GetCurveFloat3Min()), 0, 
			Float3::RED, module->IsForInit());
		CurvePtr curve1= new0 CurveFloat3Axis(&(module->GetCurveFloat3Min()), 1,
			Float3::GREEN, module->IsForInit());
		CurvePtr curve2= new0 CurveFloat3Axis(&(module->GetCurveFloat3Min()), 2,
			Float3::BLUE, module->IsForInit());
		AddCurve(curve0);
		AddCurve(curve1);
		AddCurve(curve2);
		curve0->SetClientDataPointer(module);
		curve1->SetClientDataPointer(module);
		curve2->SetClientDataPointer(module);
		group = new0 CurveGroup(CurveGroup::CGT_FLOAT3);
		group->mCurve0 = curve0;
		group->mCurve1 = curve1;
		group->mCurve2 = curve2;
		group->mModule = module;
		group->SetName(module->GetName());
		group->SetClientDataPointer(module);
		AddGroup(group);
	}
	else if (EffectModule::MT_FLOAT3==moduleType && isRange)
	{
		CurvePtr curve0= new0 CurveFloat3Axis(&(module->GetCurveFloat3Max()), 0,
			Float3::RED, module->IsForInit());
		CurvePtr curve1= new0 CurveFloat3Axis(&(module->GetCurveFloat3Max()), 1,
			Float3::GREEN, module->IsForInit());
		CurvePtr curve2= new0 CurveFloat3Axis(&(module->GetCurveFloat3Max()), 2,
			Float3::BLUE, module->IsForInit());
		float low = 0.4f;
		CurvePtr curve3= new0 CurveFloat3Axis(&(module->GetCurveFloat3Min()), 0,
			Float3(low, 0.0f, 0.0f), module->IsForInit());
		CurvePtr curve4= new0 CurveFloat3Axis(&(module->GetCurveFloat3Min()), 1,
			Float3(0.0f, low, 0.0f), module->IsForInit());
		CurvePtr curve5= new0 CurveFloat3Axis(&(module->GetCurveFloat3Min()), 2,
			Float3(0.0f, 0.0f, low), module->IsForInit());
		AddCurve(curve0);
		AddCurve(curve1);
		AddCurve(curve2);
		AddCurve(curve3);
		AddCurve(curve4);
		AddCurve(curve5);
		curve0->SetClientDataPointer(module);
		curve1->SetClientDataPointer(module);
		curve2->SetClientDataPointer(module);
		curve3->SetClientDataPointer(module);
		curve4->SetClientDataPointer(module);
		curve5->SetClientDataPointer(module);
		group = new0 CurveGroup(CurveGroup::CGT_FLOAT3RANGE);
		group->mCurve0 = curve0;
		group->mCurve1 = curve1;
		group->mCurve2 = curve2;
		group->mCurve3 = curve3;
		group->mCurve4 = curve4;
		group->mCurve5 = curve5;
		group->mModule = module;
		group->SetName(module->GetName());
		group->SetClientDataPointer(module);
		AddGroup(group);
	}

	UICurveGroupPtr uiGroup = new0 UICurveGroup(group);
	UIView *view = UIManager::GetSingleton().GetUIView("CurveEditWindow");
	if (view)
	{
		view->GetMainFrame()->AttachChild(uiGroup);

		float uiHeight = uiGroup->GetSize().Height;
		int numGroups = GetNumGroups();
		float posZ = (numGroups-1)*uiHeight;
		uiGroup->LocalTransform.SetTranslate(APoint(0.0f, 0.0f, posZ));
	}
}
//----------------------------------------------------------------------------
void CurveEdit::ReCreateAddCurve (PX2::EffectModule *module)
{
	if (!HasCurveGroup(module))
		return;

	RemoveGroup(module);

	CreateAddCurve(module);
}
//----------------------------------------------------------------------------
bool CurveEdit::HasCurveGroup (PX2::EffectModule *module)
{
	for (int i=0; i<(int)mCurveGroups.size(); i++)
	{
		if (module == mCurveGroups[i]->mModule)
		{
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void CurveEdit::RemoveGroup (PX2::EffectModule *module)
{
	UIView *view = UIManager::GetSingleton().GetUIView("CurveEditWindow");

	std::vector<CurveGroupPtr>::iterator it = mCurveGroups.begin();
	for (; it!=mCurveGroups.end(); it++)
	{
		if ((*it)->mModule == module)
		{
			CurveGroup *group = *it;

			RemoveCurve(group->mCurve0);
			RemoveCurve(group->mCurve1);
			RemoveCurve(group->mCurve2);
			RemoveCurve(group->mCurve3);
			RemoveCurve(group->mCurve4);
			RemoveCurve(group->mCurve5);

			if (view)
			{
				UIFrame *frame = view->GetMainFrame();
				UICurveGroup *uiGroup = GetUICurveGroupFormUIView(frame, group);
				if (uiGroup)
				{
					frame->DetachChild(uiGroup);
				}
			}

			*it = 0;
			mCurveGroups.erase(it);
			break;
		}
	}

	// adjust all ui position
	for (int i=0; i<(int)mCurveGroups.size(); i++)
	{
		CurveGroup *group = mCurveGroups[i];

		if (view)
		{
			UIFrame *frame = view->GetMainFrame();
			UICurveGroup *uiGroup = GetUICurveGroupFormUIView(frame, group);
			if (uiGroup)
			{
				float uiHeight = uiGroup->GetSize().Height;
				float posZ = i*uiHeight;
				uiGroup->LocalTransform.SetTranslate(APoint(0.0f, 0.0f, posZ));
			}
		}
	}
}
//----------------------------------------------------------------------------
void CurveEdit::ClearGroup (UICurveGroup *uiGroup)
{
	UIView *view = UIManager::GetSingleton().GetUIView("CurveEditWindow");
	if (!view)
		return;
	UIFrame *frame = view->GetMainFrame();

	if (!uiGroup)
		return;

	CurveGroup *curveGroup = uiGroup->GetCurveGroup();
	frame->DetachChild(uiGroup);

	RemoveCurve(curveGroup->mCurve0);
	RemoveCurve(curveGroup->mCurve1);
	RemoveCurve(curveGroup->mCurve2);
	RemoveCurve(curveGroup->mCurve3);
	RemoveCurve(curveGroup->mCurve4);
	RemoveCurve(curveGroup->mCurve5);
	RemoveGroup(curveGroup);

	// adjust all ui position
	for (int i=0; i<(int)mCurveGroups.size(); i++)
	{
		CurveGroup *group = mCurveGroups[i];

		if (view)
		{
			UIFrame *frame = view->GetMainFrame();
			UICurveGroup *uiGroup = GetUICurveGroupFormUIView(frame, group);
			if (uiGroup)
			{
				float uiHeight = uiGroup->GetSize().Height;
				float posZ = i*uiHeight;
				uiGroup->LocalTransform.SetTranslate(APoint(0.0f, 0.0f, posZ));
			}
		}
	}
}
//----------------------------------------------------------------------------
void CurveEdit::ClearAllGroups ()
{
	for (int i=0; i<(int)mCurveGroups.size(); i++)
	{
		CurveGroup *group = mCurveGroups[i];

		RemoveCurve(group->mCurve0);
		RemoveCurve(group->mCurve1);
		RemoveCurve(group->mCurve2);
		RemoveCurve(group->mCurve3);
		RemoveCurve(group->mCurve4);
		RemoveCurve(group->mCurve5);
	}
	mCurveGroups.clear();

	UIView *view = UIManager::GetSingleton().GetUIView("CurveEditWindow");
	if (!view)
		return;

	UIFrame *frame = view->GetMainFrame();
	for (int i=0; i<frame->GetNumChildren(); i++)
	{
		frame->DetachChildAt(i);
	}
}
//----------------------------------------------------------------------------
CurveGroup *CurveEdit::GetCurveGroup (Curve *curve)
{
	for (int i=0; i<(int)mCurveGroups.size(); i++)
	{
		if (curve == mCurveGroups[i]->mCurve0 
			|| curve == mCurveGroups[i]->mCurve0 
			|| curve == mCurveGroups[i]->mCurve1
			|| curve == mCurveGroups[i]->mCurve2 
			|| curve == mCurveGroups[i]->mCurve3 
			|| curve == mCurveGroups[i]->mCurve4 
			|| curve == mCurveGroups[i]->mCurve5)
		{
			return mCurveGroups[i];
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
CurveGroup *CurveEdit::GetCurveGroup (PX2::EffectModule *module)
{
	for (int i=0; i<(int)mCurveGroups.size(); i++)
	{
		if (module == mCurveGroups[i]->mModule)
		{
			return mCurveGroups[i];
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
void CurveEdit::UpdateCurve (PX2::EffectModule *module)
{
	CurveGroup *group = GetCurveGroup(module);
	if (group)
	{
		if (group->mCurve0)
		{
			group->mCurve0->UpdateCurve();
			group->mCurve0->UpdateCtrls();
		}

		if (group->mCurve1)
		{
			group->mCurve1->UpdateCurve();
			group->mCurve1->UpdateCtrls();
		}

		if (group->mCurve2)
		{
			group->mCurve2->UpdateCurve();
			group->mCurve2->UpdateCtrls();
		}

		if (group->mCurve3)
		{
			group->mCurve3->UpdateCurve();
			group->mCurve3->UpdateCtrls();
		}

		if (group->mCurve4)
		{
			group->mCurve4->UpdateCurve();
			group->mCurve4->UpdateCtrls();
		}

		if (group->mCurve5)
		{
			group->mCurve5->UpdateCurve();
			group->mCurve5->UpdateCtrls();
		}
	}
}
//----------------------------------------------------------------------------
void CurveEdit::SetActiveCurve (Curve *curve)
{ 
	if (mActiveCurve == curve)
		return;

	mActiveCurve = curve;
}
//----------------------------------------------------------------------------
void CurveEdit::SetSelectedCurveCtrl (CurveCtrl *ctrl)
{ 
	if (mSelectedCurveCtrl == ctrl)
		return;

	if (mSelectedCurveCtrl)
	{
		mSelectedCurveCtrl->Select(false);
	}

	mSelectedCurveCtrl = ctrl;

	if (mSelectedCurveCtrl)
	{
		mSelectedCurveCtrl->Select(true);
	}
}
//----------------------------------------------------------------------------
void CurveEdit::SetSelectedUICurveGroup (PX2::UICurveGroup *group) 
{
	if (mSelectedCruveGroup)
	{
		mSelectedCruveGroup->SetBackColor(Float3(0.659f, 0.659f, 0.659f));
	}			

	mSelectedCruveGroup = group;

	if (mSelectedCruveGroup)
	{
		mSelectedCruveGroup->SetBackColor(Float3(0.5f, 0.0f, 0.25f));
	}
}
//----------------------------------------------------------------------------
CurveCtrl * CurveEdit::TrySelectCurve (PX2::Movable *mov)
{
	for (int i=0; i<(int)mCurves.size(); i++)
	{
		if (mCurves[i])
		{
			CurveCtrl * ctrl = mCurves[i]->TrySelectCurve(mov);
			if (ctrl)
			{
				return ctrl;
			}
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
void CurveEdit::AddGroup (CurveGroup *group)
{
	if (!group)
		return;

	mCurveGroups.push_back(group);
}
//----------------------------------------------------------------------------
int CurveEdit::GetNumGroups ()
{
	return (int)mCurveGroups.size();
}
//----------------------------------------------------------------------------
void CurveEdit::RemoveGroup (CurveGroup *group)
{
	std::vector<CurveGroupPtr>::iterator it = mCurveGroups.begin();
	for (; it!=mCurveGroups.end(); it++)
	{
		if (group == *it)
		{
			mCurveGroups.erase(it);
			return;
		}
	}
}
//----------------------------------------------------------------------------
PX2::Polysegment *CurveEdit::CreatePoly (PX2::InterpCurveFloat *curve, 
	Float3 color)
{
	if (!curve)
		return 0;

	VertexBufferPtr vbuffer = new0 VertexBuffer(mNumSamples,
		mVFormat->GetStride(), Buffer::BU_DYNAMIC);
	Polysegment *p = new0 Polysegment(mVFormat, vbuffer, true);

	UpdatePoly(curve, p, color);

	p->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	return p;
}
//----------------------------------------------------------------------------
void CurveEdit::UpdatePoly (PX2::InterpCurveFloat *curve, PX2::Polysegment *p,
	Float3 color)
{
	int keyNum = curve->GetNumPoints();
	if (0 == keyNum)
		return;

	float outValMin = curve->Eval(-mMaxRange, 0.0f);
	float outValMax = curve->Eval(mMaxRange, 0.0f);

	VertexFormat *vFormat = p->GetVertexFormat();
	VertexBuffer *vBuffer = p->GetVertexBuffer();
	VertexBufferAccessor vba(vFormat, vBuffer);

	int numPoints = 0;
	vba.Position<Float3>(numPoints) = Float3(-mMaxRange, 0.0f, outValMin);
	vba.Color<Float3>(0, numPoints) = color;
	numPoints++;

	for (int i=0; i<keyNum-1; i++)
	{
		const InterpCurvePoint<float> &point = curve->Points[i];
		const InterpCurvePoint<float> &pointP1 = curve->Points[i+1];

		if (ICM_CONSTANT == point.InterpMode)
		{
			vba.Position<Float3>(numPoints) = Float3(point.InVal, 0.0f, point.OutVal);
			vba.Color<Float3>(0, numPoints) = color;
			numPoints++;
			vba.Position<Float3>(numPoints) = Float3(pointP1.InVal, 0.0f, point.OutVal);
			vba.Color<Float3>(0, numPoints) = color;
			numPoints++;
		}
		else if (ICM_LINEAR == point.InterpMode)
		{
			vba.Position<Float3>(numPoints) = Float3(point.InVal, 0.0f, point.OutVal);
			vba.Color<Float3>(0, numPoints) = color;
			numPoints++;
			vba.Position<Float3>(numPoints) = Float3(pointP1.InVal, 0.0f, pointP1.OutVal);
			vba.Color<Float3>(0, numPoints) = color;
			numPoints++;
		}
		else
		{
			for (int k=0; k<21; k++)
			{
				float inVal = Lerp<float, float>(point.InVal, pointP1.InVal, (float)k/20.0f);
				float outVal = curve->Eval(inVal, 0.0f);

				vba.Position<Float3>(numPoints) = Float3(inVal, 0.0f, outVal);
				vba.Color<Float3>(0, numPoints) = color;
				numPoints++;
			}
		}
	}

	const InterpCurvePoint<float> &lastPoint = curve->Points[keyNum-1];	
	vba.Position<Float3>(numPoints) = Float3(lastPoint.InVal, 0.0f, lastPoint.OutVal);
	vba.Color<Float3>(0, numPoints) = color;
	numPoints++;

	vba.Position<Float3>(numPoints) = Float3(mMaxRange, 0.0f, outValMax);
	vba.Color<Float3>(0, numPoints) = color;
	numPoints++;

	p->SetNumSegments(numPoints-1);
	p->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);

	Renderer::UpdateAll(vBuffer);
}
//----------------------------------------------------------------------------
UICurveGroup *CurveEdit::GetUICurveGroupFormUIView (UIFrame *frame,
	CurveGroup *group)
{
	if (!frame)
		return 0;

	for (int i=0; frame->GetNumChildren(); i++)
	{
		UICurveGroup *uiGroup = DynamicCast<UICurveGroup>(frame->GetChild(i));
		if (uiGroup)
		{
			if (uiGroup->GetCurveGroup() == group)
			{
				return uiGroup;
			}
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
PX2::Polysegment *CurveEdit::CreatePoly(PX2::InterpCurveFloat3 *curve,
	int axis, Float3 color)
{
	if (!curve)
		return 0;

	// p0
	VertexBufferPtr vbuffer = new0 VertexBuffer(mNumSamples,
		mVFormat->GetStride(), Buffer::BU_DYNAMIC);
	Polysegment *poly = new0 Polysegment(mVFormat, vbuffer, true);
	poly->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	
	UpdatePoly(curve, poly, axis, color);

	return poly;
}
//----------------------------------------------------------------------------
void CurveEdit::UpdatePoly (PX2::InterpCurveFloat3 *curve, PX2::Polysegment *p,
	int axis, Float3 color)
{
	int keyNum = curve->GetNumPoints();
	if (0 == keyNum)
		return;

	float outValMin = curve->Eval(-mMaxRange, Float3::ZERO)[axis];
	float outValMax = curve->Eval(mMaxRange, Float3::ZERO)[axis];

	VertexFormat *vFormat = p->GetVertexFormat();
	VertexBuffer *vBuffer = p->GetVertexBuffer();
	VertexBufferAccessor vba(vFormat, vBuffer);

	int numPoints = 0;
	vba.Position<Float3>(numPoints) = Float3(-mMaxRange, 0.0f, outValMin);
	vba.Color<Float3>(0, numPoints) = color;
	numPoints++;

	for (int i=0; i<keyNum-1; i++)
	{
		const InterpCurvePoint<Float3> &point = curve->Points[i];
		const InterpCurvePoint<Float3> &pointP1 = curve->Points[i+1];

		if (ICM_CONSTANT == point.InterpMode)
		{
			vba.Position<Float3>(numPoints) = Float3(point.InVal, 0.0f, point.OutVal[axis]);
			vba.Color<Float3>(0, numPoints) = color;
			numPoints++;
			vba.Position<Float3>(numPoints) = Float3(pointP1.InVal, 0.0f, point.OutVal[axis]);
			vba.Color<Float3>(0, numPoints) = color;
			numPoints++;
		}
		else if (ICM_LINEAR == point.InterpMode)
		{
			vba.Position<Float3>(numPoints) = Float3(point.InVal, 0.0f, point.OutVal[axis]);
			vba.Color<Float3>(0, numPoints) = color;
			numPoints++;
			vba.Position<Float3>(numPoints) = Float3(pointP1.InVal, 0.0f, pointP1.OutVal[axis]);
			vba.Color<Float3>(0, numPoints) = color;
			numPoints++;
		}
		else
		{
			for (int k=0; k<21; k++)
			{
				float inVal = Lerp<float, float>(point.InVal, pointP1.InVal, (float)k/20.0f);
				float outVal = curve->Eval(inVal, Float3::ZERO)[axis];

				vba.Position<Float3>(numPoints) = Float3(inVal, 0.0f, outVal);
				vba.Color<Float3>(0, numPoints) = color;
				numPoints++;
			}
		}
	}

	const InterpCurvePoint<Float3> &lastPoint = curve->Points[keyNum-1];	
	vba.Position<Float3>(numPoints) = Float3(lastPoint.InVal, 0.0f, lastPoint.OutVal[axis]);
	vba.Color<Float3>(0, numPoints) = color;
	numPoints++;

	vba.Position<Float3>(numPoints) = Float3(mMaxRange, 0.0f, outValMax);
	vba.Color<Float3>(0, numPoints) = color;
	numPoints++;

	p->SetNumSegments(numPoints-1);
	p->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);

	Renderer::UpdateAll(vBuffer);
}
//----------------------------------------------------------------------------