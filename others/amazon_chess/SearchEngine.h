#ifdef _SEARCH_ENGINE_H_
#else
#define _SEARCH_ENGINE_H_

#include "define.h"

class SearchEngine	//搜索引擎类
{
	public:
		SearchEngine ();          
		//对外接口
		//参数说明：map:当前棋局，color:走子方颜色，bestmove:最优招法指针 
		//返回类型说明：如果搜索成功返回true,否则返回false;
        bool search_a_goodmove(MapType m,int color ,MoveType* bestmove);
		//堆排序
		//参数说明：line:待排序的序列，num: 要排前num个元素，n:总排序列的个数-1
		void heap_sort(int line[],int num,int n);                       
	private:
		int alpha_beta_search(int dep,int color,int alpha,int beta);   //alpha-beta搜索
		bool lost(int color);                                //判断color方是否赢
		void movechess(MoveType nowmove);                    //移动子
		void unmovechess(MoveType nowmove);                  //撤销移动
		void init_heap();                                    //初始化堆
		void heap_down(int i);                               //节点下沉
		
		MapType map;                      //搜索文件的棋盘   
		MoveType mybestmove;              //一个走法，搜索文件中的
};

#endif