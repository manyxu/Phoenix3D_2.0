/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtCollisionDebugDrawer.hpp
*
* 版本		:	1.0 (2011/03/08)
*
* 作者		：	more
*
*/

#ifndef PX2BTCOLLISIONDEBUGDRAWER_HPP
#define PX2BTCOLLISIONDEBUGDRAWER_HPP

#include "PX2BtCollisionDebugLines.hpp"

namespace TdBt
{

	class DebugDrawer : public DebugLines, public btIDebugDraw
	{
	public:
		DebugDrawer ();
		virtual ~DebugDrawer ();

		// 多肽
		virtual void setDebugMode (int mode);
		virtual int getDebugMode () const;

		virtual void drawLine (const btVector3& from, const btVector3& to,
			const btVector3& color);
		virtual void drawContactPoint (const btVector3 &pointOnB,
			const btVector3 &normalOnB, btScalar distance, int lifeTime, 
			const btVector3 &color);
		virtual void draw3dText (const btVector3& location,
			const char* textString);
		virtual void reportErrorWarning(const char* warningString);

		void DrawLine (const PX2::APoint &from, const PX2::APoint &to,
			const PX2::Float4 &color);

		void SetDrawAABB (bool enable);
		void SetDrawWireframe (bool enable);
		void SetDrawFeaturesText (bool enable);
		void SetDrawContactPoints (bool enable);
		void SetNoDeactivation (bool enable);
		void SetNoHelpText (bool enable);
		void SetDrawText (bool enable);
		void SetProfileTimings (bool enable);
		void SetEnableSatComparison (bool enable);
		void SetDisableBulletLCP (bool enable);
		void SetEnableCCD (bool enable);

		bool IsDrawAabb () const;
		bool IsDrawWireframe () const;
		bool IsDrawFeaturesText () const;
		bool IsDrawContactPoints () const;
		bool IsNoDeactivation () const;
		bool IsNoHelpText () const;
		bool IsDrawText () const;
		bool IsProfileTimings () const;
		bool IsEnableSatComparison () const;
		bool IsDisableBulletLCP () const;
		bool IsEnableCCD () const;

	protected:
		int mDebugMode;
	};

	typedef PX2::Pointer0<DebugDrawer> DebugDrawerPtr;

}

#endif