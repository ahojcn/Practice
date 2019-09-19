#pragma once

namespace ahoj
{
	template<class T>
	struct ListNode
	{
		ListNode<T>* next;
		ListNode<T>* prev;
		T _val;

		ListNode(const T& val = T())
			: next(nullptr)
			, prev(nullptr)
			, _val(val)
		{}
	};

	// ����������ԭ��ָ̬����з�װ
	// �������Ĳ�������������Ҫ�߱�ָ�����Ϊ
	// *    ->    ++    --    ==    !=
	// ��Ϊ��˫������������Ҫ֧�� -- ������
	template <class T>
	struct ListIterator
	{
		typedef ListNode<T> Node;
		typedef ListIterator<T> self;
		Node* _pNode;

		ListIterator(Node* pNode = nullptr)
			: _pNode(pNode)
		{}

		T& operator*()
		{
			return _pNode->_val;
		}

		T* operator->()
		{
			return &(_pNode->_val);
		}

		// ++ǰ��
		self& operator++()
		{
			_pNode = _pNode->next;
			return *this;
		}

		// ����++
		self operator++(int)
		{
			self tmp(*this);
			_pNode = _pNode->next;
			return tmp;
		}

		// --ǰ��
		self& operator--()
		{
			_pNode = _pNode->prev;
			return *this;
		}

		// ����--
		self operator--(int)
		{
			self tmp(*this);
			_pNode = _pNode->prev;
			return tmp;
		}

		bool operator==(const self& s)
		{
			return _pNode == s._pNode;
		}

		bool operator!=(const self& s)
		{
			return !this->operator==(s);
		}
	};

	// ��ͷ˫��ѭ������
	template <class T>
	class List
	{
	public:
		typedef ListNode<T> Node;
		typedef ListIterator<T> iterator;

	public:
		// construct
		List()
		{
			CreateHead();
		}

		List(size_t n, const T& val)
		{
			CreateHead();
			for (size_t i = 0; i < n; ++i)
			{
				push_back(val);
			}
		}

		List(T* first, T* last)
		{
			CreateHead();
			while (first != last)
			{
				push_back(*first++);
			}
		}

		List(const List<T>& l)
		{
			CreateHead();
			Node* pCur = l._pHead->next;
			while (pCur != l._pHead)
			{
				push_back(pCur->_val);
				pCur = pCur->next;
			}
		}

		List<T>& operator=(const List<T>& l)
		{}

		~List()
		{
			clear();

			delete _pHead;
			_pHead = nullptr;
		}

		// iterator
		iterator begin()
		{
			return iterator(_pHead->next);
		}

		iterator end()
		{
			return iterator(_pHead);
		}

		// capacity
		size_t size() const
		{
			size_t count = 0;
			Node* pCur = _pHead->next;
			while (pCur != _pHead)
			{
				count++;
				pCur = pCur->next;
			}
			return count;
		}

		bool empty() const
		{
			return _pHead == _pHead->next;
		}

		void resize(size_t newSize, const T& val = T())
		{
			size_t oldSize = size();
			if (newSize <= oldSize)
			{
				for (int i = newSize; i < oldSize; ++i)
				{
					pop_back();
				}
			}
			else
			{
				for (int i = oldSize; i < newSize; ++i)
				{
					push_back(val);
				}
			}
		}

		// access
		T& front()
		{
			return _pHead->next->_val;
		}

		const T& front() const
		{
			return _pHead->next->_val;
		}

		T& back()
		{
			return _pHead->prev->_val;
		}

		const T& back() const
		{
			return _pHead->prev->_val;
		}

		// modify
		void push_front(const T& val)
		{
			Node* pNewNode = new Node(val);
			pNewNode->prev = _pHead;
			pNewNode->next = _pHead->next;
			_pHead->next->prev = pNewNode;
			_pHead->next = pNewNode;
		}

		void pop_front()
		{
			if (empty())
			{
				return;
			}

			Node* pDelNode = _pHead->next;
			_pHead->next = pDelNode->next;
			pDelNode->next->prev = _pHead;
			delete pDelNode;
		}

		void push_back(const T& val)
		{
			Node* newNode = new Node(val);
			newNode->prev = _pHead->prev;
			newNode->next = _pHead;
			_pHead->prev->next = newNode;
			_pHead->prev = newNode;
		}

		void pop_back()
		{
			if (empty())
			{
				return;
			}

			Node* pDelNode = _pHead->prev;
			pDelNode->prev->next = _pHead;
			_pHead->prev = pDelNode->prev;
			delete pDelNode;
		}

		iterator insert(iterator pos, const T& val)
		{
			Node* pNewNode = new Node(val);
			pNewNode->next = pos._pNode;
			pNewNode->prev = pos._pNode->prev;
			pNewNode->prev->next = pNewNode;
			pNewNode->next->prev = pNewNode;

			return iterator(pNewNode);
		}

		iterator erase(iterator pos)
		{
			if (pos == end())
			{
				return end();
			}

			Node* pDelNode = pos._pNode;
			Node* pRet = pDelNode->next;
			pDelNode->prev->next = pDelNode->next;
			pDelNode->next->prev = pDelNode->prev;
			delete pDelNode;

			return iterator(pRet);
		}

		void swap(List<T>& l)
		{
			swap(_pHead, l._pHead);
		}

		void clear()
		{
			Node* pCur = _pHead->next;

			while (pCur != _pHead)
			{
				_pHead = pCur->next;
				delete pCur;
				pCur = _pHead;
			}

			_pHead->next = _pHead;
			_pHead->prev = _pHead;
		}

	private:
		void CreateHead()
		{
			_pHead = new Node;
			_pHead->next = _pHead;
			_pHead->prev = _pHead;
		}

	private:
		Node* _pHead;
	};
}

#include <iostream>

void TestList1()
{
	using namespace std;
	ahoj::List<int> L;
	L.push_back(1);
	L.push_back(2);
	L.push_back(3);
	L.push_back(4);
	L.push_back(5);

	cout << L.front() << endl;
	cout << L.back() << endl;
	cout << L.size() << endl;

	ahoj::List<int>::iterator it = L.begin();
	while (it != L.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	L.insert(L.begin(), 0);
	cout << L.size() << endl;
	cout << L.front() << endl;

	for (auto e : L)
	{
		cout << e << " ";
	}
	cout << endl;

	L.erase(L.begin());

	// ֻҪ���� begin �� end �Ϳ���ʹ�÷�Χ for ѭ����
	for (auto e : L)
	{
		cout << e << " ";
	}
	cout << endl;

	L.clear();

	for (auto e : L)
	{
		cout << e << " ";
	}
	cout << endl;
}
