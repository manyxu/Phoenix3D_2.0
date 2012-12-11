/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainBrush.hpp
*
*/

#ifndef PX2TERRAINBRUSH_HPP
#define PX2TERRAINBRUSH_HPP

#include "PX2EditorLibPre.hpp"
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

		virtual void SetPos (PX2::APoint pos);
		virtual void SetSize (float size);

		void SetTerrain (PX2::RawTerrain *terrain) { mTerrain = terrain; }
		PX2::RawTerrain *GetTerrain () { return mTerrain; }

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