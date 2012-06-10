/*
*
* ÎÄ¼þÃû³Æ	£º	LightActorPropertyGrid.cpp
*
*/

#include "PX2LightActorPropertyGrid.hpp"
#include "wxPropertyExtend.hpp"
#include "PX2ObjectNameProperty.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(LightActorPropertyGrid, ObjectPropertyGrid)
BEGIN_EVENT_TABLE(LightActorPropertyGrid, ObjectPropertyGrid)
EVT_PG_CHANGED(PGT_LIGHTACTOR, LightActorPropertyGrid::OnPropertyGridChange )
END_EVENT_TABLE()

LightActorPropertyGrid::LightActorPropertyGrid (wxWindow *parent)
:
ObjectPropertyGrid (parent)
{
	mPropertyGridType = PGT_LIGHTACTOR;
}
//-----------------------------------------------------------------------------
LightActorPropertyGrid::~LightActorPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void LightActorPropertyGrid::OnSetObject(PX2::Object *object)
{
	if (object->IsExactly(LightActor::TYPE))
	{
		RefreshOnLightActor();
	}
}
//-----------------------------------------------------------------------------
void LightActorPropertyGrid::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	PX2::LightActor *actor = DynamicCast<LightActor>(mObject);
	if (!actor)
		return;

	PX2::LightNode *node = actor->GetLightNode();
	PX2::Light *light = actor->GetLight();

	PX2::APoint pos(mPosition);
	actor->SetPosition(pos);

	PX2::AVector dVec(mDirection);
	PX2::AVector uVec;
	PX2::AVector rVec;
	AVector::GenerateOrthonormalBasis(uVec, rVec, dVec);
	
	HMatrix rotate(dVec, uVec, rVec, APoint::ORIGIN, true);
	node->WorldTransform.SetRotate(rotate);
	node->Update(0);

	light->Ambient = Float4(mAmbientColor[0], mAmbientColor[1], 
		mAmbientColor[2], 1.0f);
	light->Diffuse = Float4(mDiffuseColor[0], mDiffuseColor[1], 
		mDiffuseColor[2], 1.0f);
	light->Specular = Float4(mSpecularColor[0], mSpecularColor[1], 
		mSpecularColor[2], 1.0f);
	light->Constant = mConstant;
	light->Linear = mLinear;
	light->Quadratic = mQuadratic;
	light->Intensity = mIntensity;
}
//-----------------------------------------------------------------------------
void LightActorPropertyGrid::OnPropertyGridChanging (wxPropertyGridEvent
													 &event)
{

}
//-----------------------------------------------------------------------------
void LightActorPropertyGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{

}
//-----------------------------------------------------------------------------
void LightActorPropertyGrid::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void LightActorPropertyGrid::DoUpdate ()
{

}
//-----------------------------------------------------------------------------
void LightActorPropertyGrid::DoExecute (PX2::Event *event)
{
	ObjectPropertyGrid::DoExecute(event);

	if (EditorEventSpace::IsEqual(event, EditorEventSpace::CreateLightActor))
	{
		RefreshOnLightActor();
	}

	if (EditorEventSpace::IsEqual(event, EditorEventSpace::ActorTransformChanged))
	{
		PX2::Actor *actor = DynamicCast<PX2::Actor>(mObject);
		PX2::LightActor *lightActor = PX2::DynamicCast<LightActor>(actor); 
		if (lightActor)
		{
			PropertyPage *page = GetPropertyPage("Light");
			Property *prop = page->GetProperty("Position");
			
			APoint pos = lightActor->GetPosition();

			wxVariant variant;
			variant = Float3ToVariant(Float3(pos[0], pos[1], pos[1]));
			if (prop)
			{
				wxPGProperty *wxProp = prop->GetWxProperty();
				if (wxProp)
					wxProp->SetValue(variant);
			}
		}
	}
}
//-----------------------------------------------------------------------------
void LightActorPropertyGrid::DoLeave ()
{

}
//-----------------------------------------------------------------------------
LightActorPropertyGrid::LightActorPropertyGrid ()
{

}
//-----------------------------------------------------------------------------
void LightActorPropertyGrid::RefreshOnLightActor ()
{
	Clear();

	if (!mObject)
		return;

	PropertyPage *page = AddPropertyPage("Light");

	PX2::Object* object = mObject;
	LightActor *actor = DynamicCast<LightActor>(object);
	PX2::Light *light = actor->GetLight();
	if (light)
	{
		std::string strLightType = "Ambient";
		if (light->GetType() == Light::LT_DIRECTIONAL)
			strLightType = "Directional";
		else if (light->GetType() == Light::LT_POINT)
			strLightType = "Point";
		else if (light->GetType() == Light::LT_SPOT)
			strLightType = "Spot";

		page->AddProperty("Light", Property::PT_CATEGORY, 0);
		Property *prop = new0 ObjectNameProperty(page, "Name", mObject);
		PX2_UNUSED(prop);
		page->AddProperty("Type", Property::PT_STRING, &strLightType);
		page->AddProperty("Transform", Property::PT_CATEGORY, 0);
		mPosition = light->Position;
		mDirection = light->DVector;
		mAngle = light->Angle;
		mAmbientColor = Float3(light->Ambient[0], light->Ambient[1], 
			light->Ambient[2]);
		mDiffuseColor = Float3(light->Diffuse[0], light->Diffuse[1],
			light->Diffuse[2]);
		mSpecularColor = Float3(light->Specular[0], light->Specular[1],
			light->Specular[2]);
		page->AddProperty("Position", Property::PT_FLOAT3, &mPosition);
		page->AddProperty("Direction", Property::PT_FLOAT3, &mDirection);
		page->AddProperty("Angle", Property::PT_FLOAT, &mAngle);

		page->AddProperty("Colors", Property::PT_CATEGORY, 0);
		page->AddProperty("AmbientColor", Property::PT_COLOR3FLOAT3,
			&mAmbientColor);
		page->AddProperty("DiffuseColor", Property::PT_COLOR3FLOAT3,
			&mDiffuseColor);
		page->AddProperty("SpecularColor", Property::PT_COLOR3FLOAT3,
			&mSpecularColor);

		mConstant = light->Constant;
		mLinear = light->Linear;
		mQuadratic = light->Quadratic;
		mIntensity = light->Intensity;
		page->AddProperty("FadeParams", Property::PT_CATEGORY, 0);
		page->AddProperty("Constant", Property::PT_FLOAT, &mConstant);
		page->AddProperty("Linear", Property::PT_FLOAT, &mLinear);
		page->AddProperty("Quadratic", Property::PT_FLOAT, &mQuadratic);
		page->AddProperty("Intensity", Property::PT_FLOAT, &mIntensity);
	}

	mPropGridManager->ExpandAll();
}
//-----------------------------------------------------------------------------