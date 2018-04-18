#ifndef _EVALUE_H_
#define _EVALUE_H_

#include <string.h>
#include <stdio.h>

#define INFINITY (1 << 16 + 1)   //����һ������󣬱�ʾ������ͨ��        =0��
#define UNIT (1<<16)			 //����һ����λֵ�����Գ��Ը�����ͨ��    =65536��

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


class mapvalue 
{
public:
	int Evalue (MapType map,int step,int color);     //�Ե�ǰ���̵Ĺ�ֵ

private:
	void set ();
	void search_path (MapType map, int i, int j, int ourcolor);
	double f1(double w);
	double f2(double w);
    double f3(double w);
	double f4(double w);
};

#endif