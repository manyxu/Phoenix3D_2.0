/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIPicBox.hpp
*
*/

#ifndef PX2UIPICBOX_HPP
#define PX2UIPICBOX_HPP

#include "PX2UIPre.hpp"
#include "PX2Float2.hpp"
#include "PX2Size.hpp"
#include "PX2Rect.hpp"
#include "PX2Texture2D.hpp"
#include "PX2Material.hpp"
#include "PX2MaterialInstance.hpp"
#include "PX2TriMesh.hpp"
#include "PX2Camera.hpp"
#include "PX2UIMaterial.hpp"
#include "PX2InputEvent.hpp"
#include "PX2TexPackData.hpp"

namespace PX2
{

	class UIPicBox : public TriMesh
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(UIPicBox);

	public:
		UIPicBox (std::string filename = "Data/images/default.png");
		virtual ~UIPicBox ();

		enum PicBoxType
		{
			PBT_NORMAL,
			PBT_NINE,
			PBT_MAX_TYPE
		};
		void SetPicBoxType (PicBoxType type);
		PicBoxType GetPicBoxType ();

		void SetDynamic (bool dyn);
		bool IsDynamic ();

		// vertexs
		void SetSize (float width, float height);
		void SetSize (const Sizef &size);
		const Sizef &GetSize () const;
		void SetWidth (float width);
		float GetWidth ();
		void SetHeight (float height);
		float GetHeight ();

		void SetColor (Float3 color);
		Float3 GetColor () const;
		void SetAlpha (float alpha); //< 0-1
		float GetAlpha () const;

		// material
		void SetTexture (Texture2D *tex);
		void SetTexture (const std::string &filename);
		void SetTexture (const std::string &texPackName, std::string eleName);
		Texture2D *GetTexture ();
		void SetDoubleSide (bool d);
		bool IsDoubleSide ();

		void SetTexCornorSize (float width, float height);
		void SetTexCornorSize (const Sizef &size);
		const Sizef &GetTexCornorSize ();
		void SetTexCornerWidth (float width);
		float GetTexCornerWidth ();
		void SetTexCornerHeight (float height);
		float GetTexCornerHeight ();

		virtual void UIAfterPicked (int info);

	protected:
		void UpdateBuffers ();
		void UpdateVertexBuffer ();
		void UpdateIndexBuffer ();
		virtual void OnPicked (int info);

		PicBoxType mPicBoxType;
		bool mIsDynamic;

		Sizef mSize;
		Sizef mCorSize;
		Float2 mUV0;
		Float2 mUV1;
		Float2 mUV2;
		Float2 mUV3;
		Float4 mColor;
		TexPackElement mPackEle;

		UIMaterialPtr mUIMtl;
		MaterialInstancePtr mUIMtlInst;
		Texture2DPtr mTexture;
	};

	PX2_REGISTER_STREAM(UIPicBox);
	typedef Pointer0<UIPicBox> UIPicBoxPtr;
#include "PX2UIPicBox.inl"

}

#endif