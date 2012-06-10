/*
*
* 文件名称	：	PX2Particle.cpp
*
*/

#include "PX2Particle.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Particle::Particle()
{
	SizeU		= 0.1f;
	SizeR		= 0.1f;
	SizeUStep	= 0.0f;
	SizeRStep	= 0.0f;
	Life		= 2.0f;
	Age			= 0.0f;
	EventTime	= 0.0f;
	Color		= Float3(1.0f, 1.0f, 1.0f);
	ColorStep	= Float3(0.0, 0.0f, 0.0f);
	Alpha		= 1.0f;
	AlphaStep	= 0.0f;
	Speed		= 4.0f;
	SpeedStep	= 0.0f;
	SpeedDir	= AVector::UNIT_Z;
	SpeedDirStep= AVector::ZERO;
	Pos			= APoint::ORIGIN;
	PrePos		= APoint::ORIGIN;
	InitialDVector	= AVector::UNIT_Z;
	InitialUVector	= AVector::UNIT_X;
	InitialRVector	= AVector::UNIT_Y;
	DVector			= InitialDVector;
	UVector			= InitialUVector;
	RVector			= InitialRVector;
	RotDegree		= 0.0f;
	RotAxis			= AVector::UNIT_Z;
	RotSpeed		= 0.0f;
	RotSpeedStep	= 0.0f;
}
//----------------------------------------------------------------------------
Particle::~Particle()
{
}
//----------------------------------------------------------------------------
bool Particle::Update (float elapsedTime)
{
	Age += elapsedTime;

	if (Age >= Life)
		return false;

	EventTime += elapsedTime;

	PrePos			=  Pos;
	Speed			+= SpeedStep * elapsedTime;
	SpeedDir		+= SpeedDirStep * elapsedTime;
	Pos				+= SpeedDir * Speed * elapsedTime;
	Color[0]		+= ColorStep[0] * elapsedTime;
	Color[1]		+= ColorStep[1] * elapsedTime;
	Color[2]		+= ColorStep[2] * elapsedTime;
	Alpha			+= AlphaStep * elapsedTime;
	SizeU			+= SizeUStep * elapsedTime;
	SizeR			+= SizeRStep * elapsedTime;
	RotSpeed		+= RotSpeedStep * elapsedTime;
	RotDegree		+= RotSpeed * elapsedTime;

	// 有旋转才进行计算
	if (RotDegree >0.0001f)
	{
		HMatrix matRot(RotAxis, RotDegree);
		UVector = matRot * InitialUVector;
		RVector = matRot * InitialRVector;
	}
	else
	{
		UVector = InitialUVector;
		RVector = InitialRVector;
	}

	return true;
}
//----------------------------------------------------------------------------