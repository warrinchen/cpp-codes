
/********************************************
kmp算法：字符串搜索算法。
在p字符串（短）和s字符串（长）匹配失败时，更新p字符串（p[j]）的坐标，而s[i]不变。
>>>>在此时，p、s字符串的前j个字符已经匹配。
>>>>因此，若要寻找s里出现了几次p（可部分重叠时），把p字符串（长度n）当成长度n+1的字符串匹配即可。
求next数组的思想和kmp一致，区别是：kmp是s和p字符串，而next数组的p字符串是p的前一部分。
********************************************/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int s[1000010], p[10010];
int nextidx[10010];
int m, n;
/********************************************
next数组，路标作用，获取匹配失败时下一步的位置。
应时刻牢记：nextidx[j]=k, 此值是j位以前最大重复子串的长度，代表匹配失败时，应该去的位置
********************************************/
void getNext(int *p)
{
    int i = 0;
    int k = -1;
    nextidx[0] = -1; //初始化为-1，因在kmp()[getNext()]中，i++时j(k)++,在下一个位置，s[i]还是要和p[0]验证;
    for(i = 0;i < n-1;){
        if(k == -1 || p[i] == p[k]){    //p[k]代表的是p数组，p[i]代表s数组
            i++;
            k++;
            if(p[i] != p[k])
                nextidx[i] = k;
            else
                nextidx[i] = nextidx[k]; //若p[i] == p[k], （kmp中）p[j]匹配失败时，p[nextidx[j]]也必然和s匹配失败，因此在求next数组时提前更新位置。
        }
        else
            k = nextidx[k];//i和k位的值不等，k溯回。i(3c)和d匹配失败，k(d)溯回1c位置：abc....abd..abc....abc
    }
}

int kmp()
{
    int i, j;
    i = 0;
    j = 0;
 getNext(p);
    for(;i < m && j < n;){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j = nextidx[j];
    }
    if(j == n)
        return i - j + 1;
    else
        return -1;
}

int main()
{
    int t;
    cin >> t;
    for(;t--;){
        cin >> m >> n;
        for(int i = 0;i < m;i++) 
            scanf("%d",&s[i]);
        for(int j = 0;j < n;j++)
            scanf("%d",&p[j]);
        if(m < n)
            cout << -1 << endl;
        else
            cout << kmp() << endl;
    }

    return 0;
}