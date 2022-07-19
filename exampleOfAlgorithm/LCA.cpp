/****LCA之eulerSequence+RMQ(st算法实现)***
 * 最近公共祖先 * 欧拉序* 区间最值 *
 * graph[N]: 给节点编号，便于寻祖，如30->10, 30->20, 30 10 20 对应图的遍历顺序为1 2 3
 * 如3->4, 4->5, 1->4, 2->4,初节点是3，二节点是4
 * 问题：n个城市（1-n），两两之间只有一条路，问两城市之间的路程
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

#define N 40010
#define ll long long
#define P pair<int, int>
#define INF 0x4f4f4f4f
#define fio ios::sync_with_stdio(false);cin.tie(NULL)

using namespace std;

vector<P> nd[N];
int el[N<<1], in[N], out[N], eLen, graph[N], dp[N<<1][30], cost[N], lg2[N<<1];

void LG2()
{
    int lg = 0;
    for(int i = 1;i <= N*2;i++)
    {
        if(1<<(lg+1) <= i) lg++;
        lg2[i] = lg;
    }
}
void dfs(int node, int father, int idx, int step)
{
    el[++eLen] = node;
    if(in[node] == -1) in[node] = eLen;
    graph[node] = idx;
    for(int i = 0;i < nd[node].size();i++)
    {
        int to = nd[node][i].first;
        if(to != father)
        {
            if( !cost[ nd[node][i].first ] )
                cost[ nd[node][i].first ] = step + nd[node][i].second;
            dfs(to, node, idx+1, step+nd[node][i].second);
            el[++eLen] = node;
        }
    }
    out[node] = eLen;
}

void st()
{
    for(int i = 1;i <= eLen;i++)
        dp[i][0] = el[i];
    for(int len = 1;(1<<len) <= eLen;len++)
    {
        for(int i = 1;i+(1<<len)-1 <= eLen;i++)
        {
            if(graph[ dp[i][len-1] ] < graph[ dp[ i + ( 1<<(len-1) ) ][len-1] ])
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

int main()
{
    fio;
    int t, n, m, a, b, step;
    cin >> t;
    for(;t--;)
    {
        cin >> n >> m;
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        memset(cost, 0, sizeof(cost));
        memset(graph, 0, sizeof(graph));
        
        for(int i = 0;i < n-1;i++)
        {
            cin >> a >> b >> step;
            nd[a].push_back(P(b,step));
            nd[b].push_back(P(a,step));
        }
        eLen = 0;
        dfs(1, 0, 1, 0);
        st();
        LG2();
        for(int i = 0; i< m;i++)
        {
            int x, y;
            cin >> x >> y;
            int l = in[x], r = in[y];
            int anc = lca(l, r);
            cout << cost[x] + cost[y] - 2 * cost[anc] << '\n';
        }
        for(int i = 0;i < n;i++) nd[i].clear();//要一直清空到节点的最大值，注意从0开始和从1开始的区别n与n+1
    }
    return 0;
}