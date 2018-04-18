#ifndef _MAKEMOVE_H_                            //这些宏定义是避免重复include的
#define _MAKEMOVE_H_
#include "define.h"


class mapmove                                    
{
	public:                                      //公共成员，用于和其他类之间交互
		StackType stack;                         //用来存招法的招法栈，每生成一个招法就压到栈中
		void makemoves(MapType map,int color);   /*和其他函数交互的接口，传入的参数是棋盘和走子
		                                           方颜色，次函数运行后将走子方招法压入栈中*/
	private:                                     //Why this function should be private?
		
        MapType map;                         //皇后函数
        MapType map2;                        //障碍函数
		void push(int x_o,int y_o,int x_d,int y_d,int z_o,int z_d); //将一个招法压入招法栈
		void move_queen(int i,int j);     //皇后招法生成，传入棋子坐标，生成棋子招法，
                void move_ob(int i,int j);     //障碍招法生成，传入棋子坐标，生成棋子招法，
		void bit(int i,int j,int m,int n);//交换数据

};

#endif