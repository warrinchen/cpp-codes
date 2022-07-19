#include <iostream>
#include <cstdio>
#define N 100010
using namespace std;

int head[N] = {0}, tot, n;
struct node
{
	int next, to;
	double val;
} a[N<<1];

void add(int x, int y, int va)
{
	a[++tot].next = head[x];
	head[x] = tot;
	a[tot].to = y;
	a[tot].val = va;
}

int main()
{
	for(int i = 1;i < n;i++)
	{
		int x, y;
		double z;
		scanf("%d%d%lf", &x, &y, &z);
		add(x,y,z);
		add(y,x,z);
	}
    return 0;
}