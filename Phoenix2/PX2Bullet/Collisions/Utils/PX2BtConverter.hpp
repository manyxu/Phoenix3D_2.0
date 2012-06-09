/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtConverter.hpp
*
* 版本		:	1.0 (2011/03/07)
*
* 作者		：	more
*
*/

#ifndef PX2_BULLETCONVERTER_HPP
#define PX2_BULLETCONVERTER_HPP

#include "PX2BtPreRequisites.hpp"

namespace TdBt
{

	class PX2_BT_ENTRY Converter
	{
	public:
		Converter ();
		~Converter ();

		static btVector3 ConvertFrom (const PX2::APoint &point);
		static btVector3 ConvertFrom (const PX2::AVector &vec);
		static btVector3 ConvertFrom (const PX2::Vector3f &vec);
		static btQuaternion ConvertFrom (const PX2::HQuaternion &quat);

		static PX2::APoint APointConvertFrom (const btVector3 &point);
		static PX2::AVector AVectorConvertFrom (const btVector3 &vec);
		static PX2::Vector3f Vector3fConvertFrom (const btVector3 &vec);
		static PX2::HQuaternion ConvertFrom (const btQuaternion &quat);
	};

}

#endif