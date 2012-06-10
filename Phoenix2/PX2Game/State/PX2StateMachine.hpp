/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2StateMachine.hpp
*
* 版本		:	1.0 (2011/04/01)
*
* 作者		：	more
*
*/

#ifndef PX2STATEMACHINE_HPP
#define PX2STATEMACHINE_HPP

#include "PX2State.hpp"
#include "PX2EventHandler.hpp"

namespace PX2
{

	template <typename T>
	class StateMachine : public EventHandler
	{
	public:
		StateMachine (T *owner);
		virtual ~StateMachine ();
		
		void SetCurrentState (State<T> *state);
		void SetGlobalState (State<T> *state);
		void SetPreviousState (State<T> *state);

		State<T> *GetCurrentState () const;
		State<T> *GetGlobalState () const;
		State<T> *GetPreviousState () const;

		void ChangeToState (State<T> *newState);
		void RevertToPreviousState ();
		bool IsInState (const State<T> &state) const;

		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

	private:
		T *mOwner;
		State<T> *mCurrentState;
		State<T> *mPreviousState;
		State<T> *mGlobalState;
	};

#include "PX2StateMachine.inl"

}

#endif
