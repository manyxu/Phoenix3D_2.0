/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2KeyframeController.hpp
*
* 版本		:	1.0 (2011/02/01)
*
* 作者		：	more
*
*/

#ifndef PX2KEYFRAMECONTROLLER_HPP
#define PX2KEYFRAMECONTROLLER_HPP

#include "PX2GraphicsPrerequisites.hpp"
#include "PX2TransformController.hpp"
#include "PX2HMatrix.hpp"
#include "PX2HQuaternion.hpp"

namespace PX2
{

	class PX2_GRAPHICS_ENTRY KeyframeController : public TransformController
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(KeyframeController);

	public:
		/**
		* 如果translations，rotations，和scales共享相同的关键帧时间，设置
		* numCommonTimes为非负。如果关键帧时间不被共享，设置numCommonTimes为0，
		* 将其他的参数设置到合适的值——存在该类型变换为正，不存在为0。
		*/
		KeyframeController (int numCommonTimes, int numTranslations,
			int numRotations, int numScales, const Transform& localTransform);

		virtual ~KeyframeController ();

		// 成员访问
		inline int GetNumCommonTimes () const;
		inline float* GetCommonTimes () const;

		inline int GetNumTranslations () const;
		inline float* GetTranslationTimes () const;
		inline APoint* GetTranslations () const;

		inline int GetNumRotations () const;
		inline float* GetRotationTimes () const;
		inline HQuaternion* GetRotations () const;

		inline int GetNumScales () const;
		inline float* GetScaleTimes () const;
		inline float* GetScales () const;

		// 动画更新
		/*
		* 时间为毫秒
		*/
		virtual bool Update (double applicationTime);

	protected:
		// 根据给定的时间计算当前的帧
		static void GetKeyInfo (float ctrlTime, int numTimes, float* times,
			int& lastIndex, float& normTime, int& i0, int& i1);

		APoint GetTranslate (float normTime, int i0, int i1);
		HMatrix GetRotate (float normTime, int i0, int i1);
		float GetScale (float normTime, int i0, int i1);

		// 当translations，rotations和scales共享时间时，才使用这个数组。
		int mNumCommonTimes;
		float* mCommonTimes;

		int mNumTranslations;
		float* mTranslationTimes;
		APoint* mTranslations;

		int mNumRotations;
		float* mRotationTimes;
		HQuaternion* mRotations;

		int mNumScales;
		float* mScaleTimes;
		float* mScales;

		// 记录索引，用来进行插值。
		int mTLastIndex, mRLastIndex, mSLastIndex, mCLastIndex;
	};

	PX2_REGISTER_STREAM(KeyframeController);
	typedef Pointer0<KeyframeController> KeyframeControllerPtr;
#include "PX2KeyframeController.inl"

}

#endif