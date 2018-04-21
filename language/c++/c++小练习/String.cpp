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
	if (str == nullptr) {  //�жϲ���str�Ƿ�Ϊnullptr
		m_data = new char[1];
		m_data[0] = '\0';
	}
	else {
		m_data = new char[strlen(str)+1];  //�����ڴ棬����+1��Ϊ�˴洢�ַ��������'\0'
		strcpy(m_data, str);
	}
}

/*����another�ĳ�Ա������ֵ����һ��String�ĳ�Ա������Ҫ�����ڴ棬
���ֱ��"m_data = another.m_data"�ǲ��еģ�
��anouther.m_data��delete��ʱ��,m_data����Ұָ����*/
String::String(const String &another) {
	m_data = new char[strlen(another.m_data) + 1];
	strcpy(m_data, another.m_data);
}

String& String::operator=(const String &rhs) {
	if (this == &rhs) { //�����rhs��һ������,����&rhs��ʾ���ǵ�ַ,Ҳ����rhs�����õ��Ǹ�����ĵ�ַ
		return *this;
	}

	/*ɾ��ԭ��������,���¿�һ���ڴ�;
	�����ɾ��ԭ���������������ڴ����;
	���ⲻֱ�ӽ�rhs.m_dataֱ�ӿ�����m_dataԭ���ĵ�ַ������Ϊ����֮��ĳ��Ȳ�һ�����*/
	delete[] m_data;
	m_data = new char[strlen(rhs.m_data) + 1];
	strcpy(m_data, rhs.m_data);
	return *this;
}

String::~String(void) {
	delete m_data;
	m_data = nullptr;
}