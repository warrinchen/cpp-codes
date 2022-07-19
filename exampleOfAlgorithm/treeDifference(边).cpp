/*大致题意：有n个城市(1--n)，两两之间只有一条路，给出连接两城市的道路信息，给一个某城人要去某城(多人)，问道路被走过次数(按输入时的顺序)
input：先n, 接下来n-1行，m，m行
output：路被走过的次数
example:
in
5
3 4
4 5
1 4
2 4
3
2 3
1 3
3 5
out
3 1 1 1
*/
/*树上差分，此处用vector<pair<int, int>> nd[N]记录从s->t是第几条路，用数组ptimes记录差分数组
从s->t, anc = lca(s,t),
只更新ptimes[s]++; ptimes[t]++; ptimes[anc] -= 2; （anc会被加两次）
询问结束后，dfs遍历一次即可求得路径被经过次数
*/
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#define N 100010
#define ll long long
#define P pair<int, int>
#define INF 0x4f4f4f4f
#define fio ios::sync_with_stdio(false);

using namespace std;

vector<P> nd[N];
int el[N<<1], in[N], eLen, dp[N<<1][20], lg2[N<<1], as[N], ptimes[N];
int graph[N];
void LG2()
{
    int lg = 0;
    for(int i = 1;i <= N*2;i++)
    {
        if(1<<(lg+1) <= i) lg++;
        lg2[i] = lg;
    }
}
void dfs(int node, int father, int idx)
{
    el[++eLen] = node;
    if(in[node] == -1) in[node] = eLen;
    graph[node] = idx;
    for(int i = 0;i < nd[node].size();i++)
    {
        int to = nd[node][i].first;
        if(to != father)
        {
            dfs(to, node, idx+1);
            el[++eLen] = node;
        }
    }
}
void st()
{
    for(int i = 1;i <= eLen;i++)
        dp[i][0] = el[i];
    for(int len = 1;(1<<len) <= eLen;len++)
    {
        for(int i = 1;i+(1<<len)-1 <= eLen;i++)
        {
            if(graph[dp[i][len-1]] < graph[dp[ i + ( 1<<(len-1) ) ][len-1]])
                dp[i][len] = dp[i][len-1];
            else
                dp[i][len] = dp[i + (1<<(len-1))][len-1];
        }
    }
}
int lca(int l, int r)//对应欧拉序中的位置，由in[]或out[]得
{
    if(l > r) swap(l, r);
    int k = lg2[r-l+1];
    if(graph[dp[l][k]] <graph[dp[r-(1<<k)+1][k]])
        return dp[l][k];
    else
        return dp[r-(1<<k)+1][k];
}
int dfsUpdata(int node, int father)//树上差分
{
    for(int i = 0;i < nd[node].size();i++)
    {
        int to = nd[node][i].first;
        if(to != father)
        {
            int steps = dfsUpdata(to, node);
            as[ nd[node][i].second ] += steps;
            ptimes[node] += steps;
        }
    }
    return ptimes[node];
}
/******暴力遍历
int solve(int fr, int fa, int dest)
{
    if(fr == dest){
        for(int i = 0;i < nd[fr].size();i++)
            if(nd[fr][i].first == fa)
                return nd[fr][i].second;
    }
    if(nd[fr].size() == 1 && nd[fr][0].first == fa) return -1;
    int re, fg = -1;
    for(int i = 0;i < nd[fr].size();i++){
        if(nd[fr][i].first != fa){
            re = solve(nd[fr][i].first, fr, dest);
            if(re >= 0){
                as[re]++;
                for(int i = 0;i < nd[fr].size();i++)
                    if(nd[fr][i].first == fa)
                        fg = nd[fr][i].second;
                break;
            }
        }
    }
    return fg;
}
*/
int main()
{
    fio;
    int n, m, a, b;
    for(;scanf("%d",&n) != EOF;)
    {
        memset(in, -1, sizeof(in));
        memset(as, 0, sizeof(as));
        memset(ptimes, 0, sizeof(ptimes));
        for(int i = 0;i < n-1;i++)
        {
            scanf("%d%d", &a, &b);
            nd[a].push_back(P(b, i));
            nd[b].push_back(P(a, i));
        }
        eLen = 0;
        dfs(1, 0, 0);
        st();
        LG2();
        scanf("%d", &m);
        for(int i = 0; i< m;i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if(in[x] > in[y]) swap(x, y);
            ptimes[y]++; ptimes[x]++; ptimes[ lca(in[x], in[y]) ] -= 2;
            /*********暴力遍历
            int anc = lca(in[x], in[y]);
            solve(anc, 0, x);
            solve(anc, 0, y);
            */
        }
        dfsUpdata(1, 0);//树上差分
        for(int i = 0;i < n-1;i++){
            if(i != n-2)
                printf("%d ", as[i]);
            else
                printf("%d\n", as[i]);
        }
        for(int i = 0;i <= n;i++) nd[i].clear();
    }
    return 0;
}