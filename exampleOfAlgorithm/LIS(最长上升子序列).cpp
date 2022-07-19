#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

#define N 40010
#define ll long long
#define INF 0x4f4f4f4f

using namespace std;
//原数组ar，副本数组ar1，树状数组b， 离散化后数组大小sz
int ar[N], ar1[N], b[N]={0}, sz, n, p;

int lowBit(int x)
{
    return x&(-x);
}

void upDate(int i, int val)
{
    for(;i <= sz;i += lowBit(i))
    {
        b[i] = max(b[i], val);
    }
}

int query(int i)
{
    int maxl = 0;
    for(;i>0;i -= lowBit(i))
    {
        maxl = max(maxl, b[i]);
    }
    return maxl;
}
int lisBit()//BIT实现，树状数组存的是最长上升子序列的末元素 不大于 d[i]时，序列的最长长度。
{
    int maxL = 1, len;
    memset(b, 0, sizeof(b));
    sort(ar1+1, ar1+p+1);//数据过大时离散化
    sz = unique(ar1+1, ar1+p+1) - (ar1 + 1);
    for(int j = 1;j <= p;j++)
    {
        ar[j] = lower_bound(ar1+1, ar1+sz+1, ar[j]) - ar1;
    }
    for(int i = 1;i <= p;i++)
    {
        len = query(ar[i] - 1) + 1;
        maxL = max(maxL, len);
        upDate(ar[i], len);
    }
    return maxL;
}

int lis(int a[], int aLen)//暴力做法，每次都从1开始匹配，好处是会经过每个子序列
{               //**在数据较小时**，可让d[]储存长度为d[i]的子序列的元素和，
                //从而**简单地**求得子序列元素和的最大值(hdu1807)
    int asr = 1, d[N];//求和时，asr初始化为-INF
    
    for(int i = 1;i <= aLen;i++)
    {
        d[i] = 1;//求和时，初始化为a[i]
        for(int j = 1;j < i;j++)
        {
            if(a[j] < a[i] && (d[j] + 1) > d[i])//求和时，条件2过滤负数
            {
                d[i] = d[j] + 1;
            }
        }
        if(d[i] > asr)
        {
            asr = d[i];
        }
    }
    return asr;
}

int lisHalf(int a[], int aLen)//二分实现,下标从1起，dp[i]存的是长度为i的序列末元素的值，通过更新此值(越来越小)
{
    int asr = 1, dp[N] = {0}, l, r, mid;
    dp[1] = a[1];
    for(int i = 2;i <= aLen;i++)
    {
        l = 1;
        r = asr;
        for(;l <= r;)
        {
            mid = (l + r) >> 1;
            if(a[i] > dp[mid])
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        dp[l] = a[i];
        if(l > asr)
        {
            asr = l;
        }
    }

    return asr;
}
int main()
{
    ios::sync_with_stdio(false);
    scanf("%d", &n);
    for(;n--;)
    {
        scanf("%d", &p);
        for(int i = 1;i <= p;i++)
        {
            scanf("%d", &ar[i]);
            ar1[i] = ar[i];
        }
        //printf("%d\n", lisHalf(ar, p));
        printf("%d\n", lisBit());
    }
    return 0;
}