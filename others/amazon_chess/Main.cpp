#ifndef _MAIN_CPP_
#define _MAIN_CPP_

#include "Define.h"
#include "string.h"
#include "stdio.h"
#include "windows.h"
#include "SearchEngine.h"


//全局变量
MapType       map;                         //记录棋盘信息
MoveType      bestMove;					   //返回的最好招法
int           ourcolor;                    //记录我方棋子颜色
int           posx[8] = {0,0,3,3,6,6,9,9}; //记录八个子的位置，前4个是红方，后4个是白方
int           posy[8] = {3,6,0,9,0,9,3,6}; //记录八个子的位置，前4个是红方，后4个是白方
SearchEngine  Engine;                      //搜索引擎

//初始化棋盘
void  init_map()
{
	int i;
	memset(map,NOSTONE,sizeof(map));
	for (i = 0; i<4; i++)
	{
		map[posx[i]][posy[i]] = RED;
		map[posx[i+4]][posy[i+4]] = WHITE;
	}
}

void load_map()
{
	int whitechess,redchess,i,j;
	
	for (i = 0; i<MAXSIZE; i++)              //接收棋盘信息
		for (j = 0; j<MAXSIZE; j++)
			scanf("%d",map[i][j]);
	whitechess = 4;
	redchess = 0;
	for (i = 0; i<MAXSIZE; i++)
		for (j = 0; j<MAXSIZE; j++)
			if (map[i][j] == RED)
			{
				posx[redchess] = i;          //记录现时的棋子的位置信息
				posy[redchess] = j;
				redchess++;
			}
			else if (map[i][j] == WHITE)
			{
				posx[whitechess] = i;
				posy[whitechess] = j;
				whitechess++;
			}
}

//移动棋子更新棋盘
void movechess(MoveType nowmove)
{
	for (int i = 0; i<8; i++)
		if (posx[i] == nowmove.x[0] && posy[i] == nowmove.y[0])     //找到要移动的棋子
		{
			posx[i] = nowmove.x[1];     //改变棋子位置记录信息
			posy[i] = nowmove.y[1];
		}
	map[nowmove.x[1]][nowmove.y[1]] = map[nowmove.x[0]][nowmove.y[0]];    //移动棋子
	map[nowmove.x[0]][nowmove.y[0]] = NOSTONE;
	map[nowmove.x[2]][nowmove.y[2]] = OBSTACLE;                           //放箭

}

//处理move 命令
void cmd_move()
{
	char move[] = "move AAAAAA\n";	//走法 初始化

    if (Engine.search_a_goodmove(map,ourcolor,&bestMove))        //搜索，走出下一步     其中bestMove返回走法指针
	{
		//将着法记录在棋盘中
		movechess(bestMove);

		//将着法转换成要发送的字符形式
		move[5]  = bestMove.x[0] + 'A';
		move[6]  = bestMove.y[0] + 'A';
		move[7]  = bestMove.x[1] + 'A';
		move[8]  = bestMove.y[1] + 'A';
		move[9]  = bestMove.x[2] + 'A';
		move[10] = bestMove.y[2] + 'A';

		//发送信息
		printf ("%s",move);        //发送信息给裁判平台
		fflush(stdout);

	}
}
   //棋子的位置有两条线
int main()
{
	char Msg[500] = {0};		//保存接收到的消息
	char name[] = "name 大北理珠\n";	//队伍信息

    init_map();                 //初始化棋盘

	while (1)
	{

		//循环接收裁判平台发送的消息
		//注意需要发送的字符串应该以'\n'结束，裁判平台才会认为是一次完整的输入
		//发送完需要调用fflush(stdout)清空输出缓冲区，使字符串立刻输出到裁判平台

		memset(Msg,0,500);
		scanf("%s",Msg);
		
		if (strcmp(Msg,"name?") == 0)
		{
			printf("%s",name);           //在裁判平台显示名字
			fflush(stdout);	             //清空输出缓冲区
			continue;
		}
		if (strcmp(Msg,"stop") == 0)
		{

			fflush(stdout);	
			return 0;
		}


		if (strcmp(Msg,"new") == 0)
		{			
			//new
			
			init_map();//初始化棋盘

			scanf("%s",Msg);
			
			if (strcmp(Msg,"white") == 0)
			{
				//new white
				ourcolor = WHITE;
				/*MoveType erer;
				erer.x[0]=9;erer.y[0]=3;erer.x[1]=3;erer.y[1]=3;erer.x[2]=3;erer.y[2]=6;
				movechess(erer);*/
				cmd_move();        //白棋先行
				/*printf("move JDDDDG\n");
				fflush(stdout);*/
				continue;
			}
			else
			{
				//new red
				ourcolor = RED;
				continue;
			}

			continue;
		}

		if (strcmp(Msg,"move") == 0)
		{
		    //move
			scanf("%s",Msg);            //接收步法
			if (Msg[6] == '\0')         //判断最后一个是否为'\0'
			{
				//move XX\n
				bestMove.x[0] = Msg[0] - 'A';         //把棋盘信息转换成数字
				bestMove.y[0] = Msg[1] - 'A';
				bestMove.x[1] = Msg[2] - 'A';
				bestMove.y[1] = Msg[3] - 'A';
				bestMove.x[2] = Msg[4] - 'A';
				bestMove.y[2] = Msg[5] - 'A';		
				movechess(bestMove);                  //移动棋盘
			}
		
			cmd_move();       //走出一步好的
			continue;
		}

		if (strcmp(Msg,"load") == 0)                  //加载棋盘
			load_map();

	}
	return 0;
}

#endif