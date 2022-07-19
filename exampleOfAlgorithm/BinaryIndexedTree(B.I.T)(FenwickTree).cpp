/***********树状数组***********问题input描述********************
第一行一个整数T，表示有T组数据。
每组数据第一行一个正整数N（N<=50000）,表示敌人有N个工兵营地，
接下来有N个正整数,第i个正整数a[i]代表第i个工兵营地里开始时有a[i]个人（1<=ai<=50）。
接下来每行有一条命令，命令有4种形式：
(1) Add i j,i和j为正整数,表示第i个营地增加j个人（j不超过30）
(2)Sub i j ,i和j为正整数,表示第i个营地减少j个人（j不超过30）;
(3)Query i j ,i和j为正整数,i<=j，表示询问第i到第j个营地的总人数;
(4)End 表示结束，这条命令在每组数据最后出现;
每组数据最多有40000条命令。

output描述
对第i组数据,首先输出“Case i:”和回车,
对于每个Query询问，输出一个整数并回车,表示询问的段中的总人数,这个数保持在int以内。
*************************************************************/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>

#define N 50010
#define ll long long
#define fio ios::sync_with_stdio(false)

int ar[N] = {0}, c[N] = {0}, n;

using namespace std;
/*************************************************************数组下标从1开始
C[1] = A[1];
C[2] = A[1] + A[2];
C[3] = A[3];
C[4] = A[1] + A[2] + A[3] + A[4];
C[5] = A[5];
C[6] = A[5] + A[6];
C[7] = A[7];
C[8] = A[1] + A[2] + A[3] + A[4] + A[5] + A[6] + A[7] + A[8];
（画图表示c数组更易理解下列叙述）
函数功能：求使i的二进制形式多一个0（在树上移动一节点）所需的10进制的值，加上则左移。
即求2^k，k是i在二进制形式下，从最低位到最高位连续0的个数。10  1010  k=1
如：7，111   7&(-7)=1,  =>1000，110
加，上移遇包含自己的最近的节点（对于辅助数组c)，反之将下移遇到的节点（包括自己）相加，得前i项和
sum[7] = c[7]+c[6]+c[4] 111为7，110为6，100为4
*************************************************************/
int lowBit(int i){
    return i&(-i);
}

void upData(int i, int a){//维护辅助数组
    for(;i <= n;){
        c[i] += a;
        i += lowBit(i);
    }
}

int getSum(int i){//求前i项和
    int sum = 0;
    for(;i > 0;){
        sum += c[i];
        i -= lowBit(i);
    }
    return sum;
}

int main()
{
    int t, x, y, idx;
    char str[6];

    scanf("%d",&t);

    for(idx = 1;idx <= t;idx++){
        scanf("%d", &n);
        for(int i = 1;i <= n;i++){//初始化辅助数组（为了不影响第1次以后的case
            c[i] = 0;
        }
        for(int i = 1;i <= n;i++){
            scanf("%d",&ar[i]);
            upData(i, ar[i]);
        }
        scanf("%s",str);
        cout << "Case " << idx << ":" << endl;
        for(;strcmp(str, "End") != 0;){
            scanf("%d%d", &x, &y);
            if(strcmp(str, "Query") == 0){
                cout << getSum(y) - getSum(x) + ar[x] << endl;
            }
            else if(strcmp(str, "Add") == 0){
                ar[x] += y;//维护原数组
                upData(x, y);
            }
            else{
                ar[x] -= y;//维护原数组
                upData(x, -y);
            }
            scanf("%s",str);
        }
    }
    return 0;
}
