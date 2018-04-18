
#include "define.h"
#include "SearchEngine.h"
#include "Evalue.h"
#include "makemove.h"

mapmove move;		//�з����ɶ���
mapvalue value;	    //��ֵ����

int searchdeep = MAX_DEEP;  
int searchwidth = 15;     //What's this?
HeapType heap[MAXMOVE];
int end;
int stepnumber=0;//�ҷ��ߵĲ���
SearchEngine::SearchEngine ()
{
}

bool SearchEngine::search_a_goodmove(MapType m,int color ,MoveType* bestmove)
{
	int score = MAX_VALUE + 10;       //��ʼΪ��ֵ

	for (int i=0; i<MAXSIZE; i++)        //��������
		for (int j = 0; j<MAXSIZE; j++)
			map[i][j] = m[i][j];     
	if(stepnumber == 0  && color == WHITE)
	{
		StackType start0;
		start0.top = 0;
		start0.chessmove[start0.top].x[0]=9;
		start0.chessmove[start0.top].y[0]=3;
		start0.chessmove[start0.top].x[1]=2;
		start0.chessmove[start0.top].y[1]=3;
		start0.chessmove[start0.top].x[2]=4;
		start0.chessmove[start0.top].y[2]=1;
		*bestmove = start0.chessmove[0];
		stepnumber++;
		return true;
	}
   if(color==RED)
	{
	   if(stepnumber == 0&&map[6][9]==WHITE&&map[5][8]==NOSTONE&&map[6][7]==NOSTONE)
		{
			int count=0;
		  for(int i=1;map[i][6]==NOSTONE&&i<=7;i++)
		  {
		     count++;
		  }
		  if(count==7)
		  {
		  StackType start0;
		start0.top = 0;
		start0.chessmove[start0.top].x[0]=0;
		start0.chessmove[start0.top].y[0]=6;
		start0.chessmove[start0.top].x[1]=7;
		start0.chessmove[start0.top].y[1]=6;
		start0.chessmove[start0.top].x[2]=5;
		start0.chessmove[start0.top].y[2]=8;
		*bestmove = start0.chessmove[0];
		stepnumber++;
		return true;
		  }
		} 
	    if(stepnumber == 0&&map[6][0]==WHITE&&map[5][1]==NOSTONE&&map[6][2]==NOSTONE)
		{
			int count=0;
		  for(int i=1;map[i][3]==NOSTONE&&i<=7;i++)
		  {
		     count++;
		  }
		  if(count==7)
		  {
		  StackType start0;
		start0.top = 0;
		start0.chessmove[start0.top].x[0]=0;
		start0.chessmove[start0.top].y[0]=3;
		start0.chessmove[start0.top].x[1]=7;
		start0.chessmove[start0.top].y[1]=3;
		start0.chessmove[start0.top].x[2]=5;
		start0.chessmove[start0.top].y[2]=1;
		*bestmove = start0.chessmove[0];
		stepnumber++;
		return true;
		  }
		} 
	}
    if(stepnumber+1>=13&&stepnumber+1<=49){searchdeep=4;searchwidth=20;}
	if(stepnumber+1>=50){searchdeep=5;searchwidth=25;}
	score = alpha_beta_search(searchdeep,color,-MAX_VALUE - 1,MAX_VALUE + 1);   //����
	if (score != MAX_VALUE + 10)       
	{
		*bestmove = mybestmove;      //�ı�����߷�ָ���ֵ
		{
			stepnumber++;
			return true;
		}
	}
	return false;                    //�����ص���Ȼ�Ǽ�ֵ��������ʧ��
}
bool SearchEngine::lost(int color)       //�ж�ĳ���Ƿ�Ӯ
{
	int k,i,t;
	int dx[8] = {-1,-1,-1, 0, 0, 1,1,1};     //�������경��
	int dy[8] = {-1, 0, 1,-1, 1,-1,0,1};
	if (color == WHITE)
		k = 4;
	else k = 0;
	for (i = k; i<k+4; i++)    //i����ڼ�������
	{
		for (t = 0; t < 8; t++)    //t�ǲ�������Ŀ���
			if ( posx[i] + dx[t] >= 0 && posx[i] + dx[t] < MAXSIZE && posy[i] + dy[t] >= 0 && posy[i] + dy[t] < MAXSIZE
				   && map[posx[i]+dx[t]][posy[i]+dy[t]] == NOSTONE)
				   return false;
	}
	return true;

}

void SearchEngine::movechess(MoveType nowmove)       
{
	for (int i = 0; i<8; i++)
		if (posx[i] == nowmove.x[0] && posy[i] == nowmove.y[0])        //�ҵ��ƶ�������
		{
			posx[i] = nowmove.x[1];
			posy[i] = nowmove.y[1];
		}
	map[nowmove.x[1]][nowmove.y[1]] = map[nowmove.x[0]][nowmove.y[0]];
	map[nowmove.x[0]][nowmove.y[0]] = NOSTONE;
	map[nowmove.x[2]][nowmove.y[2]] = OBSTACLE;

}

void SearchEngine::unmovechess(MoveType nowmove)     //�������ӵ��ƶ�
{
	for (int i = 0; i<8; i++)
		if (posx[i] == nowmove.x[1] && posy[i] == nowmove.y[1])
		{
			posx[i] = nowmove.x[0];
			posy[i] = nowmove.y[0];
		}
	map[nowmove.x[2]][nowmove.y[2]] = NOSTONE;
	map[nowmove.x[0]][nowmove.y[0]] = map[nowmove.x[1]][nowmove.y[1]];
	map[nowmove.x[1]][nowmove.y[1]] = NOSTONE;
}





int SearchEngine::alpha_beta_search(int dep,int color,int alpha,int beta)  //������ֵ�㷨
{
	StackType stack;                                //����һ���з�ջ
	int score,i,bestscore = -MAX_VALUE - 1;         //���ֵ��ʼΪ������
	int t,width;                                    //width�����ò��Ǻ��˽�
	int pointvalue[MAXMOVE];     //�з��Ʒ�����

	if (lost(color))             //�жϸ÷��Ƿ��� ��ȷ��
		return -MAX_VALUE;
	if (lost(color ^ 3))         //�ж���һ���Ƿ���
		return MAX_VALUE;
	if (dep <= 0)               //Ҷ�ӽڵ㣬���ع�ֵ
	{
		if (color == WHITE)
			score = value.Evalue(map,stepnumber,color);
		else score = -value.Evalue(map,stepnumber,color);
		return score;
	}
	else                  
	{
		move.makemoves(map,color);                //�߷����ɣ�����ȫ�������߷�
		stack = move.stack;                       //����ջ
        for (i = 0; i<=stack.top; i++)            //�����ɵĿ��ܾ��涼����һ�ι�ֵ
		{
			movechess(stack.chessmove[i]);        
			if (color == WHITE)
				pointvalue[i] = value.Evalue(map,stepnumber,color);
			else pointvalue[i] = -value.Evalue(map,stepnumber,color);
			unmovechess(stack.chessmove[i]);           //��ֵ��ظ�����
		}
		width = searchwidth < stack.top+1 ? searchwidth : stack.top+1;        //��������˽�
		heap_sort(pointvalue,width,stack.top);         //�ڵ�����
		for (i = stack.top; i>stack.top - width; i--)
			pointvalue[i] = heap[i].index;             //�Ʒ����飬�����˳��

		for ( t = stack.top; t>stack.top - width; t--)     //�����п��ܵ��߷�
		{
			i = pointvalue[t];                             
			movechess(stack.chessmove[i]);
			score = -alpha_beta_search(dep-1,color ^ 3,-beta,-alpha);//�ݹ������ӽڵ�
			unmovechess(stack.chessmove[i]);
			if (score > alpha)
			{
				alpha = score;                //ȡ���ֵ
				if (dep == searchdeep)        
					mybestmove = stack.chessmove[i];        //�����в��˽�ĵط�
			}
			if (alpha>=beta)
				break;
		}
	}
	return alpha;                             
	
}

//��Ŀ��Ŀ�ǳ��󣬹ʲ��ö�����
void SearchEngine:: init_heap()
{
	int i;
	for (i = end / 2 ; i>=0; i--)
		heap_down(i);
}

void SearchEngine:: heap_down(int i)
{
	int j;
	HeapType temp;

	j = i*2;
	while (j<=end)
	{
		if (j<end && heap[j].data<heap[j+1].data) j++;
		if (heap[i].data<heap[j].data)
		{
			temp = heap[i];
			heap[i] = heap[j];
			heap[j] = temp;
			i = j;
			j = i*2;
		}
		else break;
	}
}

void SearchEngine:: heap_sort(int line[],int num,int n)
{
	int i;
	HeapType temp;
	for (i = 0; i<=n; i++)
	{
		heap[i].data = line[i];
		heap[i].index = i;
	}
	end = n;
	init_heap();
	for (i = 0; i<num; i++)
	{
		temp = heap[0];
		heap[0] = heap[end];
		heap[end] = temp;
		end--;
		heap_down(0);
	}
}