/*
*
* 文件名称	：	PX2Renderable.cpp
*
*/

#include "PX2Renderable.hpp"
#include "PX2Culler.hpp"
#include "PX2VertexBufferAccessor.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Movable, Renderable);
PX2_IMPLEMENT_STREAM(Renderable);
PX2_IMPLEMENT_ABSTRACT_FACTORY(Renderable);

//----------------------------------------------------------------------------
Renderable::Renderable (PrimitiveType type)
:
mRenderUsageBits(0),
mEyeDistance(0.0f),
mType(type),
mVFormat(0),
mVBuffer(0),
mIBuffer(0),
mMaterial(0)
{
}
//----------------------------------------------------------------------------
Renderable::Renderable (PrimitiveType type, VertexFormat* vformat,
				VertexBuffer* vbuffer, IndexBuffer* ibuffer)
				:
mType(type),
mVFormat(vformat),
mVBuffer(vbuffer),
mIBuffer(ibuffer),
mMaterial(0)
{
	UpdateModelSpace(GU_MODEL_BOUND_ONLY);
}
//----------------------------------------------------------------------------
Renderable::~Renderable ()
{
}
//----------------------------------------------------------------------------
bool Renderable::AddLight (Light *light)
{
	bool bIn = false;

	for (int i=0; i<(int)mInfulencedLights.size(); i++)
	{
		if (light == mInfulencedLights[i])
			bIn = true; 
	}

	if (!bIn)
	{
		mInfulencedLights.push_back(light);
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
bool Renderable::RemoveLight (Light *light)
{
	std::vector<LightPtr>::iterator it = mInfulencedLights.begin();
	for (; it!=mInfulencedLights.end(); it++)
	{
		if (light == *it)
		{
			mInfulencedLights.erase(it);
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void Renderable::ClearLights ()
{
	mInfulencedLights.clear();
}
//----------------------------------------------------------------------------
int Renderable::GetNumLights ()
{
	return (int)mInfulencedLights.size();
}
//----------------------------------------------------------------------------
Light *Renderable::GetLight (int i)
{
	assertion(0<=i && i<(int)mInfulencedLights.size(),
		"i should be in right range.");

	if (0<=i && i<(int)mInfulencedLights.size())
	{
		return mInfulencedLights[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
void Renderable::UpdateModelSpace (UpdateType)
{
	UpdateModelBound();
}
//----------------------------------------------------------------------------
void Renderable::UpdateWorldBound ()
{
	mModelBound.TransformBy(WorldTransform, WorldBound);
}
//----------------------------------------------------------------------------
void Renderable::UpdateModelBound ()
{
	int numVertices = mVBuffer->GetNumElements();
	int stride = mVFormat->GetStride();

	int posIndex = mVFormat->GetIndex(VertexFormat::AU_POSITION);
	if (posIndex == -1)
	{
		assertion(false, "Update requires vertex positions\n");
		return;
	}

	VertexFormat::AttributeType posType =
		mVFormat->GetAttributeType(posIndex);
	if (posType != VertexFormat::AT_FLOAT3
		&&  posType != VertexFormat::AT_FLOAT4)
	{
		assertion(false, "Positions must be 3-tuples or 4-tuples\n");
		return;
	}

	char* data = mVBuffer->GetData();
	int posOffset = mVFormat->GetOffset(posIndex);
	mModelBound.ComputeFromData(numVertices, stride, data + posOffset);
}
//----------------------------------------------------------------------------
void Renderable::GetVisibleSet (Culler& culler, bool)
{
	AdjustTransparent();

	const Camera *camera = culler.GetCamera();

	assertion(camera!=0, "camera must not be 0.");

	AVector cameraDir = camera->GetDVector();
	AVector diff = WorldBound.GetCenter() - camera->GetPosition();

	mEyeDistance = cameraDir.Dot(diff);

	culler.Insert(this);
}
//----------------------------------------------------------------------------
void Renderable::AdjustTransparent ()
{
	if (!mMaterial)
	{
		SetTransparent(false);
		return;
	}

	for (int i=0; i<mMaterial->GetNumPasses(); i++)
	{
		AlphaProperty *alphaProperty =
			mMaterial->GetPass(i)->GetAlphaProperty();
		if (alphaProperty)
		{
			if (alphaProperty->BlendEnabled)
			{
				SetTransparent(true);
				return;
			}
			else
			{
				SetTransparent(false);
				return;
			}
		}
	}

	SetTransparent(false);
}
//----------------------------------------------------------------------------
bool Renderable::LessThan (const Renderable *renderable0,
						   const Renderable *renderable1)
{
	if (renderable0->mSortIndex == renderable1->mSortIndex)
	{
		if (renderable0->IsTransparent())
			return renderable0->mEyeDistance > renderable1->mEyeDistance;
		else
		{
			return renderable0 < renderable1;
		}
	}

	return renderable0->mSortIndex < renderable1->mSortIndex;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Begin load/save
//----------------------------------------------------------------------------
void Renderable::LoadPX2VF (const std::string& name, PrimitiveType& type,
					   VertexFormat*& vformat, VertexBuffer*& vbuffer, IndexBuffer*& ibuffer,
					   int mode)
{
	FileIO inFile(name, mode);
	if (!inFile)
	{
		assertion(false, "Failed to open file %s\n", name.c_str());
		return;
	}

	int iType;
	inFile.Read(sizeof(int), &iType);
	type = (PrimitiveType)iType;

	vformat = LoadVertexFormat(inFile);
	vbuffer = LoadVertexBuffer(inFile, vformat);
	ibuffer = LoadIndexBuffer(inFile);

	inFile.Close();
}
//----------------------------------------------------------------------------
void Renderable::SavePX2VF (const std::string& name, int mode)
{
	FileIO outFile(name, mode);
	if (!outFile)
	{
		assertion(false, "Failed to open file %s\n", name.c_str());
		return;
	}

	int type = (int)mType;
	outFile.Write(sizeof(int), &type);

	SaveVertexFormat(outFile);
	SaveVertexBuffer(outFile);
	SaveIndexBuffer(outFile);

	outFile.Close();
}
//----------------------------------------------------------------------------
VertexFormat* Renderable::LoadVertexFormat (FileIO& inFile)
{
	int numAttributes;
	inFile.Read(sizeof(int), &numAttributes);

	VertexFormat* vformat = new0 VertexFormat(numAttributes);
	for (int i = 0; i < numAttributes; ++i)
	{
		unsigned int streamIndex, offset, usageIndex;
		int type, usage;

		inFile.Read(sizeof(unsigned int), &streamIndex);
		inFile.Read(sizeof(unsigned int), &offset);
		inFile.Read(sizeof(int), &type);
		inFile.Read(sizeof(int), &usage);
		inFile.Read(sizeof(unsigned int), &usageIndex);

		vformat->SetAttribute(i, streamIndex, offset,
			(VertexFormat::AttributeType)type,
			(VertexFormat::AttributeUsage)usage, usageIndex);
	}

	int stride;
	inFile.Read(sizeof(int), &stride);
	vformat->SetStride(stride);

	return vformat;
}
//----------------------------------------------------------------------------
VertexBuffer* Renderable::LoadVertexBuffer (FileIO& inFile, VertexFormat* vformat)
{
	int numElements, elementSize, usage;
	inFile.Read(sizeof(int), &numElements);
	inFile.Read(sizeof(int), &elementSize);
	inFile.Read(sizeof(int), &usage);

	VertexBuffer* vbuffer = new0 VertexBuffer(numElements, elementSize,
		(Buffer::Usage)usage);

	VertexBufferAccessor vba(vformat, vbuffer);
	vba.Read(inFile);

	return vbuffer;
}
//----------------------------------------------------------------------------
IndexBuffer* Renderable::LoadIndexBuffer (FileIO& inFile)
{
	int numElements;
	inFile.Read(sizeof(int), &numElements);

	if (numElements > 0)
	{
		int elementSize, usage, offset;
		inFile.Read(sizeof(int), &elementSize);
		inFile.Read(sizeof(int), &usage);
		inFile.Read(sizeof(int), &offset);

		IndexBuffer* ibuffer = new0 IndexBuffer(numElements, elementSize,
			(Buffer::Usage)usage);
		ibuffer->SetOffset(offset);

		inFile.Read(elementSize, ibuffer->GetNumBytes()/elementSize,
			ibuffer->GetData());

		return ibuffer;
	}

	return 0;
}
//----------------------------------------------------------------------------
void Renderable::SaveVertexFormat (FileIO& outFile)
{
	int numAttributes = mVFormat->GetNumAttributes();
	outFile.Write(sizeof(int), &numAttributes);

	for (int i = 0; i < numAttributes; ++i)
	{
		unsigned int streamIndex, offset, usageIndex;
		VertexFormat::AttributeType vftype;
		VertexFormat::AttributeUsage vfusage;
		mVFormat->GetAttribute(i, streamIndex, offset, vftype, vfusage,
			usageIndex);
		int type = (int)vftype;
		int usage = (int)vfusage;

		outFile.Write(sizeof(unsigned int), &streamIndex);
		outFile.Write(sizeof(unsigned int), &offset);
		outFile.Write(sizeof(int), &type);
		outFile.Write(sizeof(int), &usage);
		outFile.Write(sizeof(unsigned int), &usageIndex);
	}

	int stride = mVFormat->GetStride();
	outFile.Write(sizeof(int), &stride);
}
//----------------------------------------------------------------------------
void Renderable::SaveVertexBuffer (FileIO& outFile)
{
	int numElements = mVBuffer->GetNumElements();
	int elementSize = mVBuffer->GetElementSize();
	Buffer::Usage vbusage = mVBuffer->GetUsage();
	int usage = (int)vbusage;
	outFile.Write(sizeof(int), &numElements);
	outFile.Write(sizeof(int), &elementSize);
	outFile.Write(sizeof(int), &usage);

	VertexBufferAccessor vba(mVFormat, mVBuffer);
	vba.Write(outFile);
}
//----------------------------------------------------------------------------
void Renderable::SaveIndexBuffer (FileIO& outFile)
{
	if (mIBuffer)
	{
		int numElements = mIBuffer->GetNumElements();
		int elementSize = mIBuffer->GetElementSize();
		Buffer::Usage ibusage = mIBuffer->GetUsage();
		int usage = (int)ibusage;
		int offset = mIBuffer->GetOffset();
		outFile.Write(sizeof(int), &numElements);
		outFile.Write(sizeof(int), &elementSize);
		outFile.Write(sizeof(int), &usage);
		outFile.Write(sizeof(int), &offset);

		outFile.Write(elementSize, mIBuffer->GetNumBytes()/elementSize,
			mIBuffer->GetData());
	}
	else
	{
		int numElements = 0;
		outFile.Write(sizeof(int), &numElements);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* Renderable::GetObjectByName (const std::string& name)
{
	Object* found = Movable::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	PX2_GET_OBJECT_BY_NAME(mVFormat, name, found);
	PX2_GET_OBJECT_BY_NAME(mVBuffer, name, found);
	PX2_GET_OBJECT_BY_NAME(mIBuffer, name, found);
	PX2_GET_OBJECT_BY_NAME(mMaterial, name, found);

	return 0;
}
//----------------------------------------------------------------------------
void Renderable::GetAllObjectsByName (const std::string& name,
								  std::vector<Object*>& objects)
{
	Movable::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mVFormat, name, objects);
	PX2_GET_ALL_OBJECTS_BY_NAME(mVBuffer, name, objects);
	PX2_GET_ALL_OBJECTS_BY_NAME(mIBuffer, name, objects);
	PX2_GET_ALL_OBJECTS_BY_NAME(mMaterial, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
Renderable::Renderable (LoadConstructor value)
:
Movable(value),
mType(PT_NONE),
mVFormat(0),
mVBuffer(0),
mIBuffer(0),
mMaterial(0)
{
}
//----------------------------------------------------------------------------
void Renderable::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Movable::Load(source);

	source.ReadEnum(mType);
	source.ReadAggregate(mModelBound);
	source.ReadPointer(mVFormat);
	source.ReadPointer(mVBuffer);
	source.ReadPointer(mIBuffer);
	source.ReadPointer(mMaterial);

	PX2_END_DEBUG_STREAM_LOAD(Renderable, source);
}
//----------------------------------------------------------------------------
void Renderable::Link (InStream& source)
{
	Movable::Link(source);

	source.ResolveLink(mVFormat);
	source.ResolveLink(mVBuffer);
	source.ResolveLink(mIBuffer);
	source.ResolveLink(mMaterial);
}
//----------------------------------------------------------------------------
void Renderable::PostLink ()
{
	Movable::PostLink();
}
//----------------------------------------------------------------------------
bool Renderable::Register (OutStream& target) const
{
	if (Movable::Register(target))
	{
		target.Register(mVFormat);
		target.Register(mVBuffer);
		target.Register(mIBuffer);
		target.Register(mMaterial);
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Renderable::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Movable::Save(target);

	target.WriteEnum(mType);
	target.WriteAggregate(mModelBound);
	target.WritePointer(mVFormat);
	target.WritePointer(mVBuffer);
	target.WritePointer(mIBuffer);
	target.WritePointer(mMaterial);

	PX2_END_DEBUG_STREAM_SAVE(Renderable, target);
}
//----------------------------------------------------------------------------
int Renderable::GetStreamingSize () const
{
	int size = Movable::GetStreamingSize();
	size += PX2_ENUMSIZE(mType);
	size += sizeof(mModelBound);
	size += PX2_POINTERSIZE(mVFormat);
	size += PX2_POINTERSIZE(mVBuffer);
	size += PX2_POINTERSIZE(mIBuffer);
	size += PX2_POINTERSIZE(mMaterial);
	return size;
}
//----------------------------------------------------------------------------