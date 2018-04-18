#ifdef _DEFINE_H_H_        //防止重复定义
#else
#define _DEFINE_H_H_

/*
备注
(1)坐标系：原点棋盘左上角，x是纵坐标（第x行）y是横坐标（第y行）
(2)你们可以自行填加删除这个头文件里的内容，注意更改后就要发更新的define并通知其他人
(3)一些私有的常量定义就放到你们各自的头文件里，共有的放这里。
*/


#define  MAXMOVE    3000     //一个棋局的最大招法个数
#define  MAX_VALUE  9999999    //评估的最大值 {}
#define  MAX_DEEP   3       //搜索最大的大深度
#define  TURNROLE   3       


//棋盘常量定义

#define   MAXSIZE   10        //棋盘大小10*10下标0-9
#define   NOSTONE   0         //无棋子
#define   RED       1         //红方棋子
#define   WHITE     2         //白方棋子
#define   OBSTACLE  3         //障碍

//着法定义
typedef struct 
{
	int x[3];                 //x[0] 棋子起点x轴坐标、x[1]棋子落点x轴坐标、x[2]障碍坐标
    int y[3];                 //y[0] 棋子起点y轴坐标、y[1]棋子落点y轴坐标、y[2]障碍坐标
}MoveType;
//定义自己方

//招法栈定义
typedef struct             
{
     MoveType chessmove[MAXMOVE];
     int top;           //数量 最顶 作用相当于一个指针，指示作用
}StackType;

//堆结构定义
typedef  struct                  //用于堆排序
{
	int data;                                   //关键字
	int index;                                  //关键字索引
}HeapType;

//棋盘定义
typedef   int MapType[MAXSIZE][MAXSIZE];        //棋盘

extern    int ourcolor;                         //记录我方颜色
extern    int posx[8];                          //记录八个子的位置，前4个是红方，后4个是白方
extern    int posy[8];                          //记录八个子的位置，前4个是红方，后4个是白方

//-------------------------------------------界面常量定义区----------------------------

//界面框架大小
#define CHESSLENGTH        50               //棋子大小
#define BOARD              10               //边界宽
#define MAP_OUTSIDE_BOARD  20               //地图外边界宽度
#define OUTPUT_WIDTH       250              //输出信息窗口宽度
#define PLAYERAREA_WIDTH   150              //选手区宽度
#define PLAYERAREA_BOARD   5                //选手区域边界
#define PLAYERTIME_WIDTH   13               //秒表数字区域宽度
#define PLAYERTIME_HEIGH   23               //秒表数字区域高度


//游戏状态
#define GAME_OVER         0
#define GAME_VICOTORY     1
#define GAME_WAIT         2
#define GAME_RUN          3
#define GAME_SELECT       4 
#define GAME_MOVE         5

//按钮状态
#define BUTTON_NOMAL      0
#define BUTTON_SELECT     1
#define BUTTON_DOWN       2

//游戏区域划分
#define BODYAREA          0
#define MAPAREA           1
#define OUTPUTAREA        2
#define PLAYER1AREA       3
#define PLAYER2AREA       4
#define BUTTON0AREA       5
#define BUTTON1AREA       6
#define BUTTON2AREA       7
#define BUTTON3AREA       8



//计时器ID
#define   ID_TIMER1       100
#define   ID_TIMER2       200
#define   ID_TIMER3       300

//按钮大小定义
#define   BUTTON_WIDTH    120
#define   BUTTON_HEIGH    30
#define   BUTTON_TOP      157

//头像大小定义
#define   PHOTO_WIDTH     98
#define   PHOTO_HEIGH     98
#define   PHOTO_TOP       25

//游戏颜色定义
#define   COLOR_YELLOW    RGB(255,255,0)
#define   COLOR_BLACK     RGB(0,0,0)

//输出文本定义
#define  MAXOUTPUTWORD    200       //最大输出字符个数   
#define  WORD_HEIGH       17
#define  OUTPUT_WORD_NUM  30        //最多输出的招法个数

//音效定义

//-------------------------------------------------------------------------------------


#endif
