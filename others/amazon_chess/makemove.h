#ifndef _MAKEMOVE_H_                            //��Щ�궨���Ǳ����ظ�include��
#define _MAKEMOVE_H_
#include "define.h"


class mapmove                                    
{
	public:                                      //������Ա�����ں�������֮�佻��
		StackType stack;                         //�������з����з�ջ��ÿ����һ���з���ѹ��ջ��
		void makemoves(MapType map,int color);   /*���������������Ľӿڣ�����Ĳ��������̺�����
		                                           ����ɫ���κ������к����ӷ��з�ѹ��ջ��*/
	private:                                     //Why this function should be private?
		
        MapType map;                         //�ʺ���
        MapType map2;                        //�ϰ�����
		void push(int x_o,int y_o,int x_d,int y_d,int z_o,int z_d); //��һ���з�ѹ���з�ջ
		void move_queen(int i,int j);     //�ʺ��з����ɣ������������꣬���������з���
                void move_ob(int i,int j);     //�ϰ��з����ɣ������������꣬���������з���
		void bit(int i,int j,int m,int n);//��������

};

#endif