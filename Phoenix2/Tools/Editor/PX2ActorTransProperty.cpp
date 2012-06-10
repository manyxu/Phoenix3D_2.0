/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ActorTransProperty.cpp
*
*/

#include "PX2ActorTransProperty.hpp"
#include "PX2PropertyPage.hpp"
#include "wxPropertyExtend.hpp"
using namespace PX2Editor;
using namespace PX2;

ActorTransProperty::ActorTransProperty (PropertyPage *parent, std::string name, 
										PX2::Actor *actor)
:
Property(parent, name, Property::PT_ACTORTRANSFORMATION, 0)
,
mPropertyTranslate(NULL),
mPropertyRotation(NULL),
mPropertyScale(NULL)
{
	mActor = actor;

	APoint position;
	APoint rotation;
	APoint scale(1.0f, 1.0f, 1.0f);

	if (mActor)
	{
		position = mActor->GetPosition();
		rotation = mActor->GetRotation();
		scale = mActor->GetScale();
	}

	mProperty = parent->mPage->Append(new wxStringProperty(
		wxT("Transformation"), wxPG_LABEL, wxT("<composed>")) );

	mPropertyTranslate = parent->mPage->AppendIn(mProperty, 
		new wxAPoint3Property(wxT("Translate"), wxPG_LABEL, position));
	mPropertyRotation = parent->mPage->AppendIn(mProperty, 
		new wxAPoint3Property(wxT("Rolate"), wxPG_LABEL, rotation));
	mPropertyScale = parent->mPage->AppendIn(mProperty, 
		new wxAPoint3Property(wxT("Scale"), wxPG_LABEL, scale));
}
//-----------------------------------------------------------------------------
ActorTransProperty::~ActorTransProperty ()
{

}
//-----------------------------------------------------------------------------
void ActorTransProperty::OnChange (wxPropertyGridEvent &event)
{
	if (!mActor)
		return;

	wxPGProperty *id = event.GetProperty();
	const wxString &name = event.GetPropertyName();
	std::string stdName = std::string(name);
	wxVariant variant = event.GetPropertyValue();

	if (0 == id)
		return;

	if (variant.IsNull())
		return;

	APoint value;

	if (mPropertyTranslate == id)
	{
		value = APointFromVariant(variant);
		mActor->SetPosition(value);
	}
	else if (mPropertyRotation == id)
	{
		value = APointFromVariant(variant);
		mActor->SetRotation(value);
	}
	else if (mPropertyScale == id)
	{
		value = APointFromVariant(variant);
		mActor->SetScale(value);
	}

	Event *tdEvent = 0;
	tdEvent = EditorEventSpace::CreateEvent(
		EditorEventSpace::ActorTransformChanged);
	EventWorld::GetSingleton().BroadcastingLocalEvent(tdEvent);
}
//-----------------------------------------------------------------------------
void ActorTransProperty::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void ActorTransProperty::DoUpdate ()
{

}
//-----------------------------------------------------------------------------
void ActorTransProperty::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::ActorTransformChanged))
	{
		APoint position = mActor->GetPosition();
		APoint rotation = mActor->GetRotation();
		APoint scale = mActor->GetScale();

		wxVariant variant;
		variant = APointToVariant(position);
		mPropertyTranslate->SetValue(variant);
		variant = APointToVariant(rotation);
		mPropertyRotation->SetValue(variant);
		variant = APointToVariant(scale);
		mPropertyScale->SetValue(variant);
	}
}
//-----------------------------------------------------------------------------
void ActorTransProperty::DoLeave ()
{

}
//-----------------------------------------------------------------------------