/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2LODTerrainPage.hpp
*
* 版本		:	1.0 (2011/03/05)
*
* 作者		：	more
*
*/

#ifndef PX2LODTERRAINPAGE_HPP
#define PX2LODTERRAINPAGE_HPP

#include "PX2TerrainPrerequisites.hpp"

namespace PX2
{

	class Renderer;
	class Camera;
	class LODTerrainBlock;
	class LODTerrainVertex;

	class PX2_TERRAIN_ENTRY LODTerrainPage : public TriMesh
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(LODTerrainPage);

	public:
		// size = 2^p + 1, p <= 7 (size = 3, 5, 9, 17, 33, 65, 129)
		LODTerrainPage (VertexFormat *vformat, int size,
			unsigned short *height, const Vector2f &origin,
			float minElevation, float maxElevation, float spacing, 
			float uvBias);

		virtual ~LODTerrainPage ();

		// 高程访问
		int GetSize () const;
		const unsigned short *GetHeights () const;
		const Vector2f &GetOrigin () const;
		float GetMinElevation () const;
		float GetMaxElevation () const;
		float GetSpacing () const;

		// pixel tolerance on projected vertex height
		void SetPixelTolerance (const Renderer* renderer, float tolerance);
		float GetPixelTolerance () const;

		/// 高程测量
		/**
		* 如果输入位置在地形页范围外，返回INFINITY。
		* @ param x	地形世界X轴向位置
		* @ param y	地形世界Y轴向位置
		*/
		float GetHeight (float x, float y) const;

		float &GetUVBias ();

	protected:
		friend class LODTerrainBlock;

		// 持久化支持
		LODTerrainPage ();

		void InitializeDerivedData ();

		// queue handlers
		void AddToQueue (unsigned short blockIndex);
		unsigned short RemoveFromQueue ();
		unsigned short ReadFromQueue (unsigned short index);

		/// 地形页和相机相交检测
		bool IntersectFrustum (const Camera *camera);

		// 地形块简化
		void SimplifyBlocks (const Camera* camera, const APoint &modelEye,
			const AVector &modelDir, bool closeAssumption);

		// 顶点简化
		void SimplifyVertices (const APoint &modelEye,
			const AVector &modelDir, bool closeTerrainAssumption);

		// 地形简化
		friend class LODTerrain;
		void EnableBlocks ();
		void ResetBlocks ();
		void Simplify (const Renderer* renderer, const APoint &modelEye,
			const AVector &modelDir, bool closeAssumption);

		// 网格
		float GetX (int x) const; //< x表X向网格顶点索引
		float GetY (int y) const; //< y表Y向网格顶点索引
		float GetHeight (int index) const; //< iIndex表网格顶点索引
		float GetTextureCoordinate (int index) const;
		void Render (LODTerrainBlock &block);
		void RenderTriangle (int t, int l, int r);
		void RenderBlocks ();

		// 可见集裁剪
		virtual void GetVisibleSet (Culler &culler, bool noCull);

		// 高程数据
		int mSize, mSizeM1;
		unsigned short *mHeights;
		Vector2f mOrigin;
		float mMinElevation, mMaxElevation, mSpacing;
		float mInvSpacing, mTextureSpacing, mMultiplier;

		// 纹理参数
		float mUVBias;

		// 简化
		float mPixelTolerance, mWorldTolerance;
		mutable bool mNeedsTessellation;
		int *mLookup;
		int mConnectLength;

		/// (2^p+1) * (2^p+1)的顶点数组，行主序列
		LODTerrainVertex *mVertexs;
		VertexBufferAccessor mVBA;

		// maximum quantities
		int mTotalVQuantity, mTotalTQuantity, mTotalIQuantity;

		// quadtree of blocks
		int mBlockQuantity;
		LODTerrainBlock* mBlocks;

		// 记录最子层Block，
		unsigned short *mQueue;
		unsigned short mQueueQuantity;
		unsigned short mFront, mRear;
		unsigned short mNumUnprocessed;
		unsigned short mItemsInQueue;

		// 内部使用
	public:
		// 高程获取函数为 z = h(x,y)，xy平面使用右手坐标系。如下图所示
		//
		// y
		// ^
		// | col 0   col 1
		// +--------+-------+
		// |   10   |  11   | row 1
		// +--------+-------+
		// |   00   |  01   | row 0
		// +--------+-------+--> x

		// 地形页(r,c)和(r,c+1)之间的缝合
		void StitchNextCol (LODTerrainPage *nextCol);
		void UnstitchNextCol (LODTerrainPage *nextCol);

		// 地形页(r,c)和(r+1,c)之间的缝合
		void StitchNextRow (LODTerrainPage *nextRow);
		void UnstitchNextRow (LODTerrainPage *nextRow);
	};

	PX2_REGISTER_STREAM(LODTerrainPage);
	typedef Pointer0<LODTerrainPage> LODRawTerrainPagePtr;
#include "PX2LODTerrainPage.inl"

}

#endif