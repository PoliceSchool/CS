#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "Snake.h"

int main(void) {
	char orien = 'a', get_char;
	int game_over = 0;

	FOOD food = InitFood();
	pNODE head = InitSnake();

	while (1) {
		head = SnakeEatFookd(head, &food);
		get_char = KbHit(orien);
		if (27 == get_char) {
			game_over = -1;
			break;
		}
		else
			orien = get_char;
		game_over = MoveSnake(head, orien);
		if (game_over)
			break;
		system("cls");
		Print(head, food);
		Sleep(200);
	}
	if (game_over) {
		printf("游戏结束！\n");
		FreeMemory(&head);
		if (NULL == head)
			printf("内存释放成功！\n");
		else
			printf("内存释放失败！\n");
	}
	getch();
	return 0;
}

//初始化，创建蛇的第一节
pNODE InitSnake(void) {
	pNODE pHead = (pNODE)malloc(sizeof(NODE));
	srand((unsigned)time(NULL) + 1);

	if (NULL == pHead) {
		printf("内存分配失败！\n");
		exit(-1);
	}

	pHead->x = rand() % ROW;
	pHead->y = rand() % COL;
	pHead->next = NULL;
	pHead->pre = NULL;

	return pHead;
}

FOOD InitFood(void) {
	FOOD food;
	srand((unsigned)time(NULL));

	food.x = rand() % ROW;
	food.y = rand() % COL;
	food.c = 65 + rand() % 26;

	return food;
}

//蛇吃到食物处理函数
pNODE SnakeEatFookd(pNODE pHead, pFOOD pFood) {
	pNODE p_add = NULL, pt = NULL, rear = NULL;
	
	if (pFood->x == pHead->x && pFood->y == pHead->y) {
		p_add = (pNODE)malloc(sizeof(NODE));
		if (NULL == p_add) {
			printf("分配内存失败！\n");
			exit(-1);
		}

		pt = pHead;
		while (pt->next != NULL) {
			pt = pt->next;
		}
		p_add->pre = pt;
		p_add->next = NULL;
		pt->next = p_add;

		*pFood = InitFood();

		//不让食物出现在蛇的位置上
		pt = pHead;
		while (pt != NULL) {
			if (pFood->x == pHead->x && pFood->y == pHead->y) {
				*pFood = InitFood();
				break;
			}
			pt = pt->next;
		}
	}
	return pHead;
}

char KbHit(char orient) {
	char c;
	if (kbhit()) {
		c = getch();
		if (orient != 'd' && c == 'a')
		{
			orient = c;
		}
		else if (orient != 'a' && c == 'd')
		{
			orient = c;
		}
		else if (orient != 'w' && c == 's')
		{
			orient = c;
		}
		else if (orient != 's' && c == 'w')
		{
			orient = c;
		}
		else if (27 == c)
		{
			orient = c;
		}
	}
	return orient;
}

//蛇运动函数
int MoveSnake(pNODE pHead, char ch) {
	INT game_over = 0;
	pNODE pt = pHead;

	//让pt指向蛇尾
	while (pt->next != NULL) {
		pt = pt->next;
	}

	//从蛇尾向蛇头前进
	while (pt != pHead) {
		pt->x = pt->pre->x;
		pt->y = pt->pre->y;
		pt = pt->pre;
	}

	if ('d' == ch) {
		pHead->x += 1;
		if (pHead->x >= ROW) {
			pHead->x -= ROW;
		}
	}

	if ('a' == ch) {
		pHead->x -= 1;
		if (pHead->x < 0) {
			pHead->x += ROW;
		}
	}

	if ('s' == ch) {
		pHead->y += 1;
		if (pHead->y >= COL) {
			pHead->y -= COL;
		}
	}

	if ('w' == ch) {
		pHead->y -= 1;
		if (pHead->y < 0) {
			pHead->y += COL;
		}
	}

	pt = pHead->next;
	while (pt != NULL) {
		if (pt->x == pHead->x && pt->y == pHead->y) {
			game_over = 1;
		}
		pt = pt->next;
	}

	return game_over;
}

//打印游戏界面函数
void Print(pNODE pHead, FOOD food) {
	int row = 0, col = 0, flag = 0;
	pNODE pt = NULL;

	printf("  方向控制-----上：w  下：s  左：a  右：d  （Esc退出）\n");
	for (row = 0; row < ROW; ++row)
		printf("-");
	putchar('\n');

	for (col = 0; col < COL; ++col) {
		printf(" |");
		for (row = 0; row < ROW; ++row) {
			pt = pHead;
			flag = 0;

			//打印蛇
			while (pt != NULL) {
				if (row == pt->x && col == pt->y) {
					if (pt == pHead)
						printf("■");
					else
						printf("□");
					flag = 1;
					break;
				}
				pt = pt->next;
			}

			//打印出食物或两个空格
			if (0 == flag) {
				if (row == food.x && col == food.y) {
					putchar(food.c);
					putchar(food.c);
					continue;
				}
				printf("  ");
			}
		}
		printf("|");
		putchar('\n');
	}
	printf(" ");
	for (row = 0; row < ROW; ++row)
		printf("-");
	putchar('\n');
}

//释放内存函数
void FreeMemory(pNODE *ppHead) {
	pNODE p_delete = NULL, pt = NULL;

	while (*ppHead != NULL) {
		pt = (*ppHead)->next;
		if (pt != NULL) {
			pt->pre = NULL;
		}
		p_delete = *ppHead;
		free(p_delete);
		p_delete = NULL;
		*ppHead = pt;
	}
}