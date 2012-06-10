/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2EditCommand.hpp
*
* 版本		:	1.0 (2011/06/25)
*
* 作者		：	more
*
*/

#ifndef PX2EDITCOMMAND_HPP
#define PX2EDITCOMMAND_HPP

#include "PX2EditorLibPrerequisites.hpp"
#include "PX2EditEventType.hpp"

namespace PX2Editor
{

	class EditCommand
	{
	public:
		EditCommand ();
		~EditCommand ();

		virtual void OnUnDo ();
		virtual void OnReDo ();
	};

	typedef PX2::Pointer0<EditCommand> EditCommandPtr;

	class ActorTransCommand : public EditCommand
	{
	public:
		ActorTransCommand ();
		virtual ~ActorTransCommand ();

		bool operator== (const ActorTransCommand &command) const;
		
		virtual void OnUnDo ();
		virtual void OnReDo ();
		
	protected:
		std::vector<PX2::ActorPtr> mActors;
		std::vector<PX2::APoint> mPositions;
		std::vector<PX2::APoint> mRotations;
		std::vector<PX2::APoint> mScales;
	};

	class ActorAddDeleteCommand : public EditCommand
	{
	public:
		ActorAddDeleteCommand (PX2::Actor *actor);
		virtual ~ActorAddDeleteCommand ();

		PX2::ActorPtr GetActor () { return mActor; }

		virtual void OnUnDo ();
		virtual void OnReDo ();

	protected:
		ActorAddDeleteCommand ();
		PX2::ActorPtr mActor;
	};

	class EditCommandManager : public PX2::Singleton<EditCommandManager>
	{
	public:
		EditCommandManager ();
		~EditCommandManager ();

		void Reset ();

		void PushUnDo (EditCommandPtr command);
	
		void UnDo ();
		void ReDo ();

	protected:
		std::deque<EditCommandPtr> mUnDoCommands;
		std::deque<EditCommandPtr> mReDoCommands;
	};

}

#endif