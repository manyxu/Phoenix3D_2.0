/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2SwitchNode.hpp
*
* 版本		:	1.0 (2011/03/17)
*
* 作者		：	more
*
*/

#ifndef PX2SWITCHNODE_HPP
#define PX2SWITCHNODE_HPP

#include "PX2GraphicsPrerequisites.hpp"
#include "PX2Node.hpp"

namespace PX2
{

	class PX2_GRAPHICS_ENTRY SwitchNode : public Node
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(SwitchNode);

	public:
		SwitchNode ();
		virtual ~SwitchNode ();

		enum { SN_INVALID_CHILD = -1 };

		inline void SetActiveChild (int activeChild);
		inline int GetActiveChild () const;
		inline void DisableAllChildren ();

	protected:
		virtual void GetVisibleSet (Culler& culler, bool noCull);

		int mActiveChild;
	};

	PX2_REGISTER_STREAM(SwitchNode);
	typedef Pointer0<SwitchNode> SwitchNodePtr;
#include "PX2SwitchNode.inl"

}

#endif