/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Brush.hpp
*
*/

#ifndef PX2BRUSH_HPP
#define PX2BRUSH_HPP

#include "PX2EditorLibPre.hpp"

namespace PX2Editor
{

	class Brush
	{
	public:
		Brush ();
		virtual ~Brush ();

		virtual void SetPos (PX2::APoint pos);
		PX2::APoint GetPos () { return mPos; }

		virtual void SetSize (float size);
		float GetSize () { return mSize; }

		void SetStrength (float strength) { mStrength = strength; }
		float GetStrength () { return mStrength; }

	protected:
		PX2::APoint mPos;
		float mSize;
		float mStrength;
	};

}

#endif
