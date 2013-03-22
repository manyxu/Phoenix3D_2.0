/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ControllerKeyPointsValuePropertyGrid.cpp
*
*/

#include "PX2ControllerKeyPointsValuePropertyGrid.hpp"
#include "PX2EditEventType.hpp"
#include "PX2LanguageManager.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(ControllerKeyPointsValuePropertyGrid, ObjectPropertyGrid)
	BEGIN_EVENT_TABLE(ControllerKeyPointsValuePropertyGrid, ObjectPropertyGrid)
	EVT_PG_CHANGED(PGT_CONTROLKEYPOINTSVALUE, ControllerKeyPointsValuePropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
ControllerKeyPointsValuePropertyGrid::ControllerKeyPointsValuePropertyGrid (
wxWindow *parent)
:
ObjectPropertyGrid (parent),
mIndex(-1)
{
}
//-----------------------------------------------------------------------------
ControllerKeyPointsValuePropertyGrid::~ControllerKeyPointsValuePropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void ControllerKeyPointsValuePropertyGrid::SetIndex (int index)
{
	mIndex = index;

	Clear();

	if (mIndex < 0)
		return;

	AddPropertyPage("General");
	PropertyPage *page = GetPropertyPage("General");
	page->AddProperty(PX2_LM.GetValue("General"), Property::PT_CATEGORY, 0);

	InterpCurveScaleController *scaleCtrl = DynamicCast<
		InterpCurveScaleController>(mObject);
	InterpCurveRotateController *rotateCtrl = DynamicCast<
		InterpCurveRotateController>(mObject);
	InterpCurveTranslateController *transCtrl = DynamicCast<
		InterpCurveTranslateController>(mObject);

	if (scaleCtrl)
	{
		mType = "Scale";
		page->AddProperty(PX2_LM.GetValue("Type"), Property::PT_STRING, &mType, false);
		mTime = scaleCtrl->mScales.Points[mIndex].InVal;
		mValue = scaleCtrl->mScales.Points[mIndex].OutVal;
		page->AddProperty(PX2_LM.GetValue("Index"), Property::PT_INT, &mIndex, false);
		page->AddProperty(PX2_LM.GetValue("Time(s)"), Property::PT_FLOAT, &mTime);
		page->AddProperty("[0]", Property::PT_FLOAT, &mValue[0]);
		page->AddProperty("[1]", Property::PT_FLOAT, &mValue[1]);
		page->AddProperty("[2]", Property::PT_FLOAT, &mValue[2]);
	}
	else if (rotateCtrl)
	{
		mType = "Rotate";
		page->AddProperty(PX2_LM.GetValue("Type"), Property::PT_STRING, &mType, false);
		mTime = rotateCtrl->mRotates.Points[mIndex].InVal;
		mValue = rotateCtrl->mRotates.Points[mIndex].OutVal;
		page->AddProperty(PX2_LM.GetValue("Index"), Property::PT_INT, &mIndex, false);
		page->AddProperty(PX2_LM.GetValue("Time(s)"), Property::PT_FLOAT, &mTime);
		page->AddProperty("[0]", Property::PT_FLOAT, &mValue[0]);
		page->AddProperty("[1]", Property::PT_FLOAT, &mValue[1]);
		page->AddProperty("[2]", Property::PT_FLOAT, &mValue[2]);
	}
	else if (transCtrl)
	{
		mType = "Translate";
		page->AddProperty(PX2_LM.GetValue("Type"), Property::PT_STRING, &mType, false);
		mTime = transCtrl->mTranslates.Points[mIndex].InVal;
		mValue = transCtrl->mTranslates.Points[mIndex].OutVal;
		page->AddProperty(PX2_LM.GetValue("Index"), Property::PT_INT, &mIndex, false);
		page->AddProperty(PX2_LM.GetValue("Time(s)"), Property::PT_FLOAT, &mTime);
		page->AddProperty("[0]", Property::PT_FLOAT, &mValue[0]);
		page->AddProperty("[1]", Property::PT_FLOAT, &mValue[1]);
		page->AddProperty("[2]", Property::PT_FLOAT, &mValue[2]);
	}
}
//-----------------------------------------------------------------------------
void ControllerKeyPointsValuePropertyGrid::OnSetObject(PX2::Object *object)
{
	Clear();
}
//-----------------------------------------------------------------------------
void ControllerKeyPointsValuePropertyGrid::OnPropertyGridChange (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);
}
//-----------------------------------------------------------------------------
void ControllerKeyPointsValuePropertyGrid::OnPropertyGridChanging (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void ControllerKeyPointsValuePropertyGrid::OnPropertyGridSelect (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void ControllerKeyPointsValuePropertyGrid::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void ControllerKeyPointsValuePropertyGrid::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::SelectControlKeyPoint))
	{
		int sel = event->GetData<int>();
		SetIndex(sel);
	}
}
//-----------------------------------------------------------------------------
void ControllerKeyPointsValuePropertyGrid::DoLeave ()
{

}
//-----------------------------------------------------------------------------
ControllerKeyPointsValuePropertyGrid::ControllerKeyPointsValuePropertyGrid ()
{

}
//-----------------------------------------------------------------------------