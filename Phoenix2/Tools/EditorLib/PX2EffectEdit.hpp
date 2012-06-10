/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EffectEdit.hpp
*
* 版本		:	1.0 (2011/08/02)
*
* 作者		：	more
*
*/

#ifndef PX2EFFECTEDIT_HPP
#define PX2EFFECTEDIT_HPP

#include "PX2EditorLibPrerequisites.hpp"

namespace PX2Editor
{

	class EffectEdit
	{
	public:
		EffectEdit ();
		~EffectEdit ();

		void SetEditEffectNode (PX2::EffectNode *node);
		PX2::EffectNode *GetEditEffectNode ();

		void SetEditEffect (PX2::Movable *obj);
		PX2::Movable *GetEditEffect ();

		// 当前准备插入事件的时间
		/**
		* 如果获取的时间小于0，不允许插入事件
		*/
		void SetInsertingTime (float insertingTime);
		float GetInsertingTime ();

	private:
		PX2::EffectNodePtr mEffectNode;
		PX2::MovablePtr mEffect;
		float mInsertingTime; // 当前准备插入关键帧的时间
	};
}

#endif