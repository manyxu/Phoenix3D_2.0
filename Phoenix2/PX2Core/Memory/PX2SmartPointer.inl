/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SmartPointer.inl
*
*/

//----------------------------------------------------------------------------
// PointerBaseu
//----------------------------------------------------------------------------
inline void PointerBase::MutexEnter ()
{
	GetMutex().Enter();
}
//----------------------------------------------------------------------------
inline void PointerBase::MutexLeave ()
{
	GetMutex().Leave();
}
//----------------------------------------------------------------------------
inline Mutex &PointerBase::GetMutex()
{
	static Mutex mutex;
	return mutex;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Pointer0
//----------------------------------------------------------------------------
template <typename T>
Pointer0<T>::Pointer0 (T* data)
{
	MutexEnter();

	mData = data;
	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			++iter->second;
		}
		else
		{
			msMap[mData] = 1;
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
Pointer0<T>::Pointer0 (const Pointer0& pointer)
{
	MutexEnter();

	mData = pointer.mData;
	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			++iter->second;
		}
		else
		{
			assertion(false, "pointer.mData must be in the map\n");
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
Pointer0<T>::~Pointer0 ()
{
	MutexEnter();

	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			if (--iter->second == 0)
			{
				msMap.erase(mData);
				delete0(mData);
			}
		}
		else
		{
			assertion(false, "mData must be in the map\n");
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
inline Pointer0<T>::operator T* () const
{
	return mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline T& Pointer0<T>::operator* () const
{
	return *mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline T* Pointer0<T>::operator-> () const
{
	return mData;
}
//----------------------------------------------------------------------------
template <typename T>
Pointer0<T>& Pointer0<T>::operator= (T* data)
{
	MutexEnter();

	if (mData != data)
	{
		RMIterator iter;

		if (data)
		{
			iter = msMap.find(data);
			if (iter != msMap.end())
			{
				++iter->second;
			}
			else
			{
				msMap[data] = 1;
			}
		}

		if (mData)
		{
			iter = msMap.find(mData);
			if (iter != msMap.end())
			{
				if (--iter->second == 0)
				{
					msMap.erase(mData);
					delete0(mData);
				}
			}
			else
			{
				assertion(false, "mData must be in the map\n");
			}
		}

		mData = data;
	}

	MutexLeave();
	return *this;
}
//----------------------------------------------------------------------------
template <typename T>
Pointer0<T>& Pointer0<T>::operator= (const Pointer0& pointer)
{
	MutexEnter();

	if (mData != pointer.mData)
	{
		RMIterator iter;

		if (pointer.mData)
		{
			iter = msMap.find(pointer.mData);
			if (iter != msMap.end())
			{
				++iter->second;
			}
			else
			{
				assertion(false, "pointer.mData must be in the map\n");
			}
		}

		if (mData)
		{
			iter = msMap.find(mData);
			if (iter != msMap.end())
			{
				if (--iter->second == 0)
				{
					msMap.erase(mData);
					delete0(mData);
				}
			}
			else
			{
				assertion(false, "mData must be in the map\n");
			}
		}

		mData = pointer.mData;
	}

	MutexLeave();
	return *this;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer0<T>::operator== (T* data) const
{
	return mData == data;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer0<T>::operator!= (T* data) const
{
	return mData != data;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer0<T>::operator== (const Pointer0& pointer) const
{
	return mData == pointer.mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer0<T>::operator!= (const Pointer0& pointer) const
{
	return mData != pointer.mData;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Pointer1
//----------------------------------------------------------------------------
template <typename T>
Pointer1<T>::Pointer1 (T* data)
{
	MutexEnter();

	mData = data;
	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			++iter->second;
		}
		else
		{
			msMap[mData] = 1;
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
Pointer1<T>::Pointer1 (const Pointer1& pointer)
{
	MutexEnter();

	mData = pointer.mData;
	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			++iter->second;
		}
		else
		{
			assertion(false, "pointer.mData must be in the map\n");
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
Pointer1<T>::~Pointer1 ()
{
	MutexEnter();

	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			if (--iter->second == 0)
			{
				msMap.erase(mData);
				delete1(mData);
			}
		}
		else
		{
			assertion(false, "mData must be in the map\n");
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
inline Pointer1<T>::operator T* () const
{
	return mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline T& Pointer1<T>::operator* () const
{
	return *mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline T* Pointer1<T>::operator-> () const
{
	return mData;
}
//----------------------------------------------------------------------------
template <typename T>
Pointer1<T>& Pointer1<T>::operator= (T* data)
{
	MutexEnter();

	if (mData != data)
	{
		RMIterator iter;

		if (data)
		{
			iter = msMap.find(data);
			if (iter != msMap.end())
			{
				++iter->second;
			}
			else
			{
				msMap[data] = 1;
			}
		}

		if (mData)
		{
			iter = msMap.find(mData);
			if (iter != msMap.end())
			{
				if (--iter->second == 0)
				{
					msMap.erase(mData);
					delete1(mData);
				}
			}
			else
			{
				assertion(false, "mData must be in the map\n");
			}
		}

		mData = data;
	}

	MutexLeave();
	return *this;
}
//----------------------------------------------------------------------------
template <typename T>
Pointer1<T>& Pointer1<T>::operator= (const Pointer1& pointer)
{
	MutexEnter();

	if (mData != pointer.mData)
	{
		RMIterator iter;

		if (pointer.mData)
		{
			iter = msMap.find(pointer.mData);
			if (iter != msMap.end())
			{
				++iter->second;
			}
			else
			{
				assertion(false, "pointer.mData must be in the map\n");
			}
		}

		if (mData)
		{
			iter = msMap.find(mData);
			if (iter != msMap.end())
			{
				if (--iter->second == 0)
				{
					msMap.erase(mData);
					delete1(mData);
				}
			}
			else
			{
				assertion(false, "mData must be in the map\n");
			}
		}

		mData = pointer.mData;
	}

	MutexLeave();
	return *this;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer1<T>::operator== (T* data) const
{
	return mData == data;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer1<T>::operator!= (T* data) const
{
	return mData != data;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer1<T>::operator== (const Pointer1& pointer) const
{
	return mData == pointer.mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer1<T>::operator!= (const Pointer1& pointer) const
{
	return mData != pointer.mData;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Pointer2
//----------------------------------------------------------------------------
template <typename T>
Pointer2<T>::Pointer2 (T** data)
{
	MutexEnter();

	mData = data;
	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			++iter->second;
		}
		else
		{
			msMap[mData] = 1;
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
Pointer2<T>::Pointer2 (const Pointer2& pointer)
{
	MutexEnter();

	mData = pointer.mData;
	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			++iter->second;
		}
		else
		{
			assertion(false, "pointer.mData must be in the map\n");
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
Pointer2<T>::~Pointer2 ()
{
	MutexEnter();

	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			if (--iter->second == 0)
			{
				msMap.erase(mData);
				delete2(mData);
			}
		}
		else
		{
			assertion(false, "mData must be in the map\n");
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
inline Pointer2<T>::operator T** () const
{
	return mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline T*& Pointer2<T>::operator* () const
{
	return *mData;
}
//----------------------------------------------------------------------------
template <typename T>
Pointer2<T>& Pointer2<T>::operator= (T** data)
{
	MutexEnter();

	if (mData != data)
	{
		RMIterator iter;

		if (data)
		{
			iter = msMap.find(data);
			if (iter != msMap.end())
			{
				++iter->second;
			}
			else
			{
				msMap[data] = 1;
			}
		}

		if (mData)
		{
			iter = msMap.find(mData);
			if (iter != msMap.end())
			{
				if (--iter->second == 0)
				{
					msMap.erase(mData);
					delete2(mData);
				}
			}
			else
			{
				assertion(false, "mData must be in the map\n");
			}
		}

		mData = data;
	}

	MutexLeave();
	return *this;
}
//----------------------------------------------------------------------------
template <typename T>
Pointer2<T>& Pointer2<T>::operator= (const Pointer2& pointer)
{
	MutexEnter();

	if (mData != pointer.mData)
	{
		RMIterator iter;

		if (pointer.mData)
		{
			iter = msMap.find(pointer.mData);
			if (iter != msMap.end())
			{
				++iter->second;
			}
			else
			{
				assertion(false, "pointer.mData must be in the map\n");
			}
		}

		if (mData)
		{
			iter = msMap.find(mData);
			if (iter != msMap.end())
			{
				if (--iter->second == 0)
				{
					msMap.erase(mData);
					delete2(mData);
				}
			}
			else
			{
				assertion(false, "mData must be in the map\n");
			}
		}

		mData = pointer.mData;
	}

	MutexLeave();
	return *this;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer2<T>::operator== (T** data) const
{
	return mData == data;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer2<T>::operator!= (T** data) const
{
	return mData != data;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer2<T>::operator== (const Pointer2& pointer) const
{
	return mData == pointer.mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer2<T>::operator!= (const Pointer2& pointer) const
{
	return mData != pointer.mData;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Pointer3
//----------------------------------------------------------------------------
template <typename T>
Pointer3<T>::Pointer3 (T*** data)
{
	MutexEnter();

	mData = data;
	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			++iter->second;
		}
		else
		{
			msMap[mData] = 1;
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
Pointer3<T>::Pointer3 (const Pointer3& pointer)
{
	MutexEnter();

	mData = pointer.mData;
	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			++iter->second;
		}
		else
		{
			assertion(false, "pointer.mData must be in the map\n");
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
Pointer3<T>::~Pointer3 ()
{
	MutexEnter();

	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			if (--iter->second == 0)
			{
				msMap.erase(mData);
				delete3(mData);
			}
		}
		else
		{
			assertion(false, "mData must be in the map\n");
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
inline Pointer3<T>::operator T*** () const
{
	return mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline T**& Pointer3<T>::operator* () const
{
	return *mData;
}
//----------------------------------------------------------------------------
template <typename T>
Pointer3<T>& Pointer3<T>::operator= (T*** data)
{
	MutexEnter();

	if (mData != data)
	{
		RMIterator iter;

		if (data)
		{
			iter = msMap.find(data);
			if (iter != msMap.end())
			{
				++iter->second;
			}
			else
			{
				msMap[data] = 1;
			}
		}

		if (mData)
		{
			iter = msMap.find(mData);
			if (iter != msMap.end())
			{
				if (--iter->second == 0)
				{
					msMap.erase(mData);
					delete3(mData);
				}
			}
			else
			{
				assertion(false, "mData must be in the map\n");
			}
		}

		mData = data;
	}

	MutexLeave();
	return *this;
}
//----------------------------------------------------------------------------
template <typename T>
Pointer3<T>& Pointer3<T>::operator= (const Pointer3& pointer)
{
	MutexEnter();

	if (mData != pointer.mData)
	{
		RMIterator iter;

		if (pointer.mData)
		{
			iter = msMap.find(pointer.mData);
			if (iter != msMap.end())
			{
				++iter->second;
			}
			else
			{
				assertion(false, "pointer.mData must be in the map\n");
			}
		}

		if (mData)
		{
			iter = msMap.find(mData);
			if (iter != msMap.end())
			{
				if (--iter->second == 0)
				{
					msMap.erase(mData);
					delete3(mData);
				}
			}
			else
			{
				assertion(false, "mData must be in the map\n");
			}
		}

		mData = pointer.mData;
	}

	MutexLeave();
	return *this;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer3<T>::operator== (T*** data) const
{
	return mData == data;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer3<T>::operator!= (T*** data) const
{
	return mData != data;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer3<T>::operator== (const Pointer3& pointer) const
{
	return mData == pointer.mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer3<T>::operator!= (const Pointer3& pointer) const
{
	return mData != pointer.mData;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Pointer4
//----------------------------------------------------------------------------
template <typename T>
Pointer4<T>::Pointer4 (T**** data)
{
	MutexEnter();

	mData = data;
	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			++iter->second;
		}
		else
		{
			msMap[mData] = 1;
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
Pointer4<T>::Pointer4 (const Pointer4& pointer)
{
	MutexEnter();

	mData = pointer.mData;
	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			++iter->second;
		}
		else
		{
			assertion(false, "pointer.mData must be in the map\n");
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
Pointer4<T>::~Pointer4 ()
{
	MutexEnter();

	if (mData)
	{
		RMIterator iter = msMap.find(mData);
		if (iter != msMap.end())
		{
			if (--iter->second == 0)
			{
				msMap.erase(mData);
				delete4(mData);
			}
		}
		else
		{
			assertion(false, "mData must be in the map\n");
		}
	}

	MutexLeave();
}
//----------------------------------------------------------------------------
template <typename T>
inline Pointer4<T>::operator T**** () const
{
	return mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline T***& Pointer4<T>::operator* () const
{
	return *mData;
}
//----------------------------------------------------------------------------
template <typename T>
Pointer4<T>& Pointer4<T>::operator= (T**** data)
{
	MutexEnter();

	if (mData != data)
	{
		RMIterator iter;

		if (data)
		{
			iter = msMap.find(data);
			if (iter != msMap.end())
			{
				++iter->second;
			}
			else
			{
				msMap[data] = 1;
			}
		}

		if (mData)
		{
			iter = msMap.find(mData);
			if (iter != msMap.end())
			{
				if (--iter->second == 0)
				{
					msMap.erase(mData);
					delete4(mData);
				}
			}
			else
			{
				assertion(false, "mData must be in the map\n");
			}
		}

		mData = data;
	}

	MutexLeave();
	return *this;
}
//----------------------------------------------------------------------------
template <typename T>
Pointer4<T>& Pointer4<T>::operator= (const Pointer4& pointer)
{
	MutexEnter();

	if (mData != pointer.mData)
	{
		RMIterator iter;

		if (pointer.mData)
		{
			iter = msMap.find(pointer.mData);
			if (iter != msMap.end())
			{
				++iter->second;
			}
			else
			{
				assertion(false, "pointer.mData must be in the map\n");
			}
		}

		if (mData)
		{
			iter = msMap.find(mData);
			if (iter != msMap.end())
			{
				if (--iter->second == 0)
				{
					msMap.erase(mData);
					delete4(mData);
				}
			}
			else
			{
				assertion(false, "mData must be in the map\n");
			}
		}

		mData = pointer.mData;
	}

	MutexLeave();
	return *this;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer4<T>::operator== (T**** data) const
{
	return mData == data;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer4<T>::operator!= (T**** data) const
{
	return mData != data;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer4<T>::operator== (const Pointer4& pointer) const
{
	return mData == pointer.mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer4<T>::operator!= (const Pointer4& pointer) const
{
	return mData != pointer.mData;
}
//----------------------------------------------------------------------------