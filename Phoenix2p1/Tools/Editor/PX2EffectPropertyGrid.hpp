/*
*
* ÎÄ¼þÃû³Æ	£º	PX2KeyPointPropertyGrid.hpp
*
*/

#ifndef PX2EFFECTPROPERTYGRID_HPP
#define PX2EFFECTPROPERTYGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"
#include "PX2EffectModule.hpp"

namespace PX2Editor
{

	class EffectPropertyGrid : public ObjectPropertyGrid
	{
	public:
		EffectPropertyGrid (wxWindow *parent);
		~EffectPropertyGrid ();

		DECLARE_DYNAMIC_CLASS(EffectPropertyGrid)

		virtual void OnSetObject(PX2::Object *object);
		void SetSelectedEffect (PX2::Movable *mov);
		PX2::Movable *GetSelectedEffect () { return mSelectedEffect; }
		void SetSelectedModule (PX2::EffectModule *module);
		PX2::EffectModule *GetSelectedModule () { return mSelectedModule; }
		void TryRefreshModule (void *pointer);
		void TryRefreshModulePoints (void *pointer);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

	protected:
		DECLARE_EVENT_TABLE()

		EffectPropertyGrid ();
		void RefreshModule (PX2::EffectModule *module);
		void RefreshModuleKeyPoints (PX2::EffectModule *module, bool forChange);

		PropertyPage *mActorPage;
		PropertyPage *mSelectedEffectPage;
		PropertyPage *mSelectedModulePage;

		std::string mActorName;
		std::string mActorType;

		PX2::MovablePtr mSelectedEffect;
		std::string mSelectedEffectName;
		std::string mSelectedEffectType;
		int mBlendMode;
		std::string mTextPath;

		// particles
		int mMaxNumParticles;
		bool mIsLocal;
		int mFaceType;
		int mRotateAxisType;
		bool mIsFixedBound;
		PX2::Float3 mFixedBoundCenter;
		float mFixedBoundRadius;
		int mPlacerType;
		float mInLength;
		float mOutLength;
		float mInWidth;
		float mOutWidth;
		float mInHeight;
		float mOutHeight;

		PX2::EffectModulePtr mSelectedModule;
		std::string mSelectedModuleName;
		std::string mSelectedModuleType;
		bool mSelectedModuleIsRange;
	};

}

#endif