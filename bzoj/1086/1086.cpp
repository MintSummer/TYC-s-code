#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=1010;
    int n,b,cnt,tot,top,Head[N],belong[N],st[N],city[N];

    struct edge
    {
        int to,next;
    }E[N<<1];

    void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    void dfs(int u,int fa)
    {
        int in=top;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa) continue;
            dfs(v,u);
            if(top-in>=b)
            {
                city[++tot]=u;
                while(top>in) belong[st[top--]]=tot;
            }
        }
        st[++top]=u;
    }

    void work()
    {
        scanf("%d%d",&n,&b);
        int u,v;
        for(int i=1;i<n;i++) 
        {
            scanf("%d%d",&u,&v);
            add(u,v),add(v,u);
        }
        dfs(1,0);
        while(top) belong[st[top--]]=tot;
        printf("%d\n",tot);
        for(int i=1;i<=n;i++) printf("%d ",belong[i]);
        puts("");
        for(int i=1;i<=tot;i++) printf("%d ",city[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
