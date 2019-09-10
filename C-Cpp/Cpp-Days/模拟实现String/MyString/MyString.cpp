#include <iostream>

// ����̲ģ�������Ĭ�����ɵģ�ǳ��������Դ��ʧ
#if 0
class String {
public:
	String(const char* str = "")
	{
		if (nullptr == str)
		{
			str = "";
		}

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s) : _str(s._str)
	{}

	String& operator=(const String& s)
	{
		_str = s._str;
		return *this;
	}

	~String()
	{
		if (_str != nullptr)
		{
			delete[] _str;
		}
	}

private:
	char* _str;
};
#endif


// ��ͳ�汾��������������졢��ֵ��������أ�д��
#if 0
class String {
public:
	String(const char* str = "")
	{
		if (nullptr == str)
		{
			str = "";
		}

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s) : _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)
	{
		// �����Լ����Լ���ֵ
		if (this != &s)
		{
			// ���ַ�ʽ�����ͷ���ԭ�пռ䣬�������¿ռ�
			//     ��һ����ռ�ʧ�ܣ�ԭ�е�����Ҳû����
			/*delete _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);*/

			// ����д����������΢��һЩ��������ռ䣬
			//     ʧ���Ժ�Ͳ����ͷ�ԭ�еĿռ��ˣ����沶����쳣�ͺ���
			char* pstr = new char[strlen(s._str) + 1];
			strcpy(pstr, s._str);
			delete[] _str;
			_str = pstr;
		}

		return *this;
	}

	~String()
	{
		if (_str != nullptr)
		{
			delete[] _str;
		}
	}

private:
	char* _str;
};

void TestString()
{
	String s1("hello");
	String s2(s1);

	String s3;
	s3 = s2;
}
#endif


// �ִ������д��
#if 0
class String {
public:
	String(const char* str = "")
	{
		if (nullptr == str)
		{
			str = "";
		}

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		: _str(nullptr)
	{
		String strTemp(s._str);
		std::swap(_str, strTemp._str);
	}

	// ����һ������д��
	//String& operator=(const String& s)
	//{
	//	// �����Լ����Լ���ֵ
	//	if (this != &s)
	//	{
	//		String strTemp(s._str);
	//		std::swap(_str, strTemp._str);
	//	}
	//	return *this;
	//}

	// ���д��
	String& operator=(String s)
	{
		std::swap(_str, s._str);
		return *this;
	}

	~String()
	{
		if (_str != nullptr)
		{
			delete[] _str;
		}
	}

private:
	char* _str;
};
#endif


// ���ü������ǳ�������⣬дʱ���� Copy On Write
// ���̻߳�������⣬��Ϊ _pCount �Ĳ�������ԭ���ԵĲ���
//     ���������1. C++11 ����ԭ�����ͱ���  2. ����
#if 0
class String {
public:
	String(const char* str = "")
		: _pCount(new int(1))
	{
		if (nullptr == str)
		{
			str = "";
		}

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		: _str(s._str)
		, _pCount(s._pCount)
	{
		++(*_pCount);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			// ��ǰ��������Լ���Դ�ļ���
			Release();

			// ��ǰ������ s ������Դ�ͼ���
			_str = s._str;
			_pCount = s._pCount;
			++(*_pCount);
		}
		return *this;
	}

	char& operator[](size_t index)
	{
		if (GetRef() > 1)
		{
			String strTemp(_str);
			std::swap(_str, strTemp._str);
			std::swap(_pCount, strTemp._pCount);
		}
		return _str[index];
	}

	const char& operator[](size_t index) const
	{
		return _str[index];
	}

	~String()
	{
		Release();
	}

private:
	void Release()
	{
		if (_str != nullptr && 0 == --(*_pCount))
		{
			delete[] _str;
			delete _pCount;
		}
	}

	int GetRef()
	{
		return *_pCount;
	}

private:
	char* _str;
	int* _pCount;
};

void TestString()
{
	String s1("hello");
	String s2(s1);

	String s3("world");
	String s4(s3);

	s3 = s2;  // s3: ԭ���ļ��� 1
	s4 = s2;  // 

	s1[0] = 'H';
}

int main()
{
	TestString();
	return 0;
}
#endif