void preprocess(){
	f[0][0] = 1;
	for (int i = 1; i <= MAXN; i++)
		for (int j = 1; j <= MAXN; j++)
			f[i][j] = f[i-1][j-1] + f[i-1][j] * (i-1);
}

while(input()){
	BigInteger ans(0);
	for (int i = 1; i <= k; i++)
		ans = ans + f[n][i];
	ans.print();
	puts("");
}

//高精度加法
for (int i = 0; i < ret.len; i++)			//忽略进位逐位相加
	ret.d[i] = d[i] + other.d[i];
for (int i = 0; i < ret.len; i++)			//处理进位
	if (ret.d[i] > 9){
		ret.d[i] -= 10;
		ret.d[i+1]++;
	}
if (ret.d[ret.len] > 0)
	ret.len++;

//高精度乘法
for(int i = 0; i < len; i++)				//高精度乘法
	for (int j = 0; j < other.len; j++)
		ret.d[i+j] += d[i] * other.d[j];
for (int i = 0; i < ret.len; i++)			//处理进位
	if (ret.d[i] > 9){
		ret.d[i+1] += ret.d]i] / 10;
		ret.d[i] %= 10;
	}
if (ret.d[ret.len] > 0)
	ret.len++;								//最高位进位

//重要数据结构
class BigInteger{};		//高精度正整数类只用加法和乘法 
int f[][];				//状态数组，表示i元置换中有多少个置换可以可以分解为j个不相交的轮换