#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int bin[35];

namespace Tree
{
	const int N=12000*32+10;
	int cnt,son[N][2],val[N];

	void insert(int &root,int last,int x)
	{
		root=++cnt;
		int tmp=root;
		for(int i=30;i>=0;i--)
		{
			son[root][0]=son[last][0];
			son[root][1]=son[last][1];
			val[root]=val[last]+1;
			int t=(x&bin[i])>>i;
			son[root][t]=++cnt;
			root=son[root][t];
			last=son[last][t];
		}
		val[root]=val[last]+1;
		root=tmp;
	}

	int query(int l,int r,int x)
	{
		int ans=0;
		for(int i=30;i>=0;i--)
		{
			int t=(x&bin[i])>>i;
			if(val[son[r][t^1]]>val[son[l][t^1]])
				ans|=bin[i],r=son[r][t^1],l=son[l][t^1];
			else r=son[r][t],l=son[l][t];
		}
		return ans;
	}
}

namespace TYC
{
	typedef long long ll;
	const int N=12010;
	int n,m,block,tot,xorsum[N],root[N],f[112][N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void work()
	{
		n=read(),m=read();
		block=sqrt(n);
		tot=n/block+(n%block!=0);
		bin[0]=1;
		for(int i=1;i<=30;i++) bin[i]=bin[i-1]<<1;
		for(int i=1;i<=n;i++) 
		{
			xorsum[i]=xorsum[i-1]^read();
			Tree::insert(root[i],root[i-1],xorsum[i]);
		}
		for(int i=1;i<=tot;i++)
			for(int j=(i-1)*block+1;j<=n;j++)
			{
				f[i][j]=max(f[i][j-1],Tree::query(root[(i-1)*block],root[j],xorsum[j]));
				if(i==1) f[i][j]=max(f[i][j],xorsum[j]);
			}
		int ans=0;
		while(m--)
		{
			int l=read(),r=read();
			l=(l+ans%n)%n+1;
			r=(r+ans%n)%n+1;
			if(l>r) swap(l,r);
			l--;
			int belong=l/block+(l%block!=0),nxt=belong*block+1;
			ans=0;
			if(nxt<=r) ans=f[belong+1][r];
			nxt=min(nxt,r);
			for(int i=l;i<nxt;i++)
				ans=max(ans,Tree::query(root[l],root[r],xorsum[i]));
			printf("%d\n",ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
