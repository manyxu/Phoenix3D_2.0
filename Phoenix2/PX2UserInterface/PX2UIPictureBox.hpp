/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2UIPictureBox.hpp
*
* 版本		:	1.0 (2011/02/23)
*
* 作者		：	more
*
*/

#ifndef PX2UIPICTUREBOX_HPP
#define PX2UIPICTUREBOX_HPP

#include "PX2UIPrerequisites.hpp"
#include "PX2UIElement.hpp"
#include "PX2Texture.hpp"
#include "PX2UIMaterial.hpp"
#include "PX2ScreenTarget.hpp"

namespace PX2
{

	class UIPictureBox : public UIElement
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;

	public:
		UIPictureBox (UIElement *parent, int ID, const std::string &name,
			const std::string &textureName="",
			Float4 color=Float4(1.0f,1.0f,1.0f,1.0f),
			float deltaX=0.0f,
			float deltaY=0.0f,
			float width=100.0f,
			float height=100.0f,
			bool visible=true);
		virtual ~UIPictureBox ();

		void SetTexture (std::string textureName);
		void SetTexture (Texture *texture);

		virtual void SetPosition (float offsetParentX, float offsetParentY);
		virtual void SetSize (float width, float height);
		virtual void Move (float deltaX, float deltaY);

		void SetUV (float uLeftBotton,	float vLeftBotton,
					float uRightUp,		float vRightUp);
		void SetUV (float uLeftBotton,	float vLeftBotton,
					float uRightBotton, float vRightBotton,
					float uRightUp,		float vRightUp,
					float uLeftUp,		float vLeftUp);

		virtual void GetVisibleSet (VisibleSet &set);

		virtual void Draw (Renderer *renderer);

	protected:
		UIPictureBox ();
		void CalculatePostionSize ();

		TexturePtr mTexture;
		Float4 mColor;
		float mULeftTop;
		float mVLeftTop;
		float mURightBotton;
		float mVRightBotton;
		TriMeshPtr mMesh;
		VertexBuffer *mVertexBuffer;
		IndexBuffer *mIndexBuffer;
		VertexBufferAccessor mVBA;
		CameraPtr mCamera;
		MaterialInstancePtr mMaterialInstance;
	};

	typedef Pointer0<UIPictureBox> UIPictureBoxPtr;

}

#endif