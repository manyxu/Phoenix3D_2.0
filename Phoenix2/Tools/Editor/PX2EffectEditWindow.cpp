/*
*
* 文件名称	：	PX2EffectEditWindow.cpp
*
*/

#include "PX2EffectEditWindow.hpp"
#include "PX2EffectEditTimeLineWindow.hpp"
using namespace PX2Editor;
using namespace PX2;

#define ID_EFFECTNEW wxID_HIGHEST + 1000
#define ID_EFFECTOPEN wxID_HIGHEST + 1001
#define ID_EFFECTSAVE wxID_HIGHEST + 1002
#define ID_EFFECTSAVEAS wxID_HIGHEST + 1003
#define ID_EFFECTDELETE wxID_HIGHEST + 1004
#define ID_EFFECT_ITEMDELETE wxID_HIGHEST + 1005
#define ID_EFFECT_PARTICLEEMITTER wxID_HIGHEST + 1006
#define ID_EFFECTLIST wxID_HIGHEST + 1050

IMPLEMENT_DYNAMIC_CLASS(PX2Editor::EffectEditWindow, wxPanel)
BEGIN_EVENT_TABLE(EffectEditWindow, wxPanel)
	EVT_SIZE(EffectEditWindow::OnSize)
	EVT_MENU(ID_EFFECTNEW, EffectEditWindow::OnNew)
	EVT_MENU(ID_EFFECTOPEN, EffectEditWindow::OnOpen)
	EVT_MENU(ID_EFFECTDELETE, EffectEditWindow::OnDelete)
	EVT_MENU(ID_EFFECTSAVE, EffectEditWindow::OnSave)
	EVT_MENU(ID_EFFECTSAVEAS, EffectEditWindow::OnSaveAs)
	EVT_MENU(ID_EFFECT_ITEMDELETE, EffectEditWindow::OnDeleteEffectItem)
	EVT_MENU(ID_EFFECT_PARTICLEEMITTER, EffectEditWindow::OnNewParticleEmitter)
	EVT_LISTBOX(ID_EFFECTLIST, EffectEditWindow::OnEffectListbox)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
EffectEditWindow::EffectEditWindow ()
:
wxPanel(0, -1),
mToolbar(0),
mEffectList(0)
{
}
//----------------------------------------------------------------------------
EffectEditWindow::EffectEditWindow(wxWindow* parent)
:
wxPanel(parent, -1),
mToolbar(0),
mEffectList(0)
{
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxVERTICAL );
	
	mToolbar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL ); 
	mToolbar->AddTool(ID_EFFECTNEW, _("新建"), 
		wxBitmap( wxT("./ToolRes/Icons/effect_new.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );
	mToolbar->AddTool(ID_EFFECTOPEN, _("打开"), 
		wxBitmap( wxT("./ToolRes/Icons/effect_open.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );
	mToolbar->AddTool(ID_EFFECTDELETE, _("删除"), 
		wxBitmap( wxT("./ToolRes/Icons/effect_delete.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );
	mToolbar->AddTool(ID_EFFECTSAVE, _("存储"), 
		wxBitmap( wxT("./ToolRes/Icons/effect_save.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );
	mToolbar->AddTool(ID_EFFECTSAVEAS, _("另存为"), 
		wxBitmap( wxT("./ToolRes/Icons/effect_saveas.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );
	mToolbar->AddSeparator();

	mToolbar->AddTool(ID_EFFECT_ITEMDELETE, _("删除"), 
		wxBitmap( wxT("./ToolRes/Icons/effect_delete.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );
	mToolbar->AddTool(ID_EFFECT_PARTICLEEMITTER, _("粒子"), 
		wxBitmap( wxT("./ToolRes/Icons/effect_particleemitter.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );

	mToolbar->Realize(); 
	
	bSizer23->Add(mToolbar, 0, wxEXPAND, 5);
	bSizer21->Add(bSizer23, 0, wxEXPAND, 5);
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	mEffectList = new wxListBox( this, ID_EFFECTLIST, wxDefaultPosition, 
		wxSize( 120,-1 ), 0, NULL, wxLB_SINGLE|wxSTATIC_BORDER );
	bSizer22->Add( mEffectList, 0, wxEXPAND, 5 );

	mEffectEditTimeLine = new EffectEditTimeLineWindow(this);
	bSizer22->Add(mEffectEditTimeLine, 1, wxEXPAND, 5);
	
	bSizer21->Add( bSizer22, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer21 );
	this->Layout();
}
//----------------------------------------------------------------------------
EffectEditWindow::~EffectEditWindow()
{
}
//----------------------------------------------------------------------------
void EffectEditWindow::OnSize(wxSizeEvent& e)
{
	wxPanel::OnSize(e);

	wxSize sz = GetSize();

	mEffectEditTimeLine->SetSize(100, 100);

	if (mToolbar)
		mToolbar->Realize();
}
//----------------------------------------------------------------------------
void EffectEditWindow::OnNew (wxCommandEvent &e)
{
	NewEffectEditNode("NoName");
}
//----------------------------------------------------------------------------
void EffectEditWindow::OnOpen (wxCommandEvent &e)
{
	LoadEffectEditNode ();
}
//----------------------------------------------------------------------------
void EffectEditWindow::OnDelete (wxCommandEvent &e)
{
	PX2::EffectNode *selectNode = GetSelectedEffectNode();

	if (selectNode)
	{
		DeleteEffectEditNode(selectNode);
		int selectIndex = mEffectList->GetSelection();
		mEffectList->Delete(selectIndex);

		mEffectEditTimeLine->ClearEffectObjects();
	}
}
//----------------------------------------------------------------------------
void EffectEditWindow::OnSave (wxCommandEvent &e)
{
	SaveEffectEditNode ();
}
//----------------------------------------------------------------------------
void EffectEditWindow::OnSaveAs (wxCommandEvent &e)
{
	int selectID = mEffectList->GetSelection();
	if (selectID < 0)
		return;

	EffectNodeData data = mEffectNodes[selectID];

	wxFileDialog dlg(this,
		wxT("Save Effect"),
		wxEmptyString,
		wxEmptyString,
		wxT("effect (*.pxof)|*.pxof"),
		wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		SaveEffectNode(dlg.GetPath().ToAscii(), data.mNode);
	}
}
//----------------------------------------------------------------------------
void EffectEditWindow::OnDeleteEffectItem (wxCommandEvent &e)
{
	PX2::EffectNode *node = GetSelectedEffectNode();

	DeleteEffectItemOnNode(node,
		mEffectEditTimeLine->GetSelectEffectObject());
}
//----------------------------------------------------------------------------
void EffectEditWindow::OnNewParticleEmitter (wxCommandEvent &e)
{
	PX2::EffectNode *node = GetSelectedEffectNode();

	if (node)
	{
		NewParticleEmitterOnNode(node, "NoName");
	}
}
//----------------------------------------------------------------------------
void EffectEditWindow::DoEnter ()
{

}
//----------------------------------------------------------------------------
void EffectEditWindow::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void EffectEditWindow::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, 
		EditorEventSpace::AddEffectEvent))
	{
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::UpdateEffect))
	{
		mEffectEditTimeLine->Refresh();
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::UpdateEffectNode))
	{
		PX2::EffectNode *node = DynamicCast<PX2::EffectNode>(event
			->GetData<PX2::Movable*>());
		if (node)
		{
			for (int i=0; i<(int)(mEffectList->GetCount()); i++)
			{
				if (mEffectList->GetClientData(i) == (void*)node)
				{
					mEffectList->SetString(i, node->GetName());
					return;
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void EffectEditWindow::DoLeave ()
{

}
//----------------------------------------------------------------------------
void EffectEditWindow::NewEffectEditNode (std::string name)
{
	EffectNodePtr effectNode = new0 EffectNode();
	effectNode->SetName(name);

	int index = mEffectList->Append(name);
	mEffectList->SetClientData(index, effectNode);
	EffectNodeData data(effectNode);
	mEffectNodes.push_back(data);

	ActorPtr actor = new0 Actor();
	actor->SetName(name);
	actor->SetMovable(effectNode);
	actor->ComeInToEventWorld();

	EditSystem::GetSingleton().GetEditMap()->AddActor(actor);

	Event *event = 0;
	event = EditorEventSpace::CreateEvent
		(EditorEventSpace::CreateEditEffectNode);
	event->SetData<Actor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	mEffectEditTimeLine->ResetSelectIndex();
}
//----------------------------------------------------------------------------
void EffectEditWindow::LoadEffectEditNode ()
{
	wxFileDialog dlg(this,
		wxT("Open Effect"),
		wxEmptyString,
		wxEmptyString,
		wxT("effect (*.pxof)|*.pxof"));

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		mEffectEditTimeLine->ResetSelectIndex();

		LoadEffectNode(dlg.GetPath().ToAscii());
	}
}
//----------------------------------------------------------------------------
void EffectEditWindow::DeleteEffectEditNode (PX2::EffectNode *node)
{
	std::vector<EffectNodeData>::iterator it = mEffectNodes.begin();
	for (; it!=mEffectNodes.end(); it++)
	{
		if ((*it).mNode == node)
		{
			mEffectNodes.erase(it);
			break;
		}
	}

	PX2::Actor *actor = EditSystem::GetSingleton().GetEditMap()->GetScene()
		->GetActor(node);

	if (actor)
	{
		actor->GoOutFromEventWorld();
		EditSystem::GetSingleton().GetEditMap()->RemoveActor(actor);
	}
}
//----------------------------------------------------------------------------
bool EffectEditWindow::SaveEffectEditNode ()
{
	int selectID = mEffectList->GetSelection();
	if (selectID < 0)
		return false;

	EffectNodeData data = mEffectNodes[selectID];

	if (data.mPath != "")
	{
		SaveEffectNode(data.mPath, data.mNode);
	}
	else
	{
		wxFileDialog dlg(this,
			wxT("Save Effect Node"),
			wxEmptyString,
			wxEmptyString,
			wxT("effect (*.pxof)|*.pxof"),
			wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

		dlg.CenterOnParent();

		if (dlg.ShowModal() == wxID_OK)
		{
			if (SaveEffectNode(dlg.GetPath().ToAscii(), data.mNode))
			{
				data.mPath = dlg.GetPath().ToAscii();

				return true;
			}
		}
	}

	return false;
}
//----------------------------------------------------------------------------
bool EffectEditWindow::SaveEffectNode (std::string pathname, 
									   PX2::EffectNode *node)
{
	if (!node)
		return false;

	OutStream outStream;

	outStream.Insert(node);

	if (outStream.Save(pathname))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
bool EffectEditWindow::LoadEffectNode (std::string pathname)
{
	InStream inStream;

	if (inStream.Load(pathname))
	{
		Object *object = inStream.GetObjectAt(0);

		EffectNode *effectNode = DynamicCast<EffectNode>(object);
		if (effectNode)
		{
			std::string name = effectNode->GetName();

			int index = mEffectList->Append(name);
			mEffectList->SetClientData(index, effectNode);

			EffectNodeData data(effectNode);
			data.mPath = pathname;
			mEffectNodes.push_back(data);

			ActorPtr actor = new0 Actor();
			actor->SetName(name);
			actor->SetMovable(effectNode);
			actor->ComeInToEventWorld();

			EditSystem::GetSingleton().GetEditMap()->AddActor(actor);

			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void EffectEditWindow::SaveAsEffectEditNode (std::string path)
{

}
//----------------------------------------------------------------------------
void EffectEditWindow::DeleteEffectItemOnNode (EffectNode *node, 
											   Movable *object)
{
	if (!node)
		return;

	PX2_UNUSED(node);

	node->DetachChild(object);
	mEffectEditTimeLine->RemoveEffectObject(object);
}
//----------------------------------------------------------------------------
void EffectEditWindow::NewParticleEmitterOnNode (PX2::EffectNode *node, 
												 std::string name)
{
	if (!node)
		return;

	ParticleEmitter *emitter = new0 ParticleEmitter();
	emitter->SetName(name);
	node->AttachChild(emitter);
	node->Update(0);

	mEffectEditTimeLine->AddEffectObject(emitter);
}
//----------------------------------------------------------------------------
void EffectEditWindow::OnEffectListbox (wxCommandEvent& event)
{
	int selectIndex = mEffectList->GetSelection();
	if (selectIndex < 0)
		return;

	EffectNodeData data = mEffectNodes[selectIndex];

	OnSelectEffectNode(data.mNode);
}
//----------------------------------------------------------------------------
PX2::EffectNode *EffectEditWindow::GetSelectedEffectNode ()
{
	int selectID = mEffectList->GetSelection();

	if (selectID >= 0)
		return mEffectNodes[selectID].mNode;

	return 0;
}
//----------------------------------------------------------------------------
void EffectEditWindow::OnSelectEffectNode (PX2::EffectNode *node)
{
	mEffectEditTimeLine->SelectEffectNode(node);
	
	EditSystem::GetSingleton().GetEffectEdit()->SetEditEffect(node);
}
//----------------------------------------------------------------------------