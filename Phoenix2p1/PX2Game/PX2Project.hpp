/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Project.hpp
*
*/

#ifndef PX2PROJECT_HPP
#define PX2PROJECT_HPP

#include "PX2GamePre.hpp"
#include "PX2Scene.hpp"
#include "PX2UIFrame.hpp"

namespace PX2
{

	class Project : public Singleton<Project>
	{
	public:
		Project ();
		virtual ~Project ();

		void SetInGamePlay (bool inGamePlay);
		bool IsInGamePlay();

		bool Save (const std::string &filename); //< only used in editor		
		bool Load (const std::string &filename);
		
		void SetName (const std::string &name);
		const std::string &GetName () const;

		void SetWidth (int width);
		int GetWidth () const;

		void SetHeight (int height);
		int GetHeight () const;

		void SetColor (Float4 color);
		Float4 GetColor ();

		void SetSceneFilename (std::string filename);
		const std::string &GetSceneFilename () const;

		void SetUIFilename (std::string filename);
		const std::string &GetUIFilename () const;

		void SetScene (Scene *scene);
		Scene *GetScene () const;
		void SetUI (UIFrame *frame);
		UIFrame *GetUI () const;

		// infos
		void SetShowProjectInfo (bool show);
		bool IsShowProjectInfo ();

		void SetSceneWired (bool wire);
		bool IsSceneWired ();
		void SetShowSceneBound (bool show);
		bool IsShowSceneBound ();
		void SetShowGrid(bool show);
		bool IsShowGrid ();
		void SetUIWired (bool wire);
		bool IsUIWired ();
		void SetUICameraPercent (float percent);
		float GetUICameraPercent ();
		void SetShowUI (bool show);
		bool IsShowUI ();
		void SetShowUIRange (bool show);
		bool IsShowUIRange ();		

	protected:
		bool mIsInGamePlay;
		std::string mName;
		int mWidth;
		int mHeight;
		Float4 mColor;
		std::string mSceneFilename;
		ScenePtr mScene;
		std::string mUIFilename;
		UIFramePtr mUI;

		bool mIsShowProjectInfo;

		bool mIsShowSceneBound;
		bool mIsSceneWired;

		bool mIsShowUI;
		bool mIsShowUIRange;
		float mUICameraPercent;
		bool mIsUIWired;
		bool mIsShowGrid;
	};

#include "PX2Project.inl"

}

#endif