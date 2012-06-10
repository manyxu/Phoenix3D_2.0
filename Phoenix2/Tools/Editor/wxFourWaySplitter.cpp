/*
-----------------------------------------------------------------------------
Filename:			wxFourWaySplitter.cpp
Purpose:			4-panel cross-splitter window as required by CAD programs
Copyright:			(c) 2007 Steve Streeting, Torus Knot Software Ltd
License:			Released under the wxWindows license
Acknowledgements:	Based heavily on wxPython FourWaySplitter.py by Andrea Gavana
-----------------------------------------------------------------------------
*/
#include "wxFourWaySplitter.h"

#include "wx/renderer.h"
#include "wx/toplevel.h"
#include "wx/dcscreen.h"


DEFINE_EVENT_TYPE(EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGED)
DEFINE_EVENT_TYPE(EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGING)

#define TOLERANCE 5

#define FLAG_CHANGED 1
#define FLAG_PRESSED 2

IMPLEMENT_DYNAMIC_CLASS(wxFourWaySplitter, wxWindow)
IMPLEMENT_DYNAMIC_CLASS(wxFourWaySplitterEvent, wxNotifyEvent)

//----------------------------------------------------------------------------
wxFourWaySplitter::wxFourWaySplitter()
:wxWindow()
, mSashCursorWE(wxCursor(wxCURSOR_SIZEWE))
, mSashCursorNS(wxCursor(wxCURSOR_SIZENS))
, mSashCursorSize(wxCursor(wxCURSOR_SIZING))
, mSashTrackerPen(new wxPen(*wxBLACK, 2, wxSOLID))
, mIsHot(false)
, mExpanded(-1)
, mFracSize(5000, 5000)
, mFlags(0)
, mMode(0)
, mActiveIndex(-1)
{
	// Init window pointers to null
	memset(mWindows, 0, sizeof(wxWindow*) * 4);

	SizeWindows();


}
//----------------------------------------------------------------------------
wxFourWaySplitter::wxFourWaySplitter(wxWindow *parent, wxWindowID id, 
									 const wxPoint &pos, const wxSize &size, long style, const wxString &name)
									 : wxWindow(parent, id, pos, size, style, name)
									 , mSashCursorWE(wxCursor(wxCURSOR_SIZEWE))
									 , mSashCursorNS(wxCursor(wxCURSOR_SIZENS))
									 , mSashCursorSize(wxCursor(wxCURSOR_SIZING))
									 , mSashTrackerPen(new wxPen(*wxBLACK, 2, wxSOLID))
									 , mIsHot(false)
									 , mExpanded(-1)
									 , mFracSize(5000, 5000)
									 , mFlags(0)
									 , mMode(0)
									 , mActiveIndex(-1)
{
	// Init window pointers to null
	memset(mWindows, 0, sizeof(wxWindow*) * 4);

	SizeWindows();


}
//----------------------------------------------------------------------------
wxFourWaySplitter::~wxFourWaySplitter()
{
	delete mSashTrackerPen;

}
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(wxFourWaySplitter, wxWindow)
EVT_PAINT(wxFourWaySplitter::OnPaint)
EVT_MOTION(wxFourWaySplitter::OnMotion)
EVT_SIZE(wxFourWaySplitter::OnSize)
EVT_LEFT_DOWN(wxFourWaySplitter::OnLeftDown)
EVT_LEFT_UP(wxFourWaySplitter::OnLeftUp)
EVT_LEAVE_WINDOW(wxFourWaySplitter::OnLeaveWindow)
EVT_ENTER_WINDOW(wxFourWaySplitter::OnEnterWindow)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
wxWindow* wxFourWaySplitter::GetWindow(int i) const
{
	if (i < 4)
		return mWindows[i];
	else
		return NULL;
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::SetWindow(int i, wxWindow* wnd)
{
	if (i < 4)
	{
		mWindows[i] = wnd;
	}
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::ReplaceWindow(wxWindow* oldWin, wxWindow* newWin)
{
	for (int i = 0; i < 4; ++i)
	{
		if (mWindows[i] == oldWin)
		{
			mWindows[i] = newWin;
			break;
		}
	}

	// refresh?

}
//----------------------------------------------------------------------------
void wxFourWaySplitter::ExchangeWindows(wxWindow* one, wxWindow* two)
{
	int oneIdx = -1;
	int twoIdx = -1;

	for (int i = 0; i < 4; ++i)
	{
		if (mWindows[i] == one)
		{
			oneIdx = i;
		}
		else if (mWindows[i] == two)
		{
			twoIdx = i;
		}
	}

	if (oneIdx != -1 && twoIdx != -1)
	{
		wxWindow* tmp = mWindows[oneIdx];
		mWindows[oneIdx] = mWindows[twoIdx];
		mWindows[twoIdx] = tmp;
	}

	// refresh?

}
//----------------------------------------------------------------------------
void wxFourWaySplitter::SetExpanded(int expanded)
{
	if (expanded != mExpanded && expanded >= -1 && expanded < 4)
	{
		mExpanded = expanded;
		SizeWindows();
	}

}
//----------------------------------------------------------------------------
void wxFourWaySplitter::SetExpanded(wxWindow* expanded)
{
	if (!expanded)
		SetExpanded(-1);
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			if (mWindows[i] == expanded)
			{
				SetExpanded(i);
				break;
			}
		}
	}
}
//----------------------------------------------------------------------------
int wxFourWaySplitter::GetExpanded() const
{
	return mExpanded;
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::SetActiveWindow (wxWindow* expanded)
{
	for (int i = 0; i < 4; ++i)
	{
		if (mWindows[i] == expanded)
		{
			mActiveIndex = i;
		}
	}

	wxClientDC tempDC(this);
	DrawActiveWindow(tempDC);
}
//----------------------------------------------------------------------------
int wxFourWaySplitter::GetActiveWidnow ()
{
	return mActiveIndex;
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::SetSplit(const wxSize& inSplit)
{
	// Sanitise
	wxSize split(inSplit);

	if (split.x < 0) split.x = 0;	
	if (split.x > 10000) split.x = 10000;
	if (split.y < 0) split.y = 0;	
	if (split.y > 10000) split.y = 10000;

	mFracSize = split;		

}
//----------------------------------------------------------------------------
const wxSize& wxFourWaySplitter::GetSplit() const
{
	return mFracSize;
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::SetHSplit(int frac)
{
	SetSplit(wxSize(frac, mFracSize.y));
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::SetVSplit(int frac)
{
	SetSplit(wxSize(mFracSize.x, frac));
}
//----------------------------------------------------------------------------
int wxFourWaySplitter::GetHSplit() const
{
	return mFracSize.x;
}
//----------------------------------------------------------------------------
int wxFourWaySplitter::GetVSplit() const
{
	return mFracSize.y;
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::OnPaint(wxPaintEvent& e)
{
	wxPaintDC dc(this);

	//if (!mOnlyDrawActive)
	/*	DrawSplitter(dc);*/

	DrawActiveWindow(dc);

	//mOnlyDrawActive = false;
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::RedrawIfHotSensitive(bool isHot)
{
	if (wxRendererNative::Get().GetSplitterParams(this).isHotSensitive)
	{
		mIsHot = isHot;
		wxClientDC dc(this);
		DrawSplitter(dc);
	}

}
//----------------------------------------------------------------------------
void wxFourWaySplitter::DrawSplitter(wxClientDC& dc)
{
	wxColour backColour = this->GetBackgroundColour();

	dc.SetBrush(wxBrush(backColour, wxSOLID));
	dc.SetPen(wxPen(backColour));
	dc.Clear();

	if (this->HasFlag(wxSP_3DBORDER))
	{
		wxRendererNative::Get().DrawSplitterBorder(this, dc, this->GetClientRect());
	}

	// if we are not supposed to use a sash then we're done.
	if (HasFlag(wxSP_NOSASH))
		return;

	int flag = 0;
	if (mIsHot)
		flag |= wxCONTROL_CURRENT;

	wxSize sz = this->GetSize();

	wxRendererNative::Get().DrawSplitterSash(this, dc,
		this->GetClientSize(),
		mSplit.x, wxVERTICAL, flag);

	wxRendererNative::Get().DrawSplitterSash(this, dc,
		this->GetClientSize(),
		mSplit.y, wxHORIZONTAL, flag);
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::OnMotion(wxMouseEvent& e)
{

	if (HasFlag(wxSP_NOSASH))
		return;

	wxPoint pt = e.GetPosition();

	// Moving split
	if (mFlags & FLAG_PRESSED)
	{
		wxPoint oldSplit = mSplit;

		if (mMode == wxBOTH)
		{
			MoveSplit(pt.x - mOffset.x, pt.y - mOffset.y);
		}
		else if(mMode == wxVERTICAL)
		{
			MoveSplit(pt.x - mOffset.x, mSplit.y);
		}
		else if (mMode == wxHORIZONTAL)
		{
			MoveSplit(mSplit.x, pt.y - mOffset.y);
		}



		// Send a changing event
		if (!DoSendChangingEvent(mSplit))
		{
			mSplit = oldSplit;
			return;   

		}

		if (oldSplit.x != mSplit.x || oldSplit.y != mSplit.y)
		{
			if ((GetWindowStyle() & wxSP_LIVE_UPDATE) == 0)
			{
				DrawTrackSplitter(oldSplit);
				DrawTrackSplitter(mSplit);
			}
			else
			{
				AdjustLayout();
			}

			mFlags |= FLAG_CHANGED;
		}


	}

	UpdateMode(pt);

	// Change cursor based on position
	if (mMode == wxBOTH)
		SetCursor(mSashCursorSize);
	else if (mMode == wxVERTICAL)
		SetCursor(mSashCursorWE);
	else if (mMode == wxHORIZONTAL)
		SetCursor(mSashCursorNS);
	else
		SetCursor(*wxSTANDARD_CURSOR);

	e.Skip();
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::UpdateMode(const wxPoint& pt)
{

	int barSize = GetSashSize();

	mMode = wxBOTH;

	if ((pt.x < mSplit.x - TOLERANCE) ||
		(pt.x >= mSplit.x + barSize + TOLERANCE))
		mMode &= ~wxVERTICAL;

	if ((pt.y < mSplit.y - TOLERANCE) ||
		(pt.y >= mSplit.y + barSize + TOLERANCE))
		mMode &= ~wxHORIZONTAL;

}
//----------------------------------------------------------------------------
void wxFourWaySplitter::DrawActiveWindow (wxClientDC &dc)
{
	wxColour yellow(255, 255, 0);
	wxColour darkBlue(54, 63, 75);

	for (int i=0; i<4; i++)
	{
		wxPoint pos = mWindows[i]->GetPosition();
		pos.x -= 1;
		pos.y -= 1;
 		wxSize size = mWindows[i]->GetSize();
		size += wxSize(2, 2);

		dc.SetLogicalFunction(wxCOPY);
		if (mActiveIndex == i)
			dc.SetPen(wxPen(yellow, 1, wxSOLID));
		else
			dc.SetPen(wxPen(darkBlue, 1, wxSOLID));
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.DrawRectangle(pos, size);

		//wxPoint pos1 = pos;
		//pos1 += wxPoint(1,1);
		//wxSize size1 = size;
		//size1 -= wxSize(2, 2);
		//dc.DrawRectangle(pos1, size1);
	}
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::MoveSplit(int x, int y)
{
	// Moves the split accordingly to user action.

	wxSize sz = GetSize();
	int barSize = GetSashSize();

	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x > (sz.x - barSize)) x = sz.x - barSize;
	if (y > (sz.y - barSize)) y = sz.y - barSize;

	mSplit.x = x;
	mSplit.y = y;
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::AdjustLayout()
{
	// Adjust layout of FourWaySplitter. Mainly used to recalculate the
	// correct values for split fractions.

	wxSize sz = GetSize();
	int barSize = GetSashSize();
	int border = GetBorderSize();

	mFracSize.x = sz.x > barSize ? 
		(10000 * mSplit.x + (sz.x - barSize - 1)) / (sz.x - barSize) : 0;

	mFracSize.y = sz.y > barSize ?
		(10000 * mSplit.y + (sz.y - barSize - 1)) / (sz.y - barSize) : 0;

	SizeWindows();
}
//----------------------------------------------------------------------------
bool wxFourWaySplitter::DoSendChangingEvent(const wxPoint& pt)
{
	// Sends a EVT_FOURWAYSPLITTER_SASH_POINT_CHANGING event.

	// send the event
	wxFourWaySplitterEvent e(EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGING, this);
	e.SetSashIdx(mMode);
	e.SetSashPosition(pt);

	GetEventHandler()->ProcessEvent(e);

	// Might want to put a veto in here, ignore for now 
	return true;

}
//----------------------------------------------------------------------------
void wxFourWaySplitter::DrawTrackSplitter(const wxPoint& pt)
{
	// Draws a fake sash in case we don't have wx.SP_LIVE_UPDATE style. 

	// Draw a line to represent the dragging sash, for when not
	// doing live updates            
	wxSize sz = GetClientSize();
	wxScreenDC dc;

	dc.SetLogicalFunction(wxINVERT);
	dc.SetPen(*mSashTrackerPen);
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	if (mMode == wxVERTICAL || mMode == wxBOTH)
	{
		wxPoint newPt1(pt.x, 2);
		wxPoint newPt2(pt.x, sz.y-2);

		if (newPt1.x > sz.x)
			newPt1.x = newPt2.x = sz.x;
		else if (newPt1.x < 0)
			newPt1.x = newPt2.x = 0;

		newPt1 = ClientToScreen(newPt1);
		newPt2 = ClientToScreen(newPt2);

		dc.DrawLine(newPt1, newPt2);
	}

	if(mMode == wxHORIZONTAL || mMode == wxBOTH)
	{
		wxPoint newPt1(2, pt.y);
		wxPoint newPt2(sz.x-2, pt.y);

		if (newPt1.y > sz.y)
			newPt1.y = newPt2.y = sz.y;
		else if (newPt1.y < 0)
			newPt1.y = newPt2.y = 0;

		newPt1 = ClientToScreen(newPt1);
		newPt2 = ClientToScreen(newPt2);

		dc.DrawLine(newPt1, newPt2);
	}
	dc.SetLogicalFunction(wxCOPY);


}
//----------------------------------------------------------------------------
void wxFourWaySplitter::OnSize(wxSizeEvent& e)
{

	wxTopLevelWindow* parent = static_cast<wxTopLevelWindow*>(
		wxGetTopLevelParent(this));
	if (parent->IsIconized())
	{
		e.Skip();
		return;
	}

	SizeWindows();

	// Make sure we clear the entire region
	Refresh();

}
//----------------------------------------------------------------------------
int wxFourWaySplitter::GetSashSize() const
{
	if (this->HasFlag(wxSP_NOSASH))
		return 0;
	else
		return wxRendererNative::Get().GetSplitterParams(this).widthSash;

}
//----------------------------------------------------------------------------
int wxFourWaySplitter::GetBorderSize() const
{
	return wxRendererNative::Get().GetSplitterParams(this).border;
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::SizeWindows()
{
	wxSize sz = GetSize();
	//int border = GetBorderSize();
	//int sashSize = GetSashSize();
	int border = 1;
	//int barSize = GetSashSize() + 2 * border;
	int barSize = 1;
	int space = 1;

	if (mExpanded == -1)
	{
		// All 4 regions are shown
		int totw = sz.x - barSize;
		int toth = sz.y - barSize;
		mSplit.x = (mFracSize.x*totw)/10000;
		mSplit.y = (mFracSize.y*toth)/10000;
		int rightw = totw - mSplit.x;
		int bottomh = toth - mSplit.y;
		if (mWindows[0])
		{
			mWindows[0]->SetSize(space, space, mSplit.x-2*space, mSplit.y-2*space);
			mWindows[0]->Show();
		}
		if (mWindows[1])
		{
			mWindows[1]->SetSize(mSplit.x + barSize+space, 0+space,
				rightw-2*space, mSplit.y-2*space);
			mWindows[1]->Show();
		}
		if (mWindows[2])
		{
			mWindows[2]->SetSize(space, mSplit.y + barSize+space, 
				mSplit.x-2*space, bottomh-2*space);
			mWindows[2]->Show();
		}
		if (mWindows[3])
		{
			mWindows[3]->SetSize(mSplit.x + barSize+space, mSplit.y + barSize+space,
				rightw-2*space, bottomh-2*space);
			mWindows[3]->Show();
		}

	}
	else
	{
		// a window is expanded to full size
		for (int i = 0; i < 4; ++i)
		{
			wxWindow* win = mWindows[i];

			if (win)
			{
				if (i == mExpanded)
				{
					win->SetSize(0, 0, 
						sz.x - (2 * border), sz.y - (2 * border));
					win->Show();
				}
				else
				{
					win->Hide();
				}

			}

		}
	}
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::OnLeftDown(wxMouseEvent& e)
{
	// Handles the wx.EVT_LEFT_DOWN event for FourWaySplitter.

	if (!IsEnabled())
		return;

	wxPoint pt = e.GetPosition();

	CaptureMouse();
	UpdateMode(pt);

	if (mMode)
	{
		mOffset = pt - mSplit;

		if ((GetWindowStyle() & wxSP_LIVE_UPDATE) == 0)
		{
			wxClientDC tempDC(this);
		//	DrawSplitter(tempDC);
			DrawTrackSplitter(mSplit);
		}
		mFlags |= FLAG_PRESSED;
	}
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::OnLeftUp(wxMouseEvent& e)
{
	// Handles the wx.EVT_LEFT_UP event for FourWaySplitter. 
	if (!IsEnabled())
		return;

	if (HasCapture())
		ReleaseMouse();

	int oldFlags = mFlags;

	mFlags &= ~FLAG_CHANGED;
	mFlags &= ~FLAG_PRESSED;

	if (oldFlags & FLAG_PRESSED)
	{
		if ((GetWindowStyle() & wxSP_LIVE_UPDATE) == 0)
		{
			DrawTrackSplitter(mSplit);
			wxClientDC tempDC(this);
		//	DrawSplitter(tempDC);
			AdjustLayout();
		}

		if (oldFlags & FLAG_CHANGED)
		{
			wxFourWaySplitterEvent e(EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGED, this);
			e.SetSashIdx(mMode);
			e.SetSashPosition(mSplit);
			GetEventHandler()->ProcessEvent(e);
		}
	}

	mMode = 0;

	Refresh();
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::OnEnterWindow(wxMouseEvent& e)
{
	RedrawIfHotSensitive(true);
}
//----------------------------------------------------------------------------
void wxFourWaySplitter::OnLeaveWindow(wxMouseEvent& e)
{
	SetCursor(*wxSTANDARD_CURSOR);
	RedrawIfHotSensitive(false);
}
//----------------------------------------------------------------------------

