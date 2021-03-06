//吐槽……和bzoj2375一毛一样好不好……
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000011;
int n,m,p,q,fa[MAXN],ans[MAXN];
//并查集fa[i]=j 表示自i往后第一个没有染颜色的是j

inline int find(int x) 
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    scanf("%d%d%d%d",&n,&m,&p,&q);
    for(int i=1;i<=n+1;i++) fa[i]=i;
    //注意有可能跑到第n + 1个点，于是也要给这个点赋个father

    int l,r;
    for(int i=m;i;i--)
    {
	l=(i*p+q)%n+1,r=(i*q+p)%n+1;
	if(l>r) swap(l,r);
	for(int x=find(l);x<=r;x=find(x))
	    ans[x]=i,fa[x]=x+1;
    }

    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    return 0;
}
