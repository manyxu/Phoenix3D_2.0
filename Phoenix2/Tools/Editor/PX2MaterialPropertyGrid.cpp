/*
*
* ÎÄ¼þÃû³Æ	£º	PX2MaterialPropertyGrid.cpp
*
*/

#include "PX2MaterialPropertyGrid.hpp"
#include "PX2ObjectNameProperty.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(MaterialPropertyGrid, ObjectPropertyGrid)
	BEGIN_EVENT_TABLE(MaterialPropertyGrid, ObjectPropertyGrid)
	EVT_PG_CHANGED(PGT_ACTOR, MaterialPropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
MaterialPropertyGrid::MaterialPropertyGrid (wxWindow *parent)
:
ObjectPropertyGrid (parent)
{
	mPropertyGridType = PGT_ACTOR;
	mWireframe = false;
}
//-----------------------------------------------------------------------------
MaterialPropertyGrid::~MaterialPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void MaterialPropertyGrid::SetRenderable (PX2::Renderable *ren)
{
	mRenderable = ren;
}
//-----------------------------------------------------------------------------
void MaterialPropertyGrid::OnSetObject(PX2::Object *object)
{
	if (object->IsDerived(Material::TYPE))
	{
		RefreshOnMaterial();
	}
}
//-----------------------------------------------------------------------------
void MaterialPropertyGrid::OnPropertyGridChange (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	PX2::Material *mtl = DynamicCast<Material>(mObject);
	if (mtl)
	{
		mtl->GetWireProperty(0, 0)->Enabled = mWireframe;
	}
}
//-----------------------------------------------------------------------------
void MaterialPropertyGrid::OnPropertyGridChanging (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void MaterialPropertyGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void MaterialPropertyGrid::DoEnter ()
{
	ObjectPropertyGrid::DoEnter();
}
//-----------------------------------------------------------------------------
void MaterialPropertyGrid::DoUpdate ()
{
	ObjectPropertyGrid::DoUpdate();
}
//-----------------------------------------------------------------------------
void MaterialPropertyGrid::DoExecute (PX2::Event *event)
{
}
//-----------------------------------------------------------------------------
void MaterialPropertyGrid::DoLeave ()
{
	ObjectPropertyGrid::DoLeave();
}
//-----------------------------------------------------------------------------
MaterialPropertyGrid::MaterialPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void Texture2D_Callback (Property *prop)
{
	PX2::Object *object = EditSystem::GetSingleton().GetSelectedResource();
	PX2::Texture2D *tex = DynamicCast<PX2::Texture2D>(object);
	if (tex)
	{
		std::string name = tex->GetName();
		prop->mProperty->SetValueFromString(wxString(name.c_str()));

		((MaterialPropertyGrid*)(prop->mParent->mParent))->mTexture2D_Tex
			= tex;
	}
}
//-----------------------------------------------------------------------------
void MaterialPropertyGrid::RefreshOnMaterial ()
{
	Clear();

	if (!mObject)
		return;

	AddPropertyPage("General");
	PropertyPage *page = GetPropertyPage("General");
	page->AddProperty("General", Property::PT_CATEGORY, 0);

	mMaterialType = mObject->GetRttiType().GetName();

	Property *prop = new0 Property(page,"MaterialType", 
		Property::PT_STRING, &mMaterialType);
	prop = new0 ObjectNameProperty(page, "Name", mObject);

	VertexColor4Material *vcm = DynamicCast<VertexColor4Material>(mObject);
	Texture2DMaterial *t2m = DynamicCast<Texture2DMaterial>(mObject);

	if (vcm)
	{
	}
	else if (t2m)
	{
		prop = new0 Property(page, "TextureName", Property::PT_STRINGBUTTON, 
			0);
		prop->SetButtonDownCallback(Texture2D_Callback);
	}

	PX2::Material *mtl = DynamicCast<Material>(mObject);
	if (mtl)
	{
		page->AddProperty("Propertys", Property::PT_CATEGORY, 0);
		page->AddProperty("WireFrame", Property::PT_BOOL, &mWireframe);
	}
	
	mPropGridManager->ExpandAll();
}
//-----------------------------------------------------------------------------