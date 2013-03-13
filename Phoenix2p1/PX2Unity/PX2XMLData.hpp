/*
*
* 文件名称	：	PX2XMLData.hpp
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
		void Create ();

		XMLNode GetRootNode ();

		// path="Config.RenderSystem.FXSetting",如果中间任何一个节点不存在,返回
		// 空节点
		XMLNode GetNodeByPath (const char *path);

		void LinkEndChild (XMLNode node);

	private:
		XMLData (const XMLData &);
		XMLData &operator= (const XMLData &);

		TiXmlDocument *mDocument;
	};

}

#endif