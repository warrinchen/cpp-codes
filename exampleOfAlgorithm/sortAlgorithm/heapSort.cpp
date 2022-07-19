#include <stdio.h>
#include <iostream>

#define N 11

using namespace std;

int ar[N] = {0,12,2,16,30,28,10,16,20,6,18};

void adjust(int ar[], int i, int n){
    int j = 2 * i, tmp = ar[i];

    for(;j <= n;j = j << 1) {
        if(j < n && ar[j] < ar[j + 1]) j++; //选择两个子中较大的
        if(tmp >= ar[j]) break; //已是堆，无需调整
        ar[j / 2] = ar[j];
    }
    ar[j >> 1] = tmp;
}

void heapSort(int ar[], int n) {
    int i, tmp;
    
    for(int i = n >> 1; i >= 1;i--) adjust(ar, i, n);
    for(int i = n - 1;i >= 1;i--)  {
        tmp = ar[i + 1];
        ar[i + 1] = ar[1];
        ar[1] = tmp;
        for(int i = 1; i < 11; i++) cout << ar[i] << " ";
        cout << endl;
        adjust(ar, 1, i);
        
    }
}

int main(){
    heapSort(ar, 10);
    cout << endl;
    for(int i : ar) cout << i << " ";
    return 0;
}