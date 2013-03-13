/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ObjectSelection.hpp
*
*/

#ifndef PX2OBJECTSELECTION_HPP
#define PX2OBJECTSELECTION_HPP

#include "PX2EditorLibPre.hpp"
#include "PX2Actor.hpp"

namespace PX2Editor
{

	class ObjectSelection
	{
	public:
		ObjectSelection ();
		~ObjectSelection ();

		void AddObject (PX2::Object *obj);
		void RemoveObject (PX2::Object *obj);
		PX2::Object *GetObjectAt (int i);
		int GetNumObjects ();
		bool IsObjectIn (PX2::Object *obj);
		void Clear ();

		void Translate (PX2::AVector vec);
		void TranslateTo (PX2::APoint pos);
		void AddRolate (PX2::AVector vec);
		void AddScale (PX2::AVector vec);

	private:
		std::vector<PX2::ObjectPtr> mObjects;
	};
}

#endif