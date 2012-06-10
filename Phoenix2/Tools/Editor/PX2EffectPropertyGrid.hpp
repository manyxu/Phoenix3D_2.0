/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EffectPropertyGrid.hpp
*
* 版本		:	1.0 (2012/01/29)
*
* 作者		：	more
*
*/

#ifndef PX2EFFECTPROPERTYGRID_HPP
#define PX2EFFECTPROPERTYGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"

namespace PX2Editor
{

	class EffectPropertyGrid : public ObjectPropertyGrid
	{
	public:
		EffectPropertyGrid (wxWindow *parent);
		~EffectPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(EffectPropertyGrid)

		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()

		EffectPropertyGrid ();
		void RefreshOnEffect ();

		PX2::EffectNodePtr mEffectNode;
		int mParticleMaxNum;
		std::string mEffectNodeName;
		PX2::MovablePtr mSelectedEffect;
		std::string mSelectedEffectName;
		std::string mTextureName;
	};

}

#endif