/*
*
* 文件名称	：	PX2SceneBuilderSkinModifier.cpp
*
*/

#include "PX2SceneBuilder.hpp"
using namespace PX2;

void SceneBuilder::ProcessSkin(INode *node, Modifier *skinMod)
{
	// 构造皮肤控制器。如果Max的网格被按照材质细分，每一个网格都需要自己的蒙皮
	// 信息控制器。蒙皮信息中的offset，在动画起始时被计算，是骨骼的世界变换。
	//
	// node:
	//		指向蒙皮修改器指向的Max中的节点。
	// skinMod:
	//		指向蒙皮修改器

	// 1. 获得max蒙皮信息中的骨骼，对应的在Phoenix的骨骼节点列表
	// 2. 获得maxNode影响的Phoenix网格
	// 3. 获得max中每个骨骼所影响的Phoenix网格中的顶点的数量，忽略不受蒙皮信息
	//	  影响的网格
	// 4. 计算Phoenix mesh的蒙皮信息，生成SkinControl，AttachController到
	//    Phoenix mesh上。
	
	// 1

	bool needDel;
	TriObject *triObj = GetTriObject(node, &needDel);
	Mesh *maxMesh = &triObj->GetMesh();

	// Max皮肤控制器接口
	ISkin *skin = (ISkin*)skinMod->GetInterface(I_SKIN);
	ISkinContextData *skinData = skin->GetContextInterface(node);

	// max Skin Bones -> Phoenix2 Skin Bones
	int b, allBoneQuantity = skin->GetNumBones();
	PX2::Node **bones = new1<PX2::Node*>(allBoneQuantity);
	for (b=0; b<allBoneQuantity; b++)
	{
		INode *boneNode = skin->GetBone(b);
		PX2::Node *node = PX2::StaticCast<PX2::Node>(mScene->GetObjectByName(
			boneNode->GetName()));
		bones[b] = node;
	}

	// 1

	// 获得maxNode相关联的Phoenix mesh
	std::vector<PX2::TriMesh*> meshes;
	PX2::Object *object = mScene->GetObjectByName(node->GetName());
	if (object->IsExactly(PX2::TriMesh::TYPE))
	{
		meshes.push_back(PX2::StaticCast<PX2::TriMesh>(object));
	}
	else
	{
		PX2::Node *node = PX2::StaticCast<PX2::Node>(object);
		const char *nName = node->GetName().c_str();
		for (int c=0; c<node->GetNumChildren(); c++)
		{
			PX2::Movable *child = node->GetChild(c);
			const char *cName = child->GetName().c_str();
			if (strncmp(cName, nName, strlen(cName)) == 0)
			{
				meshes.push_back(PX2::StaticCast<PX2::TriMesh>(child));
			}
		}
	}

	// 为Phoenix2的每个网格建立相关的皮肤控制器

	int *vertNumInfuseByBone = new1<int>(allBoneQuantity);
	for (int m=0; m<(int)meshes.size(); m++)
	{
		PX2::TriMesh *mesh = meshes[m];

		// Phoenix顶点在max顶点中的索引
		PX2::VertexBuffer *vb = mesh->GetVertexBuffer();
		int tdMeshVertexNum = vb->GetNumElements();
		std::vector<int> VIArray;
		int v, i, j, k;

		PX2::VertexBufferAccessor vba(mesh->GetVertexFormat(), vb);

		// 3

		for (int v=0; v<tdMeshVertexNum; ++v)
		{
			Float3 &position = vba.Position<Float3>(v);
			for (i=0; i<maxMesh->getNumVerts(); i++)
			{
				if (position[0] == maxMesh->verts[i].x
					&& position[1] == maxMesh->verts[i].y 
					&& position[2] == maxMesh->verts[i].z)
				{
					VIArray.push_back(i);
					break;
				}
			}
		}

		// 确定每个骨骼所影响的顶点数量
		int vertexNumEqualInMax = (int)VIArray.size();
		memset(vertNumInfuseByBone, 0, sizeof(int)*allBoneQuantity);
		for (i=0; i<vertexNumEqualInMax; i++)
		{
			v = VIArray[i];
			for (j=0; j<skinData->GetNumAssignedBones(v); j++)
			{
				b = skinData->GetAssignedBone(v, j);
				vertNumInfuseByBone[b]++;
			}
		}

		// 如果Max的网格是被按照材质分割的，可能一些骨骼对当前Phoenix2网格没有
		// 影响
		int bQuantity = 0; // 影响当前Phoenix2网格的骨骼数量
		for (b=0; b<allBoneQuantity; b++)
		{
			if (vertNumInfuseByBone[b] > 0)
				bQuantity++;
		}

		if (bQuantity == 0)
		{
			// Phoenix网格不被任何骨骼影响，进入下一个网格
			continue;
		}

		// 4

		PX2::Node **theBones = new1<PX2::Node*>(bQuantity);
		float **weight = new2<float>(bQuantity, vertexNumEqualInMax);
		memset(weight[0],0,bQuantity*vertexNumEqualInMax*sizeof(float));
		PX2::APoint **offset = new2<PX2::APoint>(bQuantity, vertexNumEqualInMax);
		memset(offset[0],0,bQuantity*vertexNumEqualInMax*sizeof(PX2::APoint));

		// 计算max骨骼到Phoenix骨骼对应的索引(k)
		std::vector<int> bIArray(allBoneQuantity);
		for (b=0, k=0; b<allBoneQuantity; b++)
		{
			if (vertNumInfuseByBone[b] > 0)
			{
				theBones[k] = bones[b];
				bIArray[b] = k;
				k++;
			}
		}

		// 遍历顶点，计算顶点权重和offset
		for (i=0; i<vertexNumEqualInMax; i++)
		{
			v = VIArray[i];
			for (j=0; j<skinData->GetNumAssignedBones(v); j++)
			{ // 遍历影响该Max顶点的骨骼
				b = skinData->GetAssignedBone(v, j);
				k = bIArray[b];
				float wit = skinData->GetBoneWeight(v, j); // 第j个骨骼的影响权重
				weight[i][k] = wit;

				Float3 &position = vba.Position<Float3>(i);
				APoint point = bones[k]->WorldTransform.Inverse() 
					* (mesh->WorldTransform * APoint(position));
				offset[i][k] = Float3(point.X(), point.Y(), point.Z()); // 在所受影响骨骼中的位置
			}
		}

		PX2::SkinController *skinCtrl = new0 PX2::SkinController
			(vertexNumEqualInMax, bQuantity);
		for (int i=0; i<bQuantity; i++)
		{
			skinCtrl->GetBones()[i] = theBones[i];
		}
		for (int i=0; i<vertexNumEqualInMax; i++)
		{
			for (int j=0; j<bQuantity; j++)
			{
				float wgt = weight[i][j];
				APoint oft = offset[i][j];
				skinCtrl->GetWeights()[i][j] = wgt;
				skinCtrl->GetOffsets()[i][j] = oft; 
			}
		}
		
		skinCtrl->Repeat = Controller::RT_WRAP;
		skinCtrl->MinTime = 0.0f;
		skinCtrl->MaxTime = TicksToSec(mTimeEnd - mTimeStart);

		mesh->AttachController(skinCtrl);

		delete1(theBones);
		delete2(weight);
		delete2(offset);
	}

	if (needDel)
	{
		delete0(triObj);
	}

	delete1(bones);
	delete1(vertNumInfuseByBone);
}
//----------------------------------------------------------------------------