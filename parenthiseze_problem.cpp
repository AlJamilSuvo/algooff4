#include<bits/stdc++.h>
using namespace std;
#define MAX 10000
int check[55][55];
map<int,int>dp[55][55];
int a[MAX];
char s[MAX];
#define ff first
int n;

void f(int l,int r)
{
    if(l>r)return;
    if(l==r){
        dp[l][r][a[l]]=1;
        return;
    }
    if(check[l][r]!=-1)return;

    if(l+1==r){
        int ans=0;
        if(s[l]=='+')ans=a[l]+a[r];
        else ans=a[l]*a[r];
        dp[l][r][ans]=1;
        return;
    }

    for(int i=l;i<r;i++){
        if(s[i]=='+'){
            f(l,i);
            f(i+1,r);
            for(const auto j:dp[l][i]){
                for(const auto k: dp[i+1][r]){
                   dp[l][r][j.ff+k.ff]=1;

                }
            }
        }
        else{

            f(l,i);
            f(i+1,r);

            for(const auto j:dp[l][i]){
                for(const auto k: dp[i+1][r]){
                    dp[l][r][j.ff*k.ff]=1;
                }
            }
        }

    }
    check[l][r]=1;
    return;
}



int main()
{
    int k;
    cin>>n;
    int cnt1=0,cnt2=0;

    for(int i=0;i<2*n-1;i++){
        if(i%2){
            cin>>s[i-cnt1];
            cnt2++;
        }
        else {
           cin>>a[i-cnt2];
           cnt1++;
        }
    }
    for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)check[i][j]=-1;
    f(0,n-1);

    while(1){
        cin>>k;
        if(!dp[0][n-1][k])cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }

}
