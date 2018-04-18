#include "define.h"
#include "makemove.h"

void mapmove::push(int x_o,int y_o,int x_d,int y_d,int z_o,int z_d)
{
	if(x_o<0 || y_o<0 || x_o>=10 || y_o>=10 || z_o<0 || z_o>=10)
		return ;
	if(x_d<0 || y_d<0 || x_d>=10 || y_d>=10 || z_d<0 || z_d>=10)
		return ;
	stack.top++;
	stack.chessmove[stack.top].x[0]=x_o;
	stack.chessmove[stack.top].y[0]=y_o;
	stack.chessmove[stack.top].x[1]=x_d;
	stack.chessmove[stack.top].y[1]=y_d;
    stack.chessmove[stack.top].x[2]=z_o;
	stack.chessmove[stack.top].y[2]=z_d;
}
int bit1,bit2,bit3,bit4,jiaoh;      //全局变量 交换数据
void mapmove::bit(int i,int j,int m,int n)
{
   bit1=i;
   bit2=j;
   bit3=m;
   bit4=n; 
}
void mapmove::move_queen(int i,int j)     //移动皇后
{
	int lu,rd,ld,ru,k;
	//左上-右下走子
    lu=-1;      //左上角
	while(i+lu>=0&&j+lu>=0&&map[i+lu][j+lu]==NOSTONE)    //走到终点，记录终点-1
		lu--;
    rd=1;       //右下角
	while(i+rd<=9&&j+rd<=9&&map[i+rd][j+rd]==NOSTONE)     //走到终点，记录终点+1
		rd++;
	for(k=lu+1;k<rd;k++)
                    if(k!=0)
                 {  
				    bit(i,j,i+k,j+k);                     //交换数据
                    move_ob(i+k,j+k);                     //进入障碍物移动
                 }
	//右上-左下走子
    ru=-1;       //右上角
	while (i+ru>=0&&j-ru<=9&&map[i+ru][j-ru]==NOSTONE)
		ru--;
    ld=1;        //左下角
	while(i+ld<=9&&j-ld>=0&&map[i+ld][j-ld]==NOSTONE)
		ld++;
	for(k=ru+1;k<ld;k++)
		if(k!=0)
		  {
                     bit(i,j,i+k,j-k);
                     move_ob(i+k,j-k);
           } 
        /* 

        */
	int u,d,r,L,k2;
	//纵向走子
	u=i-1;
	while(u>=0&&map[u][j]==NOSTONE)    
		u--;
    d=i+1;
	while(d<=9&&map[d][j]==NOSTONE)
		d++;
	for(k2=u+1;k2<d;k2++)
		if(k2!=i)
                  {
    	             bit(i,j,k2,j);
                     move_ob(k2,j);
                   }
	//横向走子
	L=j-1;
	while(L>=0&&map[i][L]==NOSTONE)
		L--;
    r=j+1;
	while(r<=9&&map[i][r]==NOSTONE)
		r++;
	for(k2=L+1;k2<r;k2++)
		if(k2!=j)
		{
			bit(i,j,i,k2);
            move_ob(i,k2);
		}
}
void mapmove::move_ob (int i,int j)
{
    jiaoh=map2[bit3][bit4];                       //先移动皇后
	map2[bit3][bit4]=map2[bit1][bit2];
    map2[bit1][bit2]=jiaoh;
    
	
    int lu,rd,ld,ru,k;
	//左上-右下走子
    lu=-1;
	while(i+lu>=0&&j+lu>=0&&map2[i+lu][j+lu]==NOSTONE)
		lu--;
    rd=1;
	while(i+rd<=9&&j+rd<=9&&map2[i+rd][j+rd]==NOSTONE)
		rd++;
	for(k=lu+1;k<rd;k++)
		if(k!=0)
		    push(bit1,bit2,bit3,bit4,i+k,j+k);        //入招法栈
	//右上-左下走子
    ru=-1;
	while(i+ru>=0&&j-ru<=9&&map2[i+ru][j-ru]==NOSTONE)
		ru--;
    ld=1;
	while(i+ld<=9&&j-ld>=0&&map2[i+ld][j-ld]==NOSTONE)
		ld++;
	for(k=ru+1;k<ld;k++)
		if(k!=0)
		    push(bit1,bit2,bit3,bit4,i+k,j-k);
        /*

        */
	int u,d,r,L,k2;
	//纵向走子
	u=i-1;
	while(u>=0&&map2[u][j]==NOSTONE)
		u--;
    d=i+1;
	while(d<=9&&map2[d][j]==NOSTONE)
		d++;
	for(k2=u+1;k2<d;k2++)
		if(k2!=i)
    	    push(bit1,bit2,bit3,bit4,k2,j);
	//横向走子
	L=j-1;
	while(L>=0&&map2[i][L]==NOSTONE)
		L--;
    r=j+1;
	while(r<=9&&map2[i][r]==NOSTONE)
		r++;
	for(k2=L+1;k2<r;k2++)
		if(k2!=j)
		    push(bit1,bit2,bit3,bit4,i,k2);
		/**/
   jiaoh=map2[bit1][bit2];             //皇后移回去，因为招法已经入栈
   map2[bit1][bit2]=map2[bit3][bit4];
   map2[bit3][bit4]=jiaoh;

}
void mapmove::makemoves(MapType m,int color)     //传入棋盘和颜色
{
	int i,j;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			map2[i][j]=map[i][j]=m[i][j];
	stack.top = -1;                         //空栈
	if(color==RED)
	{
       for(i=0;i<=3;i++)              //posx,posy存了红棋的位置
           move_queen(posx[i],posy[i]);
	}
    if (color==WHITE)
	{
        for(i=4;i<=7;i++)              //posx,posy存了白棋的位置
           move_queen(posx[i],posy[i]);                           
	}
		
}

