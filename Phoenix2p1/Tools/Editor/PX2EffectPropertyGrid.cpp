/*
*
* ÎÄ¼þÃû³Æ	£º	PX2KeyPointPropertyGrid.cpp
*
*/

#include "PX2EffectPropertyGrid.hpp"
#include "PX2ActorTransProperty.hpp"
#include "PX2MovableTransProperty.hpp"
#include "PX2ParticleEmitter.hpp"
#include "PX2EM_P_SizeByAge.hpp"
#include "PX2EMFloatProperty.hpp"
#include "PX2EMFloatRangeProperty.hpp"
#include "PX2EMFloat3Property.hpp"
#include "PX2EMFloat3RangeProperty.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditSystem.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2ParticleEmitterControl.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(EffectPropertyGrid, ObjectPropertyGrid)
BEGIN_EVENT_TABLE(EffectPropertyGrid, ObjectPropertyGrid)
EVT_PG_CHANGED(PGT_EFFECT, EffectPropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
EffectPropertyGrid::EffectPropertyGrid()
:
mActorPage(0),
mSelectedEffectPage(0),
mSelectedModulePage(0)
{
	mPropertyGridType = PGT_EFFECT;
	mBlendMode = 0;
	mIsLocal = true;
	mFaceType = 0;
	mRotateAxisType = 0;
	mIsFixedBound = true;
	mFixedBoundRadius = 0.0f;
	mPlacerType = 0;
	mInLength = 0.0f;
	mOutLength = 0.0f;
	mInWidth = 0.0f;
	mOutWidth = 0.0f;
	mInHeight = 0.0f;
	mOutHeight = 0.0f;
	mMaxNumParticles = 0;
	mSelectedModuleIsRange = false;
}
//-----------------------------------------------------------------------------
EffectPropertyGrid::EffectPropertyGrid (wxWindow *parent)
	:
ObjectPropertyGrid (parent),
mActorPage(0),
mSelectedEffectPage(0),
mSelectedModulePage(0)
{
	mPropertyGridType = PGT_EFFECT;
	mBlendMode = 0;
	mIsLocal = true;
	mIsFixedBound = true;
	mFixedBoundRadius = 0.0f;
	mPlacerType = 0;
	mInLength = 0.0f;
	mOutLength = 0.0f;
	mInWidth = 0.0f;
	mOutWidth = 0.0f;
	mInHeight = 0.0f;
	mOutHeight = 0.0f;
	mMaxNumParticles = 0;
	mSelectedModuleIsRange = false;
}
//-----------------------------------------------------------------------------
EffectPropertyGrid::~EffectPropertyGrid ()
{
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::OnSetObject(PX2::Object *object)
{
	Clear();

	mActorPage = AddPropertyPage(PX2_LM.GetValue("Actor"));
	mActorPage->AddProperty(PX2_LM.GetValue("Actor"), Property::PT_CATEGORY, 0);
	PX2::Actor *actor = DynamicCast<Actor>(mObject);
	mActorName = actor->GetName();
	mActorType = actor->GetRttiType().GetName();
	Property *propName = new0 Property(mActorPage, PX2_LM.GetValue("Name"),
		Property::PT_STRING, &mActorName);
	Property *propType = new0 Property(mActorPage, PX2_LM.GetValue("Type"),
		Property::PT_STRING, &mActorType, false);
	Property *propTrans = new0 ActorTransProperty(mActorPage,
		PX2_LM.GetValue("Trans"), actor);
	EventWorld::GetSingleton().ComeIn(propTrans);

	mSelectedEffectPage = AddPropertyPage(PX2_LM.GetValue("SelectedEffect"));
	mSelectedModulePage = AddPropertyPage(PX2_LM.GetValue("SelectedModule"));
}
//-----------------------------------------------------------------------------
void TexButCall (Property *p)
{
	std::string name = EditSystem::GetSingleton().GetSelectedResourceName();
	if ("" == name)
		return;

	Object *obj = ResourceManager::GetSingleton().BlockLoad(name);
	Texture2D *tex = DynamicCast<Texture2D>(obj);
	if (tex)
	{
		p->SetValue(name);
	}
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::SetSelectedEffect (PX2::Movable *mov)
{
	if (mSelectedEffect == mov)
		return;

	mSelectedEffect = mov;
	mSelectedEffectPage->Clear();

	if (!mSelectedEffect)
		return;

	mSelectedEffectName = mSelectedEffect->GetName();
	mSelectedEffectType = mSelectedEffect->GetRttiType().GetName();

	mSelectedEffectPage->AddProperty(PX2_LM.GetValue("Effect"),
		Property::PT_CATEGORY, 0);
	Property *propName = new0 Property(mSelectedEffectPage, PX2_LM.GetValue("Name"),
		Property::PT_STRING, &mSelectedEffectName);
	Property *propType = new0 Property(mSelectedEffectPage, PX2_LM.GetValue("Type"),
		Property::PT_STRING, &mSelectedEffectType, false);
	Property *propTrans = new0 MovableTransProperty(mSelectedEffectPage,
		PX2_LM.GetValue("Trans"), mSelectedEffect);
	EventWorld::GetSingleton().ComeIn(propTrans);

	ParticleEmitter *pE = DynamicCast<ParticleEmitter>(mSelectedEffect);
	if (pE)
	{
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("Material"),
			Property::PT_CATEGORY, 0);
		if (pE->GetTexture())
			mTextPath = pE->GetTexture()->GetResourcePath();
		Property *prop = mSelectedEffectPage->AddProperty(PX2_LM.GetValue("Texture"), 
			Property::PT_STRINGBUTTON, &mTextPath);
		prop->SetButtonDownCallback(TexButCall);
		mBlendMode = pE->GetBlendMode();
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("BlendMode"), 
			Property::PT_INT, &mBlendMode);

		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("ParticleEmitter"),
			Property::PT_CATEGORY, 0);
		mMaxNumParticles = pE->GetParticleEmitterControl()->GetMaxNumParticles();
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("MaxNumParticles"),
			Property::PT_INT, &mMaxNumParticles);

		mIsLocal = pE->IsLocal();
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("IsLocal"),
			Property::PT_BOOLCHECK, &mIsLocal);

		mFaceType = (int)pE->GetFaceType();
		std::vector<std::string> faceTypes;
		faceTypes.push_back(PX2_LM.GetValue("FT_CAMERA"));
		faceTypes.push_back(PX2_LM.GetValue("FT_SPEEDDIR"));
		faceTypes.push_back(PX2_LM.GetValue("FT_FREE"));
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("FaceType"),
			Property::PT_ENUM, &mFaceType, true, &faceTypes);

		mRotateAxisType = (int)pE->GetRotateAxisType();
		std::vector<std::string> rotateAxisTypes;
		rotateAxisTypes.push_back(PX2_LM.GetValue("RAT_D"));
		rotateAxisTypes.push_back(PX2_LM.GetValue("RAT_U"));
		rotateAxisTypes.push_back(PX2_LM.GetValue("RAT_R"));
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("RotateAxisType"),
			Property::PT_ENUM, &mRotateAxisType, true, &rotateAxisTypes);

		mIsFixedBound = pE->IsFixedBound();
		mFixedBoundRadius = pE->GetFixedBoundRadius();
		mFixedBoundCenter = pE->GetFixedBoundCenter();
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("IsFixedBound"),
			Property::PT_BOOLCHECK, &mIsFixedBound);
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("FixedBoundCenter"),
			Property::PT_FLOAT3, &mFixedBoundCenter, mIsFixedBound);
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("FixedBoundRadius"),
			Property::PT_FLOAT, &mFixedBoundRadius, mIsFixedBound);

		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("Placer"),
			Property::PT_CATEGORY, 0);
		mPlacerType = (int)(pE->GetParticleEmitterControl()->GetPlacerType());
		bool enWidth = (0==mPlacerType);
		bool enHeight = (0==mPlacerType || 2==mPlacerType);
		mInLength = pE->GetParticleEmitterControl()->GetPlacerInLength();
		mOutLength = pE->GetParticleEmitterControl()->GetPlacerOutLength();
		mInWidth = pE->GetParticleEmitterControl()->GetPlacerInWidth();
		mOutWidth = pE->GetParticleEmitterControl()->GetPlacerOutWidth();
		mInHeight = pE->GetParticleEmitterControl()->GetPlacerInHeight();
		mOutHeight = pE->GetParticleEmitterControl()->GetPlacerOutWidth();

		std::vector<std::string> placerTypes;
		placerTypes.push_back(PX2_LM.GetValue("PlacerBox"));
		placerTypes.push_back(PX2_LM.GetValue("PlacerSphere"));
		placerTypes.push_back(PX2_LM.GetValue("PlacerColumn"));
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("PlacerType"),
			Property::PT_ENUM, &mPlacerType, true, &placerTypes);
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("OutLength"),
			Property::PT_FLOAT, &mOutLength);
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("InLength"),
			Property::PT_FLOAT, &mInLength);
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("OutWidth"),
			Property::PT_FLOAT, &mOutWidth, enWidth);
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("InWidth"),
			Property::PT_FLOAT, &mInWidth, enWidth);
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("OutHeight"),
			Property::PT_FLOAT, &mOutHeight, enHeight);
		mSelectedEffectPage->AddProperty(PX2_LM.GetValue("InHeight"),
			Property::PT_FLOAT, &mInHeight, enHeight);

	}
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::SetSelectedModule (PX2::EffectModule *module)
{
	if (mSelectedModule == module)
		return;

	mSelectedModule = module;

	RefreshModule(module);
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::RefreshModule (PX2::EffectModule *module)
{
	mSelectedModulePage->Clear();

	if (!module)
		return;

	mSelectedModuleName = module->GetName();
	mSelectedModuleType = module->GetRttiType().GetName();
	mSelectedModuleIsRange = module->IsRange();
	mSelectedModulePage->AddProperty(PX2_LM.GetValue("Module"), 
		Property::PT_CATEGORY, 0);
	mSelectedModulePage->AddProperty(PX2_LM.GetValue("Name"),
		Property::PT_STRING, &mSelectedModuleName, false);
	mSelectedModulePage->AddProperty(PX2_LM.GetValue("Type"),
		Property::PT_STRING, &mSelectedModuleType, false);
	mSelectedModulePage->AddProperty(PX2_LM.GetValue("SetBeRange"),
		Property::PT_BOOL, &mSelectedModuleIsRange);

	mSelectedModulePage->AddProperty(PX2_LM.GetValue("KeyPoints"), 
		Property::PT_CATEGORY, 0);

	RefreshModuleKeyPoints(module, false);
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::RefreshModuleKeyPoints (PX2::EffectModule *module,
	bool forChange)
{
	mPropGridManager->ClearSelection(); // this is important

	for (int i=0; i<module->GetNumKeyPoints(); i++)
	{
		std::string name = "["+StringHelp::IntToString(i)+"]";

		mSelectedModulePage->RemoveProperty(name);
	}

	EffectModule::ModuleType moduleType = module->GetModuleType();

	if (forChange)
	{
		EditSystem::GetSingleton().GetCurveEdit()->SetSelectedCurveCtrl(0);
		EditSystem::GetSingleton().GetCurveEdit()->SetSelectedUICurveGroup(0);

		if (EffectModule::MT_FLOAT==moduleType && mSelectedModuleIsRange)
		{
			module->GetCurveFloatMax().Points = module->GetCurveFloatMin().Points;
		}
		else if (EffectModule::MT_FLOAT3==moduleType && mSelectedModuleIsRange)
		{
			module->GetCurveFloat3Max().Points = module->GetCurveFloat3Min().Points;
		}
	}

	for (int i=0; i<module->GetNumKeyPoints(); i++)
	{
		float *inVal = module->GetKeyPointInVal(i);		
		bool isForInit = module->IsForInit();
		std::string name = "["+StringHelp::IntToString(i)+"]";

		if (EffectModule::MT_FLOAT == moduleType && !mSelectedModuleIsRange)
		{
			InterpCurvePointFloat *point = &(module->GetCurveFloatMin().Points[i]);

			Property *propFloat = new0 EMFloatProperty(mSelectedModulePage,
				name, point, isForInit);
			PX2_UNUSED(propFloat);
		}
		else if (EffectModule::MT_FLOAT==moduleType && mSelectedModuleIsRange)
		{
			InterpCurvePointFloat *pointMin = &(module->GetCurveFloatMin().Points[i]);
			InterpCurvePointFloat *pointMax = &(module->GetCurveFloatMax().Points[i]);
			Property *propFloatRange = new0 EMFloatRangeProperty(mSelectedModulePage,
				name, pointMin, pointMax, isForInit);
			PX2_UNUSED(propFloatRange);
		}
		else if (EffectModule::MT_FLOAT3 == moduleType && !mSelectedModuleIsRange)
		{
			InterpCurvePointFloat3 *point = &(module->GetCurveFloat3Min().Points[i]);
			Property *prop = new0 EMFloat3Property(mSelectedModulePage,
				name, point, isForInit);
			PX2_UNUSED(prop);
		}
		else if (EffectModule::MT_FLOAT3==moduleType && mSelectedModuleIsRange)
		{
			InterpCurvePointFloat3 *pointMin = &(module->GetCurveFloat3Min().Points[i]);
			InterpCurvePointFloat3 *pointMax = &(module->GetCurveFloat3Max().Points[i]);
			Property *propFloat3 = new0 EMFloat3RangeProperty(mSelectedModulePage,
				name, pointMin, pointMax, isForInit);
			PX2_UNUSED(propFloat3);
		}
	}
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::TryRefreshModule (void *pointer)
{
	if (!pointer)
		return;

	Curve *curve = (Curve*)(pointer);
	if (curve->GetClientDataPointer() == mSelectedModule)
	{
		RefreshModule(mSelectedModule);
	}
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::TryRefreshModulePoints (void *pointer)
{
	if (!pointer)
		return;

	Curve *curve = (Curve*)(pointer);
	if (curve->GetClientDataPointer() == mSelectedModule)
	{
		RefreshModuleKeyPoints(mSelectedModule, false);
	}
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::OnPropertyGridChange (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	wxPGProperty *prop = event.GetProperty();
	
	if (mSelectedEffectPage ==  GetPropertyPage(prop))
	{
		ParticleEmitter *pE = DynamicCast<ParticleEmitter>(mSelectedEffect);
		if (pE)
		{
			if (PX2_LM.GetValue("BlendMode") == event.GetPropertyName())
			{
				pE->SetBlendMode(mBlendMode);
			}
			else if (PX2_LM.GetValue("MaxNumParticles") == event.GetPropertyName())
			{
				pE->GetParticleEmitterControl()->SetMaxNumParticles(mMaxNumParticles);
			}
			else if (PX2_LM.GetValue("IsLocal") == event.GetPropertyName())
			{
				pE->SetLocal(mIsLocal);
			}
			else if (PX2_LM.GetValue("FaceType") == event.GetPropertyName())
			{
				pE->SetFaceType((ParticleEmitter::FaceType)mFaceType);
			}
			else if (PX2_LM.GetValue("RotateAxisType") == event.GetPropertyName())
			{
				pE->SetRotateAxisType((ParticleEmitter::RotateAxisType)mRotateAxisType);
			}
			else if (PX2_LM.GetValue("Texture") == event.GetPropertyName())
			{
				Object *obj = ResourceManager::GetSingleton().BlockLoad(mTextPath);
				Texture2D *tex = DynamicCast<Texture2D>(obj);
				if (tex)
				{
					pE->SetTexture(tex);
				}
			}
			else if (PX2_LM.GetValue("IsFixedBound") == event.GetPropertyName())
			{
				pE->SetFixedBound(mIsFixedBound);
				Property *propCenter = mSelectedEffectPage->GetProperty(PX2_LM.GetValue("FixedBoundCenter"));
				if (propCenter)
				{
					propCenter->Enable(mIsFixedBound);
				}
				Property *propRadius = mSelectedEffectPage->GetProperty(PX2_LM.GetValue("FixedBoundRadius"));
				if (propRadius)
				{
					propRadius->Enable(mIsFixedBound);
				}
			}
			else if (PX2_LM.GetValue("FixedBoundCenter") == event.GetPropertyName())
			{
				pE->SetFixedBoundCenter(mFixedBoundCenter);
			}
			else if (PX2_LM.GetValue("FixedBoundRadius") == event.GetPropertyName())
			{
				pE->SetFixedBoundRadius(mFixedBoundRadius);
			}
			else if (PX2_LM.GetValue("PlacerType") == event.GetPropertyName())
			{
				pE->GetParticleEmitterControl()->SetPlacerType(
					(ParticleEmitterController::PlacerType)mPlacerType);
				bool enWidth = (0==mPlacerType);
				bool enHeight = (0==mPlacerType || 2==mPlacerType);

				Property *prop= mSelectedEffectPage->GetProperty(PX2_LM.GetValue("OutWidth"));
				if (prop)
				{
					prop->Enable(enWidth);
				}
				prop = mSelectedEffectPage->GetProperty(PX2_LM.GetValue("InWidth"));
				if (prop)
				{
					prop->Enable(enWidth);
				}

				prop = mSelectedEffectPage->GetProperty(PX2_LM.GetValue("OutHeight"));
				if (prop)
				{
					prop->Enable(enHeight);
				}
				prop = mSelectedEffectPage->GetProperty(PX2_LM.GetValue("InHeight"));
				if (prop)
				{
					prop->Enable(enHeight);
				}
			}
			else if (PX2_LM.GetValue("OutLength") == event.GetPropertyName())
			{
				pE->GetParticleEmitterControl()->SetPlacerOutLength(mOutLength);
			}
			else if (PX2_LM.GetValue("InLength") == event.GetPropertyName())
			{
				pE->GetParticleEmitterControl()->SetPlacerInLength(mInLength);
			}
			else if (PX2_LM.GetValue("OutWidth") == event.GetPropertyName())
			{
				pE->GetParticleEmitterControl()->SetPlacerOutWidth(mOutWidth);
			}
			else if (PX2_LM.GetValue("InWidth") == event.GetPropertyName())
			{
				pE->GetParticleEmitterControl()->SetPlacerInWidth(mInWidth);
			}
			else if (PX2_LM.GetValue("OutHeight") == event.GetPropertyName())
			{
				pE->GetParticleEmitterControl()->SetPlacerOutHeight(mOutHeight);
			}
			else if (PX2_LM.GetValue("InHeight") == event.GetPropertyName())
			{
				pE->GetParticleEmitterControl()->SetPlacerInHeight(mInHeight);
			}
		}
	}	
	else if (mSelectedModulePage == GetPropertyPage(prop))
	{
		if (PX2_LM.GetValue("SetBeRange") == event.GetPropertyName())
		{
			if (mSelectedModule->IsRange() != mSelectedModuleIsRange)
			{
				mSelectedModule->SetRange(mSelectedModuleIsRange);
				mPropGridManager->SelectPage(mSelectedModulePage->mPage);

				RefreshModuleKeyPoints(mSelectedModule, true);

				EditSystem::GetSingleton().GetCurveEdit()->ReCreateAddCurve(mSelectedModule);
			}
		}
		else
		{
			Event *ent = EditorEventSpace::CreateEventX(
				EditorEventSpace::CurveChangedByGrid);
			ent->SetData<EffectModule*>(mSelectedModule);
			EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
		}
	}
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::OnPropertyGridChanging (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void EffectPropertyGrid::OnPropertyGridSelect (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
