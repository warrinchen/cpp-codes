#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
//#include <bits/stdc++.h>
#define LOCAL
typedef long long ll;
typedef unsigned long long ull;
#define INF 0x7f7f7f7f
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0) //此时 cin,cout和scanf,printf不能混用!!!
// 线段树, 以区间最大值为例
const int N = 1 + 5;
int a[N+1] = {0,1,8,6,4,3,5}, tree[N << 2], lazy[N << 2];

using namespace std;

//建树-递归方式
void push_up(int k) { // 更新父节点的最大值
    tree[k] = max(tree[k << 1], tree[k << 1 | 1]);
}
void build(int k, int L, int R) {// 递归建树, k 当前区间所属的线段树    节点, L左边界, R右边界
    if (L == R) {// 左右边界相同, 说明k是叶结点
        tree[k] = a[L];
    } else {
        int m = L + ((R - L) >> 1);
        build(k << 1, L, m); // 构造左子树
        build(k << 1 | 1, m + 1, R); // 构造右子树
        push_up(k); // 更新父节点
    }
}

//基本操作
//单点更新-递归方式
void node_update(int nd, int val, int L, int R, int k) { // nd要更新的数组节点, val变化量, L当前区间左边界, R右边界, k区间所属的线段树节点
    if (L == R) {
        a[L] += val;
        tree[k] += val;
    }else {
        int m = L + ((R - L) >> 1);
        if (nd <= m)
            node_update(nd, val, L, m, k << 1);
        else
            node_update(nd, val, m + 1, R, k << 1 | 1);
        push_up(k);
    }
}
//区间查询-递归方式(思路同单点更新)
int node_query(int qL, int qR, int L, int R, int k) { // qL待查询区间左边界, qR待查询区间右边界, L当前区间左边界,R当前区间右边界, k当前区间所属的线段树节点
    if (qL <= L && R <= qR)
        return tree[k];
    else {
        int res = -INF;
        int m = L + ((R - L) >> 1);
        if (qL <= m)
            res = max(res, node_query(qL, qR, L, m, k << 1));
        if (qR > m)
            res = max(res, node_query(qL, qR, m + 1, R, k << 1 | 1));
        return res;
    }
}
//区间更新-递归方式(需要新增一个和tree一样大的lazy数组, 需要修改query和update函数并引入lazy标记处理函数)
void push_down(int k) {// 下放线段树k节点的lazy标记到子节点
    if (lazy[k] != 0) { // 如果当前线段树区间有lazy标记
        lazy[k << 1] += lazy[k];    //lazy下放到左子树
        lazy[k << 1 | 1] += lazy[k];//lazy下放到右子树
        tree[k << 1] += lazy[k];      // 由于是求区间最大值, 线段树左区间最值加上变化量
        tree[k << 1 | 1] += lazy[k];  // 由于是求区间最大值, 线段树右区间最值加上变化量
        lazy[k] = 0; //清除当前线段树节点lazy标记
    }
}
// 引入lazy标记, 只更新待更新区间的最大真子区间代表的节点, 其余延后
void range_update(int uL, int uR, int val, int L, int R, int k) { // uL待更新a数组左区间边界, uR待更新a数组右区间边界, val变化量, L当前区间左边界, R右边界, k区间所属的线段树节点
    if (uL <= L && R <= uR) {
        tree[k] = val; // 当前节点更新
        lazy[k] += val; // 子节点延迟更新
    }
    else {
        push_down(k); //下放线段树节点lazy标记, 如果之前的更新产生了lazy标记,保证子区间是最新状态
        int m = L + ((R - L) >> 1);
        if (uL <= m)
            range_update(uL, uR, val, L, m, k << 1);
        if(uR > m)
            range_update(uL, uR, val, m + 1, R, k << 1 | 1);
        push_up(k); // 更新父节点
    }
}
int range_query(int qL, int qR, int L, int R, int k) {
    if (qL <= L && qR <= R)
        return tree[k];
    else {
        push_down(k); // 查询子区间前, 先下放lazy标记(如果有), 保证子区间是最新状态
        int res = -INF;
        int m = L + ((R - L) >> 1);
        if (qL <= m)
            res = max(res, node_query(qL, qR, L, m, k << 1));
        if (qR > m)
            res = max(res, node_query(qL, qR, m + 1, R, k << 1 | 1));
        return res;
    }
}

void trav(int ar[], string name, int st, int ed) {
    cout << name << " array:" << endl;
    for (int i = st; i <= ed; ++i)
        cout << i << ":" << ar[i] << "  ";
    cout << endl;
}

int main() {
    // 第一行为输入，第二行为输出
    //文件重定向可方便调试程序
    #ifdef LOCAL
    freopen("main_in.txt", "r", stdin);
    freopen("main_out.txt", "w", stdout);
    #endif
    #ifdef LOCAL
    time_t start = clock();
    #endif

    // answer code here
    build(1, 1, 6);
    node_update(3, 13, 1, 6, 1);
    cout << "query [2,5] : " << node_query(2, 5, 1, 6, 1) << endl;
    trav(a, "a", 0, N - 1);
    trav(tree, "tree", 0, (N << 2) - 1);

    #ifdef LOCAL
    time_t end = clock();
    #endif 
    #ifdef LOCAL
    cout << endl <<"use time(ms): " << (end - start) << endl;
    #endif
    return 0;
}
/*
三\线段树的基本操作
1.点更新
a[k] += v,t[k] += v;应该改为a[l] += v,t[k] += v;
因为k是线段树的节点id, 而l==r时,l才是a数组的id, 此时l==r==p


*/