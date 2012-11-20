/*
*
* ÎÄ¼þÃû³Æ	£º	PX2CtrlMan.hpp
*
*/

#ifndef PX2CTRLINSTMAN_HPP
#define PX2CTRLINSTMAN_HPP

#include "PX2EditorPre.hpp"
#include "PX2Singleton.hpp"
#include "PX2ViewCtrlInst.hpp"

namespace PX2Editor
{

	class ViewCtrlInstMan : public PX2::Singleton<ViewCtrlInstMan>
	{
	public:
		ViewCtrlInstMan ();
		virtual ~ViewCtrlInstMan ();

		void RegisterViewCtrlInst (const std::string &name, ViewCtrlInst *instance);
		void UnRegisterViewCtrlInst (const std::string &name);

		ViewCtrlInst *GetCurViewCtrlInst ();

		static const std::string DEFAULT_CTRL_NAME;
		static const std::string MULTIITEM_CTRL_NAME;

	protected:
		void SwitchCtrlInst (const std::string& typeName);

		std::map<std::string, ViewCtrlInst*> mViewCtrlInsts;
		ViewCtrlInst *mDefViewCtrlInst;
		ViewCtrlInst *mMultiViewCtrlInst;
		std::string mCurViewCtrlType;
		ViewCtrlInst *mCurViewCtrlInst;
	};

#include "PX2ViewCtrlInstMan.inl"

}

#endif