/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2SkinController.hpp
*
* 版本		:	1.0 (2011/02/01)
*
* 作者		：	more
*
*/

#ifndef PX2SKINCONTROLLER_HPP
#define PX2SKINCONTROLLER_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Controller.hpp"
#include "PX2Node.hpp"
#include "PX2Vector3.hpp"

namespace PX2
{

	class SkinController : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(SkinController);

	public:
		// Construction and destruction.  The numbers of vertices and bones are
		// fixed for the lifetime of the object.
		SkinController (int numVertices, int numBones);
		virtual ~SkinController ();

		// Member access.  After calling the constructor, you must set the data
		// using these functions.
		inline int GetNumVertices () const;
		inline int GetNumBones () const;
		inline Node** GetBones () const;
		inline float** GetWeights () const;
		inline APoint** GetOffsets () const;

		// The animation update.  The application time is in milliseconds.
		virtual bool Update (double applicationTime);

	protected:
		int mNumVertices;   // nv
		int mNumBones;      // nb
		Node** mBones;      // bones[nb]
		float** mWeights;   // weight[nv][nb], index b+nb*v
		APoint** mOffsets;  // offset[nv][nb], index b+nb*v
	};

	PX2_REGISTER_STREAM(SkinController);
	typedef Pointer0<SkinController> SkinControllerPtr;
#include "PX2SkinController.inl"

}

#endif
