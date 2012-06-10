/*
*
* ÎÄ¼þÃû³Æ	£º	PX2PropertyPage.cpp
*
*/

#include "PX2PropertyPage.hpp"
#include "PX2PropertyGrid.hpp"

using namespace PX2Editor;
using namespace PX2;

PropertyPage::PropertyPage (PropertyGrid *parent, std::string name)
:
mParent(parent),
mName(name)
{
	mParent->mPropGridManager->AddPage(wxT(name.c_str()));
	mPage = mParent->mPropGridManager->GetPage(wxT(name.c_str()));
}
//-----------------------------------------------------------------------------
PropertyPage::~PropertyPage ()
{
	for (int i=0; i<(int)mProperties.size(); i++)
	{
		EventWorld::GetSingleton().GoOut(mProperties[i]);
	}
}
//-----------------------------------------------------------------------------
void PropertyPage::AddProperty (std::string name, Property::PropertyType type,
								void *data)
{
	Property *prop = new0 Property(this, name, type, data);
	PX2_UNUSED(prop);
}
//-----------------------------------------------------------------------------
Property *PropertyPage::GetProperty (std::string name)
{
	for (int i=0; i<(int)mProperties.size(); i++)
	{
		if (name == mProperties[i]->GetName())
			return mProperties[i];
	}

	return 0;
}
//-----------------------------------------------------------------------------
void PropertyPage::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	for (int i=0; i<(int)mProperties.size(); i++)
	{
		mProperties[i]->OnChange(event);
	}
}
//-----------------------------------------------------------------------------
void PropertyPage::OnPropertyGridChanging (wxPropertyGridEvent &event)
{

}
//-----------------------------------------------------------------------------
void PropertyPage::OnPropertyGridSelect (wxPropertyGridEvent &event)
{

}
//-----------------------------------------------------------------------------