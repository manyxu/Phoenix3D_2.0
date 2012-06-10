/*
-----------------------------------------------------------------------------
Filename:			wxFourWaySplitter.h
Purpose:			4-panel cross-splitter window as required by CAD programs
Copyright:			(c) 2007 Steve Streeting, Torus Knot Software Ltd
License:			Released under the wxWindows license
Acknowledgements:	Based heavily on wxPython four way splitter by Andrea Gavana
-----------------------------------------------------------------------------
*/
#ifndef _WX_FOURWAYSPLITTER_H
#define _WX_FOURWAYSPLITTER_H

#include "wx/event.h"
#include "wx/window.h"     
#include "wx/dcclient.h"
#include "wx/containr.h"                   
// for common constants
#include "wx/splitter.h"

/** Implementation of a 4-way window splitter.
@remarks
This class performs the same kind of task as wxSplitterWindow, except that
instead of splitting into two, it splits into four panes, in a traditional
CAD-style view. Whilst you can split 4 ways using 3 wxSplitterWindow instances,
you cannot get the same look, the same ability to drag the center of the 
sashes to resize horizontally and vertically at once, and other such expected
behaviour. This class addresses that.
@par
You can also maximise one of the windows so that it takes up the entire
area, and return to the 4-way split afterwards; again this is typical in 
CAD-style applications. This class does not support the 'unsplit' option 
like wxSplitterWindow, in favour of this option.
@par
Unlike wxSplitterWindow, this class maintains proportionality of the child
panes when resized. You can set the proportions manually or they will be set
when the sashes are dragged around.
*/
class wxFourWaySplitter :  public wxWindow
{
public:
	DECLARE_DYNAMIC_CLASS(wxFourWaySplitter)

	/// Default constructor
	wxFourWaySplitter();

	/// Usual constructor - same meaning as wxSplitterWindow
	wxFourWaySplitter(wxWindow *parent, wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxSP_3D,
		const wxString& name = wxT("splitter"));
	~wxFourWaySplitter();


	/** Get one of the child windows at pane index i.
	@remarks
	The windows are indexed top to bottom, left to right. This method will
	return NULL if there is no window assigned to that pane.
	*/
	wxWindow* GetWindow(int i) const;
	/** Sets the content of one of the panes according to index i.
	@remarks
	The windows are indexed top to bottom, left to right. You may pass NULL
	as a window pointer to clear the pane (will render as the background colour
	of the splitter).
	*/
	void SetWindow(int i, wxWindow* wnd);
	/** Replaces an existing window with another. 
	@remarks
	Nothing happens if oldWin is not present. Either of oldWin and newWin 
	may be NULL (if oldWin is NULL the first empty pane will be populated)
	*/
	void ReplaceWindow(wxWindow* oldWin, wxWindow* newWin);
	/** Swaps two windows in their panes.
	@remarks
	If either the first or second window are not found, this method does nothing.
	*/
	void ExchangeWindows(wxWindow* one, wxWindow* two);

	/** Sets the pane which is expanded to full size.
	@remarks
	You can use this method to expand one window to full size, or return to the
	default 4-pane view. Pass an index between 0 and 3 to set a pane to be
	expanded, or -1 to return to thr 4-pane view. All other values are
	ignored.
	*/
	void SetExpanded(int expanded);
	/** Sets the pane which is expanded to full size using a child window pointer.
	*/
	void SetExpanded(wxWindow* expanded);
	/** Gets the currently expanded pane index, or -1 if no panes are expanded. */
	int GetExpanded() const;

	void SetActiveWindow (wxWindow* expanded);
	int GetActiveWidnow ();

	/** Sets the proportional split points.
	@remarks
	By default the split points are at 50% in both horizontal and vertical
	directions, until the user alters them. This method allows you to alter
	them yourself.
	Both split values should be from 0 to 10000 inclusive, with 5000 meaning
	50%, 2500 meaning 25%, etc.
	*/
	void SetSplit(const wxSize& split);
	/** Gets the proportional split points. */
	const wxSize& GetSplit() const;

	/** Set the horizonal split point.
	@see SetSplit
	*/
	void SetHSplit(int frac);
	/** Set the vertical split point.
	@see SetSplit
	*/
	void SetVSplit(int frac);
	/** Get the horizontal split point. */
	int GetHSplit() const;
	/** Get the vertical split point. */
	int GetVSplit() const;


	// Event Hooks
	void OnPaint(wxPaintEvent& e);
	void OnMotion(wxMouseEvent& e);
	void OnSize(wxSizeEvent& e);
	void OnLeftDown(wxMouseEvent& e);
	void OnLeftUp(wxMouseEvent& e);
	void OnEnterWindow(wxMouseEvent& e);
	void OnLeaveWindow(wxMouseEvent& e);



private:

	void RedrawIfHotSensitive(bool isHot);
	void DrawSplitter(wxClientDC& dc);
	void SizeWindows();
	int GetSashSize() const;
	int GetBorderSize() const;
	void MoveSplit(int x, int y);
	void AdjustLayout();
	bool DoSendChangingEvent(const wxPoint& pt);
	void DrawTrackSplitter(const wxPoint& pt);
	void UpdateMode(const wxPoint& pt);
	void DrawActiveWindow (wxClientDC &dc);


	wxWindow* mWindows[4];
	wxCursor mSashCursorWE;
	wxCursor mSashCursorNS;
	wxCursor mSashCursorSize;
	wxPen* mSashTrackerPen;
	// Hot right now?
	bool mIsHot; 
	// Current split position (pixels)
	wxPoint mSplit;
	// Which of the windows is expanded to full size (-1 for none)
	int mExpanded;
	// Fractional size allocation (*10000)
	wxSize mFracSize;
	// Flags covering current operation
	int mFlags;
	// Offset of pointer from sash when it started moving
	wxPoint mOffset;
	// Mode in which sashes are being moved (horz, vert, both)
	int mMode;

	int mActiveIndex;

	DECLARE_EVENT_TABLE()
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGED, wxNewEventType())
DECLARE_EVENT_TYPE(EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGING, wxNewEventType())
END_DECLARE_EVENT_TYPES()

/// Event argument for four way splitter
class wxFourWaySplitterEvent : public wxNotifyEvent
{
public:
	wxFourWaySplitterEvent(wxEventType type = wxEVT_NULL,
		wxFourWaySplitter *splitter = (wxFourWaySplitter *)NULL)
		: wxNotifyEvent(type)
	{
		SetEventObject(splitter);
		if (splitter) m_id = splitter->GetId();
	}

	// SASH_POS_CHANGED methods
	// sash position is a point rather than an int since we have 2 splits
	void SetSashPosition(wxPoint _pt)
	{
		wxASSERT( GetEventType() == EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGED
			|| GetEventType() == EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGING);

		mPoint = _pt;
	}

	wxPoint GetSashPosition() const
	{
		wxASSERT( GetEventType() == EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGED
			|| GetEventType() == EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGING);

		return mPoint;
	}

	// Sash index being altered
	void SetSashIdx(int idx)
	{
		wxASSERT( GetEventType() == EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGED
			|| GetEventType() == EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGING);
		mMode = idx;

	}
	int GetSashIdx(void)
	{
		wxASSERT( GetEventType() == EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGED
			|| GetEventType() == EVT_COMMAND_FOURWAYSPLITTER_SASH_POINT_CHANGING);

		return mMode;

	}

	// No UNSPLIT event like the regular splitter

private:
	friend class wxFourWaySplitter;

	wxPoint mPoint;         // position for SASH_POINT_CHANGED event
	int mMode;				// wxHORIZONTAL, wxVERTICAL, wxBOTH

	DECLARE_DYNAMIC_CLASS_NO_COPY(wxFourWaySplitterEvent)


};

typedef void (wxEvtHandler::*wxFourWaySplitterEventFunction)(wxFourWaySplitterEvent&);

#define wxFourWaySplitterEventHandler(func) \
	(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxFourWaySplitterEventFunction, &func)

#define wx__DECLARE_4SPLITTEREVT(evt, id, fn) \
	wx__DECLARE_EVT1(wxEVT_COMMAND_4SPLITTER_ ## evt, id, wxFourWaySplitterEventHandler(fn))

#define EVT_FOURWAYSPLITTER_SASH_POINT_CHANGED(id, fn) \
	wx__DECLARE_4SPLITTEREVT(SASH_POINT_CHANGED, id, fn)

#define EVT_FOURWAYSPLITTER_SASH_POINT_CHANGING(id, fn) \
	wx__DECLARE_4SPLITTEREVT(SASH_POINT_CHANGING, id, fn)

#endif
