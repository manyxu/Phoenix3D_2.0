/*
*
* ÎÄ¼þÃû³Æ	£º	TdKeyFrameArray.inl
*
*/

//----------------------------------------------------------------------------
template <typename T>
KeyframeArray<T>::KeyframeArray ()
:
mInterplateType(IM_LINEAR)
{

}
//----------------------------------------------------------------------------
template <typename T>
KeyframeArray<T>::KeyframeArray (size_t n)
:
mInterplateType(IM_LINEAR),
mKeyframeArray(n)
{

}
//----------------------------------------------------------------------------
template <typename T>
KeyframeArray<T>::~KeyframeArray ()
{

}
//----------------------------------------------------------------------------
template <typename T>
bool KeyframeArray<T>::HasSeq (int seq)
{
	if (mRanges.size() == 0)
		return false;

	if (seq<0 || seq>=(int)(mRanges.size()))
		return false;

	if (mRanges[seq].Begin > mRanges[seq].End)
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <typename T>
int KeyframeArray<T>::GetNumKeys ()
{
	return (int)mKeyframeArray.size();
}
//----------------------------------------------------------------------------
template <typename T>
int KeyframeArray<T>::GetValue (int seq, unsigned int tick, void *data)
{
	return GetValue(seq, tick, *(T*)data);
}
//----------------------------------------------------------------------------
template <typename T>
void KeyframeArray<T>::GetValue(int seq, unsigned int tick, T &data, bool loop)
{
	assertion((int)(mKeyframeArray.size()) > 0, 
		"num of Keyframe should be large than zero.");

	data = mKeyframeArray[0].Data;

	int start, end;
	int numTotalkeys = (int)mKeyframeArray.size();
	int nSeq = (int)mRanges.size();

	if (nSeq == 0)
	{
		start = 0;
		end = numTotalkeys-1;
	}
	else
	{
		assertion(seq>=0 && seq<nSeq, "seq should int right range.");

		start = mRanges[seq].Begin;
		end = mRanges[seq].End;

		assertion(start <= end, "start should not be larger than end.");
	}

	if (mInterplateType == IM_RANDOM)
	{
		int i = start;
		if (end > start)
		{
			i += Mathf::IntervalRandom(0.0f, 9999.0f)%(end - start);
		}

		data = mKeyframeArray[i].Data;

		return;
	}

	tick -= mKeyframeArray[start].Tick;
	unsigned int dtick = (mKeyframeArray[end].Tick - mKeyframeArray[start].Tick + 1);

	if (dtick == 0)
		tick = mKeyframeArray[start].Tick;
	else
	{
		if (loop)
			tick = mKeyframeArray[start].Tick + (tick%dtick);
		else if (dtick < tick)
			tick = mKeyframeArray[end].Tick;
		else
			tick = mKeyframeArray[start].Tick + tick;
	}

	for ( ; ; )
	{
		if (start >= end-1)
			break;

		int middle = (start+end)/2;

		if (tick < mKeyframeArray[middle].Tick)
			end = middle;
		else
			start = middle;
	}

	if (start == end)
		data = mKeyframeArray[start].Data;
	else
	{
		unsigned int tick0 = mKeyframeArray[start].Tick;
		unsigned int tick1 = mKeyframeArray[end].Tick;

		if (tick0 == tick1)
			return;

		assertion(tick0<tick1, "tick0 must be less than tick1.");

		float t = float(int(tick-tick0)/double(tick1-tick0));

		if (mInterplateType == IM_LINEAR)
			Lerp(data, t, mKeyframeArray[start].Data, 
			mKeyframeArray[end].Data);
		else
			Hermite(data, t, mKeyframeArray[start].Data, 
			mKeyframeArray[end].Data, mCtrlPoints[start].Out,
			mCtrlPoints[end].In);
	}
}
//----------------------------------------------------------------------------
template <typename T>
void KeyframeArray<T>::SetNumKey (int num)
{
	mKeyframeArray.resize(num);
}
//----------------------------------------------------------------------------
template <typename T>
void KeyframeArray<T>::SetKeyframe (int i, unsigned int tick, T data)
{
	assertion(i<mKeyframeArray.size(), "i should in right range.");

	mKeyframeArray[i]. = tick;
	mKeyframeArray[i].Data = data;
}
//----------------------------------------------------------------------------
template <typename T>
void KeyframeArray<T>::GetKeyframe (int i, unsigned int &tick, T &data)
{

}
//----------------------------------------------------------------------------