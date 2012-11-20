/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditorParams.hpp
*
*/

#ifndef PX2EDITORPARAMS_HPP
#define PX2EDITORPARAMS_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class EditorParams
	{
	public:
		EditorParams ();
		~EditorParams ();

		static EditorParams &GetSingleton ();

		bool Save (std::string filename);
		bool Load (std::string filename);

		float mGridSize;
	};

}

#endif