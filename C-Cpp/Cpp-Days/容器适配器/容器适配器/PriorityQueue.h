#pragma once

#include <vector>
#include <functional>

namespace ahoj
{
	/*
	���ȼ����У��ѣ�ʹ�� vector
	*/
	template <class T, class Container = std::vector<T>, class Compare = std::less<T>>
	class PriorityQueue
	{
	public:
		PriorityQueue()
		{}

		template <class Iterator>
		PriorityQueue(Iterator first, Iterator last)
			: _con(first, last)
		{
			// �ҵ�������һ����Ҷ�ӽڵ�
			size_t leaf = (_con.size() - 2) / 2;
			for (int i = leaf; i >= 0; i--)
			{
				_adjustDown(i);
			}
		}

		void push(const T& data)
		{
			_con.push_back(data);

			// ���ϵ���
			_adjustUp();
		}

		void pop()
		{
			if (empty() == true)
				return;

			std::swap(_con.front(), _con.back());
			_con.pop_back();
			_adjustDown(0);
		}

		const T& top() const
		{
			return _con.front();
		}

		size_t size() const
		{
			return _con.size();
		}

		bool empty() const
		{
			return _con.empty();
		}

	private:
		void _adjustUp()
		{
			int child = (int)_con.size() - 1;
			int parent = (child - 1) / 2;

			while (child)
			{
				if (Compare()(_con[parent], _con[child]))
				{
					std::swap(_con[parent], _con[child]);
					child = parent;
					parent = (child - 1) >> 1;
				}
				else
				{
					return;
				}
			}
		}

		void _adjustDown(int parent)
		{
			int child = parent * 2 + 1;
			int size = (int)_con.size();
			
			while (child < size)
			{
				// �ҵ����Һ����н�С�ĺ���
				if (child + 1 < size && Compare()(_con[child], _con[child + 1]))
				{
					child += 1;
				}

				if (Compare()(_con[parent], _con[child]))
				{
					std::swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					return;
				}
			}
		}

	private:
		Container _con;
	};
}