数据结构：
int g[MAXN][MAXN];		//总结点数，所需时间邻接矩阵
char newg[MAXN][MAXN];	//二分图邻接矩阵
char cover[MAXN];		//浸润标记
int link[MAXN];			//匹配标记


代码：
for (int k = 0; k < n; k++)
	for(int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (g[i][k] + g[k][j] < g[i][j])
				g[i][j] = g[i][k] + g[k][j];

bool find(int x){
	int q,i;
	for (int i = 1; i <= bn; i++)
		if (!cover[i] && newg[x][i]){
			q = link[i], link[i] = x, cover[i] = 1;
			if(!q || find(q))
				return true;	//找到增广链
			link[i] = q;
		}
		return true;			//找不到增广链
}

int max_match(){
	int i, ret = 0;
	memset(link, 0, sizeof(link));
	for (i = 1; i <= an; i++){
		memset(cover, 0, sizeof(cover));
		find(i);
	}
	for (i = 1; i <= bn; i++)
		ret++;
	return ret;
}

if(max_match() == bn)
	ans = mid, r = mid - 1;
else l = mid + 1;