#ifndef _MAIN_CPP_
#define _MAIN_CPP_

#include "Define.h"
#include "string.h"
#include "stdio.h"
#include "windows.h"
#include "SearchEngine.h"


//ȫ�ֱ���
MapType       map;                         //��¼������Ϣ
MoveType      bestMove;					   //���ص�����з�
int           ourcolor;                    //��¼�ҷ�������ɫ
int           posx[8] = {0,0,3,3,6,6,9,9}; //��¼�˸��ӵ�λ�ã�ǰ4���Ǻ췽����4���ǰ׷�
int           posy[8] = {3,6,0,9,0,9,3,6}; //��¼�˸��ӵ�λ�ã�ǰ4���Ǻ췽����4���ǰ׷�
SearchEngine  Engine;                      //��������

//��ʼ������
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
	
	for (i = 0; i<MAXSIZE; i++)              //����������Ϣ
		for (j = 0; j<MAXSIZE; j++)
			scanf("%d",map[i][j]);
	whitechess = 4;
	redchess = 0;
	for (i = 0; i<MAXSIZE; i++)
		for (j = 0; j<MAXSIZE; j++)
			if (map[i][j] == RED)
			{
				posx[redchess] = i;          //��¼��ʱ�����ӵ�λ����Ϣ
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

//�ƶ����Ӹ�������
void movechess(MoveType nowmove)
{
	for (int i = 0; i<8; i++)
		if (posx[i] == nowmove.x[0] && posy[i] == nowmove.y[0])     //�ҵ�Ҫ�ƶ�������
		{
			posx[i] = nowmove.x[1];     //�ı�����λ�ü�¼��Ϣ
			posy[i] = nowmove.y[1];
		}
	map[nowmove.x[1]][nowmove.y[1]] = map[nowmove.x[0]][nowmove.y[0]];    //�ƶ�����
	map[nowmove.x[0]][nowmove.y[0]] = NOSTONE;
	map[nowmove.x[2]][nowmove.y[2]] = OBSTACLE;                           //�ż�

}

//����move ����
void cmd_move()
{
	char move[] = "move AAAAAA\n";	//�߷� ��ʼ��

    if (Engine.search_a_goodmove(map,ourcolor,&bestMove))        //�������߳���һ��     ����bestMove�����߷�ָ��
	{
		//���ŷ���¼��������
		movechess(bestMove);

		//���ŷ�ת����Ҫ���͵��ַ���ʽ
		move[5]  = bestMove.x[0] + 'A';
		move[6]  = bestMove.y[0] + 'A';
		move[7]  = bestMove.x[1] + 'A';
		move[8]  = bestMove.y[1] + 'A';
		move[9]  = bestMove.x[2] + 'A';
		move[10] = bestMove.y[2] + 'A';

		//������Ϣ
		printf ("%s",move);        //������Ϣ������ƽ̨
		fflush(stdout);

	}
}
   //���ӵ�λ����������
int main()
{
	char Msg[500] = {0};		//������յ�����Ϣ
	char name[] = "name ������\n";	//������Ϣ

    init_map();                 //��ʼ������

	while (1)
	{

		//ѭ�����ղ���ƽ̨���͵���Ϣ
		//ע����Ҫ���͵��ַ���Ӧ����'\n'����������ƽ̨�Ż���Ϊ��һ������������
		//��������Ҫ����fflush(stdout)��������������ʹ�ַ����������������ƽ̨

		memset(Msg,0,500);
		scanf("%s",Msg);
		
		if (strcmp(Msg,"name?") == 0)
		{
			printf("%s",name);           //�ڲ���ƽ̨��ʾ����
			fflush(stdout);	             //������������
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
			
			init_map();//��ʼ������

			scanf("%s",Msg);
			
			if (strcmp(Msg,"white") == 0)
			{
				//new white
				ourcolor = WHITE;
				/*MoveType erer;
				erer.x[0]=9;erer.y[0]=3;erer.x[1]=3;erer.y[1]=3;erer.x[2]=3;erer.y[2]=6;
				movechess(erer);*/
				cmd_move();        //��������
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
			scanf("%s",Msg);            //���ղ���
			if (Msg[6] == '\0')         //�ж����һ���Ƿ�Ϊ'\0'
			{
				//move XX\n
				bestMove.x[0] = Msg[0] - 'A';         //��������Ϣת��������
				bestMove.y[0] = Msg[1] - 'A';
				bestMove.x[1] = Msg[2] - 'A';
				bestMove.y[1] = Msg[3] - 'A';
				bestMove.x[2] = Msg[4] - 'A';
				bestMove.y[2] = Msg[5] - 'A';		
				movechess(bestMove);                  //�ƶ�����
			}
		
			cmd_move();       //�߳�һ���õ�
			continue;
		}

		if (strcmp(Msg,"load") == 0)                  //��������
			load_map();

	}
	return 0;
}

#endif