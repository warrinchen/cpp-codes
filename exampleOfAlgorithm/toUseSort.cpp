#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>//包含头文件

#define N 5

using namespace std;

//使之从大到小排序
bool complare(int a,int b)
{
    return a>b;
}

/*
有一个node类型的数组node arr[100]
想对它进行排序：先按a值升序排列，
如果a值相同，再按b值降序排列，
如果b还相同，就按c降序排列。可以写这样一个比较函数：
*/
struct node
{
   int a;
   int b;
   double c;
};

bool cmp(node x,node y)
{
    if(x.a!=y.a) return x.a<y.a;
    if(x.b!=y.b) return x.b>y.b;
    return x.c>y.c;
}

int main()
{
    int a[N]={1, 3, 5, 2, 9};
    //sort(a, a+N);//默认从小到大
    sort(a, a+N, complare);//从大到小
    return 0;
}
