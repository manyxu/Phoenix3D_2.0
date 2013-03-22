/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ControllerPropertyGrid.cpp
*
*/

#include "PX2ControllerPropertyGrid.hpp"
#include "PX2ObjectNameProperty.hpp"
#include "PX2LanguageManager.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(ControllerPropertyGrid, ObjectPropertyGrid)
BEGIN_EVENT_TABLE(ControllerPropertyGrid, ObjectPropertyGrid)
EVT_PG_CHANGED(PGT_CONTROL, ControllerPropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
ControllerPropertyGrid::ControllerPropertyGrid (wxWindow *parent)
	:
ObjectPropertyGrid (parent)
{

}
//-----------------------------------------------------------------------------
ControllerPropertyGrid::~ControllerPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void ControllerPropertyGrid::OnSetObject(PX2::Object *object)
{
	Clear();

	mObjectType = mObject->GetRttiType().GetName();

	AddPropertyPage("General");
	PropertyPage *page = GetPropertyPage("General");
	page->AddProperty(PX2_LM.GetValue("General"), Property::PT_CATEGORY, 0);

	Controlledable *ctrlAble = DynamicCast<Controlledable>(mObject);

	Property *nameProp = new0 ObjectNameProperty(page, PX2_LM.GetValue("Name"),
		mObject);
	Property *propType = new0 Property(page, PX2_LM.GetValue("Type"),
		Property::PT_STRING, &mObjectType, false);
}
//-----------------------------------------------------------------------------
void ControllerPropertyGrid::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);
}
//-----------------------------------------------------------------------------
void ControllerPropertyGrid::OnPropertyGridChanging (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void ControllerPropertyGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
ControllerPropertyGrid::ControllerPropertyGrid ()
{
}
//-----------------------------------------------------------------------------