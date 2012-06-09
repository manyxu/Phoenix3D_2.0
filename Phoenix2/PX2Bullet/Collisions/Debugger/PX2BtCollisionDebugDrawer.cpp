/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionDebugDrawer.cpp
*
*/

#include "PX2BtCollisionDebugDrawer.hpp"
#include "PX2BtConverter.hpp"
using namespace TdBt;

//----------------------------------------------------------------------------
DebugDrawer::DebugDrawer ()
:
mDebugMode(0)
{
}
//----------------------------------------------------------------------------
DebugDrawer::~DebugDrawer ()
{
}
//----------------------------------------------------------------------------
void DebugDrawer::setDebugMode (int mode)
{
	mDebugMode = mode;
}
//----------------------------------------------------------------------------
int DebugDrawer::getDebugMode () const
{
	return mDebugMode;
}
//----------------------------------------------------------------------------
void DebugDrawer::drawLine (const btVector3 &from, const btVector3 &to,
					   const btVector3 &color)
{
	if (mDebugMode > 0)
	{
		DrawLine(Converter::APointConvertFrom(from),
			Converter::APointConvertFrom(to), 
			PX2::Float4(color.x(), color.y(), color.z(), 1.0f));
	}
}
//----------------------------------------------------------------------------
void DebugDrawer::drawContactPoint (const btVector3 &pointOnB,
							   const btVector3 &normalOnB, btScalar distance,
							   int lifeTime, 
							   const btVector3 &color)
{
	if (mDebugMode & btIDebugDraw::DBG_DrawContactPoints)
	{
		PX2_UNUSED(pointOnB);
		PX2_UNUSED(normalOnB);
		PX2_UNUSED(distance);
		PX2_UNUSED(lifeTime);
		PX2_UNUSED(color);
	}
}
//----------------------------------------------------------------------------
void DebugDrawer::draw3dText (const btVector3& location, 
							  const char* textString)
{
	PX2_UNUSED(location);
	PX2_UNUSED(textString);
}
//----------------------------------------------------------------------------
void DebugDrawer::reportErrorWarning(const char* warningString)
{
	PX2_UNUSED(warningString);
}
//----------------------------------------------------------------------------
void DebugDrawer::DrawLine (const PX2::APoint &from, const PX2::APoint &to,
			   const PX2::Float4 &color)
{
	if (mDebugMode > 0)
    {
        AddLine(from, to);
		PX2_UNUSED(color);
    }
}
//----------------------------------------------------------------------------
void DebugDrawer::SetDrawAABB (bool enable)
{
	if (enable) 
		mDebugMode |= btIDebugDraw::DBG_DrawAabb;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawAabb;
}
//----------------------------------------------------------------------------
void DebugDrawer::SetDrawWireframe (bool enable)
{
	if (enable) 
		mDebugMode |= btIDebugDraw::DBG_DrawWireframe;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawWireframe;
}
//----------------------------------------------------------------------------
void DebugDrawer::SetDrawFeaturesText (bool enable)
{
	if (enable) 
		mDebugMode |= btIDebugDraw::DBG_DrawFeaturesText;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawFeaturesText;
}
//----------------------------------------------------------------------------
void DebugDrawer::SetDrawContactPoints (bool enable)
{
	if (enable) 
		mDebugMode |= btIDebugDraw::DBG_DrawContactPoints;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawContactPoints;
}
//----------------------------------------------------------------------------
void DebugDrawer::SetNoDeactivation (bool enable)
{
	if (enable) 
		mDebugMode |= btIDebugDraw::DBG_NoDeactivation;
	else
		mDebugMode &= ~btIDebugDraw::DBG_NoDeactivation;
}
//----------------------------------------------------------------------------
void DebugDrawer::SetNoHelpText (bool enable)
{
	if (enable) 
		mDebugMode |= btIDebugDraw::DBG_NoHelpText;
	else
		mDebugMode &= ~btIDebugDraw::DBG_NoHelpText;
}
//----------------------------------------------------------------------------
void DebugDrawer::SetDrawText (bool enable)
{
	if (enable) 
		mDebugMode |= btIDebugDraw::DBG_DrawText;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawText;
}
//----------------------------------------------------------------------------
void DebugDrawer::SetProfileTimings (bool enable)
{
	if (enable) 
		mDebugMode |= btIDebugDraw::DBG_ProfileTimings;
	else
		mDebugMode &= ~btIDebugDraw::DBG_ProfileTimings;
}
//----------------------------------------------------------------------------
void DebugDrawer::SetEnableSatComparison (bool enable)
{
	if (enable) 
		mDebugMode |= btIDebugDraw::DBG_EnableSatComparison;
	else
		mDebugMode &= ~btIDebugDraw::DBG_EnableSatComparison;
}
//----------------------------------------------------------------------------
void DebugDrawer::SetDisableBulletLCP (bool enable)
{
	if (enable) 
		mDebugMode |= btIDebugDraw::DBG_DisableBulletLCP;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DisableBulletLCP;
}
//----------------------------------------------------------------------------
void DebugDrawer::SetEnableCCD (bool enable)
{
	if (enable) 
		mDebugMode |= btIDebugDraw::DBG_EnableCCD;
	else
		mDebugMode &= ~btIDebugDraw::DBG_EnableCCD;
}
//----------------------------------------------------------------------------
bool DebugDrawer::IsDrawAabb () const
{
	return (mDebugMode & btIDebugDraw::DBG_DrawAabb) != 0;
}
//----------------------------------------------------------------------------
bool DebugDrawer::IsDrawWireframe () const
{
	return (mDebugMode & btIDebugDraw::DBG_DrawWireframe) != 0;
}
//----------------------------------------------------------------------------
bool DebugDrawer::IsDrawFeaturesText () const
{
	return (mDebugMode & btIDebugDraw::DBG_DrawFeaturesText) != 0;
}
//----------------------------------------------------------------------------
bool DebugDrawer::IsDrawContactPoints () const
{
	return (mDebugMode & btIDebugDraw::DBG_DrawContactPoints) != 0;
}
//----------------------------------------------------------------------------
bool DebugDrawer::IsNoDeactivation () const
{
	return (mDebugMode & btIDebugDraw::DBG_NoDeactivation) != 0;
}
//----------------------------------------------------------------------------
bool DebugDrawer::IsNoHelpText () const
{
	return (mDebugMode & btIDebugDraw::DBG_NoHelpText) != 0;
}
//----------------------------------------------------------------------------
bool DebugDrawer::IsDrawText () const
{
	return (mDebugMode & btIDebugDraw::DBG_DrawText) != 0;
}
//----------------------------------------------------------------------------
bool DebugDrawer::IsProfileTimings () const
{
	return (mDebugMode & btIDebugDraw::DBG_ProfileTimings) != 0;
}
//----------------------------------------------------------------------------
bool DebugDrawer::IsEnableSatComparison () const
{
	return (mDebugMode & btIDebugDraw::DBG_EnableSatComparison) != 0;
}
//----------------------------------------------------------------------------
bool DebugDrawer::IsDisableBulletLCP () const
{
	return (mDebugMode & btIDebugDraw::DBG_DisableBulletLCP) != 0;
}
//----------------------------------------------------------------------------
bool DebugDrawer::IsEnableCCD () const
{
	return (mDebugMode & btIDebugDraw::DBG_EnableCCD) != 0;
}
//----------------------------------------------------------------------------