#include <iostream>
#include <algorithm>
#define N 7
#define ll long long
#define fio ios::sync_with_stdio(false)

using namespace std;

int ar[N] = {0,2,3,4,3,5,6}, bp[N] = {0,2,3,4,3,5,6}, dest[N];
//数组下标从1起始，
//包含头文件algorithm，三个库函数的参数都是左闭右开。所以，（首地址，首地址+长度）

bool cgComparison(int a, int b)
{
    return a>b;
}
void dctz(int *ar, ll arLen, int *bp, int *dest)
{
    //sort(ar+1, ar+arLen, cgComparison);//使sort函数实现从大到小排序
    sort((ar+1), ar+arLen);
    int sz = unique((ar+1), ar+arLen) - (ar+1);//返回值是最后一个不重复的元素的后一个的地址
    for(int i = 1;i <= arLen;i++)
    {
        //返回值是第一个不小于bp[i]的值的地址， bp是ar的备份数组
        dest[i] = lower_bound((ar+1), (ar+1)+sz, bp[i]) - (ar + 1) + 1; 
    }
}

int main()
{
    fio;
    dctz(ar,N, bp, dest);
    for(int i = 1;i < N;i++)
        cout << dest[i] << endl;
    return 0;
}