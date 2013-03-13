/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ActorTransProperty.cpp
*
*/

#include "PX2ActorTransProperty.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2EditSystem.hpp"
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
		name, wxPG_LABEL, wxT("<composed>")) );

	mPropertyTranslate = parent->mPage->AppendIn(mProperty, 
		new wxAPoint3Property(PX2_LM.GetValue("Translate"), wxPG_LABEL,
		position));
	mPropertyRotation = parent->mPage->AppendIn(mProperty, 
		new wxAPoint3Property(PX2_LM.GetValue("Rolate"), wxPG_LABEL, rotation));
	mPropertyScale = parent->mPage->AppendIn(mProperty, 
		new wxAPoint3Property(PX2_LM.GetValue("Scale"), wxPG_LABEL, scale));
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
	wxVariant variant = id->GetValue();

	if (0 == id)
		return;

	if (variant.IsNull())
		return;

	APoint value;

	if (mPropertyTranslate == id)
	{
		value = APointRefFromVariant(variant);
		mActor->SetPosition(value);
	}
	else if (mPropertyRotation == id)
	{
		value = APointRefFromVariant(variant);
		mActor->SetRotation(value);
	}
	else if (mPropertyScale == id)
	{
		value = APointRefFromVariant(variant);
		mActor->SetScale(value);
	}

	Event *ent = 0;
	ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::ObjectTransformChanged);
	ent->SetData<Object*>(mActor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//-----------------------------------------------------------------------------
void ActorTransProperty::DoEnter ()
{
}
//-----------------------------------------------------------------------------
void ActorTransProperty::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::ObjectTransformChanged))
	{
		Object *obj = event->GetData<Object*>();
		if (obj == mActor)
		{
			APoint position = mActor->GetPosition();
			APoint rotation = mActor->GetRotation();
			APoint scale = mActor->GetScale();

			wxVariant variant;

			variant.Clear();
			variant << position;
			mPropertyTranslate->SetValue(variant);

			variant.Clear();
			variant << rotation;
			mPropertyRotation->SetValue(variant);

			variant.Clear();
			variant << scale;
			mPropertyScale->SetValue(variant);
		}
	}
}
//-----------------------------------------------------------------------------
void ActorTransProperty::DoLeave ()
{
}
//-----------------------------------------------------------------------------