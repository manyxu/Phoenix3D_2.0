/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2MaterialPropertyGrid.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2MATERIALPROPERTYGRID_HPP
#define PX2MATERIALPROPERTYGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"

namespace PX2Editor
{

	class MaterialPropertyGrid : public ObjectPropertyGrid
	{
	public:
		MaterialPropertyGrid (wxWindow *parent);
		~MaterialPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(MaterialPropertyGrid)

		void SetRenderable (PX2::Renderable *ren); //< 需要用到ren的信息
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

		MaterialPropertyGrid ();
		void RefreshOnMaterial ();

		std::string mMaterialType;

	public:
		PX2::RenderablePtr mRenderable;

		// Texture2D
		std::string mTexture2D_Name;
		PX2::Texture2DPtr mTexture2D_Tex;

		// Property
		bool mWireframe;
	};

}

#endif