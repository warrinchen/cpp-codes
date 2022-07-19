#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int i;
    printf("\n%lf\n",(double)clock() / CLOCKS_PER_SEC);//程序运行到此处时使用的时间，CLOCKS_PER_SEC在win中为1000
    return 0;
}