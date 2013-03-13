/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIManager.hpp
*
*/

#ifndef PX2UIMANAGER_HPP
#define PX2UIMANAGER_HPP

#include "PX2UIPre.hpp"
#include "PX2UIMaterial.hpp"
#include "PX2VertexFormat.hpp"
#include "PX2UIView.hpp"
#include "PX2Singleton.hpp"
#include "PX2EventHandler.hpp"
#include "PX2Node.hpp"
#include "PX2UIPicBox.hpp"
#include "PX2UIAnimPicBox.hpp"
#include "PX2UIStaticText.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIButton.hpp"
#include "PX2FontManager.hpp"

namespace PX2
{

	class UIManager : public Singleton<UIManager>, public EventHandler
	{
	public:
		UIManager ();
		~UIManager ();

		FontManager *GetFontManager ();

		VertexFormat *GetVertexFormat ();
		UIMaterial *GetUIMaterial ();
		UIMaterial *GetUIMaterialDoubleSide ();
		UIView *GetDefaultView ();

		void AddUIView (std::string name, UIView *view);
		std::map<std::string, UIViewPtr> &GetUIViews ();
		UIView *GetUIView (std::string name);

		UIPicBox *CreateUIPicBox (const APoint &localPos, const std::string &texPack="");
		UIAnimPicBox *CreateUIAnimPicBox (const APoint &localPos, const std::string &filename="");
		UIStaticText *CreateUIStaticText (const APoint &localPos);
		UIFrame *CreateUIFrame (const APoint &localPos);
		UIButton *CreateUIButton (const APoint &localPos);

		virtual void DoExecute (Event *event);

	protected:
		FontManager *mFontManager;

		VertexFormatPtr mVertexFormat;
		UIMaterialPtr mUIMaterial;
		UIMaterialPtr mUIMaterialDoubleSide;
		UIViewPtr mDefaultView;
		std::map<std::string, UIViewPtr> mUiViews;
	};

#include "PX2UIManager.inl"

#define PX2_UIM UIManager::GetSingleton()

}

#endif