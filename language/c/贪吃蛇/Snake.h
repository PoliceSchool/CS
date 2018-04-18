#ifndef _SNAKE_H_
#define _SNAKE_H_

//��Ϸ�����С
int const COL = 15;
int const ROW = 15;

//�߽ڵ�
typedef struct Node {
	int x;
	int y;
	struct Node *pre;
	struct Node *next;
}NODE, *pNODE;

//ʳ��
typedef struct Food {
	int x;
	int y;
	char c;
}FOOD, *pFOOD;

//��ʼ���������ߵĵ�һ��
pNODE InitSnake(void);

//��ʼ��ʳ���Ա
FOOD InitFood(void);

//���˶�����
int MoveSnake(pNODE pHead, char ch);

//�����̰���
char KbHit(char orient);

//�߳Ե�ʳ�ﴦ����
pNODE SnakeEatFookd(pNODE pHead, pFOOD pFood);

//��ӡ��Ϸ���溯��
void Print(pNODE pHead, FOOD food);

//��Ϸ�������ͷ��ڴ�
void FreeMemory(pNODE *ppHead);
#endif