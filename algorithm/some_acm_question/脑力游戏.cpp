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

//�߾��ȼӷ�
for (int i = 0; i < ret.len; i++)			//���Խ�λ��λ���
	ret.d[i] = d[i] + other.d[i];
for (int i = 0; i < ret.len; i++)			//�����λ
	if (ret.d[i] > 9){
		ret.d[i] -= 10;
		ret.d[i+1]++;
	}
if (ret.d[ret.len] > 0)
	ret.len++;

//�߾��ȳ˷�
for(int i = 0; i < len; i++)				//�߾��ȳ˷�
	for (int j = 0; j < other.len; j++)
		ret.d[i+j] += d[i] * other.d[j];
for (int i = 0; i < ret.len; i++)			//�����λ
	if (ret.d[i] > 9){
		ret.d[i+1] += ret.d]i] / 10;
		ret.d[i] %= 10;
	}
if (ret.d[ret.len] > 0)
	ret.len++;								//���λ��λ

//��Ҫ���ݽṹ
class BigInteger{};		//�߾�����������ֻ�üӷ��ͳ˷� 
int f[][];				//״̬���飬��ʾiԪ�û����ж��ٸ��û����Կ��Էֽ�Ϊj�����ཻ���ֻ�