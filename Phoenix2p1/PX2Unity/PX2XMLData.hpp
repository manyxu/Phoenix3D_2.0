/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2XMLData.hpp
*
* 版本		:	1.0 (2011/02/09)
*
* 作者		：	more
*
*/

#ifndef PX2XMLDATA_HPP
#define PX2XMLDATA_HPP

#include "PX2UnityPre.hpp"
#include "PX2XMLNode.hpp"

class TiXmlDocument;

namespace PX2
{

	class XMLData
	{
	public:
		XMLData ();
		~XMLData ();

		bool LoadFile (const std::string &fileName);
		bool LoadBuffer (const char *buffer, int size);
		bool SaveFile (const std::string &fileName);

		XMLNode GetRootNode ();

		// path="Config.RenderSystem.FXSetting",如果中间任何一个节点不存在,返回
		// 空节点
		XMLNode GetNodeByPath (const char *path);

	private:
		XMLData (const XMLData &);
		XMLData &operator= (const XMLData &);

		TiXmlDocument *mDocument;
	};

}

#endif