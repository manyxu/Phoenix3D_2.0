/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2AxisAlignedBox3.hpp
*
* 版本		:	1.0 (2011/02/19)
*
* 作者		：	more
*
*/

#ifndef PX2AXISALIGNEDBOX3_HPP
#define PX2AXISALIGNEDBOX3_HPP

#include "PX2MathematicsPrerequisites.hpp"
#include "PX2Vector3.hpp"

namespace PX2
{

	/// 坐标轴向盒
	template <typename Real>
	class AxisAlignedBox3
	{
	public:
		AxisAlignedBox3 ();  //< 未初始化
		~AxisAlignedBox3 ();

		/**
		* 调用者必须确保xmin <= xmax，ymin <= ymax，并且zmin <= zmax。
		*/
		AxisAlignedBox3 (Real xmin, Real xmax, Real ymin, Real ymax,
			Real zmin, Real zmax);

		/// 计算盒子中心和延展量（盒子长度的一半）
		void GetCenterExtents (Vector3<Real>& center, Real extent[3]);

		// 重叠（相交）检测（共边或者共面都属于重叠（相交））
		bool HasXOverlap (const AxisAlignedBox3& box) const;
		bool HasYOverlap (const AxisAlignedBox3& box) const;
		bool HasZOverlap (const AxisAlignedBox3& box) const;
		bool TestIntersection (const AxisAlignedBox3& box) const;

		/// 相交检测
		/**
		* 如果两个盒子相交，返回'true'。这样的情况下，相交的部分被存储在
		* 'intersection'中。如果范围为'false'，表明不相交，'intersection'是一个
		* 未定义值。
		*/
		bool FindIntersection (const AxisAlignedBox3& box,
			AxisAlignedBox3& intersection) const;

		Real Min[3], Max[3];
	};

#include "PX2AxisAlignedBox3.inl"

	typedef AxisAlignedBox3<float> AxisAlignedBox3f;
	typedef AxisAlignedBox3<double> AxisAlignedBox3d;

}

#endif