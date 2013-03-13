/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SkyActorPropertyGrid.cpp
*
*/

#include "PX2SkyActorPropertyGrid.hpp"
#include "PX2ObjectNameProperty.hpp"
#include "PX2LanguageManager.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(SkyActorPropertyGrid, ObjectPropertyGrid)
BEGIN_EVENT_TABLE(SkyActorPropertyGrid, ObjectPropertyGrid)
EVT_PG_CHANGED(PGT_ACTOR, SkyActorPropertyGrid::OnPropertyGridChange)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
SkyActorPropertyGrid::SkyActorPropertyGrid ()
{
	mSunParams = Float4::ZERO;
	mSkyParams = Float4::ZERO;
}
//-----------------------------------------------------------------------------
SkyActorPropertyGrid::SkyActorPropertyGrid (wxWindow *parent)
	:
ObjectPropertyGrid (parent)
{
	mPropertyGridType = PGT_SKYACTOR;
}
//-----------------------------------------------------------------------------
SkyActorPropertyGrid::~SkyActorPropertyGrid ()
{
}
//-----------------------------------------------------------------------------
void SkyActorPropertyGrid::OnSetObject(PX2::Object *object)
{
	if (object->IsDerived(SkyActor::TYPE))
	{
		mSkyActor = DynamicCast<SkyActor>(object);

		RefreshOnSkyActor();
	}
}
//-----------------------------------------------------------------------------
void SkyActorPropertyGrid::OnPropertyGridChange (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	if (!mSkyActor)
		return;

	if (PX2_LM.GetValue("SunRadiusAttenuation") == event.GetPropertyName())
	{
		mSkyActor->GetSky()->SetSunParams(mSunParams);
	}
	else if (PX2_LM.GetValue("SunLightness") == event.GetPropertyName())
	{
		mSkyActor->GetSky()->SetSunParams(mSunParams);
	}
	else if (PX2_LM.GetValue("LargeSunRadiusAttenuation") == event.GetPropertyName())
	{
		mSkyActor->GetSky()->SetSunParams(mSunParams);
	}
	else if (PX2_LM.GetValue("LargeSunLightness") == event.GetPropertyName())
	{
		mSkyActor->GetSky()->SetSunParams(mSunParams);
	}
	else if (PX2_LM.GetValue("HazeTopAltitude") == event.GetPropertyName())
	{
		mSkyActor->GetSky()->SetSkyParams(mSkyParams);
	}
	else if (PX2_LM.GetValue("DayToSunsetSharpness") == event.GetPropertyName())
	{
		mSkyActor->GetSky()->SetSkyParams(mSkyParams);
	}
}
//-----------------------------------------------------------------------------
void SkyActorPropertyGrid::OnPropertyGridChanging (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void SkyActorPropertyGrid::OnPropertyGridSelect (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void SkyActorPropertyGrid::DoEnter ()
{
	ObjectPropertyGrid::DoEnter();
}
//-----------------------------------------------------------------------------
void SkyActorPropertyGrid::DoExecute (PX2::Event *event)
{
	ObjectPropertyGrid::DoExecute(event);
}
//-----------------------------------------------------------------------------
void SkyActorPropertyGrid::DoLeave ()
{
	ObjectPropertyGrid::DoLeave();
}
//-----------------------------------------------------------------------------
void SkyActorPropertyGrid::RefreshOnSkyActor ()
{
	Clear();

	mActorType = mObject->GetRttiType().GetName();
	mSkyParams = mSkyActor->GetSky()->GetSkyParams();
	mSunParams = mSkyActor->GetSky()->GetSunParams();

	AddPropertyPage("General");

	PropertyPage *page = GetPropertyPage("General");

	page->AddProperty(PX2_LM.GetValue("General"), Property::PT_CATEGORY, 0);
	ObjectNameProperty *prop = new0 ObjectNameProperty(page, "Name", mObject);
	Property *propType = new0 Property(page, PX2_LM.GetValue("Type"),
		Property::PT_STRING, &mActorType, false);

	page->AddProperty(PX2_LM.GetValue("Weather"), Property::PT_CATEGORY, 0);

	Property *propParms = new0 Property(page, PX2_LM.GetValue("SunRadiusAttenuation"),
		Property::PT_FLOAT, &mSunParams[0]);
	propParms = new0 Property(page, PX2_LM.GetValue("SunLightness"),
		Property::PT_FLOAT, &mSunParams[1]);
	propParms = new0 Property(page, PX2_LM.GetValue("LargeSunRadiusAttenuation"),
		Property::PT_FLOAT, &mSunParams[2]);
	propParms = new0 Property(page, PX2_LM.GetValue("LargeSunLightness"),
		Property::PT_FLOAT, &mSunParams[3]);

	propParms = new0 Property(page, PX2_LM.GetValue("HazeTopAltitude"),
		Property::PT_FLOAT, &mSkyParams[0]);
	propParms = new0 Property(page, PX2_LM.GetValue("DayToSunsetSharpness"),
		Property::PT_FLOAT, &mSkyParams[1]);
}
//-----------------------------------------------------------------------------