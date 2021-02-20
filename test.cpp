#include<bits/stdc++.h>

using namespace std;

int main()
{
    string a;
    cin>>a;
    int num[64] = {0};
    int i=a.length() - 1;
    int ss=63;
    while (i>=0)
    {
        num[ss] = a[i] - '0';
        ss --;
        i--;
    }
    
    cout<<endl;
    for(int i=0;i<64;i++)
    {
        cout<<num[i];
    }
}