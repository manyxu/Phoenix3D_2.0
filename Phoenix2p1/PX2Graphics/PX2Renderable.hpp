/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Renderable.hpp
*
* 版本		:	1.0 (2011/02/01)
*
* 作者		：	more
*
*/

#ifndef PX2RENDERABLE_HPP
#define PX2RENDERABLE_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Movable.hpp"
#include "PX2IndexBuffer.hpp"
#include "PX2VertexBuffer.hpp"
#include "PX2VertexFormat.hpp"
#include "PX2MaterialInstance.hpp"
#include "PX2Light.hpp"

namespace PX2
{

	/// 渲染对象类
	/**
	* 所有渲染对象都从此类派生。
	*/
	class Renderable : public Movable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Renderable);

	public:
		enum PrimitiveType
		{
			PT_NONE,  //< default constructor
			PT_POLYPOINT,
			PT_POLYSEGMENTS_DISJOINT,
			PT_POLYSEGMENTS_CONTIGUOUS,
			PT_TRIANGLES,  //< abstract
			PT_TRIMESH,
			PT_TRISTRIP,
			PT_TRIFAN,
			PT_MAX_QUANTITY
		};

	protected:
		/**
		* 抽象基类
		*/
		Renderable (PrimitiveType type = PT_NONE);
		Renderable (PrimitiveType type, VertexFormat* vformat, VertexBuffer* vbuffer,
			IndexBuffer* ibuffer);
	public:
		virtual ~Renderable ();

		inline PrimitiveType GetPrimitiveType () const;

		inline void SetVertexFormat (VertexFormat* vformat);
		inline const VertexFormat* GetVertexFormat () const;
		inline VertexFormat* GetVertexFormat ();

		inline void SetVertexBuffer (VertexBuffer* vbuffer);
		inline const VertexBuffer* GetVertexBuffer () const;
		inline VertexBuffer* GetVertexBuffer ();

		inline void SetIndexBuffer (IndexBuffer* ibuffer);
		inline const IndexBuffer* GetIndexBuffer () const;
		inline IndexBuffer* GetIndexBuffer ();

		inline const Bound& GetModelBound () const;
		inline Bound& GetModelBound ();

		// 渲染作用
		enum RenderUsage
		{
			RU_UI,
			RU_GENERAL,
			RU_REFLECT,
			RU_SHADOWMAP,
			RU_QUANTITY
		};

		void AddRenderUsage (RenderUsage usage);
		void RemoveRenderUsage (RenderUsage usage);
		unsigned int GetRenderUsage ();

		/// 渲染层级
		enum RenderLayer
		{
			RL_BACKGROUND = 0,
			RL_TERRAIN,
			RL_SCENE,
			RL_FRONT
		};

		void SetRenderLayer (RenderLayer layer);
		unsigned int GetSortIndex ();

		// 绘制几何图形的效果实例
		inline void SetMaterialInstance (MaterialInstance* material);
		inline MaterialInstance* GetMaterialInstance () const;
		
		// 灯光
		/*
		* 当前渲染体收到影响的灯光
		*/
		bool AddLight (Light *light);
		bool RemoveLight (Light *light);		
		void ClearLights ();
		int GetNumLights ();
		Light *GetLight (int i);

		// 几何图形跟新类型
		enum UpdateType
		{
			GU_MODEL_BOUND_ONLY = -3,
			GU_NORMALS = -2,
			GU_USE_GEOMETRY = -1,
			GU_USE_TCOORD_CHANNEL = 0
		};

		/// 可视对象模型更新
		/**
		* 如果可视对象的VertexBuffer被修改了，你需要更新（normals,tangents,
		* bitangents）。传入的type决定更新的规则，如下：
		* GU_MODEL_BOUND_ONLY
		*	顶点的空间位置改变了，只更新包围盒。
		* 对于其他更新，包围盒也都会更新。如果可视对象是从Triangles派生的话，
		* 如果有法线信息，会首先更新法线信息。
		* GU_NORMALS
		*	更新完法线信息，不会再跟新纹理坐标空间。
		* GU_USE_GEOMETRY
		* GU_USE_TCOORD_CHANNEL + nonnegative_integer
		*	使用第nonnegative_integer层纹理坐标跟新纹理坐标空间。
		* 为了节省显存，你可以考虑只传入normals，tangents，然后使用像素着色器
		* 计算bitangent。
		*	bitangent = Cross(normal, tangent)			
		*/
		virtual void UpdateModelSpace (UpdateType type);

public_internal:
		float mEyeDistance; // 相机距离
		static bool LessThan (const Renderable *renderable0,
			const Renderable *renderable1);

	protected:
		void AdjustTransparent ();
		void SetTransparent (bool transparent);
		bool IsTransparent () const;

	protected:
		// 几何图形更新
		virtual void UpdateWorldBound ();
		virtual void UpdateModelBound ();

		// 场景裁剪
		virtual void GetVisibleSet (Culler& culler, bool noCull);

	protected:
		// 渲染作用
		unsigned int mRenderUsageBits;
		unsigned int mSortIndex; //(layer<<16)|current

		// 几何图形数据
		PrimitiveType mType;
		VertexFormatPtr mVFormat;
		VertexBufferPtr mVBuffer;
		IndexBufferPtr mIBuffer;
		Bound mModelBound;

		// 绘制几何图形的效果
		MaterialInstancePtr mMaterial;

		// 当前对象受影响的灯光
		/*
		* 灯光不用持久化，在每次渲染之前计算受影响的灯光。
		*/
		std::vector<LightPtr> mInfulencedLights; 

		// Begin load/save
	public:
		// created properly unless we have a Load for each instantiable primitive.
		// 使用持久化系统from/to *.tdvf Load/Save渲染对象。因为Renderable是具体几何
		// 图形一个抽象基类，所以我们不能通过此函数加载，创建，返回一个Renderable。
		static void LoadPX2VF (const std::string& name, PrimitiveType& type,
			VertexFormat*& vformat, VertexBuffer*& vbuffer, IndexBuffer*& ibuffer,
			int mode = FileIO::FM_DEFAULT_READ);

		void SavePX2VF (const std::string& name,
			int mode = FileIO::FM_DEFAULT_WRITE);

	private:
		static VertexFormat* LoadVertexFormat (FileIO& inFile);
		static VertexBuffer* LoadVertexBuffer (FileIO& inFile,
			VertexFormat* vformat);
		static IndexBuffer* LoadIndexBuffer (FileIO& inFile);
		void SaveVertexFormat (FileIO& outFile);
		void SaveVertexBuffer (FileIO& outFile);
		void SaveIndexBuffer (FileIO& outFile);
		// End load/save
	};

	PX2_REGISTER_STREAM(Renderable);
	typedef Pointer0<Renderable> RenderablePtr;
#include "PX2Renderable.inl"

}

#endif
