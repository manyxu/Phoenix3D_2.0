/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ActorTransProperty.cpp
*
*/

#include "PX2MovableTransProperty.hpp"
#include "PX2PropertyPage.hpp"
#include "wxPropertyExtend.hpp"
#include "PX2EditEventType.hpp"
#include "PX2LanguageManager.hpp"
using namespace PX2Editor;
using namespace PX2;

MovableTransProperty::MovableTransProperty (PropertyPage *parent, std::string name, 
	PX2::Movable *mov)
	:
Property(parent, name, Property::PT_ACTORTRANSFORMATION, 0)
	,
	mPropertyTranslate(0),
	mPropertyRotation(0),
	mPropertyScale(0)
{
	mMovable = mov;

	APoint position;
	APoint rotation;
	APoint scale(1.0f, 1.0f, 1.0f);

	if (mMovable)
	{
		position = mMovable->LocalTransform.GetTranslate();
		Matrix3f mat = mMovable->LocalTransform.GetRotate();
		mat.ExtractEulerXYZ(rotation.X(), rotation.Y(), rotation.Z());
		scale = mMovable->LocalTransform.GetScale();
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
MovableTransProperty::~MovableTransProperty ()
{
}
//-----------------------------------------------------------------------------
void MovableTransProperty::OnChange (wxPropertyGridEvent &event)
{
	if (!mMovable)
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
		mMovable->LocalTransform.SetTranslate(value);
	}
	else if (mPropertyRotation == id)
	{
		value = APointRefFromVariant(variant);
		mMovable->LocalTransform.SetRotate(Matrix3f().MakeEulerXYZ(
			value.X(), value.Y(), value.Z()));
	}
	else if (mPropertyScale == id)
	{
		value = APointRefFromVariant(variant);
		if (value.X()!=0.0f && value.Y()!=0.0f && value.Z()!=0.0f)
		{
			mMovable->LocalTransform.SetScale(value);
		}
	}

	Event *ent = 0;
	ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::ObjectTransformChanged);
	ent->SetData<Object*>(mMovable);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//-----------------------------------------------------------------------------
void MovableTransProperty::DoEnter ()
{
}
//-----------------------------------------------------------------------------
void MovableTransProperty::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::ObjectTransformChanged))
	{
		Object *obj = event->GetData<Object*>();
		if (obj == mMovable)
		{
			APoint position = mMovable->LocalTransform.GetTranslate();
			APoint rotation;
			Matrix3f mat = mMovable->LocalTransform.GetRotate();
			mat.ExtractEulerXYZ(rotation.X(), rotation.Y(), rotation.Z());
			APoint scale = mMovable->LocalTransform.GetScale();

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
void MovableTransProperty::DoLeave ()
{
}
//-----------------------------------------------------------------------------