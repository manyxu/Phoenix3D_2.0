/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TextureInspector.cpp
*
*/

#include "PX2TextureInspector.hpp"
#include "PX2ObjectNameProperty.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(TexturePropertyGrid, ObjectPropertyGrid)
	BEGIN_EVENT_TABLE(TexturePropertyGrid, ObjectPropertyGrid)
	EVT_PG_CHANGED(PGT_ACTOR, TexturePropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
TexturePropertyGrid::TexturePropertyGrid ()
{
}
//-----------------------------------------------------------------------------
TexturePropertyGrid::TexturePropertyGrid (wxWindow *parent)
:
ObjectPropertyGrid (parent)
{
	mPropertyGridType = PGT_TEXTURE;
}
//-----------------------------------------------------------------------------
TexturePropertyGrid::~TexturePropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void TexturePropertyGrid::OnSetObject(PX2::Object *object)
{
	if (object->IsDerived(Texture::TYPE))
	{
		RefreshOnTexture();
	}
}
//-----------------------------------------------------------------------------
void TexturePropertyGrid::OnPropertyGridChange (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);
}
//-----------------------------------------------------------------------------
void TexturePropertyGrid::OnPropertyGridChanging (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void TexturePropertyGrid::OnPropertyGridSelect (
	wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void TexturePropertyGrid::DoEnter ()
{
	ObjectPropertyGrid::DoEnter();
}
//-----------------------------------------------------------------------------
void TexturePropertyGrid::DoUpdate ()
{
	ObjectPropertyGrid::DoUpdate();
}
//-----------------------------------------------------------------------------
void TexturePropertyGrid::DoExecute (PX2::Event *event)
{
	ObjectPropertyGrid::DoExecute(event);
}
//-----------------------------------------------------------------------------
void TexturePropertyGrid::DoLeave ()
{
	ObjectPropertyGrid::DoLeave();
}
//-----------------------------------------------------------------------------
void TexturePropertyGrid::RefreshOnTexture ()
{
	Clear();

	if (!mObject)
		return;

	AddPropertyPage("Texture");
	PropertyPage *page = GetPropertyPage("Texture");

	Texture2D *texture = DynamicCast<Texture2D>(mObject);
	if (texture)
	{
		page->AddProperty("Base", Property::PT_CATEGORY, 0);
		Property *prop = new0 ObjectNameProperty(page, "Name", texture);
		PX2_UNUSED(prop);
		int width = texture->GetWidth();
		int height = texture->GetHeight();
		page->AddProperty("Width", Property::PT_INT, &width);
		page->AddProperty("Height", Property::PT_INT, &height);
	}

	mPropGridManager->ExpandAll();
}
//-----------------------------------------------------------------------------