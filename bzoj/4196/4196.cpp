#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000005;
int n,q,cnt,num=0,Head[MAXN];
int size[MAXN],top[MAXN],fa[MAXN],son[MAXN],dep[MAXN],dfn[MAXN];
char ch[15];

struct edge
{
	int to,next;
}E[MAXN*2];

struct node
{
	int l,r,sum,tag;
}tree[MAXN*4];

void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

void dfs1(int u)
{
	int hs=-1,mx=-1e5,v;
	size[u]=1;
	dep[u]=dep[fa[u]]+1;
	for(int i=Head[u];i;i=E[i].next)
	{
		v=E[i].to;
		if(fa[u]==v) continue;
		fa[v]=u;		
		dfs1(v);
		if(mx<size[v]) mx=size[v],hs=v;
		size[u]+=size[v];
	}
	son[u]=hs;
}

void dfs2(int u,int t)
{
	dfn[u]=++num;
	top[u]=t;
	if(son[u]!=-1) dfs2(son[u],t);
	int v;
	for(int i=Head[u];i;i=E[i].next)
	{
		v=E[i].to;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}

void build(int root,int lt,int rt)
{
	tree[root].l=lt,tree[root].r=rt;
	tree[root].tag=-1;
	if(lt==rt) return;
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid);
	build(root*2+1,mid+1,rt);
}

void pushdown(int root)
{
	int tag=tree[root].tag;
	if(tag==-1) return;
	int lt=tree[root].l,rt=tree[root].r,mid=(lt+rt)>>1;
	node &ll=tree[root*2],&rr=tree[root*2+1];
	ll.sum=(mid-lt+1)*tag;
	rr.sum=(rt-mid)*tag;
	ll.tag=tag;
	rr.tag=tag;
	tree[root].tag=-1;
}

int ask(int root,int s,int e)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e) return tree[root].sum;
	pushdown(root);
	int mid=(lt+rt)>>1;
	if(e<=mid) return ask(root*2,s,e);
	else if(s>mid) return ask(root*2+1,s,e);
	else return ask(root*2,s,mid)+ask(root*2+1,mid+1,e);
}

void change(int root,int s,int e,int val)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e) 
	{
		tree[root].sum=(rt-lt+1)*val;
		tree[root].tag=val;
		return;
	}
	pushdown(root);
	int mid=(lt+rt)>>1;
	if(e<=mid) change(root*2,s,e,val);
	else if(s>mid)change(root*2+1,s,e,val);
	else change(root*2,s,mid,val),change(root*2+1,mid+1,e,val);
	tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}

int main()
{
	freopen("4196.in","r",stdin);
	freopen("4196.out","w",stdout);
	scanf("%d",&n);
	int v;
	for(int i=1;i<n;i++) 
	{
		scanf("%d",&v);
		add(i,v),add(v,i);
	}

	dfs1(0);
	dfs2(0,0);
	build(1,1,n);

	scanf("%d",&q);
	int x,y=0,ans,t,len,yuan;
	while(q--)
	{
		ans=0;
		scanf("%s%d",ch,&x);
		if(ch[0]=='i')
		{
			yuan=x;
			while(top[x]!=top[y])
			{
				if(dep[top[x]]<dep[top[y]]) swap(x,y);
				ans+=ask(1,dfn[top[x]],dfn[x]);
				change(1,dfn[top[x]],dfn[x],1);
				x=fa[top[x]];
			}
			if(dep[x]<dep[y]) swap(x,y);
			ans+=ask(1,dfn[y],dfn[x]);
			change(1,dfn[y],dfn[x],1);
			printf("%d\n",dep[yuan]-ans);
		}
		else
		{
			ans=ask(1,dfn[x],dfn[x]+size[x]-1);
			change(1,dfn[x],dfn[x]+size[x]-1,0);
			printf("%d\n",ans);
		}
	}
	return 0;
}
