#include<bits/stdc++.h>
using namespace std;
int n,ans=0,a[40010],tmp[40010];

void HEBING(int lt,int rt)
{
	int mid=(lt+rt)>>1;
	int k=lt,i=lt,j=mid+1;
	while(i<=mid&&j<=rt)
	{
		if(a[i]>a[j])
		{
			tmp[k++]=a[j];
			j++;
			ans+=mid-i+1;
		}
		else
		{
			tmp[k++]=a[i];
			i++;
		}
	}
	while(i<=mid) tmp[k++]=a[i],i++;
	while(j<=rt) tmp[k++]=a[j],j++;
	for(i=lt;i<=rt;i++) a[i]=tmp[i];
}

void SORT(int l,int r)
{
	if(l<r)
	{
		int mid=(l+r)>>1;
		SORT(l,mid);
		SORT(mid+1,r);
		HEBING(l,r);
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	SORT(1,n);
	printf("%d",ans);
	return 0;
}
