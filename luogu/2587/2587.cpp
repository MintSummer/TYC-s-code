#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,A[MAXN],B[MAXN];

int getmx(int a[],int b[])
{
    int la=1,lb=1,ra=n,rb=n,mx=0;
    while(la<=ra&&lb<=rb)
    {
	if(a[la]>b[lb]) mx+=2,la++,lb++;
	else if(a[ra]>b[rb]) mx+=2,ra--,rb--;
	else mx+=(a[la]==b[rb]),la++,rb--;
    }
	return mx;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&A[i]);
    for(int i=1;i<=n;i++) scanf("%d",&B[i]);
    sort(A+1,A+1+n);
    sort(B+1,B+1+n);
    printf("%d %d",getmx(A,B),2*n-getmx(B,A));
    return 0;
}
