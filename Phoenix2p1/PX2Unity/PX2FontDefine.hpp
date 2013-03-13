/*
*
* 文件名称	：	PX2FontDefine.hpp
*
*/

#ifndef PX2FONTDEFINE_HPP
#define PX2FONTDEFINE_HPP

#include "PX2UnityPre.hpp"

namespace PX2
{

#define FES_NORMAL 0		//< 普通
#define FES_ITALIC 1		//< 斜体
#define FES_UNDERLINE 2		//< 下划线

#define FD_NORMAL 0
#define FD_SHADOW 1
#define FD_BORDER 2

#define FONT_MAXRECTNUM 2048 // 一次渲染的最大多边形个数
#define FONT_TEXSIZE 512	 // 缓存贴图的尺寸

	enum CharacterSet
	{
		CS_ENGLISH = 0,		//< 英文
		CS_CHINESE_GB,		//< 中文国标编码
		CS_CHINESE_GBK,		//< 中文国标编码
		CS_CHINESE_BIG5,	//< 中文BIG5编码
	};

	struct FontDrawRect
	{
		Rectf Rect;
		Rectf RectUV;
		Float4 Color;
	};

	enum CharCtrlCode			//< 控制码
	{
		CCC_CHARACTER = 0,		//< 普通字符
		CCC_RETURN,				//< 回车
		CCC_NEWLINE,			//< 换行
		CCC_ENDOFSTRING,		//< 字符串结束
		CCC_TRANSFER,			//< 转意控制符
		CCC_UNKNOWN,			//< 未知，不做处理
	};

	enum CharCodingType
	{
		CCT_GBK,
		CCT_UTF8,
		CCT_MAX_TYPE
	};

}

#endif