#pragma once
#include <cassert>

namespace ahoj
{
	template<class T>
	class Vector
	{
	public:
		typedef T* iterator;
		typedef T* reverse_iterator;

	public:
		// construct  // ����
		Vector()
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{}

		Vector(size_t n, const T& val)
		{
			_start = new T[n];
			for (size_t i = 0; i < n; ++i)
			{
				_start[i] = val;
			}
			_finish = _endOfStorage = _start + n;
		}

		Vector(T* first, T* last)
		{
			size_t n = last - first;
			_start = new T[n];
			_finish = _start;
			while (first != last)
			{
				*_finish++ = *first++;
			}
			_endOfStorage = _finish;
		}

		// ע�⣺ǳ����
		Vector(const Vector<T>& v)
		{}

		// ע�⣺ǳ����
		Vector<T>& operator=(const Vector<T>& v)
		{}

		~Vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _endOfStorage = nullptr;
			}
		}

		// iterator  // ������
		// ������������һ��ָ�룬[begin, end)
		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		reverse_iterator rbegin()
		{
			return end();
		}

		reverse_iterator rend()
		{
			return begin();
		}

		// capacity  // �������
		size_t size() const
		{
			return _finish - _start;
		}

		bool empty() const
		{
			return _start == _finish;
		}

		size_t capacity() const
		{
			return _endOfStorage - _start;
		}

		// ��� T ���������ͣ�T() -> 0
		// ��� T ���Զ������ͣ�T() -> ���ø����޲ι��캯��
		// T ��������޲����͵Ĺ��캯��
		void resize(size_t newSize, const T& val = T())
		{
			size_t oldSize = size();
			if (newSize < oldSize)
			{
				_finish = _start + newSize;
			}
			else
			{
				// �Ƿ���Ҫ����
				if (newSize > capacity())
				{
					reserve(newSize);
				}

				// ���Ԫ��
				for (size_t i = oldSize; i < newSize; ++i)
				{
					*_finish++ = val;
				}
			}
		}

		void reserve(size_t newCapacity)
		{
			size_t oldCap = capacity();
			if (newCapacity > oldCap)
			{
				T* tmp = new T[newCapacity];

				size_t n = size();
				if (nullptr != _start)
				{
					for (size_t i = 0; i < size(); ++i)
					{
						tmp[i] = _start[i];
					}

					free(_start);
				}
				_start = tmp;
				_finish = _start + n;
				_endOfStorage = _start + newCapacity;
			}
		}

		// access  // Ԫ�ط���
		// ��������λ�õ�Ԫ�أ�ע�� index ���ܳ�����ЧԪ�ظ���
		T& operator[](size_t index)
		{
			assert(index < size());
			return _start[index];
		}

		const T& operator[](size_t index) const
		{
			assert(index < size());
			return _start[index];
		}

		T& front()
		{
			return *_start;
		}

		const T& front() const
		{
			return *_start;
		}

		T& back()
		{
			return *(_finish - 1);
		}

		const T& back() const
		{
			return *(_finish - 1);
		}

		// modify  // �޸�
		void push_back(const T& val)
		{
			checkCapacity();
			*_finish++ = val;
		}

		void pop_back()
		{
			if (empty())
			{
				return;
			}
			--_finish;
		}

		iterator insert(iterator pos, const T& val)
		{
			checkCapacity();

			// ����Ԫ��
			for (int i = size(); i > pos - _start; i--)
			{
				_start[i] = _start[i - 1];
			}

			// ��������
			*pos = val;
			++_finish;
			return pos;
		}

		iterator erase(iterator pos)
		{
			if (pos == end())
			{
				return pos;
			}

			for (size_t i = pos - _start; i < size(); ++i)
			{
				_start[i] = _start[i + 1];
			}

			--_finish;
			return pos;
		}

		void swap(Vector<T>& v)
		{
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_endOfStorage, v._endOfStorage);
		}

		void clear()
		{
			_finish = _start;
		}

	protected:
		void checkCapacity()
		{
			if (_finish == _endOfStorage)
			{
				reserve(capacity() * 2);
			}
		}

	protected:
		T* _start;
		T* _finish;
		T* _endOfStorage;
	};
}

#include <iostream>
void TestVector()
{
	using namespace ahoj;
	using namespace std;

	Vector<int> v1;
	Vector<int> v2(10, 6);
	cout << v2.size() << endl;
	cout << v2.capacity() << endl;

	for (auto e : v2)
	{
		cout << e << " ";
	}
	cout << endl;

	int arr[] = { 0,1,2,3,4,5,6,7,8,9 };
	Vector<int> v3(arr, arr + sizeof(arr) / sizeof(arr[0]));
	for (auto e : v3)
	{
		cout << e << " ";
	}
	cout << endl;
}