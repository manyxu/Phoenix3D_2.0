/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2TerrainBrush.hpp
*
* 版本		:	1.0 (2011/08/02)
*
* 作者		：	more
*
*/

#ifndef PX2TERRAINBRUSH_HPP
#define PX2TERRAINBRUSH_HPP

#include "PX2EditorLibPrerequisites.hpp"
#include "PX2Brush.hpp"

namespace PX2Editor
{

	class VertexAffectInfo
	{
	public:
		VertexAffectInfo ()
		{
			Index = -1;
			Length = 1.0f;
			Weight = 0.0f;
		}

		int Index;
		float Length;
		float Weight;
	};

	class PageAffectInfo
	{
	public:
		PageAffectInfo ()
		{
			CenterPage = false;
		}
		~PageAffectInfo ()
		{

		}
		bool CenterPage;
		PX2::RawTerrainPagePtr InfulencedPage;
		std::vector<VertexAffectInfo> VertexInfoList;

		static float AverageHeight;
		static int VertexNum;
	};

	class TerrainBrush : public Brush
	{
	public:
		TerrainBrush ();
		virtual ~TerrainBrush ();

		virtual void SetPos (PX2::APoint pos);
		virtual void SetSize (float size);

		void SetTerrain (PX2::RawTerrain *terrain) { mTerrain = terrain; }
		PX2::RawTerrain *GetTerrain () { return mTerrain; }

		enum InterplateMode
		{
			IM_NONE,
			IM_LINER,
			IM_SQUARE,
			IM_COS,
			IM_MAX_MODE
		};

		void SetInterplateMode (InterplateMode mode) { mInterplateMode = mode; }
		InterplateMode GetInterplateMode () { return mInterplateMode; }

		void SelectPage ();
		PX2::RawTerrainPage *GetSelectedPage ();

		void CalculateInfulencedInfo ();
		std::vector<PageAffectInfo> &GetInfulencedInfo () { return mPageInfoList; }

		PX2::Renderable *GetRenderable () { return mCircleSegment; }

	protected:
		PX2::RawTerrainPtr mTerrain;
		PX2::RawTerrainPagePtr mSelectedTerrainPage;
		InterplateMode mInterplateMode;
		std::vector<PageAffectInfo> mPageInfoList;

		PX2::VertexFormatPtr mVertexFormat;
		PX2::PolysegmentPtr mCircleSegment;
	};

}

#endif