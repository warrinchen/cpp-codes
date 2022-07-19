#include <iostream>
#include <cstdio>
#include <ctime>

#define LOCAL

using namespace std;

int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);//在函数入口处加入这两句，txt和cpp文件在同一文件夹
    freopen("output.txt", "w", stdout);
#endif
    int a;
    for(;scanf("%d", &a) != EOF;)
        printf("%d\n", a);
    return 0;
}