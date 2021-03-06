#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

namespace Tree
{
	const int N=8e4*300+10;
	int cnt,ls[N],rs[N],sum[N];

	void insert(int &root,int last,int l,int r,int val)
	{
		root=++cnt;
		sum[root]=sum[last]+1;
		ls[root]=ls[last],rs[root]=rs[last];
		if(l==r) return;
		int mid=(l+r)>>1;
		if(val<=mid) insert(ls[root],ls[last],l,mid,val);
		else insert(rs[root],rs[last],mid+1,r,val);
	}

	int query(int a,int b,int c,int d,int l,int r,int k)
	{
		if(l==r) return l;
		int res=sum[ls[a]]+sum[ls[b]]-sum[ls[c]]-sum[ls[d]],mid=(l+r)>>1;
		if(k<=res) return query(ls[a],ls[b],ls[c],ls[d],l,mid,k);
		else return query(rs[a],rs[b],rs[c],rs[d],mid+1,r,k-res);
	}
}

namespace TYC
{
	const int N=8e4+10;
	int T,n,m,q,cnt,tot,size[N],val[N],tmp[N],root[N],Head[N],belong[N],dep[N],fa[N][20];

	struct edge
	{
		int to,next;
	}E[N<<2];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void add(int u,int v)
	{
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v]};
		Head[v]=cnt;
	}

	void dfs(int u,int f,int rot)
	{
		fa[u][0]=f;
		for(int i=1;i<=17;i++)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		belong[u]=rot;
		dep[u]=dep[f]+1;
		size[rot]++;
		Tree::insert(root[u],root[fa[u][0]],1,tot,val[u]);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			dfs(v,u,rot);
		}
	}

	inline int LCA(int u,int v)
	{
		if(dep[u]<dep[v]) swap(u,v);
		for(int t=0,d=dep[u]-dep[v];d;d>>=1,t++)
			if(d&1) u=fa[u][t];
		if(u==v) return u;
		for(int i=17;i>=0;i--)
			if(fa[u][i]!=fa[v][i]) 
				u=fa[u][i],v=fa[v][i];
		return fa[u][0];
	}

	void work()
	{
		int T=read();
		n=read(),m=read(),q=read();
		for(int i=1;i<=n;i++) tmp[i]=val[i]=read();
		sort(tmp+1,tmp+1+n);
		tot=unique(tmp+1,tmp+1+n)-tmp-1;
		for(int i=1;i<=n;i++) 
			val[i]=lower_bound(tmp+1,tmp+1+tot,val[i])-tmp;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v);
		}
		for(int i=1;i<=n;i++) 
			if(!belong[i]) dfs(i,0,i);
		char ch;int u,v,k,lca,ans=0;
		while(q--)
		{
			do {ch=getchar();}while(ch!='Q'&&ch!='L');
			u=read(),v=read();
			u^=ans,v^=ans;
			if(ch=='Q')
			{
				k=read();
				k^=ans;
				lca=LCA(u,v);
				ans=tmp[Tree::query(root[u],root[v],root[lca],root[fa[lca][0]],1,tot,k)];
				printf("%d\n",ans);
			}
			else 
			{
				add(u,v);
				if(size[belong[u]]<size[belong[v]]) swap(u,v);
				dfs(v,u,belong[u]);
			}
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
