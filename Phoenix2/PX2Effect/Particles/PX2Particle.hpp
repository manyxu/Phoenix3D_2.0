/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Particle.hpp
*
* 版本		:	1.0 (2011/12/17)
*
* 作者		：	more
*
*/

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "PX2EffectPrerequisites.hpp"

namespace PX2
{

	class EffectEvent;

	/// 粒子
	class Particle
	{
	public:
		Particle ();
		~Particle ();

		float		SizeU;
		float		SizeR;
		float		SizeUStep;
		float		SizeRStep;

		float		Life;
		float		Age;
		float		EventTime;

		Float3		Color;
		Float3		ColorStep;
		float		Alpha;
		float		AlphaStep;

		APoint		Pos;
		APoint		PrePos;

		AVector		InitialDVector;
		AVector		InitialUVector;
		AVector		InitialRVector;
		AVector		DVector;
		AVector		UVector;
		AVector		RVector;

		AVector		RotAxis;
		float		RotDegree;		//< 弧度
		float		RotSpeed;
		float		RotSpeedStep;

		float		Speed;
		float		SpeedStep;
		AVector		SpeedDir;
		AVector		SpeedDirStep;

		std::vector<PX2::Pointer0<PX2::EffectEvent> >::iterator CurEvent; //< 当前粒子执行的事件

		bool Update (float elapsedTime);
	};

}

#endif