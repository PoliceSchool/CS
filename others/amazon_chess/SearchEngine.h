#ifdef _SEARCH_ENGINE_H_
#else
#define _SEARCH_ENGINE_H_

#include "define.h"

class SearchEngine	//����������
{
	public:
		SearchEngine ();          
		//����ӿ�
		//����˵����map:��ǰ��֣�color:���ӷ���ɫ��bestmove:�����з�ָ�� 
		//��������˵������������ɹ�����true,���򷵻�false;
        bool search_a_goodmove(MapType m,int color ,MoveType* bestmove);
		//������
		//����˵����line:����������У�num: Ҫ��ǰnum��Ԫ�أ�n:�������еĸ���-1
		void heap_sort(int line[],int num,int n);                       
	private:
		int alpha_beta_search(int dep,int color,int alpha,int beta);   //alpha-beta����
		bool lost(int color);                                //�ж�color���Ƿ�Ӯ
		void movechess(MoveType nowmove);                    //�ƶ���
		void unmovechess(MoveType nowmove);                  //�����ƶ�
		void init_heap();                                    //��ʼ����
		void heap_down(int i);                               //�ڵ��³�
		
		MapType map;                      //�����ļ�������   
		MoveType mybestmove;              //һ���߷��������ļ��е�
};

#endif