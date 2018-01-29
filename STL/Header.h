#pragma once
#include <iostream>
#include <conio.h>

using namespace std;
template<class T>

class My_container
{
public:
	typedef T value_type;
	typedef size_t size_type;

private:
	struct Node
	{
		value_type value;
		Node * pNext;
		Node * pPrev;
		Node(const value_type &val) :value(val), pNext(0)
		{
		}
	};
	Node * pBegin;
	Node * pQueue;
	size_type nElems;

public:
	//Default constructor
	My_container() throw() :pBegin(0), nElems(0)
	{
	}
	bool empty() const throw()
	{
		return size() == 0;
	}
	size_type size() const throw()
	{
		return nElems;
	}

private:
	Node * last() throw()//возвращает указатель на последний объект типа Node
	{
		if (empty()) return 0;
		Node *p = pBegin;
		while (p->pNext)
			p = p->pNext;
		return p;
	}
public:
	void add(const value_type & val)
	{
		pQueue = pBegin;
		Node *pAdd = new Node(val);
		// if list is empty
		if (pBegin == NULL)
		{
			pBegin = pAdd;
			pAdd->pNext = pBegin;
			pBegin = pAdd;
			pAdd->pPrev = NULL;
			pAdd->pNext = NULL;
			++nElems;
			return;
		}
		Node * pCur = pQueue;
		while (pCur != NULL && pCur->value < val)//добавляем в конец списка
		{
			// if there is the End of the list
			if (pCur->pNext == NULL)
			{
				pCur->pNext = pAdd;//->
				pCur->pNext->pPrev = pCur;//<-> -_-
				++nElems;
				break;
			}

			pCur = pCur->pNext;
		}

		while (pCur != NULL && pCur->value > val)//сортируем список
		{
			if (pCur->pPrev == NULL)
			{
				// if there is the Begin of the list

				if (pBegin == NULL)
				{
					pBegin = pAdd;
					pAdd->pNext = pBegin;
					pBegin = pAdd;
					pAdd->pPrev = NULL;
					pAdd->pNext = NULL;
					return;
				}

				pAdd->pNext = pBegin;
				pBegin->pPrev = pAdd;
				pBegin = pAdd;
				pAdd->pPrev = NULL;
				++nElems;
			}
			if (pCur->pPrev->value < val)
			{
				pAdd->pNext = pCur;
				pAdd->pPrev = pCur->pPrev;
				pCur->pPrev->pNext = pAdd;
				pCur->pPrev = pAdd;
			}
			pCur = pCur->pPrev;
		}
	}

	void clear() throw()
	{
		while (pBegin)
		{
			Node *p = pBegin->pNext;
			delete pBegin;
			pBegin = p;
		}
		nElems = 0;
	}
	//Destructor:
	~My_container() throw()
	{
		clear();
	}

	//Iterators:
	class iterator
	{
		Node * pCur;
	public:
		iterator(Node *p) throw()
			:pCur(p)
		{}
		bool operator==(const iterator & iter)const throw()
		{
			return pCur == iter.pCur;
		}
		bool operator!=(const iterator & iter)const throw()
		{
			return !(*this == iter);
		}
		iterator & operator++()
		{
			pCur = pCur->pNext;
			return *this;
		}
		iterator operator++(int)
		{
			iterator temp(*this);
			operator++();
			return temp;
		}
		iterator & operator--()
		{
			pCur = pCur->pPrev;
			return *this;
		}
		iterator operator--(int)
		{
			iterator temp(*this);
			operator--();
			return temp;
		}
		value_type & operator*()throw()
		{
			return pCur->value;
		}
		value_type operator*() const
		{
			return pCur->value;
		}
		value_type operator->()
		{
			return pCur->value;
		}
		const value_type operator->() const
		{
			return pCur->value;
		}
	};

	iterator begin() throw() {
		return iterator(pBegin);
	}
	iterator begin() const throw() {
		return iterator(pBegin);
	}
	iterator end() throw() {
		return iterator(0);
	}
	iterator end() const throw() {
		return iterator(0);
	}

	//Copy constructor:
	My_container(const My_container & lst)
		:pBegin(0), nElems(0)
	{
		for (iterator i = lst.begin(); i != lst.end(); ++i)
			add(*i);
	}
	void swap(My_container & lst) throw()
	{
		swap(pBegin, lst.pBegin);
		swap(nElems, lst.nElems);
	}
	My_container & operator=(const My_container & lst)
	{
		My_container(lst).swap(*this);
		return *this;
	}

	//Conversion constructor
	template<class U>
	My_container(const My_container<U> &lst)
		:pBegin(0), nElems(0)
	{
		for (typename My_container<U>::iterator iter = lst.begin(); iter != lst.end(); ++iter)
			add(*iter);
	}

	template<class U>
	My_container & operator=(const My_container<U> &lst)
	{
		My_container(lst).swap(*this);
		return *this;
	}

	//Sequence constructor:
	template<class Iter>
	My_container(Iter first, Iter last)
		:pBegin(0), nElems(0)
	{
		for (; first != last; ++first)
			add(*first);
	}

	//Reverse iterator

	template<iterator>
	class reverse_iterator
	{
		Node * pCur;
	public:
		reverse_iterator(Node *p) throw()
			:pCur(p)
		{}
		reverse_iterator<iterator> rbegin()
		{
			return iterator(0);
		}

		reverse_iterator<iterator> rend()
		{
			return iterator(pBegin);
		}
	private:

	};

	


};
