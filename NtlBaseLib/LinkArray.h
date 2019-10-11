#ifndef _LINKARRAY
#define _LINKARRAY

#pragma once

#include "Base.h"
#include <crtdbg.h>

template<class TYPE, unsigned int MAX_SIZE = 3, unsigned int EXTRA_SIZE = 0>
class LinkArray
{
public:
	typedef unsigned int POSITION;

protected:
	struct BUCKET
	{
		POSITION prev;
		POSITION next;
		bool empty;
		TYPE data;
		bool IsEmpty() const { return empty; }
		bool SetEmpty(const bool flag) { empty = flag; }
		POSITION GetPrev() const { return prev; }
		POSITION GetNext() const { return next; }
		POSITION SetPrev(const POSITION pos) { prev = pos; }
		POSITION SetNext(const POSITION pos) { next = pos; }
		void SetData(const TYPE& t) { data = t; }
		TYPE& GetData() { return data; }
	};

public:
	LinkArray()	:_end(MAX_SIZE + EXTRA_SIZE) { Precreate(); }
	virtual ~LinkArray() {}

	unsigned int GetSize() { return _size; }
	unsigned int GetMaxSize() { return _maxSize; }
	unsigned int GetCapacity() { return MAX_SIZE; }
	unsigned int GetFreeSize() { return MAX_SIZE - _size; }
	bool IsEmpty() { return _begin == _end; }
	POSITION Begin();
	POSITION rBegin();
	POSITION Prev(POSITION pos);
	POSITION Next(POSITION pos);
	POSITION End() { return _end; }
	TYPE* Alloc(POSITION & pos);
	POSITION Free(TYPE* t);
	POSITION Insert(TYPE& t);
	POSITION Remove(POSITION pos);
	void Clear();
	TYPE& GetAt(POSITION pos);
	TYPE* GetPtr(POSITION pos);
	void SetAt(POSITION pos, TYPE& t);
	POSITION GetPosition(TYPE* t);

private:
	void Precreate();

protected:
	unsigned int _size;	
	unsigned int _maxSize;
	POSITION _end;
	POSITION _begin;
	POSITION _rBegin;
	POSITION _emptyHead;
	POSITION _emptyTail; 
	BUCKET _array[MAX_SIZE + EXTRA_SIZE];
};

template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline void LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::Clear()
{
	_ASSERT(_end > 3);

	for (POSITION pos = 0; pos != _end; pos++)
	{
		_array[pos].empty = true;
		_array[pos].prev = pos - 1;
		_array[pos].next = pos + 1;
	}

	_array[0].prev = _array[_end - 1].next = _end;

	_size = 0;
	_maxSize = 0;
	_begin = _rBegin = _end;

	_emptyHead = 0;
	_emptyTail = _end - 1;
}

template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline void LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::Precreate()
{
	_ASSERT(_end > 3);

	for (POSITION pos = 0; pos != _end; pos++)
	{
		_array[pos].empty = true;
		_array[pos].prev = pos - 1;
		_array[pos].next = pos + 1;
	}

	_array[0].prev = _array[m_end - 1].next = _end;

	_size = 0;
	_maxSize = 0;
	_begin = _rBegin = _end;

	_emptyHead = 0;
	_emptyTail = _end - 1;
}


template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline typename LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::POSITION LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::Begin()
{
	return _begin;
}


template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline typename LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::POSITION LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::rBegin()
{
	return _rBegin;
}


template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline typename LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::POSITION LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::Prev(POSITION pos)
{
	_ASSERT(pos < _end);
	_ASSERT(!IsEmpty());

	return _array[pos].prev;
}


template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline typename LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::POSITION LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::Next(POSITION pos)
{
	_ASSERT(pos < _end);
	_ASSERT(!IsEmpty());

	return _array[pos].next;
}


template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline TYPE* LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::Alloc(POSITION& pos)
{
	if (_emptyTail == _end || !GetFreeSize())
		return NULL;

	pos = _emptyHead;

	_emptyHead = _array[pos].next;

	if (_emptyHead != _end)
		_array[_emptyHead].prev = _end;
	else
		_emptyTail = _end;

	_array[pos].next = _begin;

	if (_array[pos].next != _end)
		_array[_array[pos].next].prev = pos;

	_begin = pos;
	if (_rBegin == _end)
		_rBegin = pos;

	++_size;

	if (_size > _maxSize)
	{
		_maxSize = _size;
	}

	_array[pos].empty = false;

	return &_array[pos].data;
}

template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline typename LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::POSITION LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::Free(TYPE* p)
{
	POSITION pos = GetPosition(p);

	return Remove(pos);
}


template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline typename LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::POSITION LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::Insert(TYPE& t)
{
	POSITION pos = _end;

	TYPE* p = Alloc(pos);
	if (p)
	{
		*p = t;
	}

	return pos;
}


template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline typename LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::POSITION LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::Remove(POSITION pos)
{
	if (pos >= _end || IsEmpty())
		return _end;

	POSITION ret = Next(pos);

	if (_array[pos].next != _end)
		_array[_array[pos].next].prev = _array[pos].prev;


	if (_array[pos].prev != _end)
		_array[_array[pos].prev].next = _array[pos].next;
	else
		_begin = _array[pos].next;


	if (_rBegin == pos)
		_rBegin = _array[pos].prev;

	_array[pos].prev = _emptyTail;
	_array[pos].next = _end;

	if (_array[pos].prev != _end)
		_array[_array[pos].prev].next = pos;
	else
		_emptyHead = pos;

	_emptyTail = pos;

	--_size;

	_array[pos].empty = true;

	return ret;
}


template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline typename LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::POSITION LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::GetPosition(TYPE* t)
{
	_ASSERT(t >= (TYPE*)&_array[0]);
	_ASSERT(t < (TYPE*)&_array[_end]);

	BUCKET* Bucket = (BUCKET*)(size_t(t) - (sizeof(BUCKET) - sizeof(TYPE)));

	return (POSITION)(size_t(Bucket) - size_t(_array)) / sizeof(BUCKET);
}


template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline TYPE* LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::GetPtr(POSITION pos)
{
	if (pos >= End() || _array[pos].empty)
		return NULL;

	return &(_array[pos].data);
}


template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline TYPE& LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::GetAt(POSITION pos)
{
	_ASSERT(pos < End());
	_ASSERT(!_array[pos].empty);

	return *&(_array[pos].data);
}


template<class TYPE, unsigned int MAX_SIZE, unsigned int EXTRA_SIZE>
inline void LinkArray<TYPE, MAX_SIZE, EXTRA_SIZE>::SetAt(POSITION pos, TYPE& t)
{
	_ASSERT(pos < End());
	_ASSERT(_array[pos].empty);

	_array[pos].data = t;
}

template<class TYPE>
class LinkArray_Static
{
public:
	typedef unsigned int POSITION;

protected:
	struct BUCKET
	{
		POSITION prev;
		POSITION next;
		bool empty;
		TYPE data;
		bool IsEmpty() const { return empty; }
		bool SetEmpty(const bool flag) { empty = flag; }
		POSITION GetPrev() const { return prev; }
		POSITION GetNext() const { return next; }
		POSITION SetPrev(const POSITION pos) { prev = pos; }
		POSITION SetNext(const POSITION pos) { next = pos; }
		void SetData(const TYPE& t) { data = t; }
		TYPE& GetData() { return data; }
	};

public:
	LinkArray_Static() { Init(); }
	virtual ~LinkArray_Static() { Destroy(); }

	bool Create(int MaxSize, int ExtraSize);
	void Destroy();

	unsigned int GetSize() { return _size; }
	unsigned int GetMaxSize() { return _maxSize; }
	unsigned int GetCapacity() { return MAX_SIZE; }
	unsigned int GetFreeSize() { return MAX_SIZE - _size; }
	bool IsEmpty() { return _begin == _end; }
	POSITION Begin();
	POSITION rBegin();
	POSITION Prev(POSITION pos);
	POSITION Next(POSITION pos);
	POSITION End() { return _end; }
	POSITION EmptyHead() { return _emptyHead; }
	TYPE* Alloc(POSITION & pos);
	POSITION Free(TYPE * t);
	POSITION Insert(TYPE& t);
	POSITION Remove(POSITION pos);
	void Clear();
	TYPE& GetAt(POSITION pos);
	TYPE* GetPtr(POSITION pos);
	void SetAt(POSITION pos, TYPE& t);
	POSITION GetPosition(TYPE* t);

private:
	void Init();
	void Precreate();

protected:
	unsigned int _size;
	unsigned int _maxSize;
	POSITION _end;
	POSITION _begin;
	POSITION _rBegin;
	POSITION _emptyHead;
	POSITION _emptyTail;
	BUCKET*	 _array;
	int MAX_SIZE;
	int EXTRA_SIZE;
};

template<class TYPE>
inline bool LinkArray_Static<TYPE>::Create(int MaxSize, int ExtraSize)
{
	_ASSERT(NULL == _array);

	MAX_SIZE = MaxSize;

	EXTRA_SIZE = ExtraSize;

	_end = MAX_SIZE + EXTRA_SIZE;

	_ASSERT(_end > 3);

	_array = new BUCKET[_end];
	if (NULL == _array)
		return false;

	Precreate();

	return true;
}


template<class TYPE>
inline void LinkArray_Static<TYPE>::Destroy()
{
	SAFE_DELETE_ARRAY(_array);
}


template<class TYPE>
inline void LinkArray_Static<TYPE>::Init()
{
	_array = NULL;
	_begin = _rBegin = _end = _size = _maxSize = _emptyHead = _emptyTail = MAX_SIZE = EXTRA_SIZE = 0;
}


template<class TYPE>
inline void LinkArray_Static<TYPE>::Clear()
{
	_ASSERT(NULL != _array);

	for (POSITION pos = 0; pos != _end; pos++)
	{
		_array[pos].empty = true;
		_array[pos].prev = pos - 1;
		_array[pos].next = pos + 1;
	}

	_array[0].prev = _array[m_end - 1].next = _end;

	_size = 0;
	_maxSize = 0;
	_begin = _rBegin = _end;

	_emptyHead = 0;
	_emptyTail = _end - 1;
}


template<class TYPE>
inline void LinkArray_Static<TYPE>::Precreate()
{
	_ASSERT(NULL != _array);

	for (POSITION pos = 0; pos != _end; pos++)
	{
		_array[pos].empty = true;
		_array[pos].prev = pos - 1;
		_array[pos].next = pos + 1;
	}

	_array[0].prev = _array[_end - 1].next = _end;

	_size = 0;
	_begin = _rBegin = _end;

	_emptyHead = 0;
	_emptyTail = _end - 1;
}


template<class TYPE>
inline typename LinkArray_Static<TYPE>::POSITION LinkArray_Static<TYPE>::Begin()
{
	_ASSERT(NULL != _array);

	return _begin;
}

template<class TYPE>
inline typename LinkArray_Static<TYPE>::POSITION LinkArray_Static<TYPE>::rBegin()
{
	_ASSERT(NULL != _array);

	return _rBegin;
}



template<class TYPE>
inline typename LinkArray_Static<TYPE>::POSITION LinkArray_Static<TYPE>::Prev(POSITION pos)
{
	_ASSERT(NULL != _array);
	_ASSERT(pos < _end);

	return _array[pos].prev;
}


template<class TYPE>
inline typename LinkArray_Static<TYPE>::POSITION LinkArray_Static<TYPE>::Next(POSITION pos)
{
	_ASSERT(NULL != _array);
	_ASSERT(pos < _end);

	return _array[pos].next;
}


template<class TYPE>
inline TYPE* LinkArray_Static<TYPE>::Alloc(POSITION& pos)
{
	_ASSERT(NULL != _array);

	if (_emptyTail == _end || !GetFreeSize())
		return NULL;

	pos = _emptyHead;

	_emptyHead = _array[pos].next;

	if (_emptyHead != _end)
		_array[_emptyHead].prev = _end;
	else
		_emptyTail = _end;

	_array[pos].next = _begin;

	if (_array[pos].next != _end)
		_array[_array[pos].next].prev = pos;


	_begin = pos;
	if (_rBegin == _end)
		_rBegin = pos;


	++_size;

	if (_size > _maxSize)
	{
		_maxSize = _size;
	}

	_array[pos].empty = false;

	return &_array[pos].data;
}


template<class TYPE>
inline typename LinkArray_Static<TYPE>::POSITION LinkArray_Static<TYPE>::Free(TYPE* p)
{
	_ASSERT(NULL != _array);

	POSITION pos = GetPosition(p);

	return Remove(pos);
}


template<class TYPE>
inline typename LinkArray_Static<TYPE>::POSITION LinkArray_Static<TYPE>::Insert(TYPE& t)
{
	_ASSERT(NULL != _array);

	POSITION pos = _end;

	TYPE* p = Alloc(pos);
	if (p)
	{
		*p = t;
	}

	return pos;
}


template<class TYPE>
inline typename LinkArray_Static<TYPE>::POSITION LinkArray_Static<TYPE>::Remove(POSITION pos)
{
	_ASSERT(NULL != _array);

	if (pos >= _end || IsEmpty())
		return _end;

	POSITION ret = Next(pos);

	if (_array[pos].next != _end)
		_array[_array[pos].next].prev = _array[pos].prev;


	if (_array[pos].prev != _end)
		_array[_array[pos].prev].next = _array[pos].next;
	else
		_begin = _array[pos].next;


	if (_rBegin == pos)
		_rBegin = _array[pos].prev;

	_array[pos].prev = _emptyTail;
	_array[pos].next = _end;


	if (_array[pos].prev != _end)
		_array[_array[pos].prev].next = pos;
	else
		_emptyHead = pos;


	_emptyTail = pos;

	--_size;

	_array[pos].empty = true;

	return ret;
}


template<class TYPE>
inline typename LinkArray_Static<TYPE>::POSITION LinkArray_Static<TYPE>::GetPosition(TYPE* t)
{
	_ASSERT(NULL != _array);
	_ASSERT(t >= (TYPE*)&_array[0]);
	_ASSERT(t < (TYPE*)&_array[_end]);

	BUCKET* Bucket = (BUCKET*)(size_t(t) - (sizeof(BUCKET) - sizeof(TYPE)));

	return (POSITION)(size_t(Bucket) - size_t(_array)) / sizeof(BUCKET);
}


template<class TYPE>
inline TYPE* LinkArray_Static<TYPE>::GetPtr(POSITION pos)
{
	_ASSERT(NULL != _array);

	if (pos >= End() || _array[pos].empty)
		return NULL;

	return &(_array[pos].data);
}


template<class TYPE>
inline TYPE& LinkArray_Static<TYPE>::GetAt(POSITION pos)
{
	_ASSERT(NULL != _array);
	_ASSERT(pos < End());
	_ASSERT(!_array[pos].empty);

	return *&(_array[pos].data);
}


template<class TYPE>
inline void LinkArray_Static<TYPE>::SetAt(POSITION pos, TYPE& t)
{
	_ASSERT(NULL != _array);
	_ASSERT(pos < End());
	_ASSERT(_array[pos].empty);

	_array[pos].data = t;
}

#endif