#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=310;
	int n,s,cnt,ans=0x3f3f3f3f,start,end,Head[N],dis[N],fa[N],len[N],vis[N];

	struct edge
	{
		int to,next,w;
	}E[N<<1];

	void add(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}

	void dfs1(int u)
	{
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u]) continue;
			fa[v]=u;
			dis[v]=dis[u]+E[i].w;
			dfs1(v);
		}
	}

	void dfs2(int u,int f)
	{
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]||v==f) continue;
			len[v]=len[u]+E[i].w;
			dfs2(v,u);
		}
	}

	void work()
	{
		scanf("%d%d",&n,&s);
		int u,v,w;
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%d",&u,&v,&w);
			add(u,v,w),add(v,u,w);
		}
		dfs1(1);
		for(int i=1;i<=n;i++) 
			if(dis[i]>dis[start]) start=i;
		dis[start]=0,fa[start]=0;
		dfs1(start);
		for(int i=1;i<=n;i++)
			if(dis[i]>dis[end]) end=i;
		for(int u=end;u;u=fa[u])//爬直径
		{
			int v=u;
			while(fa[v]&&dis[u]-dis[fa[v]]<=s) v=fa[v];
			int mx=0;
			memset(vis,0,sizeof(vis));
			for(int i=u;i!=fa[v];i=fa[i]) vis[i]=1;
			for(int i=u;i!=fa[v];i=fa[i])
			{
				len[i]=0;
				dfs2(i,0);
			}
			for(int i=1;i<=n;i++) mx=max(mx,len[i]);
			ans=min(mx,ans);
		}
		printf("%d",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
