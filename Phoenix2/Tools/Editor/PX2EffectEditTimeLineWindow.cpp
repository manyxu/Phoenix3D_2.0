/*
*
* 文件名称	：	PX2EffectEditTimeLineWindow.cpp
*
*/

#include "PX2EffectEditTimeLineWindow.hpp"
using namespace PX2Editor;
using namespace PX2;

#define ID_EFFECTNEW wxID_HIGHEST + 1000
#define ID_EFFECTOPEN wxID_HIGHEST + 1001

int EffectEditTimeLineWindow::sTimeLineHeight = 18;
int EffectEditTimeLineWindow::sTimeGridHeadWidth = 100;
int EffectEditTimeLineWindow::sTimeGridWidth = 8;
int EffectEditTimeLineWindow::sTimeGridHeight = 18;
int EffectEditTimeLineWindow::sTimeKeyWidth = 3;

IMPLEMENT_DYNAMIC_CLASS(PX2Editor::EffectEditTimeLineWindow, wxPanel)
BEGIN_EVENT_TABLE(EffectEditTimeLineWindow, wxScrolledWindow)
	EVT_PAINT(EffectEditTimeLineWindow::OnPaint)
	EVT_MOTION(EffectEditTimeLineWindow::OnMotion)
	EVT_LEFT_DOWN(EffectEditTimeLineWindow::OnLeftDown)
	EVT_LEFT_UP(EffectEditTimeLineWindow::OnLeftUp)
	EVT_LEFT_DCLICK(EffectEditTimeLineWindow::OnLeftDoubleClick)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
EffectEditTimeLineWindow::EffectEditTimeLineWindow ()
{

}
//----------------------------------------------------------------------------
EffectEditTimeLineWindow::EffectEditTimeLineWindow(wxWindow* parent)
:
wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
				 wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
	mWhiteBrush.SetColour(255, 255, 255);
	mBlackBrush.SetColour(0, 0, 0);
	mGrayBrush.SetColour(128, 128, 128);
	mLeftDown = false;
	mSelectIndex = -1;
	mSelectTimeKeyIndexX = -1;
	mSelectTimeKeyIndexY = -1;
	mIsDragingEvents = false;

	SetScrollbars(10, 10, 100, 240);
}
//----------------------------------------------------------------------------
EffectEditTimeLineWindow::~EffectEditTimeLineWindow()
{
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::OnPaint(wxPaintEvent &event)
{
	wxPaintDC paintDC(this);

	const wxSize size = GetClientSize();

	wxMemoryDC memDC;
	wxBitmap bmp(size.x, size.y);
	memDC.SelectObject(bmp);

	DoPaint(memDC);

	paintDC.Blit(0, 0, size.x, size.y, &memDC, 0, 0);
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::DoPaint (wxDC &dc)
{
	wxSize winSize = GetClientSize();

	dc.SetPen(*wxWHITE_PEN);
	dc.SetBrush(wxBrush(wxColor(255,255, 255), wxSOLID));
	dc.DrawRectangle(-1, -1, winSize.GetWidth()+1, winSize.GetHeight()+1);

	DrawTimeLine(dc);

	for (int i=0; i<(int)mEffectObjects.size(); i++)
	{
		PX2::Movable *obj = mEffectObjects[i];
		DrawOneTimeGridKeys(i, obj, dc);
		DrawOneTimeGrid(i, obj->GetName(), dc);
	}
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::DrawTimeLine (wxDC &dc)
{
	dc.SetPen(*wxBLACK_PEN);
	wxFont font("宋体");
	font.SetPointSize(7);
	dc.SetFont(font);

	wxSize winSize = GetClientSize();
	int timelineLength = winSize.GetWidth()*4;

	int girdNum = timelineLength /sTimeGridWidth;

	for (int i=0; i<girdNum; i++)
	{
		int xPos = i*sTimeGridWidth + sTimeGridHeadWidth;
		int yDst = 0;

		int time20 = i%10;
		if (time20 == 0)
			yDst = (int)(sTimeLineHeight*0.75f);
		else
			yDst = (int)(sTimeLineHeight*0.55f);

		dc.DrawLine(xPos, 0, xPos, yDst);

		if (i%30 == 0 && i!=0)
		{
			int number = i/30;
			dc.DrawText(wxString().Format("%d", number), xPos,
				(int)(sTimeLineHeight*0.55f));
		}
	}

	dc.SetPen(wxPen(wxColor(128, 128, 128)));
	dc.DrawLine(0, sTimeLineHeight, timelineLength, sTimeLineHeight);

	dc.SetPen(wxPen(wxColor(0,0, 0)));
	dc.DrawLine(0, 0, winSize.GetWidth()+1, 0);
	dc.DrawLine(0, 0, 0, winSize.GetHeight()+1);
	dc.DrawLine(sTimeGridHeadWidth, 0, sTimeGridHeadWidth, winSize.GetHeight()+1);
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::DrawOneTimeGrid (int index, std::string name, 
												wxDC &dc)
{
	wxSize winSize = GetClientSize();

	int xPos = 0;
	int yPos = index * sTimeGridHeight + sTimeLineHeight;
	//int yDst = (index+1) * sTimeGridHeight + sTimeLineHeight;
	int width = winSize.GetWidth()+2;

	if (mSelectIndex == index)
		dc.SetBrush(wxBrush(wxColor(0, 222, 0), wxSOLID));
	else
		dc.SetBrush(wxBrush(wxColor(222,222, 222), wxSOLID));
	dc.SetPen(wxPen(wxColor(222,222, 222)));
	dc.DrawRectangle(xPos+1, yPos+1, sTimeGridHeadWidth-1, sTimeGridHeight-1);
	dc.SetPen(wxPen(wxColor(128, 128, 128)));
	dc.DrawLine(xPos, yPos, width, yPos);
	dc.DrawLine(xPos, yPos+sTimeGridHeight, width, yPos+sTimeGridHeight);

	dc.SetFont(wxFont("宋体"));
	dc.DrawText(name.c_str(), xPos+10, yPos+2);

	// grid
	int girdNum = winSize.GetWidth()/sTimeGridWidth;

	for (int i=0; i<girdNum; i++)
	{
		int xPos = i*sTimeGridWidth + sTimeGridHeadWidth;

		if (i !=0 )
		{
			dc.SetPen(wxPen(wxColor(128, 128, 128)));
			dc.DrawLine(xPos, sTimeLineHeight+sTimeGridHeight*index, 
			xPos, sTimeLineHeight+sTimeGridHeight*(index+1));
		}

		if (index == mSelectIndex)
		{
			float insertingTime = EditSystem::GetSingleton().GetEffectEdit()
				->GetInsertingTime();
			float insertingIndex = insertingTime * 30.0f;
			int iInsertingIndex = (int)insertingIndex;
			float timeTemp = insertingIndex - iInsertingIndex;
			if (timeTemp > 0.99f)
				iInsertingIndex += 1;

			xPos = iInsertingIndex*sTimeGridWidth + sTimeGridHeadWidth;

			dc.SetBrush(wxBrush(wxColor(128, 0, 0), wxSOLID));
			dc.SetPen(wxPen(wxColor(128, 0, 0)));
			dc.DrawRectangle(xPos+1, sTimeLineHeight+sTimeGridHeight*index+1,
				sTimeGridWidth, sTimeGridHeight-1);
		}
	}
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::DrawOneTimeGridKeys (int index, 
													PX2::Movable *obj, wxDC &dc)
{
	PX2::ParticleEmitter *emitter = DynamicCast<PX2::ParticleEmitter>(obj);

	if (emitter)
	{
		int numEvents = emitter->GetParticleEmitterControl()->GetNumEvents();
		for (int i=0; i<numEvents; i++)
		{
			EffectEvent *event = emitter->GetParticleEmitterControl()
				->GetEffectEvent(i);
			float activeTime = event->GetActivateTime();

			float timeIndex = activeTime * 30.0f;
			int iTimeIndex = (int)timeIndex;
			float timeTemp = timeIndex - iTimeIndex;
			if (timeTemp > 0.99f)
				iTimeIndex += 1;

			int xPos = iTimeIndex*sTimeGridWidth + sTimeGridHeadWidth;
			
			dc.SetBrush(wxBrush(wxColor(0, 128, 0), wxSOLID));
			dc.SetPen(wxPen(wxColor(0, 128, 0)));
			dc.DrawRectangle(xPos+1, sTimeLineHeight+sTimeGridHeight*index+1,
				sTimeGridWidth, sTimeGridHeight-1);
		}
	}
}
//----------------------------------------------------------------------------
int EffectEditTimeLineWindow::GetSelectIndex (int y)
{
	y -= sTimeLineHeight;

	return (int)((float)y/(float)sTimeGridHeight);
}
//----------------------------------------------------------------------------
int EffectEditTimeLineWindow::GetSelectTimeKeyIndex (int x)
{
	if (mSelectIndex == -1)
		return -1;

	x -= sTimeGridHeadWidth;

	if (x < 0)
		return -1;

	return (int)((float)x/(float)sTimeGridWidth);
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::CalculateDragingEvents (int selectIndexX, 
													   PX2::Movable *obj)
{
	mDragingEvents.clear();

	PX2::ParticleEmitter *emitter = DynamicCast<ParticleEmitter>(obj);
	if (emitter)
	{
		int numEvents = emitter->GetParticleEmitterControl()->GetNumEvents();
		for (int i=0; i<numEvents; i++)
		{
			EffectEvent *event = emitter->GetParticleEmitterControl()
				->GetEffectEvent(i);
			float activeTime = event->GetActivateTime();
			float timeIndex = activeTime * 30.0f; 
			int iTimeIndex = (int)timeIndex;
			float timeTemp = timeIndex - iTimeIndex;
			if (timeTemp > 0.99f)
				iTimeIndex += 1;

			if (iTimeIndex == selectIndexX)
			{
				mDragingEvents.push_back(event);
				mIsDragingEvents = true;
			}
		}
	}
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::OnSelectEffect (PX2::Movable *obj)
{
	EditSystem::GetSingleton().GetEffectEdit()->SetEditEffect(obj);

	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_EFFECT);

	Event *ent = EditorEventSpace::CreateEvent(EditorEventSpace::SelectEffect);
	ent->SetData<PX2::Movable*>(obj);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::OnSelectEffectEvent (PX2::EffectEvent *event)
{

}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::OnMotion (wxMouseEvent& e)
{
	if (mLeftDown)
	{
		mIsDragingEvents = true;

		int xPos = e.GetPosition().x;

		int keyIndex = GetSelectTimeKeyIndex(xPos);

		if (keyIndex == -1)
			return;

		float keyTime = (float)keyIndex/30.0f;
		for (int i=0; i<(int)mDragingEvents.size(); i++)
		{
			mDragingEvents[i]->SetTimeRange(TRange<float>(keyTime, keyTime));
		}

		PX2::Movable *obj = GetSelectEffectObject();
		PX2::ParticleEmitter *emitter = DynamicCast<PX2::ParticleEmitter>(obj);
		if (emitter)
		{
			emitter->GetParticleEmitterControl()->ConfigeAllEvents();

			//Event *ent = EditorEventSpace::CreateEvent(
			//	EditorEventSpace::UpdateEffect);
			//ent->SetData<PX2::Movable*>(emitter);
			//EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
		}

		Refresh();
	}
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::OnLeftDown(wxMouseEvent& e)
{
	mLeftDown = true;

	int xPos = e.GetPosition().x;
	int yPos = e.GetPosition().y;

	int selectIndex = GetSelectIndex(yPos);
	if (selectIndex != mSelectIndex)
	{
		mSelectIndex = selectIndex;

		if (mSelectIndex>=0 && mSelectIndex<(int)mEffectObjects.size())
		{
			OnSelectEffect(mEffectObjects[mSelectIndex]);
		}
		
		Refresh();
	}

	// draging
	if (mSelectIndex>=0 && mSelectIndex<(int)mEffectObjects.size())
	{
		int selectTimeKeyIndexX = GetSelectTimeKeyIndex(xPos);

		if (selectTimeKeyIndexX != -1)
		{
			CalculateDragingEvents(selectTimeKeyIndexX,
				mEffectObjects[mSelectIndex]);
		}
	}
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::OnLeftUp(wxMouseEvent& e)
{
	mLeftDown = false;
	mDragingEvents.clear();
	mIsDragingEvents = false;
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::OnLeftDoubleClick(wxMouseEvent& e)
{
	int xPos = e.GetPosition().x;
	int yPos = e.GetPosition().y;

	int selectTimeKeyIndexX = GetSelectTimeKeyIndex(xPos);
	int selectTimeKeyIndexY = GetSelectIndex(yPos);
	if (selectTimeKeyIndexX != mSelectTimeKeyIndexX ||
		selectTimeKeyIndexY != mSelectTimeKeyIndexY
		&& selectTimeKeyIndexX != -1)
	{
		mSelectTimeKeyIndexX = selectTimeKeyIndexX;
		mSelectTimeKeyIndexY = selectTimeKeyIndexY;
		float insertingTime = (float)mSelectTimeKeyIndexX/30.0f;
		EditSystem::GetSingleton().GetEffectEdit()->SetInsertingTime(
			insertingTime);

		Refresh();
	}
	else if (selectTimeKeyIndexX == mSelectTimeKeyIndexX 
		&& selectTimeKeyIndexY == mSelectTimeKeyIndexY)
	{
		mSelectTimeKeyIndexX = -1;
		mSelectTimeKeyIndexY = -1;
		EditSystem::GetSingleton().GetEffectEdit()->SetInsertingTime(-1.0f);

		Refresh();
	}
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::ResetSelectIndex ()
{
	mLeftDown = false;
	mSelectIndex = -1;
	mSelectTimeKeyIndexX = -1;
	mSelectTimeKeyIndexY = -1;
	mIsDragingEvents = false;
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::SelectEffectNode (PX2::EffectNode *node)
{
	ClearEffectObjects();

	for (int i=0; i<node->GetNumChildren(); i++)
	{
		PX2::Movable *object = node->GetChild(i);

		if (object)
			AddEffectObject(object);
	}
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::AddEffectObject (PX2::Movable *obj)
{
	mEffectObjects.push_back(obj);
	Refresh();
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::RemoveEffectObject (PX2::Movable *obj)
{
	std::vector<PX2::MovablePtr>::iterator it = mEffectObjects.begin();

	for (; it!=mEffectObjects.end(); it++)
	{
		if ((*it) == obj)
		{
			mEffectObjects.erase(it);
			mSelectIndex = -1;
			Refresh();

			return;
		}
	}
}
//----------------------------------------------------------------------------
Movable *EffectEditTimeLineWindow::GetSelectEffectObject ()
{
	if (mSelectIndex>=0 && mSelectIndex<(int)mEffectObjects.size())
		return mEffectObjects[mSelectIndex];

	return 0;
}
//----------------------------------------------------------------------------
void EffectEditTimeLineWindow::ClearEffectObjects ()
{
	mEffectObjects.clear();
	Refresh();
}
//----------------------------------------------------------------------------