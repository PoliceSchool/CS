int g1[MAXN][MAXN];					//左图内部的邻接矩阵
int g2[MAXN][MAXN];					//右图内部的邻接矩阵
int cross[MAXN];					//左右两图对应顶点间的距离
int f[1 << MAXN];					//记录预处理时的最优结果
int G[1 <<	MAXN][1 << MAXN];		//新图的邻接矩阵

void process(int g[MAXN][MAXN]){
	memset(G,-1,sizeof(G));
	//直接使用边(i,j)以同时改变i和j的奇偶性
	for(int i = 0; i < n; i++)
		for(int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				G[i][i ^ (1 << j) ^ (1 << k)] = g[i][k];

	dijkstra();						//通过单源最短路径得出最优的耗费
	for (int i = 0; i < n; i++)		//把结果记录下来以供后用
		if(d[i] < INF){
			f[i] += d[i];
			flag[i]++;
		}
}

int ans = INF;
for (int i = 0; i < n; i++){
	if (flag[i] == 2){
		int t = f[i];
		for (int j = 0; j < N; j++)
			if (( i & (1 << j)) > 0)
				t += cross[j];
	}
	ans = min(ans,t);


void dijkstra(){
	for(int i = 0; i < n; i++)
		d[i] = INF;
	d[n-1] = 0;
	memset(mk, 0, sizeof(mk));
	for (int i =1; i < n; i++){
		int u= -1;
		for (int v = 0; v < n; v++)
			if (!mk[v] && (u == -1 || d[v] < d[u])
				u = v;
		mk[u] = true;
		if (d[u == INF)
			break;
		for (int v = 0; v < n; v++)
			if (G[u][v] != -1 && !mk[v]){
				int t = d[u] + G[u][v];
				if(t < d[v])
					d[v] = t;
			}
	}