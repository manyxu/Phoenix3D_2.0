/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TexPackData.hpp
*
*/

#ifndef PX2TEXPACKDATA_HPP
#define PX2TEXPACKDATA_HPP

#include "PX2UnityPre.hpp"

namespace PX2
{

	class TexPackElement
	{
	public:
		TexPackElement ();
		~TexPackElement ();

		bool IsValid () const;

		int X;
		int Y;
		int W;
		int H;
		int OX;
		int OY;
		int OW;
		int OH;
		bool Rolated;
		int TexWidth;
		int TexHeight;
		std::string ElementName;
		std::string ImagePathFull;
	};

	class TexPack
	{
	public:
		TexPack ();
		~TexPack ();

		bool IsValid () const;

		std::string ImagePath;
		int Width;
		int Height;

		std::vector<TexPackElement> Elements;
	};

#include "PX2TexPackData.inl"

}

#endif