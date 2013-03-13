/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectNodePanel.cpp
*
*/

#include "PX2EffectNodePanel.hpp"
#include "PX2EffectActorInspector.hpp"
#include "PX2CurveEditWindow.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2EditSystem.hpp"
#include "PX2ParticleEmitter.hpp"
#include "PX2ParticleEmitterControl.hpp"
#include "PX2EffectModule.hpp"
#include "PX2EM_E_EmitRate.hpp"
#include "PX2EM_E_EmitterTranslate.hpp"
#include "PX2EM_P_Accelerate.hpp"
#include "PX2EM_P_AccelerateDir.hpp"
#include "PX2EM_P_AlphaByAge.hpp"
#include "PX2EM_P_AlphaInit.hpp"
#include "PX2EM_P_ColorByAge.hpp"
#include "PX2EM_P_ColorInit.hpp"
#include "PX2EM_P_FaceAxisInit.hpp"
#include "PX2EM_P_LifeInit.hpp"
#include "PX2EM_P_RotateDegreeInit.hpp"
#include "PX2EM_P_RotateSpeedByAge.hpp"
#include "PX2EM_P_RotateSpeedInit.hpp"
#include "PX2EM_P_SizeByAge.hpp"
#include "PX2EM_P_SizeInit.hpp"
#include "PX2EM_P_SpeedDirInit.hpp"
#include "PX2EM_P_SpeedInit.hpp"
using namespace PX2Editor;
using namespace PX2;

#define ID_ENP_PARTICLE 6051
#define ID_ENP_RIBBON 6052
#define ID_ENP_BEAM 6053
#define ID_ENP_DECAL 6054
#define ID_ENP_SHAKE 6055

#define ID_ENP_PARTICLE 6051
#define ID_ENP_RIBBON 6052
#define ID_ENP_BEAM 6053
#define ID_ENP_DECAL 6054
#define ID_ENP_SHAKE 6055

#define ID_ENP_EMITTER_RATE 6070
#define ID_ENP_EMITTER_TRANSLATE 6071
#define ID_ENP_PARTICLE_ACCELERATE 6072
#define ID_ENP_PARTICLE_ACCELERATEDIR 6073
#define ID_ENP_PARTICLE_ALPHABYAGE 6074
#define ID_ENP_PARTICLE_ALPHAINIT 6075
#define ID_ENP_PARTICLE_COLORBYAGE 6076
#define ID_ENP_PARTICLE_COLORINIT 6077
#define ID_ENP_PARTICLE_FACEAXISINIT 6078
#define ID_ENP_PARTICLE_LIFEINIT 6079
#define ID_ENP_PARTICLE_ROTATEDEGREEINIT 6080
#define ID_ENP_PARTICLE_ROTATESPEEDBYAGE 6081
#define ID_ENP_PARTICLE_ROTATESPEEDINIT 6082
#define ID_ENP_PARTICLE_SIZEBYAGE 6083
#define ID_ENP_PARTICLE_SIZEINIT 6084
#define ID_ENP_PARTICLE_SPEEDDIRINIT 6085
#define ID_ENP_PARTICLE_SPEEDINIT 6086

BEGIN_EVENT_TABLE(EffectNodePanel, wxPanel)
	EVT_BUTTON(wxID_ANY, EffectNodePanel::OnButton)
	EVT_MENU(ID_ENP_PARTICLE, EffectNodePanel::OnNewParticles)
	EVT_MENU_RANGE(ID_ENP_EMITTER_RATE, ID_ENP_PARTICLE_SPEEDINIT, 
		EffectNodePanel::OnNewEffectModule)
	EVT_LISTBOX(wxID_ANY, EffectNodePanel::OnListbox)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
EffectNodePanel::EffectNodePanel (wxWindow *parent)
:
mNEffect(0),
mDEffect(0),
mNModule(0),
mDModule(0),
mParent1(0)
{
	const bool bSuccess = wxXmlResource::Get()->LoadPanel(this, parent,
		TEXT("EffectNode") );

	assertion(bSuccess, "Load EffectNodePanel failed!");
	PX2_UNUSED(bSuccess);

	mNEffect = (wxButton*)FindWindow(XRCID("mNEffect"));
	assertion(mNEffect!=0, "Window must be find!");

	mDEffect = (wxButton*)FindWindow(XRCID("mDEffect"));
	assertion(mDEffect!=0, "Window must be find!");

	mNModule = (wxButton*)FindWindow(XRCID("mNModule"));
	assertion(mNModule!=0, "Window must be find!");

	mDModule = (wxButton*)FindWindow(XRCID("mDModule"));
	assertion(mDModule!=0, "Window must be find!");

	mPlayEffect = (wxButton*)FindWindow(XRCID("mPlayEffect"));
	assertion(mPlayEffect!=0, "Window must be find!");

	mMoudleCurve = (wxButton*)FindWindow(XRCID("mMoudleCurve"));
	assertion(mMoudleCurve!=0, "Window must be find!");

	mEffectList = (wxListBox*)FindWindow(XRCID("mEffectList"));
	assertion(mEffectList!=0, "Window must be find!");

	mModuleList = (wxListBox*)FindWindow(XRCID("mModuleList"));
	assertion(mModuleList!=0, "Window must be find!");

	mEffectMenu.Append(ID_ENP_PARTICLE, PX2_LM.GetValue("Particles"));
	mEffectMenu.Append(ID_ENP_RIBBON, PX2_LM.GetValue("Ribbon"));
	mEffectMenu.Append(ID_ENP_BEAM, PX2_LM.GetValue("Beam"));
	mEffectMenu.Append(ID_ENP_DECAL, PX2_LM.GetValue("Decal"));
	mEffectMenu.Append(ID_ENP_SHAKE, PX2_LM.GetValue("Shake"));

	mModuleMenu.Append(ID_ENP_EMITTER_RATE, PX2_LM.GetValue("EmitRate"));
	mModuleMenu.Append(ID_ENP_EMITTER_TRANSLATE, PX2_LM.GetValue("EmitterTranslate"));
	mModuleMenu.AppendSeparator();

	mModuleMenu.Append(ID_ENP_PARTICLE_ACCELERATE, PX2_LM.GetValue("ParticleAccelerate"));
	mModuleMenu.Append(ID_ENP_PARTICLE_ACCELERATEDIR, PX2_LM.GetValue("ParticleAccelerateDir"));
	mModuleMenu.Append(ID_ENP_PARTICLE_ALPHABYAGE, PX2_LM.GetValue("ParticleAlphaByAge"));
	mModuleMenu.Append(ID_ENP_PARTICLE_ALPHAINIT, PX2_LM.GetValue("ParticleAlphaInit"));
	mModuleMenu.Append(ID_ENP_PARTICLE_COLORBYAGE, PX2_LM.GetValue("ParticleColorByAge"));
	mModuleMenu.Append(ID_ENP_PARTICLE_COLORINIT, PX2_LM.GetValue("ParticleColorInit"));
	mModuleMenu.Append(ID_ENP_PARTICLE_FACEAXISINIT, PX2_LM.GetValue("ParticleFaceAxisInit"));
	mModuleMenu.Append(ID_ENP_PARTICLE_LIFEINIT, PX2_LM.GetValue("ParticleLifeInit"));
	mModuleMenu.Append(ID_ENP_PARTICLE_ROTATEDEGREEINIT, PX2_LM.GetValue("ParticleRotateDegreeInit"));
	mModuleMenu.Append(ID_ENP_PARTICLE_ROTATESPEEDBYAGE, PX2_LM.GetValue("ParticleRotateSpeedByAge"));
	mModuleMenu.Append(ID_ENP_PARTICLE_ROTATESPEEDINIT, PX2_LM.GetValue("ParticleRotateSpeedInit"));
	mModuleMenu.Append(ID_ENP_PARTICLE_SIZEBYAGE, PX2_LM.GetValue("ParticleSizeByAge"));
	mModuleMenu.Append(ID_ENP_PARTICLE_SIZEINIT, PX2_LM.GetValue("ParticleSizeInit"));
	mModuleMenu.Append(ID_ENP_PARTICLE_SPEEDDIRINIT, PX2_LM.GetValue("ParticleSpeedDirInit"));
	mModuleMenu.Append(ID_ENP_PARTICLE_SPEEDINIT, PX2_LM.GetValue("ParticleSpeedInit"));
}
//-----------------------------------------------------------------------------
void EffectNodePanel::SetActor (EffectActor *actor)
{
	if (mEffectActor == actor)
		return;

	mEffectActor = actor;

	RefreshActor(mEffectActor);
}
//-----------------------------------------------------------------------------
void EffectNodePanel::SetParent1 (wxWindow *par)
{
	mParent1 = par;
}
//-----------------------------------------------------------------------------
void EffectNodePanel::OnButton (wxCommandEvent& event)
{
	if (event.GetEventObject() == mNEffect)
	{
		wxPoint popupPos = wxGetMousePosition();
		popupPos = ScreenToClient(popupPos);
		PopupMenu(&mEffectMenu, popupPos.x, popupPos.y);
	}
	else if (event.GetEventObject() == mDEffect)
	{
		EffectNode *node = mEffectActor->GetEffect();
		if (!node)
			return;

		if (mSelectedEffect)
		{
			node->DetachChild(mSelectedEffect);
			RefreshActor(mEffectActor);
			mSelectedEffect = 0;
			mSelectedEffectModule = 0;
			OnSelectEffect(0);

		}
	}
	else if (event.GetEventObject() == mPlayEffect)
	{
		EffectNode *node = mEffectActor->GetEffect();
		if (!node)
			return;

		node->Play();
	}
	else if (event.GetEventObject() == mNModule)
	{
		wxPoint popupPos = wxGetMousePosition();
		popupPos = ScreenToClient(popupPos);
		PopupMenu(&mModuleMenu, popupPos.x, popupPos.y);
	}
	else if (event.GetEventObject() == mDModule)
	{
		ParticleEmitter *emitter = DynamicCast<ParticleEmitter>(mSelectedEffect);
		EffectModule *module = DynamicCast<EffectModule>(mSelectedEffectModule);
		if (module && emitter)
		{
			emitter->GetParticleEmitterControl()->RemoveModule(module);
			OnSelectEffect(emitter);
			mSelectedEffectModule = 0;
		}
	}
	else if (event.GetEventObject() == mMoudleCurve)
	{
		if (!mSelectedEffectModule)
			return;

		EditSystem::GetSingleton().GetCurveEdit()
			->CreateAddCurve(mSelectedEffectModule);
	}
}
//-----------------------------------------------------------------------------
void EffectNodePanel::OnListbox (wxCommandEvent& event)
{
	if (event.GetEventObject() == mEffectList)
	{
		int select = mEffectList->GetSelection();
		Movable *mov = (Movable*)mEffectList->GetClientData(select);
		 
		OnSelectEffect(mov);
	}
	else if (event.GetEventObject() == mModuleList)
	{
		int select = mModuleList->GetSelection();
		EffectModule *module = (EffectModule*)mModuleList->GetClientData(select);

		OnSelectModule(module);
	}
}
//-----------------------------------------------------------------------------
void EffectNodePanel::OnNewParticles (wxCommandEvent& event)
{
	if (!mEffectActor)
		return;

	Movable *particles = EditSystem::GetSingleton().GetEditMap()
		->CreateParticlesToEffect(mEffectActor->GetEffect());

	mEffectList->Append(particles->GetName(), particles);
}
//-----------------------------------------------------------------------------
void EffectNodePanel::OnNewEffectModule (wxCommandEvent& event)
{
	int commond = event.GetId();

	EffectModulePtr module = 0;
	switch (commond)
	{
	case ID_ENP_EMITTER_RATE:
		module = new0 EM_E_EmitRate();
		break;
	case ID_ENP_EMITTER_TRANSLATE:
		module = new0 EM_E_EmitterTranslate();
		break;
	case ID_ENP_PARTICLE_ACCELERATE:
		module = new0 EM_P_Accelerate();
		break;
	case ID_ENP_PARTICLE_ACCELERATEDIR:
		module = new0 EM_P_AccelerateDir();
		break;
	case ID_ENP_PARTICLE_ALPHABYAGE:
		module = new0 EM_P_AlphaByAge();
		break;
	case ID_ENP_PARTICLE_ALPHAINIT:
		module = new0 EM_P_AlphaInit();
		break;
	case ID_ENP_PARTICLE_COLORBYAGE:
		module = new0 EM_P_ColorByAge();
		break;
	case ID_ENP_PARTICLE_COLORINIT:
		module = new0 EM_P_ColorInit();
		break;
	case ID_ENP_PARTICLE_FACEAXISINIT:
		module = new0 EM_P_FaceAxisInit();
		break;
	case ID_ENP_PARTICLE_LIFEINIT:
		module = new0 EM_P_LifeInit();
		break;
	case ID_ENP_PARTICLE_ROTATEDEGREEINIT:
		module = new0 EM_P_RotateDegreeInit();
		break;
	case ID_ENP_PARTICLE_ROTATESPEEDBYAGE:
		module = new0 EM_P_RotateSpeedByAge();
		break;
	case ID_ENP_PARTICLE_ROTATESPEEDINIT:
		module = new0 EM_P_RotateSpeedInit();
		break;
	case ID_ENP_PARTICLE_SIZEBYAGE:
		module = new0 EM_P_SizeByAge();
		break;
	case ID_ENP_PARTICLE_SIZEINIT:
		module = new0 EM_P_SizeInit();
		break;
	case ID_ENP_PARTICLE_SPEEDDIRINIT:
		module = new0 EM_P_SpeedDirInit();
		break;
	case ID_ENP_PARTICLE_SPEEDINIT:
		module = new0 EM_P_SpeedInit();
		break;
	default:
		break;
	}

	ParticleEmitter *emitter = DynamicCast<ParticleEmitter>(mSelectedEffect);
	if (module && emitter)
	{
		bool alreadyHasCtrl = emitter->GetParticleEmitterControl()->IsHasModule(
			module->GetRttiType().GetName());
		if (alreadyHasCtrl)
		{
			wxMessageBox(PX2_LM.GetValue("Tip5"), PX2_LM.GetValue("Tip0"), wxOK);
			return;
		}
		else
		{
			emitter->GetParticleEmitterControl()->AddModule(module);
			OnSelectEffect(emitter);
		}
	}
}
//-----------------------------------------------------------------------------
void EffectNodePanel::RefreshActor (PX2::EffectActor *actor)
{
	mEffectList->Clear();

	if (!actor)
		return;

	EffectNode *node = actor->GetEffect();
	if (!node)
		return;

	for (int i=0; i<node->GetNumChildren(); i++)
	{
		Movable *mov = node->GetChild(i);

		if (mov)
		{
			mEffectList->Append(mov->GetName(), mov);
		}
	}
}
//-----------------------------------------------------------------------------
void EffectNodePanel::OnSelectEffect (PX2::Movable *mov)
{
	mSelectedEffect = mov;

	((EffectInspector*)mParent1)->mEffectPropGrid->SetSelectedEffect(mov);

	mModuleList->Clear();

	ParticleEmitter *emitter = DynamicCast<ParticleEmitter>(mov);
	if (emitter)
	{
		ParticleEmitterController *pec = emitter->GetParticleEmitterControl();
		if (!pec)
			return;

		for (int i=0; i<pec->GetNumModules(); i++)
		{
			EffectModule *module = pec->GetModule(i);
			mModuleList->Append(module->GetName(), module);
		}
	}
}
//-----------------------------------------------------------------------------
void EffectNodePanel::OnSelectModule (PX2::EffectModule *module)
{
	if (mSelectedEffectModule == module)
		return;

	mSelectedEffectModule = module;

	((EffectInspector*)mParent1)->mEffectPropGrid->SetSelectedModule(module);
}
//-----------------------------------------------------------------------------