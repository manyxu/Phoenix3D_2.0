/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ResourceManager.hpp
*
* 版本		:	1.0 (2011/04/01)
*
* 作者		：	more
*
*/

#ifndef PX2RESOURCEMANAGER_HPP
#define PX2RESOURCEMANAGER_HPP

#include "PX2UnityPre.hpp"

namespace PX2
{

	typedef unsigned long ResHandle;

	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		ResourceManager ();
		~ResourceManager ();

		/// 资源加载状态
		enum LoadState
		{
			LS_UNLOADED,
			LS_LOADQUE,
			LS_LOADING,
			LS_LOADED,
			LS_MAX_STATE
		};

		// 加载
		Object *BlockLoad (const std::string &filename);
		ResHandle BackgroundLoad (const std::string &filename);
		Object *CheckRes (ResHandle handle);
		LoadState GetResLoadState (ResHandle handle);

		/// 获得buffer,在Android中从apk中获取
		/**
		* 你需要负责使用delete1释放获得的buffer
		*/
		bool GetBuffer (const std::string &filename, int &bufferSize, 
			char* &buffer);

		/// 获得可写路径
		/**
		* 在PC上为程序当前目录，在移动设备上由该设备API返回。
		*/
		std::string GetWriteablePath ();
		static const std::string GetResourcePath ();

		// 加载选项
		void DDSKeepCompressed (bool keep=true);
		bool IsDDSKeepCompressed ();

public_internal:
		struct LoadRecord
		{
			std::string Filename;
			ObjectPtr Obj;
			LoadState State;

			// 当资源引用计数为1后，超过一定时间长度后，资源将被系统回收。
			unsigned int LastTouchedTime;
		};

		unsigned int RunLoadingThread ();
		void GarbageCollect ();
		
		// 设置资源路径.在Android系统中，为apk所在目录
		static void SetResourcePath (const std::string &resPath);

	protected:
		LoadRecord &InsertRecord (const std::string &filename);
		void _LoadTheRecord (LoadRecord &rec);
		Object *_LoadObject (const std::string &filename);
		bool _LoadBuffer (const std::string &filename, int &bufferSize,
			char* &buffer);
		Texture2D *LoadTextureFromOtherImagefile (const std::string &filename);
		Texture2D *LoadTextureFromDDS (const std::string &filename);
		bool GetFileDataFromZip (const std::string &packageName, 
			const std::string &filename, int &bufferSize, char* &buffer);

		void StartThread ();
		
	private:
		bool mDDSKeepCompressed;
		Mutex mLoadRecordMutex;
		Mutex mLoadingDequeMutex;
		Thread *mLoadingThread;
		std::deque<LoadRecord *>mLoadingDeque;
		bool mQuitLoading;
		ConditionType mLoadingDequeCondition;

		typedef std::map<std::string, LoadRecord> ResTable;
		typedef ResTable::iterator ResIterator;

		Mutex mResTableMutex;
		ResTable mResTable;

		bool mReadFromZip;
		static std::string msResPath;

		unsigned int mTimeCounter;
	};

#define PX2_RM ResourceManager::GetSingleton()

#include "PX2ResourceManager.inl"

}

#endif