#include <iostream>
#include <cstring>
#include <cstdio>

#define N 100010
#define ll long long

using namespace std;

int a[N];
ll num[4 * N], lazy[4 * N];

void build(int t, int l, int r)
{
    if(l == r)
    {
        num[t] = a[l];
    }
    else
    {
        int mid  = (l + r) >> 1;
        build(t << 1, l, mid);
        build(t << 1 | 1, mid + 1, r);
        num[t] = num[t << 1] + num[t << 1 | 1];
    }
}

void pushdown(int t, int l, int r)
{
    int lt = t << 1, rt = t << 1 | 1;
    num[lt] += lazy[t] * (((l + r) >> 1) - l + 1);//更新左右区间和的值
    num[rt] += lazy[t] * (r - ((l + r) >> 1));
    lazy[lt] += lazy[t];//lazy标记下放
    lazy[rt] += lazy[t];
    lazy[t] = 0;//清除当前区间lazy标记
}

void update(int t, int l, int r, int pl, int pr, int val)//lazy标记下的区间修改
{
    if(pl <= l && r <= pr)
    {
        num[t] += (r - l + 1) * val;
        lazy[t] += val;
    }
    else
    {
        if(lazy[t] != 0)//改变的值可正可负
        {
            pushdown(t, l , r);
        }
        int mid = (l + r) >> 1;
        if(pl <= mid)
        {
            update(t << 1, l, mid, pl,pr, val);
        }
        if(pr > mid)
        {
            update(t << 1 | 1, mid + 1, r, pl, pr, val);
        }
        num[t] = num[t << 1] + num[t << 1 | 1];//此处用到字区间的信息，所以要先下lazy标记
    }
}

ll query(int t, int l, int r, int pl, int pr)//lazy标记下的区间查询
{
    if(pl <= l && r <= pr)
    {
        return num[t];
    }
    else
    {
        pushdown(t, l, r);
        int mid = (l + r) >> 1;
        ll Lasr = 0, Rasr = 0;
        if(pl <= mid)
        {
            Lasr = query(t << 1, l, mid, pl, pr);
        }
        if(pr > mid)
        {
            Rasr = query(t << 1 | 1, mid + 1, r, pl, pr);
        }
        return Lasr + Rasr;
    }
}
/*
void query(int t, int l, int r)//lazy标记下的单点查询之实现标记下放（不在此函数查询）
{
    if(l != r)
    {
        int mid = (l + r) >> 1;
        if(lazy[t] != 0)
        {
            pushdown(t);
        }
        query(t << 1, l, mid);
        query(t << 1 | 1, mid + 1, r);
    }
}
void query(int t, int l, int r)//lazy标记下的单点查询
{
    if(l == r)//核心，到达元素处
    {
        asr += lazy[t];
    }
    else
    {
        pushdown(t);
        int mid = (l + r) >> 1;
        query(t << 1, l, mid);
        query(t << 1 | 1, mid + 1, r);
    }
}
void update(int t, int l, int r, int pos, int val)//单点修改
{
    if(l == r)
    {
        num[t] += val;
    }
    else
    {
        int mid = (l+r)>>1;
        if(pos <= mid)
        {
            update(t << 1, l, mid, pos, val);
        }
        else
        {
            update(t << 1 | 1, mid + 1, r, pos, val);
        }
    }
}
*/
/*
int query(int t, int l, int r, int pos)//单点查询
{
    if(l == r)
    {
        return num[t];
    }
    else
    {
        int mid = (l + r) >> 1;
        if(pos <= mid)
        {
            return query(t << 1, l, mid, pos);
        }
        else
        {
            return query(t << 1 | 1, mid + 1, r, pos);
        }
        
    }
}
*/
/*
ll query(int t, int l, int r, int pl, int pr)//区间查询
{
    if(pl <= l && r <= pr)
    {
        return num[t];
    }
    else
    {
        int mid = (l + r)>>1;
        ll Lasr = 0, Rasr = 0;
        if(pl <= mid)
        {
            Lasr += query(t << 1, l, mid, pl, pr);
        }
        if(pr > mid)
        {
            Rasr += query(t << 1 | 1, mid + 1, r, pl, pr);
        }
        return Lasr + Rasr;
    }
}
*/
int main()
{
    int n, q, pl, pr, val;
    char s[3];

    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n;i++)
    {
        scanf("%d", &a[i]);
    }
    memset(num, 0, sizeof(num));
    memset(lazy, 0, sizeof(lazy));
    build(1, 1, n);
    for(int i = 1;i <= q;i++)
    {
        scanf("%s", s);
        if(s[0] == 'Q')
        {
            scanf("%d%d", &pl, &pr);
            printf("%lld\n", query(1, 1, n, pl, pr));
        }
        else
        {
            scanf("%d%d%d", &pl, &pr, &val);
            update(1, 1, n, pl, pr, val);
        }
    }
    return 0;
}