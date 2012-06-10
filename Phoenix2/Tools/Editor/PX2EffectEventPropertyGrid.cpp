/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectEventPropertyGrid.cpp
*
*/

#include "PX2EffectEventPropertyGrid.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(EffectEventPropertyGrid, ObjectPropertyGrid)
	BEGIN_EVENT_TABLE(EffectEventPropertyGrid, ObjectPropertyGrid)
	EVT_PG_CHANGED(PGT_ACTOR, EffectEventPropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()

EffectEventPropertyGrid::EffectEventPropertyGrid (wxWindow *parent)
:
ObjectPropertyGrid (parent)
{
	mPropertyGridType = PGT_DEFAULT;

	mIsFade = false;
	mSpeedMin = 0.0f;
	mSpeedMax = 0.0f;
	mSpeedDirMin = Float3(0.0f, 0.0f, 1.0f);
	mSpeedDirMax = Float3(0.0f, 0.0f, 1.0f);
	mSizeUMin = 0.0f;
	mSizeUMax = 0.0f;
	mSizeRMin = 0.0f;
	mSizeRMax = 0.0f;
	mColorMin = Float3(1.0f, 1.0f, 1.0f);
	mColorMax = Float3(1.0f, 1.0f, 1.0f);
	mAlphaMin = 1.0f;
	mAlphaMax = 1.0f;
}
//-----------------------------------------------------------------------------
EffectEventPropertyGrid::~EffectEventPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void EffectEventPropertyGrid::OnSetObject(PX2::Object *object)
{
	if (object->IsDerived(EffectEvent::TYPE))
	{
		RefreshOnEffectEvent();
	}
}
//-----------------------------------------------------------------------------
void EffectEventPropertyGrid::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	PX2::Object* object = mObject;
	EffectEvent *ent = (EffectEvent*)object;
	ParticleEvent_Speed *entSpeed = DynamicCast<ParticleEvent_Speed>(object);
	ParticleEvent_SpeedDir *entSpeedDir = DynamicCast<ParticleEvent_SpeedDir>(object);
	ParticleEvent_Size *entSize = DynamicCast<ParticleEvent_Size>(object);
	ParticleEvent_Color *entColor = DynamicCast<ParticleEvent_Color>(object);
	ParticleEvent_Alpha *entAlpha = DynamicCast<ParticleEvent_Alpha>(object);

	if (ent)
	{
		ent->SetBeFadeTo(mIsFade);

		PX2::Movable *editEffect = EditSystem::GetSingleton().GetSingleton().
			GetEffectEdit()->GetEditEffect();

		ParticleEmitter *emitter = DynamicCast<ParticleEmitter>(editEffect);
		if (emitter)
			emitter->GetParticleEmitterControl()->ConfigeAllEvents();
	}

	if (entSpeed)
	{
		entSpeed->SetSpeedRange(TRange<float>(mSpeedMin, mSpeedMax));
	}
	if (entSpeedDir)
	{
		entSpeedDir->SetSpeedDirRange(TRange<AVector>(
			AVector(mSpeedDirMin[0], mSpeedDirMin[1], mSpeedDirMin[2]),
			AVector(mSpeedDirMax[0], mSpeedDirMax[1], mSpeedDirMax[2])));
	}
	if (entSize)
	{
		entSize->SetSizeURange(TRange<float>(mSizeUMin, mSizeUMax));
		entSize->SetSizeRRange(TRange<float>(mSizeRMin, mSizeRMax));
	}
	if (entColor)
	{
		entColor->SetColorRange(TRange<Float3>(mColorMin, mColorMax));
	}
	if (entAlpha)
	{
		entAlpha->SetAlphaRange(TRange<float>(mAlphaMin, mAlphaMax));
	}
}
//-----------------------------------------------------------------------------
void EffectEventPropertyGrid::OnPropertyGridChanging (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void EffectEventPropertyGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void EffectEventPropertyGrid::DoEnter ()
{
	ObjectPropertyGrid::DoEnter();
}
//-----------------------------------------------------------------------------
void EffectEventPropertyGrid::DoUpdate ()
{
	ObjectPropertyGrid::DoUpdate();
}
//-----------------------------------------------------------------------------
void EffectEventPropertyGrid::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::SelectEffectEvent))
	{
		EffectEvent *ent = event->GetData<EffectEvent*>();

		SetObject(ent);
	}
}
//-----------------------------------------------------------------------------
void EffectEventPropertyGrid::DoLeave ()
{
	ObjectPropertyGrid::DoLeave();
}
//-----------------------------------------------------------------------------
EffectEventPropertyGrid::EffectEventPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void EffectEventPropertyGrid::RefreshOnEffectEvent ()
{
	Clear();

	if (!mObject)
		return;

	AddPropertyPage("EffectEvent");
	PropertyPage *page = GetPropertyPage("EffectEvent");

	PX2::Object* object = mObject;
	ParticleEvent_Speed *entSpeed = DynamicCast<ParticleEvent_Speed>(object);
	ParticleEvent_SpeedDir *entSpeedDir = DynamicCast<ParticleEvent_SpeedDir>(object);
	ParticleEvent_Size *entSize = DynamicCast<ParticleEvent_Size>(object);
	ParticleEvent_Color *entColor = DynamicCast<ParticleEvent_Color>(object);
	ParticleEvent_Alpha *entAlpha = DynamicCast<ParticleEvent_Alpha>(object);


	mIsFade = ((EffectEvent*)object)->IsFadeTo();

	if (entSpeed)
	{
		mSpeedMin = entSpeed->GetSpeedRange().Value0;
		mSpeedMax = entSpeed->GetSpeedRange().Value1;
		page->AddProperty("Fade", Property::PT_BOOL, &mIsFade);
		page->AddProperty("SpeedMin", Property::PT_FLOAT, &mSpeedMin);
		page->AddProperty("SpeedMax", Property::PT_FLOAT, &mSpeedMax);
	}
	if (entSpeedDir)
	{
		mSpeedDirMin = Float3(entSpeedDir->GetSpeedDirRange().Value0.X(),
			entSpeedDir->GetSpeedDirRange().Value0.Y(),
			entSpeedDir->GetSpeedDirRange().Value0.Z());
		mSpeedDirMax = Float3(entSpeedDir->GetSpeedDirRange().Value1.X(),
			entSpeedDir->GetSpeedDirRange().Value1.Y(),
			entSpeedDir->GetSpeedDirRange().Value1.Z());

		page->AddProperty("Fade", Property::PT_BOOL, &mIsFade);
		page->AddProperty("SpeedDirMin", Property::PT_FLOAT3, &mSpeedDirMin);
		page->AddProperty("SpeedDirMax", Property::PT_FLOAT3, &mSpeedDirMax);
	}
	if (entSize)
	{
		mSizeUMin = entSize->GetSizeURange().Value0;
		mSizeUMax = entSize->GetSizeURange().Value1;
		mSizeRMin = entSize->GetSizeRRange().Value0;
		mSizeRMax = entSize->GetSizeRRange().Value1;
		page->AddProperty("Fade", Property::PT_BOOL, &mIsFade);
		page->AddProperty("USizeMin", Property::PT_FLOAT, &mSizeUMin);
		page->AddProperty("USizeMax", Property::PT_FLOAT, &mSizeUMax);
		page->AddProperty("RSizeMin", Property::PT_FLOAT, &mSizeRMin);
		page->AddProperty("RSizeMax", Property::PT_FLOAT, &mSizeRMax);
	}
	if (entColor)
	{
		mColorMin = entColor->GetColorRange().Value0;
		mColorMax = entColor->GetColorRange().Value1;
		page->AddProperty("Fade", Property::PT_BOOL, &mIsFade);
		page->AddProperty("ColorMin", Property::PT_COLOR3FLOAT3, &mColorMin);
		page->AddProperty("ColorMax", Property::PT_COLOR3FLOAT3, &mColorMax);
	}
	if (entAlpha)
	{
		mAlphaMin = entAlpha->GetAlphaRange().Value0;
		mAlphaMax = entAlpha->GetAlphaRange().Value1;
		page->AddProperty("Fade", Property::PT_BOOL, &mIsFade);
		page->AddProperty("AlphaMin", Property::PT_FLOAT, &mAlphaMin);
		page->AddProperty("AlphaMax", Property::PT_FLOAT, &mAlphaMax);
	}

	mPropGridManager->ExpandAll();
}
//-----------------------------------------------------------------------------