/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectEventPropertyGrid.cpp
*
*/

#include "PX2EffectPropertyGrid.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(EffectPropertyGrid, ObjectPropertyGrid)
	BEGIN_EVENT_TABLE(EffectPropertyGrid, ObjectPropertyGrid)
	EVT_PG_CHANGED(PGT_ACTOR, EffectPropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()

EffectPropertyGrid::EffectPropertyGrid (wxWindow *parent)
:
ObjectPropertyGrid (parent)
{
	mPropertyGridType = PGT_DEFAULT;
	mParticleMaxNum = 100;
}
//-----------------------------------------------------------------------------
EffectPropertyGrid::~EffectPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::OnSetObject(PX2::Object *object)
{
	if (object->IsExactly(ParticleEmitter::TYPE))
	{
		RefreshOnEffect();
	}
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	if (mEffectNode)
		mEffectNode->SetName(mEffectNodeName);

	if (mSelectedEffect)
		mSelectedEffect->SetName(mSelectedEffectName);

	ParticleEmitter *emitter = DynamicCast<PX2::ParticleEmitter>(mSelectedEffect);
	if (emitter)
	{
		emitter->GetParticleEmitterControl()->SetMaxQuantity(mParticleMaxNum);
	}

	Event *ent = 0;
	ent = EditorEventSpace::CreateEvent
		(EditorEventSpace::UpdateEffect);
	ent->SetData<PX2::Movable*>(mSelectedEffect);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);

	ent = 0;
	ent = EditorEventSpace::CreateEvent
		(EditorEventSpace::UpdateEffectNode);
	ent->SetData<PX2::Movable*>(mEffectNode);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::OnPropertyGridChanging (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::DoEnter ()
{
	ObjectPropertyGrid::DoEnter();
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::DoUpdate ()
{
	ObjectPropertyGrid::DoUpdate();
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::SelectEffect))
	{
		PX2::Movable *effect = event->GetData<PX2::Movable*>();

		SetObject(effect);
	}
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::DoLeave ()
{
	ObjectPropertyGrid::DoLeave();
}
//-----------------------------------------------------------------------------
EffectPropertyGrid::EffectPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void TextureButtonDownCallback (Property *prop)
{
	PX2::Object *object = EditSystem::GetSingleton().GetSelectedResource();
	PX2::Texture2D *tex = DynamicCast<PX2::Texture2D>(object);
	if (tex)
	{
		std::string name = tex->GetName();
		prop->mProperty->SetValueFromString(wxString(name.c_str()));
		PX2::ParticleEmitter *emitter = 
			DynamicCast<ParticleEmitter>(
			((EffectPropertyGrid*)(prop->mParent->mParent))->GetObject());
		if (emitter)
		{
			emitter->SetTexture(tex);
		}
	}
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::RefreshOnEffect ()
{
	Clear();

	if (!mObject)
		return;

	AddPropertyPage("Effect");
	PropertyPage *page = GetPropertyPage("Effect");

	PX2::Object* object = mObject;
	PX2::ParticleEmitter *emitter = DynamicCast<ParticleEmitter>(object);

	if (emitter)
	{
		mSelectedEffect = emitter;
		mSelectedEffectName = emitter->GetName();
		mTextureName = emitter->GetTexture()->GetName();

		PX2::EffectNode *node = DynamicCast<PX2::EffectNode>(
			emitter->GetParent());
		if (node)
		{
			mEffectNode = node;
			mEffectNodeName = node->GetName();
		}

		page->AddProperty("EffectNode", Property::PT_CATEGORY, 0);
		page->AddProperty("EffectNodeName", Property::PT_STRING, 
			&mEffectNodeName);
		page->AddProperty("Effect", Property::PT_CATEGORY, 0);
		page->AddProperty("EffectName", Property::PT_STRING,
			&mSelectedEffectName);
		page->AddProperty("MaxQuantity", Property::PT_INT, &mParticleMaxNum);
		page->AddProperty("Texture", Property::PT_STRINGBUTTON,
			&mTextureName);
		Property *prop = page->GetProperty("Texture");
		prop->SetButtonDownCallback(TextureButtonDownCallback);
	}

	mPropGridManager->ExpandAll();
}
//-----------------------------------------------------------------------------