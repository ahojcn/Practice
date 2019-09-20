#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

/*
	������ģ�������
	ע�⣺
		1. ��������������ַ����ǲ�������Ϊ������ģ�������
		2. ������ģ����������ڱ���ʱ�ھ���ȷ�Ͻ��
*/
#if 0
template <class T, size_t N = 10>
class Array
{
private:
	T _arr[N];
	size_t _size;
};
#endif


/*
	ģ���ػ�
		ʹ��ģ�����ʵ��һЩ�������޹صĴ��룬
		���Ƕ���һЩ�������Ϳ��ܻ�õ�һЩ������
*/
// ����ģ���ػ�
#if 0
template <class T>
bool isEqual(T& l, T& r)
{
	return l == r;
}

void testIsEqual()
{
	char p1[] = "abc";
	char p2[] = "abc";
	if (isEqual(p1, p2) == true)
		cout << "equal" << endl;
	else
		cout << "not equal" << endl;  // ������
}
#endif

// �ػ�
#if 0
template <class T>
bool isEqual(T& l, T& r)
{
	return l == r;
}

template<>
bool isEqual<char*>(char*& l, char*& r)
{
	if (strcmp(l, r) == 0)
		return true;
	else
		return false;
}

void testIsEqual()
{
	char* p1 = new char[4];
	memcpy(p1, "abc", 4);
	char* p2 = new char[4];
	memcpy(p2, "abc", 4);

	if (isEqual(p1, p2) == true)
		cout << "equal" << endl;
	else
		cout << "not equal" << endl;
}
#endif


// ��ģ���ػ�
// ȫ�ػ�
#if 0
template <class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1, T2>" << endl;
	}

private:
	T1 _d1;
	T2 _d2;
};

template<>
class Data<int, char>
{
public:
	Data()
	{
		cout << "Data<int, char>" << endl;
	}

private:
	int _d1;
	char _d2;
};

void testData()
{
	Data<int, int> d1;
	Data<int, char> d2;
}
#endif

// ƫ�ػ������ػ���
// ��������ģ��
#if 0
template <class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1, T2>" << endl;
	}

private:
	T1 _d1;
	T2 _d2;
};

// ƫ�ػ��Ĳ����ػ�
template <class T1>
class Data<T1, int>
{
public:
	Data()
	{
		cout << "Data<T1, int>" << endl;
	}

private:
	T1 _d1;
	int _d2;
};

// ������һ������
template <class T1, class T2>
class Data<T1*, T2*>
{
public:
	Data() { cout << "Data<T1*, T2*>" << endl; }
private:
	T1* _d1;
	T2* _d2;
};

template <class T1, class T2>
class Data<T1&, T2&>
{
public:
	Data(const T1 &d1, const T2 &d2)
		: _d1(d1)
		, _d2(d2)
	{
		cout << "Data<T1&, T2&>" << endl;
	}
private:
	const T1& _d1;
	const T2& _d2;
};

void testData()
{
	Data<double, int> d1;  // �ػ� int �汾
	Data<int, double> d2;  // ������ģ��
	Data<int*, int*> d3;  // ָ���ػ��汾
	Data<int&, int&> d4(1, 2);  // �����ػ��汾
}

int main()
{
	//testIsEqual();
	testData();
	return 0;
}
#endif



/*
	��ģ���ػ�Ӧ�� --- ������ȡ

	ʵ��һ��ͨ�õĿ�������
*/

// 1. ʹ�� memcpy ����
//		ǳ����
#if 0
namespace ahoj
{
	template <class T>
	void copy(T* dst, const T* src, size_t size)
	{
		memcpy(dst, src, size);
	}
}

void testCopy_1()
{
	string str_arr_1[3] = { "111", "222", "333" };
	string str_arr_2[3];
	ahoj::copy(str_arr_2, str_arr_1, 3);
}
#endif

// 2. ��ֵ��ʽ����
//		��Ȼ������Զ������͵�ǳ�������⣬�����������Ϳ�����ʱ��Ч�ʵ͡�
#if 0
namespace ahoj
{
	template <class T>
	void copy(T* dst, const T* src, size_t size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			dst[i] = src[i];
		}
	}

	void testCopy_2()
	{
		string str_arr_1[3] = { "111", "222", "333" };
		string str_arr_2[3];
		ahoj::copy(str_arr_2, str_arr_1, 3);
	}
}
#endif

// 3. ����һ�����������Զ������ͺ���������
//		ȱ�ݣ��û���Ҫ����������Ԫ�ص�����ȥ���ݵ���������������������ӡ�
#if 0
namespace ahoj
{
	template <class T>
	void copy(T* dst, const T* src, size_t size, bool is_POD_type)
	{
		if (is_POD_type)
			memcpy(dst, src, size);
		else
		{
			for (size_t i = 0; i < size; ++i)
				dst[i] = src[i];
		}
	}
}
#endif

// 4. ʹ�ú��������������ͺ��Զ�������
//		ȱ�ݣ�ö����Ҫ�����е����Ͷ�����һ�飬ÿ�ζ�Ҫ���кö���ַ����Ƚϣ�Ч�ʵ͡�
#if 0
namespace ahoj
{
	bool isPODType(const char* type)
	{
		const char* arr_type[] = {
			"char", "short", "int",
			"long", "long long", "float",
			"double", "long double"
		};

		for (size_t i = 0; i < sizeof(arr_type) / sizeof(arr_type[0]); ++i)
		{
			if (0 == strcmp(type, arr_type[i]))
				return true;
		}
		return false;
	}

	template <class T>
	void copy(T* dst, const T* src, size_t size)
	{
		if (isPODType(typeid(T).name()) == true)
			memcpy(dst, src, size);
		else
		{
			for (size_t i = 0; i < size; ++i)
			{
				dst[i] = src[i];
			}
		}
	}
}
#endif

// 5. ������ȡ
#if 0
namespace ahoj
{
	struct TrueType  // ������������
	{
		static bool get()
		{
			return true;
		}
	};

	struct FalseType  // �����Զ�������
	{
		static bool get()
		{
			return false;
		}
	};

	template <class T>
	struct TypeTraits
	{
		typedef FalseType IsPODType;
	};

	template <>
	struct TypeTraits<char>
	{
		typedef TrueType IsPODType;
	};

	template <>
	struct TypeTraits<short>
	{
		typedef TrueType IsPODType;
	};

	template <>
	struct TypeTraits<int>
	{
		typedef TrueType IsPODType;
	};

	template <>
	struct TypeTraits<long>
	{
		typedef TrueType IsPODType;
	};

	template <>
	struct TypeTraits<long long>
	{
		typedef TrueType IsPODType;
	};

	template <>
	struct TypeTraits<float>
	{
		typedef TrueType IsPODType;
	};

	template <>
	struct TypeTraits<double>
	{
		typedef TrueType IsPODType;
	};

	template <class T>
	void copy(T* dst, const T* src, size_t size)
	{
		if (TypeTraits<T>::IsPODType::get())
			memcpy(dst, src, size * sizeof(T));
		else
		{
			for (size_t i = 0; i < size; ++i)
				dst[i] = src[i];
		}
	}

	void testCopy_5()
	{
		int a1[] = { 0,1,2,3,4,5,6,7,8,9 };
		int a2[10];
		ahoj::copy(a2, a1, 10);

		string str_arr_1[3] = { "111", "222", "333" };
		string str_arr_2[3];
		ahoj::copy(str_arr_2, str_arr_1, 3);
	}
}
#endif

// STL �е�����
namespace ahoj
{
	struct __true_type {};  // ��������
	struct __false_type {};  // �Զ�������

	template <class type>
	struct __type_traits
	{
		typedef __false_type is_POD_type;
	};

	// �������������ͽ����ػ�
	// ��������������ʱ��
	// ���е��������Ͷ��������س�����
	// �����з��ź��޷��ţ����磺����int���ͣ������ػ�������int -- signed int -- unsigned int
	template <>
	struct __type_traits<char>
	{
		typedef __true_type is_POD_type;
	};

	template <>
	struct __type_traits<signed char>
	{
		typedef __true_type is_POD_type;
	};

	template <>
	struct __type_traits<unsigned char>
	{
		typedef __true_type is_POD_type;
	};

	template <>
	struct __type_traits<int>
	{
		typedef __true_type is_POD_type;
	};

	template <>
	struct __type_traits<float>
	{
		typedef __true_type is_POD_type;
	};

	template <>
	struct __type_traits<double>
	{
		typedef __true_type is_POD_type;
	};

	template <class T>
	void _copy(T* dst, const T* src, size_t n, __true_type)
	{
		memcpy(dst, src, n);
	}

	template <class T>
	void _copy(T* dst, const T* src, size_t n, __false_type)
	{
		for (size_t i = 0; i < n; ++i)
			dst[i] = src[i];
	}

	template <class T>
	void copy(T* dst, const T* src, size_t n)
	{
		_copy(dst, src, n, __type_traits<T>::is_POD_type());
	}
}

void testSTLExp()
{
	int a1[] = { 0,1,2,3,4,5,6,7,8,9 };
	int a2[10];
	ahoj::copy(a2, a1, 10);

	string str_arr_1[3] = { "111", "222", "333" };
	string str_arr_2[3];
	ahoj::copy(str_arr_2, str_arr_1, 3);
}

int main()
{
	// testCopy_1();
	// ahoj::testCopy_2();
	// ahoj::testCopy_5();
	testSTLExp();
	return 0;
}
