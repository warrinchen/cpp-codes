#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MAXN 0x4f4f4f4f
#define N 10
#define SN 128

int ar[N] = {12,2,16,30,28,10,16,20,6,18};

using namespace std;

//快速排序
//待排序数组ar，左下标low，右下标high
void quickSort(int ar[], int low, int high) {
    
    if(low < high){
        //利用low这个空位置交替把大于key的放左边，小于则右边
        int i = low, j = high, key = ar[low];
        for(;i < j;){//确定key的位置并把大于key的放在右边，小于key的放在左边
            for(;i < j && ar[j] >= key;j--); //找右边第一个大于key的
            ar[i] = ar[j];

            for(;i < j && ar[i] <= key;i++); //找左边第一个小于key的
             ar[j] = ar[i];
        }
        ar[i] = key; //分界位置填入分解值
        quickSort(ar, low, i - 1); //递归排序前半部分
        quickSort(ar, i + 1, high); //递归排序后半部分
    }
}

int main()
{
    cout << "排序前：";
    for(int i: ar)
        cout << i << " ";
    cout << endl;
    quickSort(ar, 0, N - 1);
    cout << "快速排序后：";
    for(int i: ar)
        cout << i << " ";
    cout << endl;
    
    return 0;
}