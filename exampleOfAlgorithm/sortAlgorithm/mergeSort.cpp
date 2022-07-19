#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MAXN 0x4f4f4f4f
#define N 10
#define SN 128

int ar1[N] = {12,2,16,30,28,10,16,20,6,18};

using namespace std;

//归并排序
//待排序数组ar，临时存储数组tmp，排序区间左下标left，右下标right
void mergeSort(int ar[], int tmp[], int left, int right){
    if(left == right) return ;

    int mid = (left + right) >> 1;
    int left1 = left, right1 = mid,
        left2 = mid + 1, right2 = right;

    mergeSort(ar, tmp, left1, right1); //递归排序左区间
    mergeSort(ar, tmp, left2, right2); //递归排序右区间

    //归并两个区间
    int i = left;
    for(;left1 <= right1 && left2 <= right2;)
        tmp[i++] = ar[left1] < ar[left2] 
        ? ar[left1++] : ar[left2++];
    for(;left1 <= right1;tmp[i++] = ar[left1++]) ;
    for(;left2 <= right2;tmp[i++] = ar[left2++]) ;
    //把排好序的区间从临时数组转移到待排序数组
    for(i = left;i <= right;i++) ar[i] = tmp[i];
    for(int i = 0; i < 10; i++) cout << ar[i] << " ";
    cout << endl;
}

int main()
{
    cout << "排序前：";
    for(int i: ar1)
        cout << i << " ";
    cout << endl;
    int tmp[N];
    mergeSort(ar1, tmp, 0, N - 1);
    cout << "归并排序后：";
    for(int i: ar1)
        cout << i << " ";
    cout << endl;

    return 0;
}