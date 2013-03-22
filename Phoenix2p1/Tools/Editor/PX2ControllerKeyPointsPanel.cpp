/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ControllerKeyPoints.cpp
*
*/

#include "PX2ControllerKeyPointsPanel.hpp"
#include "PX2InterpCurveScaleCtrl.hpp"
#include "PX2InterpCurveRotateCtrl.hpp"
#include "PX2InterpCurveTranslateCtrl.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2EditEventType.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(ControllerKeyPointsPanel, wxPanel)
	EVT_LIST_ITEM_SELECTED(wxID_ANY, ControllerKeyPointsPanel::OnListCtrlItemSelected)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
ControllerKeyPointsPanel::ControllerKeyPointsPanel (wxWindow *parent)
:
mListCtrl(0)
{
	const bool bSuccess = wxXmlResource::Get()->LoadPanel(this, parent, 
		TEXT("KeyPoints"));

	mListCtrl = (wxListCtrl*)FindWindow(XRCID("mKeyPointsList"));
	assertion(mListCtrl!=0, "Window must be find!");

	wxListItem itemCol;
	itemCol.SetText(PX2_LM.GetValue("Index"));
	mListCtrl->InsertColumn(0, itemCol);
	mListCtrl->SetColumnWidth(0, 50);

	itemCol.SetText(PX2_LM.GetValue("Time(s)"));
	mListCtrl->InsertColumn(1, itemCol);
	mListCtrl->SetColumnWidth(1, 50);

	itemCol.SetText(PX2_LM.GetValue("Value"));
	mListCtrl->InsertColumn(2, itemCol);
	mListCtrl->SetColumnWidth(2, 150);
}
//-----------------------------------------------------------------------------
ControllerKeyPointsPanel::~ControllerKeyPointsPanel ()
{
}
//-----------------------------------------------------------------------------
void ControllerKeyPointsPanel::SetControl (PX2::Controller *ctrl)
{
	mControl = ctrl;

	RefreshControl();
}
//-----------------------------------------------------------------------------
void ControllerKeyPointsPanel::RefreshControl ()
{
	mListCtrl->DeleteAllItems();

	if (!mControl)
		return;

	InterpCurveScaleController *scaleCtrl = DynamicCast<
		InterpCurveScaleController>(mControl);
	InterpCurveRotateController *rotateCtrl = DynamicCast<
		InterpCurveRotateController>(mControl);
	InterpCurveTranslateController *transCtrl = DynamicCast<
		InterpCurveTranslateController>(mControl);

	if (scaleCtrl)
	{
		int numScales = scaleCtrl->mScales.GetNumPoints();
		for (int i=0; i<numScales; i++)
		{
			float inTime = scaleCtrl->mScales.Points[i].InVal;
			Float3 outValue = scaleCtrl->mScales.Points[i].OutVal;
			mListCtrl->InsertItem(i, wxString().Format("%d", i));
			mListCtrl->SetItem(i, 1, wxString().Format("%.2f", inTime));
			mListCtrl->SetItem(i, 2, wxString().Format("%.2f, %.2f, %.2f",
				outValue[0], outValue[1], outValue[2]));
		}
	}
	else if (rotateCtrl)
	{
		int numRotates = rotateCtrl->mRotates.GetNumPoints();
		for (int i=0; i<numRotates; i++)
		{
			float inTime = rotateCtrl->mRotates.Points[i].InVal;
			Float3 outValue = rotateCtrl->mRotates.Points[i].OutVal;
			mListCtrl->InsertItem(i, wxString().Format("%d", i));
			mListCtrl->SetItem(i, 1, wxString().Format("%.2f", inTime));
			mListCtrl->SetItem(i, 2, wxString().Format("%.2f, %.2f, %.2f",
				outValue[0], outValue[1], outValue[2]));
		}
	}
	else if (transCtrl)
	{
		int numTrans = transCtrl->mTranslates.GetNumPoints();
		for (int i=0; i<numTrans; i++)
		{
			float inTime = transCtrl->mTranslates.Points[i].InVal;
			Float3 outValue = transCtrl->mTranslates.Points[i].OutVal;
			mListCtrl->InsertItem(i, wxString().Format("%d", i));
			mListCtrl->SetItem(i, 1, wxString().Format("%.2f", inTime));
			mListCtrl->SetItem(i, 2, wxString().Format("%.2f, %.2f, %.2f",
				outValue[0], outValue[1], outValue[2]));
		}
	}
}
//-----------------------------------------------------------------------------
void ControllerKeyPointsPanel::OnListCtrlItemSelected(wxListEvent& event)
{
	int sel = event.m_itemIndex;

	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::SelectControlKeyPoint);
	ent->SetData<int>(sel);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//-----------------------------------------------------------------------------