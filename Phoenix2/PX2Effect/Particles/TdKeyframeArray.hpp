/*
* Turandot 3D 游戏引擎 Version 1.0
*
* Copyright (C) 2009-2011 http://www.Turandot3d.org/
*
* 文件名称	：	TdKeyFrameArray.hpp
*
* 版本		:	1.0 (2011/02/23)
*
* 作者		：	许多
*
*/

#ifndef TDKEYFRAMEARRAY_HPP
#define TDKEYFRAMEARRAY_HPP

#include "TdEffectPrerequisites.hpp"

namespace Td
{

	template <class T>
	inline void Lerp (T &dest, float t, const T &src0, const T &src1)
	{
		dest = src0 + (src1 - src0) * t;
	}

	template <class T>
	inline void Hermite (T &dest, const float r, const T &v0, const T &v1,
		const T &in, const T &out)
	{
		float h1 = 2.0f*r*r*r - 3.0f*r*r + 1.0f;
		float h2 = -2.0f*r*r*r + 3.0f*r*r;
		float h3 = r*r*r - 2.0f*r*r + r;
		float h4 = r*r*r - r*r;

		dest = v0*h1 + v1*h2 + in*h3 + out*h4;
	}

	template<typename T>
	class KeyframeArray : public Object
	{
	public:
		KeyframeArray ();
		KeyframeArray (size_t n);
		~KeyframeArray ();

		enum InterplateType
		{
			IM_NONE,
			IM_LINEAR,
			IM_HERMITE,
			IM_RANDOM,
			TM_MAX_TYPE
		};

		struct AnimRange
		{
			int Begin;
			int End;
		};

		bool HasSeq (int seq);
		virtual int GetNumKeys ();
		virtual int GetValue (int seq, unsigned int tick, void *data);
		void GetValue (int seq, unsigned int tick, T &data, bool loop=true);

		const KeyframeArray<T> &operator= (const KeyframeArray<T> &rhs);

		void SetNumKey (int num);
		void SetKeyframe (int i, unsigned int tick, T data);
		void GetKeyframe (int i, unsigned int &tick, T &data);

		struct KeyframeKey
		{
			unsigned int Tick;
			T Data;
		};

		struct ControlPoint
		{
			T In;
			T Out;
		};

		InterplateType mInterplateType;
		std::vector<AnimRange> mRanges;
		std::vector<KeyframeKey> mKeyframeArray;
		std::vector<ControlPoint> mCtrlPoints;
	};

#include "TdKeyframeArray.inl"

}

#endif