#include <cstdio>
#include <iostream>

using namespace std;

/*void fastPower() //快速幂取模
 {
     int a, b, c, ans = 1; //a的b次幂，c为模
     a = 2;
     b = 6;
     c = 3;
     a %= c;
     for(;b != 0;){
        if(b%2 == 1) ans = (ans*a)%c;
        b /= 2;
        a = (a*a)%c;
     }
     cout << ans;
 }
*/
//使用更快的位运算，再优化
void fastPower()
{
    int a, b, c, ans = 1; //a的b次幂，c为模
    a = 2;
    b = 6;
    c = 5;
    a %= c;
    for(;b != 0;){
        if(b&1 == 1) ans = (ans*a)%c;//位运算，取b的二进制形式最左边一位
        b >>= 1;//b的二进制向右移一位 110 -> 11
        a = (a*a)%c;
    }
    cout << ans;
}
