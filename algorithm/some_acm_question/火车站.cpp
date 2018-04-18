int g1[MAXN][MAXN];					//��ͼ�ڲ����ڽӾ���
int g2[MAXN][MAXN];					//��ͼ�ڲ����ڽӾ���
int cross[MAXN];					//������ͼ��Ӧ�����ľ���
int f[1 << MAXN];					//��¼Ԥ����ʱ�����Ž��
int G[1 <<	MAXN][1 << MAXN];		//��ͼ���ڽӾ���

void process(int g[MAXN][MAXN]){
	memset(G,-1,sizeof(G));
	//ֱ��ʹ�ñ�(i,j)��ͬʱ�ı�i��j����ż��
	for(int i = 0; i < n; i++)
		for(int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				G[i][i ^ (1 << j) ^ (1 << k)] = g[i][k];

	dijkstra();						//ͨ����Դ���·���ó����ŵĺķ�
	for (int i = 0; i < n; i++)		//�ѽ����¼�����Թ�����
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