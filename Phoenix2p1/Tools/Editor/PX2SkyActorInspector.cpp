/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SkyActorInspector.cpp
*
*/

#include "PX2SkyActorInspector.hpp"
using namespace PX2Editor;

BEGIN_EVENT_TABLE(SkyActorInspector, wxScrolledWindow)
	EVT_SIZE(SkyActorInspector::OnSize)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
SkyActorInspector::SkyActorInspector (wxWindow *parent)
:
wxScrolledWindow(parent),
mSkyActorPropertyGrid(0),
mInited(false)
{
}
//-----------------------------------------------------------------------------
SkyActorInspector::~SkyActorInspector ()
{
}
//-----------------------------------------------------------------------------
void SkyActorInspector::OnSize(wxSizeEvent& e)
{
	wxSize size = GetClientSize();

	if (!mInited)
	{
		mSkyActorPropertyGrid = new SkyActorPropertyGrid(this);
		mSkyActorPropertyGrid->SetSize(size);
		mSkyActorPropertyGrid->SetObject(mSkyActor);

		mInited = true;
	}
}
//-----------------------------------------------------------------------------
void SkyActorInspector::SetActor (PX2::SkyActor *actor)
{
	mSkyActor = actor;

	if (mSkyActorPropertyGrid)
		mSkyActorPropertyGrid->SetObject(mSkyActor);
}
//-----------------------------------------------------------------------------
SkyActorInspector::SkyActorInspector ()
{
}
//-----------------------------------------------------------------------------