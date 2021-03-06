//Hungary

#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000010;
int n,cnt=0,tim,fa[MAXN],Head[MAXN],vis[MAXN];
struct edge
{
    int to,next;
}E[MAXN*4];

void add(int x,int y)
{
    cnt++;
    E[cnt].to=y;
    E[cnt].next=Head[x];
    Head[x]=cnt;
}

bool Path(int u)
{
    int v;
    for(int i=Head[u];i;i=E[i].next)
      {
      	v=E[i].to;
      	if(vis[v]==tim) continue;
      	vis[v]=tim;
        if(!fa[v]||Path(fa[v]))
          {
          	fa[v]=u;
          	return true;
          }
      }
    return false;
}

int Hungary(int mx)
{
    int ans=0;
    for(int i=1;i<=mx;i++)
      {
      	tim++;
      	if(Path(i)) ans++;
        else break;
      }
    return ans;
}

int main()
{
    scanf("%d",&n);
    int a,b,mx=0,mn=0x3f3f3f3f;
    for(int i=1;i<=n;i++)
      {
        scanf("%d%d",&a,&b);
      	add(a,i);
      	add(b,i);
      	mx=max(mx,max(a,b));
      	mn=min(mn,min(a,b));
      }
    if(mn>1)
      {
      	printf("0");
      	return 0;
      }
    printf("%d",Hungary(mx));
    return 0;
} 
