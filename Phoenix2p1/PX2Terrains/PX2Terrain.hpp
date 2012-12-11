/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Terrain.hpp
*
*/

#ifndef PX2TERRAIN_HPP
#define PX2TERRAIN_HPP

#include "PX2TerrainsPre.hpp"
#include "PX2Node.hpp"
#include "PX2Camera.hpp"

namespace PX2
{

	class Terrain : public Node
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Terrain);

	public:
		virtual ~Terrain ();

		// members
		inline int GetRowQuantity () const;
		inline int GetColQuantity () const;
		inline int GetSize () const;
		inline float GetSpacing () const;
		virtual float GetHeight (float x, float y) const;
		virtual AVector GetNormal (float x, float y) const;

		void OnCameraMotion ();

	protected:
		Terrain();

		int mNumRows, mNumCols;
		int mSize;
		float mMinElevation, mMaxElevation, mSpacing;

		int mCameraRow, mCameraCol;
		CameraPtr mCamera;
	};

	PX2_REGISTER_STREAM(Terrain);
	typedef Pointer0<Terrain> TerrainPtr;
#include "PX2Terrain.inl"

}

#endif