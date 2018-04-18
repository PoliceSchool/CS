#ifdef _DEFINE_H_H_        //��ֹ�ظ�����
#else
#define _DEFINE_H_H_

/*
��ע
(1)����ϵ��ԭ���������Ͻǣ�x�������꣨��x�У�y�Ǻ����꣨��y�У�
(2)���ǿ����������ɾ�����ͷ�ļ�������ݣ�ע����ĺ��Ҫ�����µ�define��֪ͨ������
(3)һЩ˽�еĳ�������ͷŵ����Ǹ��Ե�ͷ�ļ�����еķ����
*/


#define  MAXMOVE    3000     //һ����ֵ�����з�����
#define  MAX_VALUE  9999999    //���������ֵ {}
#define  MAX_DEEP   3       //�������Ĵ����
#define  TURNROLE   3       


//���̳�������

#define   MAXSIZE   10        //���̴�С10*10�±�0-9
#define   NOSTONE   0         //������
#define   RED       1         //�췽����
#define   WHITE     2         //�׷�����
#define   OBSTACLE  3         //�ϰ�

//�ŷ�����
typedef struct 
{
	int x[3];                 //x[0] �������x�����ꡢx[1]�������x�����ꡢx[2]�ϰ�����
    int y[3];                 //y[0] �������y�����ꡢy[1]�������y�����ꡢy[2]�ϰ�����
}MoveType;
//�����Լ���

//�з�ջ����
typedef struct             
{
     MoveType chessmove[MAXMOVE];
     int top;           //���� � �����൱��һ��ָ�룬ָʾ����
}StackType;

//�ѽṹ����
typedef  struct                  //���ڶ�����
{
	int data;                                   //�ؼ���
	int index;                                  //�ؼ�������
}HeapType;

//���̶���
typedef   int MapType[MAXSIZE][MAXSIZE];        //����

extern    int ourcolor;                         //��¼�ҷ���ɫ
extern    int posx[8];                          //��¼�˸��ӵ�λ�ã�ǰ4���Ǻ췽����4���ǰ׷�
extern    int posy[8];                          //��¼�˸��ӵ�λ�ã�ǰ4���Ǻ췽����4���ǰ׷�

//-------------------------------------------���泣��������----------------------------

//�����ܴ�С
#define CHESSLENGTH        50               //���Ӵ�С
#define BOARD              10               //�߽��
#define MAP_OUTSIDE_BOARD  20               //��ͼ��߽���
#define OUTPUT_WIDTH       250              //�����Ϣ���ڿ��
#define PLAYERAREA_WIDTH   150              //ѡ�������
#define PLAYERAREA_BOARD   5                //ѡ������߽�
#define PLAYERTIME_WIDTH   13               //�������������
#define PLAYERTIME_HEIGH   23               //�����������߶�


//��Ϸ״̬
#define GAME_OVER         0
#define GAME_VICOTORY     1
#define GAME_WAIT         2
#define GAME_RUN          3
#define GAME_SELECT       4 
#define GAME_MOVE         5

//��ť״̬
#define BUTTON_NOMAL      0
#define BUTTON_SELECT     1
#define BUTTON_DOWN       2

//��Ϸ���򻮷�
#define BODYAREA          0
#define MAPAREA           1
#define OUTPUTAREA        2
#define PLAYER1AREA       3
#define PLAYER2AREA       4
#define BUTTON0AREA       5
#define BUTTON1AREA       6
#define BUTTON2AREA       7
#define BUTTON3AREA       8



//��ʱ��ID
#define   ID_TIMER1       100
#define   ID_TIMER2       200
#define   ID_TIMER3       300

//��ť��С����
#define   BUTTON_WIDTH    120
#define   BUTTON_HEIGH    30
#define   BUTTON_TOP      157

//ͷ���С����
#define   PHOTO_WIDTH     98
#define   PHOTO_HEIGH     98
#define   PHOTO_TOP       25

//��Ϸ��ɫ����
#define   COLOR_YELLOW    RGB(255,255,0)
#define   COLOR_BLACK     RGB(0,0,0)

//����ı�����
#define  MAXOUTPUTWORD    200       //�������ַ�����   
#define  WORD_HEIGH       17
#define  OUTPUT_WORD_NUM  30        //���������з�����

//��Ч����

//-------------------------------------------------------------------------------------


#endif
