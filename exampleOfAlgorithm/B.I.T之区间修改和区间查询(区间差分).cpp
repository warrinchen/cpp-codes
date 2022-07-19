#include <cstdio>
#define N 100010
#define ll long long
/*************************************
下标从1起.
数组sum1[i] == a数组a[i]与a[i-1]的差值 由树状数组d维护
数组sum2[i] == sum1[i](i-1) 由树状数组d2维护
k=i.
a[i]=d[1--i]求和
维护d数组即可实现区间修改，单个查询(修改update函数和getsum函数)

由d数组求a[i], 递推可得
a[1--i]求和 = k*sum1[1--i] - d[1--i]*(i-1)
再维护d2数组就可区间修改，区间查询
*************************************/
ll a[N], d[N],d2[N];
int n;
int lowBit(int i){
    return i&(-i);
}
void updata(int i, ll k){//k即差值
    for(int j=i;j<=n;){
        d[j] += k;
        d2[j] += k*(i-1);
        j += lowBit(j);
    }
}
ll getsum(int i){
    ll sum=0;
    for(int j=i;j>0;){
        sum += i*d[j] - d2[j];
        j -= lowBit(j);
    }
    return sum;
}
int main()
{
    int l,r,x,i,q;
    int j;
    char op[3];
    scanf("%d%d",&n,&q);
    for(j=1;j<=n;j++){
        scanf("%lld",&a[j]);
        updata(j,a[j]-a[j-1]);
    }
    for(j=0;j<q;j++){
        getchar();
        scanf("%s",op);
        if(op[0] == 'C'){
            scanf("%d%d%d",&l,&r,&x);
            updata(l,x);
            updata(r+1,-x);
        }
        else{
            scanf("%d%d",&l,&r);
            printf("%lld\n",getsum(r)-getsum(l-1));
        }
    }
    return 0;
}
