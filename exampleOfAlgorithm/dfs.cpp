/*
dfs之n皇后问题
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 25
using namespace std;
int n, asr, vis[3][N];//vis数组保存放置了的皇后占据哪几列，哪些正副对角线
void dfs(int cnt)//正在放置第cnt个皇后，前cnt-1个已经放好
{
	if(cnt > n) asr++;
	else
		for(int i = 1;i <= n;i++)
			if(!vis[0][i] && !vis[1][cnt + i] && !vis[2][cnt - i + n])
			{
				vis[0][i] = vis[1][cnt+i] = vis[2][cnt - i + n] = 1;
				dfs(1+cnt);
				vis[0][i] = vis[1][cnt+i] = vis[2][cnt - i + n] = 0;
			}
}

int main()
{
	int ar[11];
	memset(vis, 0, sizeof(vis));
	for(int i = 1;i<11;i++)
	{
		asr = 0;
		n = i;
		dfs(1);
		ar[i] = asr;
	}
	for(;scanf("%d", &n) != EOF && n != 0;)
	{
		printf("%d\n", ar[n]);
	}
	return 0;
}
