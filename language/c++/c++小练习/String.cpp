#include <iostream>

class String {
public:
	String(const char *str = NULL);
	String(const String &another);
	~String(void);
	String& operator=(const String &rhs);
private :
	char *m_data;
};

String::String(const char *str) {
	if (str == nullptr) {  //判断参数str是否为nullptr
		m_data = new char[1];
		m_data[0] = '\0';
	}
	else {
		m_data = new char[strlen(str)+1];  //申请内存，长度+1是为了存储字符串后面的'\0'
		strcpy(m_data, str);
	}
}

/*参数another的成员变量赋值给另一个String的成员变量需要申请内存，
如果直接"m_data = another.m_data"是不行的，
当anouther.m_data被delete的时候,m_data就是野指针了*/
String::String(const String &another) {
	m_data = new char[strlen(another.m_data) + 1];
	strcpy(m_data, another.m_data);
}

String& String::operator=(const String &rhs) {
	if (this == &rhs) { //这里的rhs是一个引用,但是&rhs表示的是地址,也就是rhs所引用的那个对象的地址
		return *this;
	}

	/*删除原来的数据,再新开一块内存;
	如果不删除原来的数据则会造成内存溢出;
	另外不直接将rhs.m_data直接拷贝到m_data原来的地址上是因为两者之间的长度不一定相等*/
	delete[] m_data;
	m_data = new char[strlen(rhs.m_data) + 1];
	strcpy(m_data, rhs.m_data);
	return *this;
}

String::~String(void) {
	delete m_data;
	m_data = nullptr;
}