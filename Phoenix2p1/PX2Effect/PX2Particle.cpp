/*
*
* 文件名称	：	PX2Particle.cpp
*
*/

#include "PX2Particle.hpp"
#include "PX2HMatrix.hpp"
#include "PX2ParticleEmitter.hpp"
#include "PX2GraphicsRoot.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Particle::Particle()
{
	SizeUInit		= 1.0f;
	SizeRInit		= 1.0f;
	SizeDInit		= 1.0f;
	SizeU			= 1.0f;
	SizeR			= 1.0f;
	SizeD			= 1.0f;
	Life			= 2.0f;
	Age				= 0.0f;
	Color			= Float3(1.0f, 1.0f, 1.0f);
	ColorInit		= Float3(1.0f, 1.0f, 1.0f);
	Alpha			= 1.0f;
	AlphaInit		= 1.0f;
	SpeedInit		= 4.0f;
	Speed			= 4.0f;
	SpeedDirInit	= AVector::UNIT_Z;
	SpeedDir		= AVector::UNIT_Z;
	Accelerate		= 0.0f;
	AccelerateDir	= AVector::ZERO;
	Pos				= APoint::ORIGIN;
	PrePos			= APoint::ORIGIN;
	DVectorInit	= AVector::UNIT_Z;
	UVectorInit	= AVector::UNIT_Y;
	RVectorInit	= AVector::UNIT_X;
	DVector			= DVectorInit;
	UVector			= UVectorInit;
	RVector			= RVectorInit;
	RotSpeedInit	= 0.0f;
	RotSpeed		= 0.0f;
	RotDegreeInit	= 0.0f;
	RotDegree		= 0.0f;
}
//----------------------------------------------------------------------------
Particle::~Particle()
{
}
//----------------------------------------------------------------------------
bool Particle::Update (ParticleEmitter *emitter, float elapsedTime)
{
	if (!emitter)
		return false;

	Camera *camera = GraphicsRoot::GetSingleton().GetCamera();
	ParticleEmitter::FaceType faceType = emitter->GetFaceType();
	ParticleEmitter::RotateAxisType rotateAxisType = emitter->GetRotateAxisType();

	// life
	Age += elapsedTime;
	if (Age >= Life)
		return false;

	PrePos			=  Pos;

	// speed
	AVector spdir	= Speed * SpeedDir;
	AVector acdir	= Accelerate * AccelerateDir;
	AVector speedDir= spdir + acdir * elapsedTime;
	Pos				+= speedDir * elapsedTime;
	float spLength	= speedDir.Normalize();
	Speed			= spLength;
	SpeedDir		= speedDir;

	// rotate
	RotDegree		+= RotSpeed * elapsedTime;

	// d u r
	if (ParticleEmitter::FT_CAMERA == faceType)
	{
		DVector = camera->GetDVector();
		UVector = camera->GetUVector();
		RVector = camera->GetRVector();
		DVectorInit = DVector;
		UVectorInit = UVector;
		RVectorInit = RVector;
	}
	else if (ParticleEmitter::FT_SPEEDDIR == faceType)
	{
		DVector = SpeedDir;

		if (DVector != AVector::UNIT_Z)
		{
			RVector = AVector::UNIT_Z.Cross(DVector);
			RVector.Normalize();

			UVector = DVector.Cross(RVector);
			UVector.Normalize();
		}
		else
		{
			RVector = AVector::UNIT_X;
			UVector = AVector::UNIT_Y;
		}
		DVectorInit = DVector;
		UVectorInit = UVector;
		RVectorInit = RVector;
	}
	// else if (ParticleEmitter::FT_FREE == faceType)

	// 有旋转才进行计算
	if (RotDegree != 0.0f)
	{
		AVector rotAxis = AVector::UNIT_Z;

		if (rotateAxisType == ParticleEmitter::RAT_D)
		{
			rotAxis = DVector;

			HMatrix matRot(rotAxis, RotDegree);
			UVector = matRot * UVectorInit;
			RVector = matRot * RVectorInit;
		}
		else if (rotateAxisType == ParticleEmitter::RAT_U)
		{
			rotAxis = UVector;

			HMatrix matRot(rotAxis, RotDegree);
			DVector = matRot * DVectorInit;
			RVector = matRot * RVectorInit;
		}
		else if (rotateAxisType == ParticleEmitter::RAT_R)
		{
			rotAxis = RVector;

			HMatrix matRot(rotAxis, RotDegree);
			DVector = matRot * DVectorInit;
			UVector = matRot * UVectorInit;
		}
	}

	return true;
}
//----------------------------------------------------------------------------