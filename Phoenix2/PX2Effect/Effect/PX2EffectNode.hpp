/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EffectNode.hpp
*
* 版本		:	1.0 (2011/12/17)
*
* 作者		：	more
*
*/

#ifndef PX2EFFECTNODE_HPP
#define PX2EFFECTNODE_HPP

#include "PX2EffectPrerequisites.hpp"

namespace PX2
{

	class EffectNode : public Node
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EffectNode);

	public:
		EffectNode ();
		virtual ~EffectNode ();
	};

	PX2_REGISTER_STREAM(EffectNode);
	typedef Pointer0<EffectNode> EffectNodePtr;

}

#endif