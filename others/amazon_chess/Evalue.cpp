#include "define.h"
#include "Evalue.h"
#include "stdlib.h"
#include "math.h"



struct line {											//�����¼����������У����ڴ�������нڵ�����
	int x;
	int y;
	//int num;
} point_line[MAXSIZE*MAXSIZE];

int stepx[] = {1, 0, -1, 0, 1, 1, -1, -1},				//���경�����飬�˸�����
	stepy[] = {0, 1, 0, -1, 1, -1, 1, -1};

bool map_color[MAXSIZE][MAXSIZE];						//����������������ɫ����

int D_queen[2][MAXSIZE][MAXSIZE],						//��������˫��������ں��ƶ���Χ����ͨ�Ծ���0����췽����1����׷�����
	D_king[2][MAXSIZE][MAXSIZE];

int konggelingdu[MAXSIZE][MAXSIZE]={0};    
//int chess_king[MAXSIZE][MAXSIZE]={0};

//bool map_queen_red[MAXSIZE][MAXSIZE]={false};
//bool map_queen_white[MAXSIZE][MAXSIZE]={false};

void mapvalue::set () {											//����ͨ�Ծ�����ȫ����ΪINFINITY
	int i, j;
	for (i = 0; i < MAXSIZE; i ++) {
		for (j = 0; j < MAXSIZE; j ++){
			D_queen[0][i][j] = INFINITY;
			D_queen[1][i][j] = INFINITY;
			D_king[0][i][j] = INFINITY;
			D_king[1][i][j] = INFINITY;
		}
	}
}


void mapvalue::search_path (MapType map, int i, int j, int ourcolor) 
{
	int r, x, y, start, end;

	start = end = 0;
	point_line[0].x = i;
	point_line[0].y = j;
	D_queen[ourcolor - 1][i][j] = 0;
	map_color[i][j] = true;

	for (; start <= end; start ++) {
		
		if (start == 0)       //����
		{
			map[i][j] = NOSTONE;
		}
		else {
			map[i][j] = ourcolor;
		}

		for (r = 0; r < 8; r ++) {//ͨ������Ѱ����̾���
			for (x = point_line[start].x, y = point_line[start].y; x >= 0 && x < MAXSIZE && y >= 0 && y < MAXSIZE ; x += stepx[r], y += stepy[r]) 
			{   
				//�����map[x][y]�����ǿո񣬲��һ�δ��̽Ѱ�������¼x��y
				if (map[x][y] != NOSTONE) break;
				else {
					if (map_color[x][y] == false) {
						end ++;
						point_line[end].x = x;
						point_line[end].y = y;
						map_color[x][y] = true;
					}
					if (D_queen[ourcolor - 1][x][y] > D_queen[ourcolor - 1][point_line[start].x][point_line[start].y] + 1) 
					{
						D_queen[ourcolor - 1][x][y] = D_queen[ourcolor - 1][point_line[start].x][point_line[start].y] + 1;
					}
				}

			}
		}
	}

	map[i][j] = ourcolor;
	
	memset (map_color, false, sizeof (map_color));
	start = end = 0;
	point_line[0].x = i;
	point_line[0].y = j;
	D_king[ourcolor - 1][i][j] = 0;
	map_color[i][j] = true;

	for (; start <= end; start ++) {
		for (r = 0; r < 8; r ++) {
			x = point_line[start].x + stepx[r];
			y = point_line[start].y + stepy[r];
			if (x >= 0 && x < MAXSIZE && y >= 0 && y < MAXSIZE && map[x][y] == NOSTONE) {
				if (map_color[x][y] == false) {
					end ++;
					point_line[end].x = x;
					point_line[end].y = y;
					map_color[x][y] = true;
				}
				if (D_king[ourcolor - 1][x][y] > D_king[ourcolor - 1][point_line[start].x][point_line[start].y] + 1)
				{
					D_king[ourcolor - 1][x][y] = D_king[ourcolor - 1][point_line[start].x][point_line[start].y] + 1;
				}
			}
		}
	}

}

int mapvalue::Evalue (MapType map,int stepnumber,int color)//�Ե�ǰ���̵Ĺ�ֵ
{
	//FILE *p = fopen("r.txt", "a+");//д��
	//FILE *pw = fopen("w.txt", "a+");//д��
	int i, j,king=0;       
	double m=0,red_value=0,white_value=0;
	double t1=0,t2=0;
	double c1=0,c2=0,t=0;
	double a=0,b=0,c=0,d=0,e=0;
	double value=0;
	set ();
	//����ÿһ�ո����ڵĿո���
	for (i = 0; i < MAXSIZE; i ++) 
	{
		for (j = 0; j < MAXSIZE; j ++)
		{
			int lingdu=0;
			int x=0,y=0;
			if (map[i][j] == NOSTONE )
			{
				for(int a=0;a<8;a++)
				{
					x=i+stepx[a];
					y=j+stepy[a];
					if(x >= 0 && x < MAXSIZE && y >= 0 && y < MAXSIZE )
					{
						if (map[x][y] == NOSTONE)  
						{lingdu++;}
					}
				}
				konggelingdu[i][j]=lingdu;
				/*fprintf(pw, "mΪ��%d\n",konggelingdu[i][j]);
				fclose(pw);*/
			}
		}
	}
	for (i = 0; i<4; i++)
	{
		memset (map_color, false, sizeof (map_color));	
		search_path (map, posx[i], posy[i], RED);
	}
	for (i = 4; i<8; i++) 
	{
		memset (map_color, false, sizeof (map_color));	
		search_path (map, posx[i], posy[i], WHITE);					//������հ׵���������ں��ƶ���Χ�µľ���
	}
	stepnumber=stepnumber+1;//ͳ��˫���ߵĲ�����
	for (i = 0; i < MAXSIZE; i ++)
	{
		for (j = 0; j < MAXSIZE; j ++) 
		{
			if (map[i][j] == NOSTONE )
			{
				if(D_queen[0][i][j]==INFINITY&&D_queen[1][i][j]==INFINITY&&D_queen[0][i][j]==D_queen[1][i][j]) {t1+=0;} 
				if(D_queen[0][i][j]==D_queen[1][i][j]&&D_queen[0][i][j]<INFINITY&&D_queen[1][i][j]<INFINITY) 
				{
					if(color==WHITE)
					{
						if(stepnumber>=0&&stepnumber<=20){t1+=0.05;}
						if(stepnumber>=21&&stepnumber<=49){t1+=0.35;}
						if(stepnumber>=50){t1+=0.55;}
					
					}
					if(color==RED)
					{
					t1-=0.25;
					}
				}
				if(D_queen[0][i][j]>D_queen[1][i][j]){t1+=1;}//����t1
				if(D_queen[0][i][j]<D_queen[1][i][j]){t1+=-1;}//����t1
				if(D_king[0][i][j]==INFINITY&&D_king[1][i][j]==INFINITY&&D_king[0][i][j]==D_king[1][i][j]){ t2+=0;}//����t2
				if(D_king[0][i][j]==D_king[1][i][j]&&D_king[0][i][j]<INFINITY&&D_king[1][i][j]<INFINITY)
				{
					if(color==WHITE)
					{
						if(stepnumber>=0&&stepnumber<=20){t2+=0.55;}
						if(stepnumber>=21&&stepnumber<=49){t2+=0.45;}
						if(stepnumber>=50){t2+=0.05;}
					}
					if(color==RED)
					{
					t2-=0.25;
					}
				}
				if(D_king[0][i][j]>D_king[1][i][j]){t2+=1;}//����t2
				if(D_king[0][i][j]<D_king[1][i][j]){t2+=-1;}//����t2
				c1+=(pow(0.5,D_queen[1][i][j])-pow(0.5,D_queen[0][i][j])); //�����Ƿ��ĵ��е�p1
				c2+=min(1,max(-1,(D_king[0][i][j]-D_king[1][i][j])/6));//�����Ƿ��ĵ��е�p2
			}
			if(map[i][j]==RED)
			{
				for(int r=0;r<8;r++)  //��ѭ���ǿ��ư˸������
				{
					king=0;
					for(int x=i,y=j;x >= 0 && x < MAXSIZE && y >= 0 && y < MAXSIZE ; x += stepx[r], y += stepy[r]) //һ������ĳ�����򣬼����÷���������֪���������ǿո��λ��
					{
						if(x!=i||y!=j)//�����������ӱ���λ��
						{
							if(map[x][y]==NOSTONE)
							{
								king++;     //kingֵ�Ǽ�������ӵ��ÿո���king�߷���ֵ
								/* fprintf(p, "�����KINGΪ��%d\n",king);
								fclose(p);*/
							red_value+=pow(0.5,king)*(double)konggelingdu[x][y];	
								
							}
							else{break;}
						}
					}
				}
			}
			if(map[i][j]==WHITE)
			{
				for(int r=0;r<8;r++)
				{
					king=0;
					for(int x=i,y=j;x >= 0 && x < MAXSIZE && y >= 0 && y < MAXSIZE ; x += stepx[r], y += stepy[r])
					{
						if(x!=i||y!=j)
						{
							if(map[x][y]==NOSTONE)
							{
								king++;
								/*fprintf(pw, "�����KINGΪ��%d\n",king);
								fclose(pw);*/
								white_value+=pow(0.5,king)*(double)konggelingdu[x][y];
								
							}
							else{break;}

						}	
					}	
				}
			}
		}
	}
		c1=c1*2.0;
		/*fprintf(pw, "��ɫ���ӵ�����Ϊ��%lf\n",white_value);
		fprintf(p, "��ɫ���ӵ�����Ϊ��%lf\n",red_value);*/
		m=white_value-red_value;  //����mֵ
		//fprintf(p, "mΪ��%lf\n",m);
		//fclose(p);
		/*fclose(pw);*/
		if(stepnumber>=0&&stepnumber<=20)
		{
			a=0.14;b=0.37;c=0.13;d=0.13,e=0.20;
			value=a*t1+b*t2+c*c1+d*c2+e*m;
		}
		if(stepnumber>=21&&stepnumber<=49)
		{
			a=0.30;b=0.25;c=0.20;d=0.20,e=0.05;
			value=a*t1+b*t2+c*c1+d*c2+e*m;
		}
		if(stepnumber>=50)
		{
			a=0.80;b=0.10;c=0.05;d=0.05,e=0.00;
			value=a*t1+b*t2+c*c1+d*c2+e*m;
		}
		return (int)value;
	}

