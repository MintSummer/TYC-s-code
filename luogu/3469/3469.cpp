#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN=100010;
int n,m,cnt=0,Head[MAXN],dfs=0;
int vis[MAXN],dfn[MAXN],low[MAXN],st[MAXN],top=0,size[MAXN];
LL ans[MAXN];

struct edge
{
	int to,next;
}E[500010*2];

void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

void Tarjan(int x)
{
	int t,z=0;
	size[x]=1;
	st[++top]=x;
	dfn[x]=low[x]=++dfs;
	for(int i=Head[x];i;i=E[i].next)
	{
		t=E[i].to;
		if(dfn[t]) low[x]=min(low[x],dfn[t]);
		else
		{
			Tarjan(t);
			size[x]+=size[t];
			low[x]=min(low[x],low[t]);
			if(dfn[x]<=low[t])
			{
				ans[x]+=(LL)z*size[t];
				z+=size[t];
			}
		}
	}
	ans[x]+=(LL)z*(n-z-1);
}

int main()
{
	scanf("%d%d",&n,&m);
	int a,b;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}	
	Tarjan(1);
	for(int i=1;i<=n;i++)
		printf("%lld\n",(ans[i]+n-1)*2);
	return 0;
}
