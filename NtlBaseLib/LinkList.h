#ifndef _LINKLIST
#define _LINKLIST

#pragma once

#include "Base.h"

class LinkObject
{
public:
	LinkObject()
		:_pPrev(NULL), _pNext(NULL) {}
	virtual ~LinkObject() {}

public:
	LinkObject* GetNext() const { return _pNext; }
	void SetNext(LinkObject* pNext) { _pNext = pNext; }
	LinkObject* GetPrev() const { return _pPrev; }
	void SetPrev(LinkObject* pPrev) { _pPrev = pPrev; }

private:
	LinkObject* _pPrev;
	LinkObject* _pNext;
};

class LinkList
{
public:
	LinkList(void)
		:_Head(NULL), _Tail(NULL), _Count(0), _MaxCount(0) {}
	virtual ~LinkList(void) {}

	bool IsEmpty() const { return _Count == 0; }
	int	GetCount() const { return _Count; }
	int	GetMaxCount() const { return _MaxCount; }
	LinkObject* GetFirst() const { return _Head; }
	LinkObject* GetLast() const { return _Tail; }
	void Append(LinkObject * pLinkObject);
	void Prepend(LinkObject * pLinkObject);
	void InsertBefore(LinkObject* BaseObject, LinkObject* pLinkObject);
	void InsertAfter(LinkObject* BaseObject, LinkObject * pLinkObject);
	void Remove(LinkObject* pLinkObject);
	void RemoveAll();
	bool Find(LinkObject* BaseObject);
	LinkObject* Pop(bool Front = false);
	void Push(LinkObject* pLinkObject, bool Front = true);
	LinkObject*	PopFront();
	LinkObject* PopBack();
	void PushBack(LinkObject* pLinkObject) { Append(pLinkObject); }
	void PushFront(LinkObject * pLinkObject) { Prepend(pLinkObject); }

private:
	LinkObject* _Head;
	LinkObject* _Tail;
	int _Count;
	int _MaxCount;

};


inline void LinkList::Append(LinkObject* pLinkObject)
{
	if (!_Head)	_Head = pLinkObject;
	pLinkObject->SetPrev(_Tail);
	if (_Tail) _Tail->SetNext(pLinkObject);
	_Tail = pLinkObject;
	pLinkObject->SetNext(NULL);
	++_Count;

	if (_Count > _MaxCount) _MaxCount = _Count;
}

inline void LinkList::Prepend(LinkObject* pLinkObject)
{
	if (!_Tail) _Tail = pLinkObject;
	pLinkObject->SetNext(_Head);
	if (_Head) _Head->SetPrev(pLinkObject);
	_Head = pLinkObject;
	pLinkObject->SetPrev(NULL);
	++_Count;

	if (_Count > _MaxCount)	_MaxCount = _Count;
}

inline void LinkList::InsertBefore(LinkObject* BaseObject, LinkObject* pLinkObject)
{
	if (!BaseObject)
	{
		Prepend(pLinkObject);
	}
	else
	{
		LinkObject* pPrev = BaseObject->GetPrev();

		pLinkObject->SetNext(BaseObject);
		pLinkObject->SetPrev(pPrev);
		BaseObject->SetPrev(pLinkObject);

		if (!pPrev)
		{
			_Head = pLinkObject;
		}
		else
		{
			pPrev->SetNext(pLinkObject);
		}

		++_Count;

		if (_Count > _MaxCount)	_MaxCount = _Count;
	}
}

inline void LinkList::InsertAfter(LinkObject* BaseObject, LinkObject* pLinkObject)
{
	if (!BaseObject)
	{
		Append(pLinkObject);
	}
	else
	{
		LinkObject * pNext = BaseObject->GetNext();

		pLinkObject->SetPrev(BaseObject);
		pLinkObject->SetNext(pNext);
		BaseObject->SetNext(pLinkObject);

		if (!pNext)
		{
			_Tail = pLinkObject;
		}
		else
		{
			pNext->SetPrev(pLinkObject);
		}

		++_Count;

		if (_Count > _MaxCount)	_MaxCount = _Count;
	}
}

inline void LinkList::Remove(LinkObject* pLinkObject)
{
	LinkObject* pPrev = pLinkObject->GetPrev();
	LinkObject* pNext = pLinkObject->GetNext();

	if (pNext)
	{
		pNext->SetPrev(pPrev);
	}
	else
	{
		_Tail = pPrev;
	}

	if (pPrev)
	{
		pPrev->SetNext(pNext);
	}
	else
	{
		_Head = pNext;
	}

	pLinkObject->SetPrev(NULL);
	pLinkObject->SetNext(NULL);

	--_Count;

}

inline void LinkList::RemoveAll()
{
	while (_Count > 0)
	{
		Remove(_Head);
	}
}

inline bool LinkList::Find(LinkObject* BaseObject)
{
	LinkObject * Object = _Head;

	while (Object)
	{
		if (Object == BaseObject)
		{
			return true;
		}

		Object = Object->GetNext();
	}

	return false;
}

inline LinkObject* LinkList::PopFront()
{
	LinkObject* pLinkObject = _Head;

	if (pLinkObject)
	{
		Remove(pLinkObject);
	}

	return pLinkObject;
}

inline LinkObject* LinkList::PopBack()
{
	LinkObject* pLinkObject = _Tail;

	if (pLinkObject)
	{
		Remove(pLinkObject);
	}

	return pLinkObject;
}

inline LinkObject* LinkList::Pop(bool Front)
{
	return Front ? PopFront() : PopBack();
}

inline void LinkList::Push(LinkObject * pLinkObject, bool Front)
{
	return Front ? Prepend(pLinkObject) : Append(pLinkObject);
}


#endif