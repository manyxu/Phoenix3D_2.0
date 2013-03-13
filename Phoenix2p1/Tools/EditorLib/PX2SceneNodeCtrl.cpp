/*
*
* 文件名称	：	PX2SceneNodeCtrl.cpp
*
*/

#include "PX2SceneNodeCtrl.hpp"
#include "PX2EditSystem.hpp"
#include "PX2SkyActor.hpp"
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
	float radius = 0.065f;
	float height = 0.35f;

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
	vbaX.Color<Float4>(0, 0) = Float4::RED;
	vbaX.Color<Float4>(0, 1) = Float4::RED;

	vbaX.Position<Float3>(2) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaX.Color<Float4>(0, 2) = Float4::RED;
	vbaX.Color<Float4>(0, 3) = Float4::RED;

	vbaX.Position<Float3>(4) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(5) = Float3(0.5f, 0.0f, 0.5f);
	vbaX.Color<Float4>(0, 4) = Float4::RED;
	vbaX.Color<Float4>(0, 5) = Float4::RED;

	Polysegment *polysegmentX = new0 PX2::Polysegment(mVertexFormat, vBufferX,
		false);
	polysegmentX->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeX->AttachChild(polysegmentX);

	TriMesh *meshX = stdMesh.Disk(3, 16, radius);
	meshX->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	meshX->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_Y, 
		-Mathf::HALF_PI));
	meshX->LocalTransform.SetTranslate(APoint(1.125f, 0.0f, 0.0f));
	vBufferTemp = meshX->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.5f, 0.0f, 0.0f, 1.0f);
	}
	nodeX->AttachChild(meshX);

	TriFan *fanX = stdMesh.Cone(16, radius, height);
	fanX->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	fanX->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_Y, 
		Mathf::HALF_PI));
	fanX->LocalTransform.SetTranslate(APoint(1.125f, 0.0f, 0.0f));
	vBufferTemp = fanX->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4::RED;
	}
	nodeX->AttachChild(fanX);

	// y
	PX2::Node *nodeY = new0 PX2::Node;
	nodeX->SetName("Translate_Y");

	VertexBuffer *vBufferY = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaY(mVertexFormat, vBufferY);

	vbaY.Position<Float3>(0) = Float3(0.0f, 0.25f, 0.0f);
	vbaY.Position<Float3>(1) = Float3(0.0f, 1.125f, 0.0f);
	vbaY.Color<Float4>(0, 0) = Float4::GREEN;
	vbaY.Color<Float4>(0, 1) = Float4::GREEN;

	vbaY.Position<Float3>(2) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaY.Color<Float4>(0, 2) = Float4::GREEN;
	vbaY.Color<Float4>(0, 3) = Float4::GREEN;

	vbaY.Position<Float3>(4) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaY.Color<Float4>(0, 4) = Float4::GREEN;
	vbaY.Color<Float4>(0, 5) = Float4::GREEN;

	Polysegment *polysegmentY = new0 PX2::Polysegment(mVertexFormat, vBufferY,
		false);
	polysegmentY->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeY->AttachChild(polysegmentY);

	TriMesh *meshY = stdMesh.Disk(3, 16, radius);
	meshY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	meshY->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		Mathf::HALF_PI));
	meshY->LocalTransform.SetTranslate(APoint(0.0f, 1.125f, 0.0f));
	vBufferTemp = meshY->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 0.5f, 0.0f, 1.0f);
	}
	nodeY->AttachChild(meshY);

	TriFan *fanY = stdMesh.Cone(16, radius, height);
	fanY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	fanY->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		-Mathf::HALF_PI));
	fanY->LocalTransform.SetTranslate(APoint(0.0f, 1.125f, 0.0f));
	vBufferTemp = fanY->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4::GREEN;
	}
	nodeY->AttachChild(fanY);

	// z
	PX2::Node *nodeZ = new0 PX2::Node();
	nodeX->SetName("Translate_Z");

	VertexBuffer *vBufferZ = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaZ(mVertexFormat, vBufferZ);

	vbaZ.Position<Float3>(0) = Float3(0.0f, 0.0f, 0.25f);
	vbaZ.Position<Float3>(1) = Float3(0.0f, 0.0f, 1.125f);
	vbaZ.Color<Float4>(0, 0) = Float4::BLUE;
	vbaZ.Color<Float4>(0, 1) = Float4::BLUE;

	vbaZ.Position<Float3>(2) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(3) = Float3(0.5f, 0.0f, 0.5f);
	vbaZ.Color<Float4>(0, 2) = Float4::BLUE;
	vbaZ.Color<Float4>(0, 3) = Float4::BLUE;

	vbaZ.Position<Float3>(4) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaZ.Color<Float4>(0, 4) = Float4::BLUE;
	vbaZ.Color<Float4>(0, 5) = Float4::BLUE;

	Polysegment *polysegmentZ = new0 PX2::Polysegment(mVertexFormat, vBufferZ,
		false);
	polysegmentZ->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeZ->AttachChild(polysegmentZ);

	TriMesh *meshZ = stdMesh.Disk(3, 16, radius);
	meshZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	meshZ->LocalTransform.SetTranslate(APoint(.0f, 0.0f, 1.125f));
	meshZ->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		Mathf::PI));
	vBufferTemp = meshZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(0.0f, 0.0f, 0.5f, 1.0f);
	}
	nodeZ->AttachChild(meshZ);

	TriFan *fanZ = stdMesh.Cone(16, radius, height);
	fanZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	fanZ->LocalTransform.SetTranslate(APoint(0.0f, 0.0f, 1.125f));
	vBufferTemp = fanZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4::BLUE;
	}
	nodeZ->AttachChild(fanZ);

	// xy
	PX2::Node *nodeXY = new0 Node;
	nodeXY->SetName("Translate_XY");
	TriMesh *meshXY = stdMesh.Rectangle(2, 2, 0.25f, 0.25f);
	meshXY->LocalTransform.SetTranslate(APoint(0.25f, 0.25f, 0.0f));
	VertexColor4Material *matXY = new0 VertexColor4Material();
	matXY->GetAlphaProperty(0, 0)->BlendEnabled = true;
	matXY->GetCullProperty(0, 0)->Enabled = false;
	meshXY->SetMaterialInstance(matXY->CreateInstance());
	vBufferTemp = meshXY->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(1.0f, 1.0f, 0.0f, 0.0f);
	}
	nodeXY->AttachChild(meshXY);

	// yz
	PX2::Node *nodeYZ = new0 Node;
	nodeYZ->SetName("Translate_YZ");
	TriMesh *meshYZ = stdMesh.Rectangle(2, 2, 0.25f, 0.25f);
	meshYZ->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_Y, 
		-Mathf::HALF_PI));
	meshYZ->LocalTransform.SetTranslate(APoint(0.0f, 0.25f, 0.25f));
	VertexColor4Material *matYZ = new0 VertexColor4Material();
	matYZ->GetAlphaProperty(0, 0)->BlendEnabled = true;
	matYZ->GetCullProperty(0, 0)->Enabled = false;
	meshYZ->SetMaterialInstance(matYZ->CreateInstance());
	vBufferTemp = meshYZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(1.0f, 1.0f, 0.0f, 0.0f);
	}
	nodeYZ->AttachChild(meshYZ);

	// xz
	PX2::Node *nodeXZ = new0 Node;
	nodeXZ->SetName("Translate_XZ");
	TriMesh *meshXZ = stdMesh.Rectangle(2, 2, 0.25f, 0.25f);
	meshXZ->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_X, 
		-Mathf::HALF_PI));
		meshXZ->LocalTransform.SetTranslate(APoint(0.25f, 0.0f, 0.25f));
	VertexColor4Material *matXZ = new0 VertexColor4Material();
	matXZ->GetAlphaProperty(0, 0)->BlendEnabled = true;
	matXZ->GetCullProperty(0, 0)->Enabled = false;
	meshXZ->SetMaterialInstance(matXZ->CreateInstance());
	vBufferTemp = meshXZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4(1.0f, 1.0f, 0.0f, 0.0f);
	}
	nodeXZ->AttachChild(meshXZ);

	// XYZ
	node->AttachChild(nodeX);
	node->AttachChild(nodeY);
	node->AttachChild(nodeZ);
	node->AttachChild(nodeXY);
	node->AttachChild(nodeYZ);
	node->AttachChild(nodeXZ);

	return node;
}
//----------------------------------------------------------------------------
PX2::Node *CtrlsFactory::CreateRolateCtrl_P ()
{
	int axisSamples = 4;
	int radialSamples = 12;
	float radial = 0.05f;
	float height = radial*4.0f;	

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

	VertexBuffer *vBufferX = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaX(mVertexFormat, vBufferX);

	vbaX.Position<Float3>(0) = Float3(0.25f, 0.0f, 0.0f);
	vbaX.Position<Float3>(1) = Float3(1.125f, 0.0f, 0.0f);
	vbaX.Color<Float4>(0, 0) = Float4::RED;
	vbaX.Color<Float4>(0, 1) = Float4::RED;

	vbaX.Position<Float3>(2) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaX.Color<Float4>(0, 2) = Float4::GREEN;
	vbaX.Color<Float4>(0, 3) = Float4::GREEN;

	vbaX.Position<Float3>(4) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(5) = Float3(0.5f, 0.0f, 0.5f);
	vbaX.Color<Float4>(0, 4) = Float4::RED;
	vbaX.Color<Float4>(0, 5) = Float4::RED;

	Polysegment *polysegmentX = new0 PX2::Polysegment(mVertexFormat, vBufferX,
		false);
	polysegmentX->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeX->AttachChild(polysegmentX);

	TriMesh *meshX = stdMesh.Cylinder(axisSamples, radialSamples, radial,
		height, false);
	meshX->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	meshX->LocalTransform.SetRotate(HMatrix().MakeRotation(AVector::UNIT_Y,
		Mathf::HALF_PI));
	meshX->LocalTransform.SetTranslate(APoint(1.125f, 0.0f, 0.0f));
	vBufferTemp = meshX->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4::RED;
	}
	nodeX->AttachChild(meshX);

	// y
	PX2::Node *nodeY = new0 PX2::Node;
	nodeX->SetName("Rolate_Y");

	VertexBuffer *vBufferY = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaY(mVertexFormat, vBufferY);

	vbaY.Position<Float3>(0) = Float3(0.0f, 0.25f, 0.0f);
	vbaY.Position<Float3>(1) = Float3(0.0f, 1.125f, 0.0f);
	vbaY.Color<Float4>(0, 0) = Float4::GREEN;
	vbaY.Color<Float4>(0, 1) = Float4::GREEN;

	vbaY.Position<Float3>(2) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaY.Color<Float4>(0, 2) = Float4::GREEN;
	vbaY.Color<Float4>(0, 3) = Float4::GREEN;

	vbaY.Position<Float3>(4) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaY.Color<Float4>(0, 4) = Float4::GREEN;
	vbaY.Color<Float4>(0, 5) = Float4::GREEN;

	Polysegment *polysegmentY = new0 PX2::Polysegment(mVertexFormat, vBufferY,
		false);
	polysegmentY->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeY->AttachChild(polysegmentY);

	TriMesh *meshY = stdMesh.Cylinder(axisSamples, radialSamples, radial,
		height, false);
	meshY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
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

	// z
	PX2::Node *nodeZ = new0 PX2::Node();
	nodeX->SetName("Rolate_Z");

	VertexBuffer *vBufferZ = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaZ(mVertexFormat, vBufferZ);

	vbaZ.Position<Float3>(0) = Float3(0.0f, 0.0f, 0.25f);
	vbaZ.Position<Float3>(1) = Float3(0.0f, 0.0f, 1.125f);
	vbaZ.Color<Float4>(0, 0) = Float4::BLUE;
	vbaZ.Color<Float4>(0, 1) = Float4::BLUE;

	vbaZ.Position<Float3>(2) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(3) = Float3(0.5f, 0.0f, 0.5f);
	vbaZ.Color<Float4>(0, 2) = Float4::BLUE;
	vbaZ.Color<Float4>(0, 3) = Float4::BLUE;

	vbaZ.Position<Float3>(4) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaZ.Color<Float4>(0, 4) = Float4::BLUE;
	vbaZ.Color<Float4>(0, 5) = Float4::BLUE;

	Polysegment *polysegmentZ = new0 PX2::Polysegment(mVertexFormat, vBufferZ,
		false);
	polysegmentZ->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeZ->AttachChild(polysegmentZ);

	TriMesh *meshZ = stdMesh.Cylinder(axisSamples, radialSamples, radial, 
		height, false);
	meshZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	meshZ->LocalTransform.SetTranslate(APoint(.0f, 0.0f, 1.125f));
	vBufferTemp = meshZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4::BLUE;
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
	float boxSize = 0.05f;

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
	vbaX.Color<Float4>(0, 0) = Float4::RED;
	vbaX.Color<Float4>(0, 1) = Float4::RED;

	vbaX.Position<Float3>(2) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaX.Color<Float4>(0, 2) = Float4::RED;
	vbaX.Color<Float4>(0, 3) = Float4::RED;

	vbaX.Position<Float3>(4) = Float3(0.5f, 0.0f, 0.0f);
	vbaX.Position<Float3>(5) = Float3(0.5f, 0.0f, 0.5f);
	vbaX.Color<Float4>(0, 4) = Float4::RED;
	vbaX.Color<Float4>(0, 5) = Float4::RED;

	Polysegment *polysegmentX = new0 PX2::Polysegment(mVertexFormat, vBufferX,
		false);
	polysegmentX->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeX->AttachChild(polysegmentX);

	TriMesh *meshX = stdMesh.Box(boxSize, boxSize, boxSize);
	meshX->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	meshX->LocalTransform.SetTranslate(APoint(1.125f, 0.0f, 0.0f));
	vBufferTemp = meshX->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4::RED;
	}
	nodeX->AttachChild(meshX);

	// y
	PX2::Node *nodeY = new0 PX2::Node;
	nodeX->SetName("Scale_Y");

	VertexBuffer *vBufferY = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaY(mVertexFormat, vBufferY);

	vbaY.Position<Float3>(0) = Float3(0.0f, 0.25f, 0.0f);
	vbaY.Position<Float3>(1) = Float3(0.0f, 1.125f, 0.0f);
	vbaY.Color<Float4>(0, 0) = Float4::GREEN;
	vbaY.Color<Float4>(0, 1) = Float4::GREEN;

	vbaY.Position<Float3>(2) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(3) = Float3(0.5f, 0.5f, 0.0f);
	vbaY.Color<Float4>(0, 2) = Float4::GREEN;
	vbaY.Color<Float4>(0, 3) = Float4::GREEN;

	vbaY.Position<Float3>(4) = Float3(0.0f, 0.5f, 0.0f);
	vbaY.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaY.Color<Float4>(0, 4) = Float4::GREEN;
	vbaY.Color<Float4>(0, 5) = Float4::GREEN;

	Polysegment *polysegmentY = new0 PX2::Polysegment(mVertexFormat, vBufferY,
		false);
	polysegmentY->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeY->AttachChild(polysegmentY);

	TriMesh *meshY = stdMesh.Box(boxSize, boxSize, boxSize);
	meshY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	meshY->LocalTransform.SetTranslate(APoint(0.0f, 1.125f, 0.0f));
	vBufferTemp = meshY->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4::GREEN;
	}
	nodeY->AttachChild(meshY);

	// z
	PX2::Node *nodeZ = new0 PX2::Node();
	nodeX->SetName("Scale_Z");

	VertexBuffer *vBufferZ = new0 VertexBuffer(6, mVertexFormat->GetStride());
	VertexBufferAccessor vbaZ(mVertexFormat, vBufferZ);

	vbaZ.Position<Float3>(0) = Float3(0.0f, 0.0f, 0.25f);
	vbaZ.Position<Float3>(1) = Float3(0.0f, 0.0f, 1.125f);
	vbaZ.Color<Float4>(0, 0) = Float4::BLUE;
	vbaZ.Color<Float4>(0, 1) = Float4::BLUE;

	vbaZ.Position<Float3>(2) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(3) = Float3(0.5f, 0.0f, 0.5f);
	vbaZ.Color<Float4>(0, 2) = Float4::BLUE;
	vbaZ.Color<Float4>(0, 3) = Float4::BLUE;

	vbaZ.Position<Float3>(4) = Float3(0.0f, 0.0f, 0.5f);
	vbaZ.Position<Float3>(5) = Float3(0.0f, 0.5f, 0.5f);
	vbaZ.Color<Float4>(0, 4) = Float4::BLUE;
	vbaZ.Color<Float4>(0, 5) = Float4::BLUE;

	Polysegment *polysegmentZ = new0 PX2::Polysegment(mVertexFormat, vBufferZ,
		false);
	polysegmentZ->SetMaterialInstance(
		VertexColor4Material::CreateUniqueInstance());
	nodeZ->AttachChild(polysegmentZ);

	TriMesh *meshZ = stdMesh.Box(boxSize, boxSize, boxSize);
	meshZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	meshZ->LocalTransform.SetTranslate(APoint(.0f, 0.0f, 1.125f));
	vBufferTemp = meshZ->GetVertexBuffer();
	vbaTemp.ApplyTo(mVertexFormat, vBufferTemp);
	for (int i=0; i<vBufferTemp->GetNumElements(); i++)
	{
		vbaTemp.Color<Float4>(0, i) = Float4::BLUE;
	}
	nodeZ->AttachChild(meshZ);

	// origin
	PX2::Node *nodeXYZ = new0 PX2::Node();
	nodeXYZ->SetName("Scale_XYZ");

	TriMesh *meshXYZ = stdMesh.Box(boxSize, boxSize, boxSize);
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
PX2::Node *CtrlsFactory::CreateBound ()
{
	StandardMesh stdMesh(mVertexFormat);
	float alpha = 0.5f;
	return stdMesh.CircleSphere(1.0f, 32, 
		Float4(1.0f, 0.0f, 0.0f, alpha),
		Float4(0.0f, 1.0f, 0.0f, alpha),
		Float4(0.0f, 0.0f, 1.0f, alpha), true);
}
//----------------------------------------------------------------------------
void CtrlsFactory::UpdateCtrlColor (PX2::Renderer *renderer,
	PX2::Movable *mov, Float4 color)
{
	PX2::Node *node = DynamicCast<Node>(mov);

	if (!node)
		return;

	for (int i=0; i<node->GetNumChildren(); i++)
	{
		PX2::Movable *child = node->GetChild(i);
		PX2::Polysegment *poly = DynamicCast<Polysegment>(child);
		if (poly)
		{
			VertexBuffer *vBuffer = poly->GetVertexBuffer();
			VertexBufferAccessor vba(mVertexFormat, vBuffer);
			for (int i=0; i<vBuffer->GetNumElements(); i++)
			{
				vba.Color<Float4>(0, i) = color;
			}

			renderer->Update(vBuffer);
		}

	}
}
//----------------------------------------------------------------------------
void CtrlsFactory::UpdateCtrlColor1 (PX2::Renderer *renderer,
	PX2::Movable *mov, PX2::Float4 color)
{
	PX2::Node *node = DynamicCast<Node>(mov);

	if (!node)
		return;

	for (int i=0; i<node->GetNumChildren(); i++)
	{
		PX2::Movable *child = node->GetChild(i);
		PX2::TriMesh *mesh = DynamicCast<TriMesh>(child);
		if (mesh)
		{
			VertexBuffer *vBuffer = mesh->GetVertexBuffer();
			VertexBufferAccessor vba(mVertexFormat, vBuffer);
			for (int i=0; i<vBuffer->GetNumElements(); i++)
			{
				vba.Color<Float4>(0, i) = color;
			}

			renderer->Update(vBuffer);
		}

	}
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
	PX2::NodePtr nodeEmpty = new0 PX2::Node();

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
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::OnLeftMouseDown (PX2::Renderer *renderer,
	const PX2::Vector2f &point)
{
	if (EditSystem::GetSingleton().GetEditMode() == EditSystem::EM_SELECT)
		return;

	DragType dt = GetDragType(renderer, point);

	SetDragType(dt);
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::OnLeftMouseUp (PX2::Renderer *renderer,
	const PX2::Vector2f &point)
{
	SetDragType(DT_NONE);

	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::SceneNodeDrag);
	ent->SetData<int>(0);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
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
		float scale = diffLength*0.04f;
		if (scale == 0.0f)
			scale = 0.0001f;
		if (scale < 1.0f)
			scale = 1.0f;
		mCtrlsGroup->WorldTransform.SetUniformScale(scale);
		mCtrlsGroup->Update();
	}
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::OnMouseMove (bool leftDown, PX2::Renderer *renderer,
	PX2::Vector2f posNow, PX2::Vector2f posBefore)
{
	// 光标移动更新
	if (DT_NONE == mDragType)
	{
		CtrlsFactory factory;

		DragType dt = GetDragType(renderer, posNow);
		Movable *ctrlMov = 0;
		Float4 colorYellowAlpha = Float4(1.0f, 1.0f, 0.0f, 0.3f);

		if (DT_X == dt)
		{
			ctrlMov = GetCurrentCtrlX();
			factory.UpdateCtrlColor(renderer, ctrlMov, Float4::YELLOW);
		}
		else if (DT_Y == dt)
		{
			ctrlMov = GetCurrentCtrlY();
			factory.UpdateCtrlColor(renderer, ctrlMov, Float4::YELLOW);
		}
		else if (DT_Z == dt)
		{
			ctrlMov = GetCurrentCtrlZ();
			factory.UpdateCtrlColor(renderer, ctrlMov, Float4::YELLOW);
		}
		else if (DT_XY == dt)
		{
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXY(), colorYellowAlpha);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlYZ(), Float4::ZERO);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXZ(), Float4::ZERO);
		}
		else if (DT_YZ == dt)
		{
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlYZ(), colorYellowAlpha);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXY(), Float4::ZERO);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXZ(), Float4::ZERO);
		}
		else if (DT_XZ == dt)
		{
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXZ(), colorYellowAlpha);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXY(), Float4::ZERO);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlYZ(), Float4::ZERO);
		}
		else if (DT_XYZ == dt)
		{		
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXYZ(), Float4::YELLOW);
		}
		else if (DT_NONE == dt)
		{
			factory.UpdateCtrlColor(renderer, GetCurrentCtrlX(), Float4::RED);
			factory.UpdateCtrlColor(renderer, GetCurrentCtrlY(), Float4::GREEN);
			factory.UpdateCtrlColor(renderer, GetCurrentCtrlZ(), Float4::BLUE);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXY(), Float4::ZERO);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlYZ(), Float4::ZERO);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXZ(), Float4::ZERO);
			factory.UpdateCtrlColor1(renderer, GetCurrentCtrlXYZ(), Float4::WHITE);
		}

		if (DT_NONE == dt)
		{
			Event *ent = EditorEventSpace::CreateEventX(
				EditorEventSpace::SceneNodeDrag);
			ent->SetData<int>(0);
			EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
		}
		else
		{
			Event *ent = EditorEventSpace::CreateEventX(
				EditorEventSpace::SceneNodeDrag);
			ent->SetData<int>(1);
			EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
		}
	}

	// Drag 更新
	if (DT_NONE == mDragType)
	{
		return;
	}
	else
	{
		Event *ent = EditorEventSpace::CreateEventX(
			EditorEventSpace::SceneNodeDrag);
		ent->SetData<int>(1);
		EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
	}

	ObjectSelection *selection = EditSystem::GetSingleton().GetSelection();
	int objNum = selection->GetNumObjects();
	if (0 == objNum)
		return;

	posNow.Y() = renderer->GetHeight() - posNow.Y();
	posBefore.Y() = renderer->GetHeight() - posBefore.Y();

	// get pickPoint with the plane
	TriMesh *meshHelp = EditSystem::GetSingleton().GetXYPlane();
	if (DT_X == mDragType)
	{
		meshHelp = EditSystem::GetSingleton().GetXYPlane();
	}
	else if (DT_Y == mDragType)
	{
		meshHelp = EditSystem::GetSingleton().GetXYPlane();
	}
	else if (DT_Z == mDragType)
	{
		meshHelp = EditSystem::GetSingleton().GetXZPlane();
	}
	else if (DT_XY == mDragType)
	{
		meshHelp = EditSystem::GetSingleton().GetXYPlane();
	}
	else if (DT_YZ == mDragType)
	{
		meshHelp = EditSystem::GetSingleton().GetYZPlane();
	}
	else if (DT_XZ == mDragType)
	{
		meshHelp = EditSystem::GetSingleton().GetXZPlane();
	}
	else if (DT_XYZ == mDragType)
	{
		meshHelp = EditSystem::GetSingleton().GetXYPlane();
	}
	meshHelp->WorldTransform.SetTranslate(GetPosition());

	APoint rayOrigin_Now;
	AVector rayDir_Now;
	renderer->GetPickRay((int)posNow.X(), (int)posNow.Y(), 
		rayOrigin_Now, rayDir_Now);

	APoint rayOrigin_Before;
	AVector rayDir_Before;
	renderer->GetPickRay((int)posBefore.X(), (int)posBefore.Y(), 
		rayOrigin_Before, rayDir_Before);

	Picker pickerNow;
	pickerNow.Execute(meshHelp, rayOrigin_Now, rayDir_Now, 0.0f,
		Mathf::MAX_REAL);
	float lengthNow = pickerNow.GetClosestToZero().T;
	APoint positionNow(rayOrigin_Now + rayDir_Now*lengthNow);

	Picker pickerOrigin;
	pickerOrigin.Execute(meshHelp, rayOrigin_Before, rayDir_Before, 0.0f,
		Mathf::MAX_REAL);
	float lengthBefore = pickerOrigin.GetClosestToZero().T;
	APoint positionBefore(rayOrigin_Before + rayDir_Before*lengthBefore);

	if (pickerNow.Records.empty() || pickerOrigin.Records.empty())
		return;

	AVector transMoved = positionNow - positionBefore;
	AVector transDir = transMoved;
	transDir.Normalize();

	float transValue = 0.0f;
	float transValue1 = 0.0f;
	AVector transVec;
	AVector rolateVec;

	if (DT_X == mDragType)
	{
		transValue = transMoved.Dot(AVector::UNIT_X);
		transVec = AVector::UNIT_X * transValue;

		rolateVec.X() = transMoved.Length() *(1.0f-Mathf::FAbs(transDir.Dot(AVector::UNIT_X)));

		AVector vec = transDir.Cross(AVector::UNIT_X);
		rolateVec.X() *= Mathf::Sign(vec.Z());
	}
	else if (DT_Y == mDragType)
	{
		transValue = transMoved.Dot(AVector::UNIT_Y);
		transVec = AVector::UNIT_Y * transValue;

		rolateVec.Y() = transMoved.Length() *(1.0f-Mathf::FAbs(transDir.Dot(AVector::UNIT_Y)));
		
		AVector vec = transDir.Cross(AVector::UNIT_Y);
		rolateVec.Y() *= Mathf::Sign(vec.Z());
	}
	else if (DT_Z == mDragType)
	{
		transValue = transMoved.Dot(AVector::UNIT_Z);
		transVec = AVector::UNIT_Z * transValue;

		rolateVec.Z() = transMoved.Length() *(1.0f-Mathf::FAbs(transDir.Dot(AVector::UNIT_Z)));

		rolateVec.Z() *= Mathf::Sign(posNow.X() - posBefore.X());
	}
	else if (DT_XY == mDragType)
	{
		transValue = transMoved.Dot(AVector::UNIT_X);
		transValue1 = transMoved.Dot(AVector::UNIT_Y);
		transVec = AVector::UNIT_X * transValue
			+AVector::UNIT_Y * transValue1;
	}
	else if (DT_YZ == mDragType)
	{
		transValue = transMoved.Dot(AVector::UNIT_Y);
		transValue1 = transMoved.Dot(AVector::UNIT_Z);
		transVec = AVector::UNIT_Y * transValue
			+AVector::UNIT_Z * transValue1;
	}
	else if (DT_XZ == mDragType)
	{
		transValue = transMoved.Dot(AVector::UNIT_X);
		transValue1 = transMoved.Dot(AVector::UNIT_Z);
		transVec = AVector::UNIT_X * transValue
			+AVector::UNIT_Z * transValue1;
	}
	else if (DT_XYZ == mDragType)
	{
		float transValue0 = Mathf::FAbs(transMoved.Dot(AVector::UNIT_X));
		float transValue1 = Mathf::FAbs(transMoved.Dot(AVector::UNIT_Y));
		float transValue2 = Mathf::FAbs(transMoved.Dot(AVector::UNIT_Z));

		float trans = (transValue0 + transValue1 + transValue2)/3.0f;
		trans *= Mathf::Sign(transMoved.Y());

		transVec = AVector(trans, trans, trans);
	}

	if (CT_TRANSLATE == mCtrlType)
	{
		EditSystem::GetSingleton().GetSelection()->Translate(transVec);

		UpdateCtrlTrans();
	}
	else if (CT_ROLATE == mCtrlType)
	{
		EditSystem::GetSingleton().GetSelection()->AddRolate(rolateVec);
	}
	else if (CT_SCALE == mCtrlType)
	{
		EditSystem::GetSingleton().GetSelection()->AddScale(transVec);
	}

	Object *obj = EditSystem::GetSingleton().GetSelection()->GetObjectAt(0);
	if (obj)
	{
		Event *event = 0;
		event = EditorEventSpace::CreateEventX(
			EditorEventSpace::ObjectTransformChanged);
		event->SetData<Object*>(obj);
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);
	}

	mCtrlsGroup->Update();
}
//----------------------------------------------------------------------------
PX2::Movable *SceneNodeCtrl::GetCurrentCtrlX ()
{
	int index = mCtrlsGroup->GetActiveChild();
	Node *node = DynamicCast<Node>(mCtrlsGroup->GetChild(index));

	if (!node)
		return 0;

	return node->GetChild(0);
}
//----------------------------------------------------------------------------
PX2::Movable *SceneNodeCtrl::GetCurrentCtrlY ()
{
	int index = mCtrlsGroup->GetActiveChild();
	Node *node = DynamicCast<Node>(mCtrlsGroup->GetChild(index));

	if (!node)
		return 0;
	
	return node->GetChild(1);
}
//----------------------------------------------------------------------------
PX2::Movable *SceneNodeCtrl::GetCurrentCtrlZ ()
{
	int index = mCtrlsGroup->GetActiveChild();
	Node *node = DynamicCast<Node>(mCtrlsGroup->GetChild(index));

	if (!node)
		return 0;

	return node->GetChild(2);
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
PX2::Movable *SceneNodeCtrl::GetCurrentCtrlXY ()
{
	int index = mCtrlsGroup->GetActiveChild();
	Node *node = DynamicCast<Node>(mCtrlsGroup->GetChild(index));

	if (node)
	{
		return node->GetChild(3);
	}

	return 0;
}
//----------------------------------------------------------------------------
PX2::Movable *SceneNodeCtrl::GetCurrentCtrlYZ ()
{
	int index = mCtrlsGroup->GetActiveChild();
	Node *node = DynamicCast<Node>(mCtrlsGroup->GetChild(index));

	if (node)
	{
		return node->GetChild(4);
	}

	return 0;
}
//----------------------------------------------------------------------------
PX2::Movable *SceneNodeCtrl::GetCurrentCtrlXZ ()
{
	int index = mCtrlsGroup->GetActiveChild();
	Node *node = DynamicCast<Node>(mCtrlsGroup->GetChild(index));

	if (node)
	{
		return node->GetChild(5);
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
void SceneNodeCtrl::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::AddSelectObject))
	{
		UpdateCtrl();
		UpdateCtrlTrans();
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::RemoveSelectObject))
	{
		UpdateCtrl();
		UpdateCtrlTrans();
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::ClearSelectObject))
	{
		UpdateCtrl();
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::ObjectTransformChanged))
	{
		UpdateCtrlTrans();
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::UnDo) || EditorEventSpace::IsEqual(event,
		EditorEventSpace::ReDo))
	{
		UpdateCtrlTrans();
		UpdateCtrl();
	}
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::DoLeave ()
{

}
//----------------------------------------------------------------------------
void SceneNodeCtrl::UpdateCtrl ()
{
	int actorNum = EditSystem::GetSingleton().GetSelection()
		->GetNumObjects();

	if (actorNum > 0)
	{
		if (mCtrlType == CT_SELECT)
		{
			mCtrlsGroup->SetActiveChild(6);
		}
		else if (mCtrlType == CT_TRANSLATE)
		{
			if (mLookType == LT_PERSPECTIVE)
			{
				mCtrlsGroup->SetActiveChild(0);
				GetCurrentCtrlX()->Culling = Movable::CULL_DYNAMIC;
				GetCurrentCtrlY()->Culling = Movable::CULL_DYNAMIC;
				GetCurrentCtrlZ()->Culling = Movable::CULL_DYNAMIC;
			}
			else
			{
				mCtrlsGroup->SetActiveChild(3);
				GetCurrentCtrlX()->Culling = Movable::CULL_DYNAMIC;
				GetCurrentCtrlY()->Culling = Movable::CULL_DYNAMIC;
				GetCurrentCtrlZ()->Culling = Movable::CULL_DYNAMIC;

				if (mLookType == LT_TOP)
				{
					GetCurrentCtrlZ()->Culling = Movable::CULL_ALWAYS;
				}
				else if (mLookType == LT_FRONT)
				{
					GetCurrentCtrlY()->Culling = Movable::CULL_ALWAYS;
				}
				else if (mLookType == LT_LEFT)
				{
					GetCurrentCtrlX()->Culling = Movable::CULL_ALWAYS;
				}
			}
		}
		else if (mCtrlType == CT_ROLATE)
		{
			if (mLookType == LT_PERSPECTIVE)
			{
				mCtrlsGroup->SetActiveChild(1);
				GetCurrentCtrlX()->Culling = Movable::CULL_DYNAMIC;
				GetCurrentCtrlY()->Culling = Movable::CULL_DYNAMIC;
				GetCurrentCtrlZ()->Culling = Movable::CULL_DYNAMIC;
			}
			else
			{
				mCtrlsGroup->SetActiveChild(4);
				GetCurrentCtrlX()->Culling = Movable::CULL_DYNAMIC;
				GetCurrentCtrlY()->Culling = Movable::CULL_DYNAMIC;
				GetCurrentCtrlZ()->Culling = Movable::CULL_DYNAMIC;

				if (mLookType == LT_TOP)
				{
					GetCurrentCtrlZ()->Culling = Movable::CULL_ALWAYS;
				}
				else if (mLookType == LT_FRONT)
				{
					GetCurrentCtrlY()->Culling = Movable::CULL_ALWAYS;
				}
				else if (mLookType == LT_LEFT)
				{
					GetCurrentCtrlX()->Culling = Movable::CULL_ALWAYS;
				}
			}

			mCtrlsGroup->Update(0.0);
		}
		else if (mCtrlType == CT_SCALE)
		{
			if (mLookType == LT_PERSPECTIVE)
			{
				mCtrlsGroup->SetActiveChild(2);
				GetCurrentCtrlX()->Culling = Movable::CULL_DYNAMIC;
				GetCurrentCtrlY()->Culling = Movable::CULL_DYNAMIC;
				GetCurrentCtrlZ()->Culling = Movable::CULL_DYNAMIC;
			}
			else
			{
				mCtrlsGroup->SetActiveChild(5);
				GetCurrentCtrlX()->Culling = Movable::CULL_DYNAMIC;
				GetCurrentCtrlY()->Culling = Movable::CULL_DYNAMIC;
				GetCurrentCtrlZ()->Culling = Movable::CULL_DYNAMIC;

				if (mLookType == LT_TOP)
				{
					GetCurrentCtrlZ()->Culling = Movable::CULL_ALWAYS;
				}
				else if (mLookType == LT_FRONT)
				{
					GetCurrentCtrlY()->Culling = Movable::CULL_ALWAYS;
				}
				else if (mLookType == LT_LEFT)
				{
					GetCurrentCtrlX()->Culling = Movable::CULL_ALWAYS;
				}
			}
		}
	}
	else
	{
		mCtrlsGroup->SetActiveChild(6);
	}

	mCtrlsGroup->Update(0.0);
}
//----------------------------------------------------------------------------
void SceneNodeCtrl::UpdateCtrlTrans ()
{
	ObjectSelection *selection = EditSystem::GetSingleton().GetSelection();

	int actorNum = selection->GetNumObjects();

	if (actorNum > 0)
	{
		APoint pos;

		for (int i=0; i<actorNum; i++)
		{
			Actor *actor = DynamicCast<Actor>(selection->GetObjectAt(i));
			if (actor)
				pos += actor->GetPosition();
		}

		pos /= (float)selection->GetNumObjects();

		mCtrlsGroup->WorldTransform.SetTranslate(pos);
	}
	else
	{
		mCtrlsGroup->SetActiveChild(6);
	}

	mCtrlsGroup->Update();
}
//----------------------------------------------------------------------------
SceneNodeCtrl::DragType SceneNodeCtrl::GetDragType (PX2::Renderer *renderer,
	const PX2::Vector2f &point)
{
	APoint origin;
	AVector direction;

	float x = point.X();
	float y = renderer->GetHeight() - point.Y();

	renderer->GetPickRay((int)x, (int)y, origin, direction);

	PX2::Picker picker;

	PX2::Movable *ctrlX = GetCurrentCtrlX();
	PX2::Movable *ctrlY = GetCurrentCtrlY();
	PX2::Movable *ctrlZ = GetCurrentCtrlZ();
	PX2::Movable *ctrlXYZ = GetCurrentCtrlXYZ();
	PX2::Movable *ctrlXY = GetCurrentCtrlXY();
	PX2::Movable *ctrlYZ = GetCurrentCtrlYZ();
	PX2::Movable *ctrlXZ = GetCurrentCtrlXZ();

	bool xDrag = false;
	bool yDrag = false;
	bool zDrag = false;
	bool xyzDrag = false;
	bool xyDrag = false;
	bool yzDrag = false;
	bool xzDrag = false;

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

	float maxLength = Mathf::MAX_REAL;
	picker.Execute(ctrlXY, origin, direction, -Mathf::MAX_REAL, Mathf::MAX_REAL);
	if ((int)picker.Records.size() > 0)
	{
		if (picker.GetClosestNonnegative().T < maxLength)
		{
			xyDrag = true;
			maxLength = picker.GetClosestNonnegative().T;
		}
	}
	else
	{
		picker.Execute(ctrlYZ, origin, direction, -Mathf::MAX_REAL, Mathf::MAX_REAL);
		if ((int)picker.Records.size() > 0)
		{
			if (picker.GetClosestNonnegative().T < maxLength)
			{
				yzDrag = true;
				maxLength = picker.GetClosestNonnegative().T;
			}
		}

		picker.Execute(ctrlXZ, origin, direction, -Mathf::MAX_REAL, Mathf::MAX_REAL);
		if ((int)picker.Records.size() > 0)
		{
			if (picker.GetClosestNonnegative().T < maxLength)
			{
				xzDrag = true;
				maxLength = picker.GetClosestNonnegative().T;
			}
		}
	}

	if (xDrag)
		return DT_X;
	else if (yDrag)
		return DT_Y;
	else if (zDrag)
		return DT_Z;
	else if (xyzDrag)
		return DT_XYZ;
	else if (xyDrag)
		return DT_XY;
	else if (yzDrag)
		return DT_YZ;
	else if (xzDrag)
		return DT_XZ;

	return DT_NONE;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
BoundCtrl::BoundCtrl ()
{
	CtrlsFactory factory;
	mCtrlsGroup = new0 SwitchNode();
	mCtrlsGroup->WorldTransformIsCurrent = true;
	mBoundNode = factory.CreateBound();
	mCtrlsGroup->AttachChild(mBoundNode);
	mCtrlsGroup->AttachChild(new0 Node());
}
//----------------------------------------------------------------------------
BoundCtrl::~BoundCtrl ()
{

}
//----------------------------------------------------------------------------
void BoundCtrl::DoEnter ()
{

}
//----------------------------------------------------------------------------
void BoundCtrl::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::AddSelectObject))
	{
		UpdateCtrl();
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::RemoveSelectObject))
	{
		UpdateCtrl();
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::ClearSelectObject))
	{
		UpdateCtrl();
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::ObjectTransformChanged))
	{
		UpdateCtrl();
	}
	else if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::UnDo) || EditorEventSpace::IsEqual(event,
		EditorEventSpace::ReDo))
	{
		UpdateCtrl();
	}
}
//----------------------------------------------------------------------------
void BoundCtrl::DoLeave ()
{

}
//----------------------------------------------------------------------------
void BoundCtrl::OnLeftMouseDown (PX2::Renderer *renderer,
	const PX2::Vector2f &point)
{
}
//----------------------------------------------------------------------------
void BoundCtrl::OnLeftMouseUp (PX2::Renderer *renderer, 
	const PX2::Vector2f &point)
{
}
//----------------------------------------------------------------------------
void BoundCtrl::OnMouseMove (bool leftDown, PX2::Renderer *renderer,
	PX2::Vector2f posNow, PX2::Vector2f posBefore)
{
}
//----------------------------------------------------------------------------
void BoundCtrl::UpdateCtrl()
{
	mCtrlsGroup->SetActiveChild(1);
	
	ObjectSelection *selection = EditSystem::GetSingleton().GetSelection();
	int actorNum = selection->GetNumObjects();

	APoint pos = APoint::ORIGIN;

	if (actorNum > 0)
	{
		Bound bound;
		int firstBound = true;

		for (int i=0; i<actorNum; i++)
		{
			Actor *actor = DynamicCast<Actor>(selection->GetObjectAt(i));
			SkyActor *skyActor = DynamicCast<SkyActor>(actor);
			if (actor && !skyActor)
			{
				mCtrlsGroup->SetActiveChild(0);

				Movable *mov = actor->GetMovable();
				if (mov)
				{
					pos += mov->WorldTransform.GetTranslate();

					if (firstBound)
					{
						bound = mov->WorldBound;
						firstBound = false;
					}
					else
					{
						bound.GrowToContain(mov->WorldBound);
					}
				}
			}
		}

		pos = pos/(float)actorNum;

		float radius = bound.GetRadius();
		mCtrlsGroup->WorldTransform.SetTranslate(bound.GetCenter());
		if (0.0f == radius)
		{
			radius = 1.0f;
		}
		mCtrlsGroup->WorldTransform.SetUniformScale(radius);
	}

	mCtrlsGroup->Update(0);
}
//----------------------------------------------------------------------------