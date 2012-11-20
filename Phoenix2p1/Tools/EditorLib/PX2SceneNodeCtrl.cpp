/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SceneNodeCtrl.cpp
*
*/

#include "PX2SceneNodeCtrl.hpp"
#include "PX2EditSystem.hpp"
using namespace PX2Editor;
using namespace PX2;

//----------------------------------------------------------------------------
CtrlsFactory::CtrlsFactory ()
{
	mVertexFormat = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0);
}
//----------------------------------------------------------------------------
CtrlsFactory::~CtrlsFactory ()
{
	mVertexFormat = 0;
}
//----------------------------------------------------------------------------
PX2::Node *CtrlsFactory::CreateTranslateCtrl_P ()
{
	// node
	PX2::Node *node = new0 Node;
	node->LocalTransform.SetUniformScale(2.0f);
	node->SetName("Translate");

	StandardMesh stdMesh(mVertexFormat);
	VertexBuffer *vBufferTemp = 0;
	VertexBufferAccessor vbaTemp;

	// x
	PX2::Node *nodeX = new0 Node;
	nodeX->SetName("Translate_X");

	VertexBuffer *vBufferX = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaX(mVertexFormat, vBufferX);

	vbaX.Position<Float3>(0) = Float3(0.25f, 0.0f, 0.0f);
	vbaX.Position<Float3>(1) = Float3(1.125f, 0.0f, 0.0f);
	vbaX.Color<Float4>(0, 0) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	vbaX.Color<Float4>(0, 1) = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	vbaX.Position<Float3>(2) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaX.Color<Float4>(0, 2) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	vbaX.Color<Float4>(0, 3) = Float4(0.0f, 1.0f, 0.0f, 1.0f);

	vbaX.Position<Float3>(4) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(5) = Float3(0.5f, 0.0f, 0.5f);
	vbaX.Color<Float4>(0, 4) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	vbaX.Color<Float4>(0, 5) = Float4(0.0f, 0.0f, 1.0f, 1.0f);

	Polysegment *polysegmentX = new0 PX2::Polysegment(mVertexFormat, vBufferX,
		false);
	polysegmentX->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeX->AttachChild(polysegmentX);

	TriMesh *meshX = stdMesh.Disk(3, 20, 0.1f);
	meshX->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshX->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshX->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_Y, 
		-Mathf::HALF_PI));
	meshX->LocalTransform.SetTranslate(APoint(1.125f, 0.0f, 0.0f));
	vBufferTemp = meshX->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	nodeX->AttachChild(meshX);

	TriFan *fanX = stdMesh.Cone(20, 0.1f, 0.45f);
	fanX->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//fanX->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	fanX->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_Y, 
		Mathf::HALF_PI));
	fanX->LocalTransform.SetTranslate(APoint(1.125f, 0.0f, 0.0f));
	vBufferTemp = fanX->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	nodeX->AttachChild(fanX);

	// y
	PX2::Node *nodeY = new0 PX2::Node;
	nodeX->SetName("Translate_Y");

	VertexBuffer *vBufferY = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaY(mVertexFormat, vBufferY);

	vbaY.Position<Float3>(0) = Float3(0.0f, 0.25f, 0.0f);
	vbaY.Position<Float3>(1) = Float3(0.0f, 1.125f, 0.0f);
	vbaY.Color<Float4>(0, 0) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	vbaY.Color<Float4>(0, 1) = Float4(0.0f, 1.0f, 0.0f, 1.0f);

	vbaY.Position<Float3>(2) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaY.Color<Float4>(0, 2) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	vbaY.Color<Float4>(0, 3) = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	vbaY.Position<Float3>(4) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaY.Color<Float4>(0, 4) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	vbaY.Color<Float4>(0, 5) = Float4(0.0f, 0.0f, 1.0f, 1.0f);

	Polysegment *polysegmentY = new0 PX2::Polysegment(mVertexFormat, vBufferY,
		false);
	polysegmentY->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeY->AttachChild(polysegmentY);

	TriMesh *meshY = stdMesh.Disk(3, 20, 0.1f);
	meshY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshY->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshY->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		Mathf::HALF_PI));
	meshY->LocalTransform.SetTranslate(APoint(0.0f, 1.125f, 0.0f));
	vBufferTemp = meshY->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	nodeY->AttachChild(meshY);

	TriFan *fanY = stdMesh.Cone(20, 0.1f, 0.45f);
	fanY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//fanY->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	fanY->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		-Mathf::HALF_PI));
	fanY->LocalTransform.SetTranslate(APoint(0.0f, 1.125f, 0.0f));
	vBufferTemp = fanY->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	nodeY->AttachChild(fanY);

	// z
	PX2::Node *nodeZ = new0 PX2::Node();
	nodeX->SetName("Translate_Z");

	VertexBuffer *vBufferZ = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaZ(mVertexFormat, vBufferZ);

	vbaZ.Position<Float3>(0) = Float3(0.0f, 0.0f, 0.25f);
	vbaZ.Position<Float3>(1) = Float3(0.0f, 0.0f, 1.125f);
	vbaZ.Color<Float4>(0, 0) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	vbaZ.Color<Float4>(0, 1) = Float4(0.0f, 0.0f, 1.0f, 1.0f);

	vbaZ.Position<Float3>(2) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(3) = Float3(0.5f, 0.0f, 0.5f);
	vbaZ.Color<Float4>(0, 2) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	vbaZ.Color<Float4>(0, 3) = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	vbaZ.Position<Float3>(4) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaZ.Color<Float4>(0, 4) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	vbaZ.Color<Float4>(0, 5) = Float4(0.0f, 1.0f, 0.0f, 1.0f);

	Polysegment *polysegmentZ = new0 PX2::Polysegment(mVertexFormat, vBufferZ,
		false);
	polysegmentZ->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeZ->AttachChild(polysegmentZ);

	TriMesh *meshZ = stdMesh.Disk(3, 20, 0.1f);
	meshZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshZ->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshZ->LocalTransform.SetTranslate(APoint(.0f, 0.0f, 1.125f));
	meshZ->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		Mathf::PI));
	vBufferTemp = meshZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	nodeZ->AttachChild(meshZ);

	TriFan *fanZ = stdMesh.Cone(20, 0.1f, 0.45f);
	fanZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//fanZ->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	fanZ->LocalTransform.SetTranslate(APoint(0.0f, 0.0f, 1.125f));
	vBufferTemp = fanZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	nodeZ->AttachChild(fanZ);

	// XYZ
	node->AttachChild(nodeX);
	node->AttachChild(nodeY);
	node->AttachChild(nodeZ);

	return node;
}
//----------------------------------------------------------------------------
PX2::Node *CtrlsFactory::CreateRolateCtrl_P ()
{
	// node
	PX2::Node *node = new0 Node;
	node->LocalTransform.SetUniformScale(2.0f);
	node->SetName("Rolate");

	StandardMesh stdMesh(mVertexFormat);
	VertexBuffer *vBufferTemp = 0;
	VertexBufferAccessor vbaTemp;

	// x
	PX2::Node *nodeX = new0 Node;
	nodeX->SetName("Rolate_X");

	TriMesh *meshX = stdMesh.Torus(40, 10, 1.0f, 0.04f);
	meshX->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshX->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshX->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_Y, 
		-Mathf::HALF_PI));
	vBufferTemp = meshX->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	nodeX->AttachChild(meshX);

	// y
	PX2::Node *nodeY = new0 PX2::Node;
	nodeX->SetName("Rolate_Y");

	TriMesh *meshY = stdMesh.Torus(40, 10, 1.0f, 0.04f);
	meshY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshY->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshY->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		Mathf::HALF_PI));
	vBufferTemp = meshY->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	nodeY->AttachChild(meshY);

	// z
	PX2::Node *nodeZ = new0 PX2::Node();
	nodeX->SetName("Rolate_Z");

	TriMesh *meshZ = stdMesh.Torus(40, 10, 1.0f, 0.04f);
	meshZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshZ->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshZ->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		Mathf::PI));
	vBufferTemp = meshZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	nodeZ->AttachChild(meshZ);

	// XYZ
	node->AttachChild(nodeX);
	node->AttachChild(nodeY);
	node->AttachChild(nodeZ);

	return node;
}
//----------------------------------------------------------------------------
PX2::Node *CtrlsFactory::CreateScaleCtrl_P ()
{
	// node
	PX2::Node *node = new0 Node;
	node->LocalTransform.SetUniformScale(2.0f);
	node->SetName("Scale");

	StandardMesh stdMesh(mVertexFormat);
	VertexBuffer *vBufferTemp = 0;
	VertexBufferAccessor vbaTemp;

	// x
	PX2::Node *nodeX = new0 Node;
	nodeX->SetName("Scale_X");

	VertexBuffer *vBufferX = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaX(mVertexFormat, vBufferX);

	vbaX.Position<Float3>(0) = Float3(0.25f, 0.0f, 0.0f);
	vbaX.Position<Float3>(1) = Float3(1.125f, 0.0f, 0.0f);
	vbaX.Color<Float4>(0, 0) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	vbaX.Color<Float4>(0, 1) = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	vbaX.Position<Float3>(2) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaX.Color<Float4>(0, 2) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	vbaX.Color<Float4>(0, 3) = Float4(0.0f, 1.0f, 0.0f, 1.0f);

	vbaX.Position<Float3>(4) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(5) = Float3(0.5f, 0.0f, 0.5f);
	vbaX.Color<Float4>(0, 4) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	vbaX.Color<Float4>(0, 5) = Float4(0.0f, 0.0f, 1.0f, 1.0f);

	Polysegment *polysegmentX = new0 PX2::Polysegment(mVertexFormat, vBufferX,
		false);
	polysegmentX->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeX->AttachChild(polysegmentX);

	TriMesh *meshX = stdMesh.Box(0.06f, 0.06f, 0.06f);
	meshX->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshX->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshX->LocalTransform.SetTranslate(APoint(1.125f, 0.0f, 0.0f));
	vBufferTemp = meshX->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	nodeX->AttachChild(meshX);

	// y
	PX2::Node *nodeY = new0 PX2::Node;
	nodeX->SetName("Scale_Y");

	VertexBuffer *vBufferY = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaY(mVertexFormat, vBufferY);

	vbaY.Position<Float3>(0) = Float3(0.0f, 0.25f, 0.0f);
	vbaY.Position<Float3>(1) = Float3(0.0f, 1.125f, 0.0f);
	vbaY.Color<Float4>(0, 0) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	vbaY.Color<Float4>(0, 1) = Float4(0.0f, 1.0f, 0.0f, 1.0f);

	vbaY.Position<Float3>(2) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaY.Color<Float4>(0, 2) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	vbaY.Color<Float4>(0, 3) = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	vbaY.Position<Float3>(4) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaY.Color<Float4>(0, 4) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	vbaY.Color<Float4>(0, 5) = Float4(0.0f, 0.0f, 1.0f, 1.0f);

	Polysegment *polysegmentY = new0 PX2::Polysegment(mVertexFormat, vBufferY,
		false);
	polysegmentY->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeY->AttachChild(polysegmentY);

	TriMesh *meshY = stdMesh.Box(0.06f, 0.06f, 0.06f);
	meshY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshY->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshY->LocalTransform.SetTranslate(APoint(0.0f, 1.125f, 0.0f));
	vBufferTemp = meshY->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	nodeY->AttachChild(meshY);

	// z
	PX2::Node *nodeZ = new0 PX2::Node();
	nodeX->SetName("Scale_Z");

	VertexBuffer *vBufferZ = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaZ(mVertexFormat, vBufferZ);

	vbaZ.Position<Float3>(0) = Float3(0.0f, 0.0f, 0.25f);
	vbaZ.Position<Float3>(1) = Float3(0.0f, 0.0f, 1.125f);
	vbaZ.Color<Float4>(0, 0) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	vbaZ.Color<Float4>(0, 1) = Float4(0.0f, 0.0f, 1.0f, 1.0f);

	vbaZ.Position<Float3>(2) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(3) = Float3(0.5f, 0.0f, 0.5f);
	vbaZ.Color<Float4>(0, 2) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	vbaZ.Color<Float4>(0, 3) = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	vbaZ.Position<Float3>(4) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaZ.Color<Float4>(0, 4) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	vbaZ.Color<Float4>(0, 5) = Float4(0.0f, 1.0f, 0.0f, 1.0f);

	Polysegment *polysegmentZ = new0 PX2::Polysegment(mVertexFormat, vBufferZ,
		false);
	polysegmentZ->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeZ->AttachChild(polysegmentZ);

	TriMesh *meshZ = stdMesh.Box(0.06f, 0.06f, 0.06f);
	meshZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshZ->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshZ->LocalTransform.SetTranslate(APoint(.0f, 0.0f, 1.125f));
	vBufferTemp = meshZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	nodeZ->AttachChild(meshZ);

	// origin
	PX2::Node *nodeXYZ = new0 PX2::Node();
	nodeXYZ->SetName("Scale_XYZ");

	TriMesh *meshXYZ = stdMesh.Box(0.06f, 0.06f, 0.06f);
	meshXYZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	vBufferTemp = meshXYZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	nodeXYZ->AttachChild(meshXYZ);

	// XYZ
	node->AttachChild(nodeX);
	node->AttachChild(nodeY);
	node->AttachChild(nodeZ);
	node->AttachChild(nodeXYZ);

	return node;
}
//----------------------------------------------------------------------------
PX2::Node *CtrlsFactory::CreateTranslateCtrl_O ()
{
	// node
	PX2::Node *node = new0 Node;
	node->LocalTransform.SetUniformScale(2.0f);
	node->SetName("Translate");

	StandardMesh stdMesh(mVertexFormat);
	VertexBuffer *vBufferTemp = 0;
	VertexBufferAccessor vbaTemp;

	// x
	PX2::Node *nodeX = new0 Node;
	nodeX->SetName("Translate_X");

	VertexBuffer *vBufferX = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaX(mVertexFormat, vBufferX);

	vbaX.Position<Float3>(0) = Float3(0.25f, 0.0f, 0.0f);
	vbaX.Position<Float3>(1) = Float3(1.125f, 0.0f, 0.0f);
	vbaX.Color<Float4>(0, 0) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	vbaX.Color<Float4>(0, 1) = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	vbaX.Position<Float3>(2) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaX.Color<Float4>(0, 2) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	vbaX.Color<Float4>(0, 3) = Float4(0.0f, 1.0f, 0.0f, 1.0f);

	vbaX.Position<Float3>(4) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(5) = Float3(0.5f, 0.0f, 0.5f);
	vbaX.Color<Float4>(0, 4) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	vbaX.Color<Float4>(0, 5) = Float4(0.0f, 0.0f, 1.0f, 1.0f);

	Polysegment *polysegmentX = new0 PX2::Polysegment(mVertexFormat, vBufferX,
		false);
	polysegmentX->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeX->AttachChild(polysegmentX);

	TriMesh *meshX = stdMesh.Disk(3, 20, 0.1f);
	meshX->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshX->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshX->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_Y, 
		-Mathf::HALF_PI));
	meshX->LocalTransform.SetTranslate(APoint(1.125f, 0.0f, 0.0f));
	vBufferTemp = meshX->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	nodeX->AttachChild(meshX);

	TriFan *fanX = stdMesh.Cone(20, 0.1f, 0.45f);
	fanX->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//fanX->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	fanX->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_Y, 
		Mathf::HALF_PI));
	fanX->LocalTransform.SetTranslate(APoint(1.125f, 0.0f, 0.0f));
	vBufferTemp = fanX->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	nodeX->AttachChild(fanX);

	// y
	PX2::Node *nodeY = new0 PX2::Node;
	nodeX->SetName("Translate_Y");

	VertexBuffer *vBufferY = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaY(mVertexFormat, vBufferY);

	vbaY.Position<Float3>(0) = Float3(0.0f, 0.25f, 0.0f);
	vbaY.Position<Float3>(1) = Float3(0.0f, 1.125f, 0.0f);
	vbaY.Color<Float4>(0, 0) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	vbaY.Color<Float4>(0, 1) = Float4(0.0f, 1.0f, 0.0f, 1.0f);

	vbaY.Position<Float3>(2) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaY.Color<Float4>(0, 2) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	vbaY.Color<Float4>(0, 3) = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	vbaY.Position<Float3>(4) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaY.Color<Float4>(0, 4) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	vbaY.Color<Float4>(0, 5) = Float4(0.0f, 0.0f, 1.0f, 1.0f);

	Polysegment *polysegmentY = new0 PX2::Polysegment(mVertexFormat, vBufferY,
		false);
	polysegmentY->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeY->AttachChild(polysegmentY);

	TriMesh *meshY = stdMesh.Disk(3, 20, 0.1f);
	meshY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshY->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshY->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		Mathf::HALF_PI));
	meshY->LocalTransform.SetTranslate(APoint(0.0f, 1.125f, 0.0f));
	vBufferTemp = meshY->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	nodeY->AttachChild(meshY);

	TriFan *fanY = stdMesh.Cone(20, 0.1f, 0.45f);
	fanY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//fanY->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	fanY->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		-Mathf::HALF_PI));
	fanY->LocalTransform.SetTranslate(APoint(0.0f, 1.125f, 0.0f));
	vBufferTemp = fanY->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	nodeY->AttachChild(fanY);

	// z
	PX2::Node *nodeZ = new0 PX2::Node();
	nodeX->SetName("Translate_Z");

	VertexBuffer *vBufferZ = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaZ(mVertexFormat, vBufferZ);

	vbaZ.Position<Float3>(0) = Float3(0.0f, 0.0f, 0.25f);
	vbaZ.Position<Float3>(1) = Float3(0.0f, 0.0f, 1.125f);
	vbaZ.Color<Float4>(0, 0) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	vbaZ.Color<Float4>(0, 1) = Float4(0.0f, 0.0f, 1.0f, 1.0f);

	vbaZ.Position<Float3>(2) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(3) = Float3(0.5f, 0.0f, 0.5f);
	vbaZ.Color<Float4>(0, 2) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	vbaZ.Color<Float4>(0, 3) = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	vbaZ.Position<Float3>(4) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaZ.Color<Float4>(0, 4) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	vbaZ.Color<Float4>(0, 5) = Float4(0.0f, 1.0f, 0.0f, 1.0f);

	Polysegment *polysegmentZ = new0 PX2::Polysegment(mVertexFormat, vBufferZ,
		false);
	polysegmentZ->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeZ->AttachChild(polysegmentZ);

	TriMesh *meshZ = stdMesh.Disk(3, 20, 0.1f);
	meshZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshZ->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshZ->LocalTransform.SetTranslate(APoint(.0f, 0.0f, 1.125f));
	meshZ->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		Mathf::PI));
	vBufferTemp = meshZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	nodeZ->AttachChild(meshZ);

	TriFan *fanZ = stdMesh.Cone(20, 0.1f, 0.45f);
	fanZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//fanZ->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	fanZ->LocalTransform.SetTranslate(APoint(0.0f, 0.0f, 1.125f));
	vBufferTemp = fanZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	nodeZ->AttachChild(fanZ);

	// XYZ
	node->AttachChild(nodeX);
	node->AttachChild(nodeY);
	node->AttachChild(nodeZ);

	return node;
}
//----------------------------------------------------------------------------
PX2::Node *CtrlsFactory::CreateRolateCtrl_O ()
{
	// node
	PX2::Node *node = new0 Node;
	node->LocalTransform.SetUniformScale(2.0f);
	node->SetName("Rolate");

	StandardMesh stdMesh(mVertexFormat);
	VertexBuffer *vBufferTemp = 0;
	VertexBufferAccessor vbaTemp;

	// x
	PX2::Node *nodeX = new0 Node;
	nodeX->SetName("Rolate_X");

	TriMesh *meshX = stdMesh.Torus(40, 10, 1.0f, 0.04f);;
	meshX->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshX->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshX->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_Y, 
		-Mathf::HALF_PI));
	vBufferTemp = meshX->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	nodeX->AttachChild(meshX);

	// y
	PX2::Node *nodeY = new0 PX2::Node;
	nodeX->SetName("Rolate_Y");

	TriMesh *meshY = stdMesh.Torus(40, 10, 1.0f, 0.04f);;
	meshY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshY->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshY->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		Mathf::HALF_PI));
	vBufferTemp = meshY->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	nodeY->AttachChild(meshY);

	// z
	PX2::Node *nodeZ = new0 PX2::Node();
	nodeX->SetName("Rolate_Z");

	TriMesh *meshZ = stdMesh.Torus(40, 10, 1.0f, 0.04f);;
	meshZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshZ->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshZ->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		Mathf::PI));
	vBufferTemp = meshZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	nodeZ->AttachChild(meshZ);

	// XYZ
	node->AttachChild(nodeX);
	node->AttachChild(nodeY);
	node->AttachChild(nodeZ);

	return node;
}
//----------------------------------------------------------------------------
PX2::Node *CtrlsFactory::CreateScaleCtrl_O ()
{
	// node
	PX2::Node *node = new0 Node;
	node->LocalTransform.SetUniformScale(2.0f);
	node->SetName("Scale");

	StandardMesh stdMesh(mVertexFormat);
	VertexBuffer *vBufferTemp = 0;
	VertexBufferAccessor vbaTemp;

	// x
	PX2::Node *nodeX = new0 Node;
	nodeX->SetName("Scale_X");

	VertexBuffer *vBufferX = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaX(mVertexFormat, vBufferX);

	vbaX.Position<Float3>(0) = Float3(0.25f, 0.0f, 0.0f);
	vbaX.Position<Float3>(1) = Float3(1.125f, 0.0f, 0.0f);
	vbaX.Color<Float4>(0, 0) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	vbaX.Color<Float4>(0, 1) = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	vbaX.Position<Float3>(2) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaX.Color<Float4>(0, 2) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	vbaX.Color<Float4>(0, 3) = Float4(0.0f, 1.0f, 0.0f, 1.0f);

	vbaX.Position<Float3>(4) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(5) = Float3(0.5f, 0.0f, 0.5f);
	vbaX.Color<Float4>(0, 4) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	vbaX.Color<Float4>(0, 5) = Float4(0.0f, 0.0f, 1.0f, 1.0f);

	Polysegment *polysegmentX = new0 PX2::Polysegment(mVertexFormat, vBufferX,
		false);
	polysegmentX->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeX->AttachChild(polysegmentX);

	TriMesh *meshX = stdMesh.Box(0.06f, 0.06f, 0.06f);
	meshX->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshX->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshX->LocalTransform.SetTranslate(APoint(1.125f, 0.0f, 0.0f));
	vBufferTemp = meshX->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	nodeX->AttachChild(meshX);

	// y
	PX2::Node *nodeY = new0 PX2::Node;
	nodeX->SetName("Scale_Y");

	VertexBuffer *vBufferY = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaY(mVertexFormat, vBufferY);

	vbaY.Position<Float3>(0) = Float3(0.0f, 0.25f, 0.0f);
	vbaY.Position<Float3>(1) = Float3(0.0f, 1.125f, 0.0f);
	vbaY.Color<Float4>(0, 0) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	vbaY.Color<Float4>(0, 1) = Float4(0.0f, 1.0f, 0.0f, 1.0f);

	vbaY.Position<Float3>(2) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaY.Color<Float4>(0, 2) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	vbaY.Color<Float4>(0, 3) = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	vbaY.Position<Float3>(4) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaY.Color<Float4>(0, 4) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	vbaY.Color<Float4>(0, 5) = Float4(0.0f, 0.0f, 1.0f, 1.0f);

	Polysegment *polysegmentY = new0 PX2::Polysegment(mVertexFormat, vBufferY,
		false);
	polysegmentY->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeY->AttachChild(polysegmentY);

	TriMesh *meshY = stdMesh.Box(0.06f, 0.06f, 0.06f);
	meshY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshY->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshY->LocalTransform.SetTranslate(APoint(0.0f, 1.125f, 0.0f));
	vBufferTemp = meshY->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	nodeY->AttachChild(meshY);

	// z
	PX2::Node *nodeZ = new0 PX2::Node();
	nodeX->SetName("Scale_Z");

	VertexBuffer *vBufferZ = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaZ(mVertexFormat, vBufferZ);

	vbaZ.Position<Float3>(0) = Float3(0.0f, 0.0f, 0.25f);
	vbaZ.Position<Float3>(1) = Float3(0.0f, 0.0f, 1.125f);
	vbaZ.Color<Float4>(0, 0) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	vbaZ.Color<Float4>(0, 1) = Float4(0.0f, 0.0f, 1.0f, 1.0f);

	vbaZ.Position<Float3>(2) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(3) = Float3(0.5f, 0.0f, 0.5f);
	vbaZ.Color<Float4>(0, 2) = Float4(1.0f, 0.0f, 0.0f, 1.0f);
	vbaZ.Color<Float4>(0, 3) = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	vbaZ.Position<Float3>(4) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaZ.Color<Float4>(0, 4) = Float4(0.0f, 1.0f, 0.0f, 1.0f);
	vbaZ.Color<Float4>(0, 5) = Float4(0.0f, 1.0f, 0.0f, 1.0f);

	Polysegment *polysegmentZ = new0 PX2::Polysegment(mVertexFormat, vBufferZ,
		false);
	polysegmentZ->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeZ->AttachChild(polysegmentZ);

	TriMesh *meshZ = stdMesh.Box(0.06f, 0.06f, 0.06f);
	meshZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	//meshZ->GetMaterialInstance()->GetPass(0)->GetWireProperty()->Enabled = true;
	meshZ->LocalTransform.SetTranslate(APoint(.0f, 0.0f, 1.125f));
	vBufferTemp = meshZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	nodeZ->AttachChild(meshZ);

	// XYZ
	node->AttachChild(nodeX);
	node->AttachChild(nodeY);
	node->AttachChild(nodeZ);

	return node;
}
//----------------------------------------------------------------------------
SceneNodeCtrl::SceneNodeCtrl ()
{
	mOriginScale = 1.0f;

	CtrlsFactory factory;
	mCtrl_P_Translate = factory.CreateTranslateCtrl_P();
	mCtrl_P_Rolate = factory.CreateRolateCtrl_P();
	mCtrl_P_Scale = factory.CreateScaleCtrl_P();
	mCtrl_O_Translate = factory.CreateTranslateCtrl_O();
	mCtrl_O_Rolate = factory.CreateRolateCtrl_O();
	mCtrl_O_Scale = factory.CreateScaleCtrl_O();
	PX2::Node *nodeEmpty = new0 PX2::Node();

	mCtrlsGroup = new SwitchNode();
	mCtrlsGroup->WorldTransformIsCurrent = true;
	mOriginScale = mCtrlsGroup->WorldTransform.GetUniformScale();
	mCtrlsGroup->AttachChild(mCtrl_P_Translate);
	mCtrlsGroup->AttachChild(mCtrl_P_Rolate);
	mCtrlsGroup->AttachChild(mCtrl_P_Scale);
	mCtrlsGroup->AttachChild(mCtrl_O_Translate);
	mCtrlsGroup->AttachChild(mCtrl_O_Rolate);
	mCtrlsGroup->AttachChild(mCtrl_O_Scale);
	mCtrlsGroup->AttachChild(nodeEmpty);

	mLookType = LT_PERSPECTIVE;
	mCtrlType = CT_SELECT;
	mDragType = DT_NONE;
}
//----------------------------------------------------------------------------
SceneNodeCtrl::~SceneNodeCtrl ()
{
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::SetAxisMode (SceneNodeCtrl::AxisMode mode)
{
	mAxisMode = mode;

	UpdateCtrl();
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::SetLookType (SceneNodeCtrl::LookType type)
{
	mLookType = type;

	UpdateCtrl();
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::SetCtrlType (SceneNodeCtrl::CtrlType type)
{
	mCtrlType = type;

	UpdateCtrl();
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::SetDragType (DragType type)
{
	mDragType = type; 

	if (type == DT_X)
	{

	}
	else if (type == DT_Y)
	{

	}
	else if (type == DT_Z)
	{

	}
	else if (type == DT_NONE)
	{

	}
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::OnLeftMouseDown (PX2::Renderer *renderer,
	const PX2::Vector2f &point)
{
	if (EditSystem::GetSingleton().GetEditMode() == EditSystem::EM_SELECT)
		return;

	APoint origin;
	AVector direction;

	float x = renderer->GetWidth() * point.X();
	float y = renderer->GetHeight() * (1.0f - point.Y());

	renderer->GetPickRay((int)x, (int)y, origin, direction);

	PX2::Picker picker;

	PX2::Movable *ctrlX = GetCurrentCtrlX();
	PX2::Movable *ctrlY = GetCurrentCtrlY();
	PX2::Movable *ctrlZ = GetCurrentCtrlZ();
	PX2::Movable *ctrlXYZ = GetCurrentCtrlXYZ();

	bool xDrag = false;
	bool yDrag = false;
	bool zDrag = false;
	bool xyzDrag = false;

	GetCtrlsGroup()->Update();

	picker.Execute(ctrlX, origin, direction, -Mathf::MAX_REAL, Mathf::MAX_REAL);
	if ((int)picker.Records.size() > 0)
		xDrag = true;

	picker.Execute(ctrlY, origin, direction, -Mathf::MAX_REAL, Mathf::MAX_REAL);
	if ((int)picker.Records.size() > 0)
		yDrag = true;

	picker.Execute(ctrlZ, origin, direction, -Mathf::MAX_REAL, Mathf::MAX_REAL);
	if ((int)picker.Records.size() > 0)
		zDrag = true;

	picker.Execute(ctrlXYZ, origin, direction, -Mathf::MAX_REAL, Mathf::MAX_REAL);
	if ((int)picker.Records.size() > 0)
		xyzDrag = true;

	if (xDrag)
		SetDragType(DT_X);
	else if (yDrag)
		SetDragType(DT_Y);
	else if (zDrag)
		SetDragType(DT_Z);
	else if (xyzDrag)
		SetDragType(DT_XYZ);
	else
		SetDragType(DT_NONE);
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::OnLeftMouseUp (PX2::Renderer *renderer,
	const PX2::Vector2f &point)
{
	SetDragType(DT_NONE);
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::OnMouseWheel (PX2::Renderer *renderer, float wheelDelta)
{
	Camera *camera = renderer->GetCamera();
	float rmax = camera->GetRMax();
	APoint cameraPosition = camera->GetPosition();
	APoint ctrlPosition = GetPosition();
	AVector diff = ctrlPosition - cameraPosition;
	float diffLength = diff.Length();

	if (mLookType != LT_PERSPECTIVE)
	{
		mCtrlsGroup->WorldTransform.SetUniformScale(rmax*0.13f);
		mCtrlsGroup->Update();
	}
	else
	{
		mCtrlsGroup->WorldTransform.SetUniformScale(diffLength*0.05f);
		mCtrlsGroup->Update();
	}
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::OnMouseMove (PX2::Renderer *renderer, float x, float y)
{
}
//----------------------------------------------------------------------------
PX2::Movable *SceneNodeCtrl::GetCurrentCtrlX ()
{
	int index = mCtrlsGroup->GetActiveChild();
	Node *node = DynamicCast<Node>(mCtrlsGroup->GetChild(index));

	if (node)
	{
		return node->GetChild(0);
	}

	return 0;
}
//----------------------------------------------------------------------------
PX2::Movable *SceneNodeCtrl::GetCurrentCtrlY ()
{
	int index = mCtrlsGroup->GetActiveChild();
	Node *node = DynamicCast<Node>(mCtrlsGroup->GetChild(index));

	if (node)
	{
		return node->GetChild(1);
	}

	return 0;
}
//----------------------------------------------------------------------------
PX2::Movable *SceneNodeCtrl::GetCurrentCtrlZ ()
{
	int index = mCtrlsGroup->GetActiveChild();
	Node *node = DynamicCast<Node>(mCtrlsGroup->GetChild(index));

	if (node)
	{
		return node->GetChild(2);
	}

	return 0;
}
//----------------------------------------------------------------------------
PX2::Movable *SceneNodeCtrl::GetCurrentCtrlXYZ ()
{
	if (mCtrlType == CT_SCALE)
	{
		int index = mCtrlsGroup->GetActiveChild();
		Node *node = DynamicCast<Node>(mCtrlsGroup->GetChild(index));

		if (node)
		{
			return node->GetChild(3);
		}

	}

	return 0;
}
//----------------------------------------------------------------------------
PX2::APoint SceneNodeCtrl::GetPosition()
{
	return mCtrlsGroup->WorldTransform.GetTranslate();
}
//----------------------------------------------------------------------------
PX2::AVector SceneNodeCtrl::GetXDir ()
{
	HPoint vector;
	mCtrlsGroup->WorldTransform.GetRotate().GetRow(0, vector);
	return AVector(vector.X(), vector.Y(), vector.Z());
}
//----------------------------------------------------------------------------
PX2::AVector SceneNodeCtrl::GetYDir ()
{
	HPoint vector;
	mCtrlsGroup->WorldTransform.GetRotate().GetRow(1, vector);
	return AVector(vector.X(), vector.Y(), vector.Z());
}
//----------------------------------------------------------------------------
PX2::AVector SceneNodeCtrl::GetZDir ()
{
	HPoint vector;
	mCtrlsGroup->WorldTransform.GetRotate().GetRow(2, vector);
	return AVector(vector.X(), vector.Y(), vector.Z());
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::DoEnter ()
{

}
//----------------------------------------------------------------------------
void SceneNodeCtrl::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void SceneNodeCtrl::DoExecute (PX2::Event *event)
{
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::DoLeave ()
{

}
//----------------------------------------------------------------------------
void SceneNodeCtrl::UpdateCtrl ()
{
	mCtrlsGroup->Update();
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::UpdateCtrlTrans ()
{
	mCtrlsGroup->Update();
}
//----------------------------------------------------------------------------