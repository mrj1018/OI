#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <bitset>
#define fir first
#define sec second
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long ll;
const int N=100002;
int ver[N],Next[N],head[N],c[N],dfn[N],low[N],s[N],ins[N],du[N],a[N],b[N],deg[N];
int n,m,t,qu,tot,num,p;
vector<int> go[N];
bitset<8192> d[N];

template<typename T> inline void R(T &x) {
	char ch = getchar(); x = 0;
	for (; ch < '0'; ch = getchar());
	for (; ch >= '0'; ch = getchar()) x = x * 10 + ch - '0'; 
}

void add(int x,int y)
{
	ver[++tot]=y,Next[tot]=head[x],head[x]=tot;
}

void tarjan(int x)
{
	dfn[x]=low[x]=++num;
	s[++p]=x,ins[x]=1;
	for(int i=head[x];i;i=Next[i])
	{
		int y=ver[i];
		if(!dfn[y])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(ins[y])
			low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x])
	{
		t++; int y;
		do{y=s[p--]; ins[y]=0; c[y]=t;}while(x!=y);
	}
}

bool topsort(int l,int r)
{
	//cout<<l<<' '<<r<<endl;
	queue<int> q;	
	for(int i=1;i<=t;i++)
	{
		deg[i]=du[i];
		d[i].reset();
	}
	for(int i=1;i<=t;i++)
		if(!deg[i]) q.push(i);
	while(q.size())
	{
		int x=q.front(); q.pop();
		if(x>=l&&x<=r) d[x][x-l]=1;
		for(int i=0;i<go[x].size();i++)
		{
			int y=go[x][i];
			d[y]|=d[x];
			if(--deg[y]==0) q.push(y);
		}
	}
	for(int i=1;i<=qu;i++)
		if(b[i]>=l&&b[i]<=r&&d[a[i]][b[i]-l]==1)
			return 0;
	return 1;
}

int main() {
	freopen("gplt.in","r",stdin);
	freopen("gplt.out","w",stdout);
	while(cin>>n>>m)
	{
		memset(head,0,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(c,0,sizeof(c));
		memset(du,0,sizeof(du));
		tot=num=p=t=0;
		for(int i=1;i<=n;i++) go[i].clear();
		for(int i=1;i<=m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);
		}
		for(int i=1;i<=n;i++)
			if(!dfn[i]) tarjan(i);
		for(int x=1;x<=n;x++)
			for(int i=head[x];i;i=Next[i])
			{
				int y=ver[i];
				if(c[x]==c[y]) continue;
				go[c[y]].push_back(c[x]);
				du[c[x]]++;
			}
		cin>>qu;
		for(int i=1;i<=qu;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			a[i]=c[x],b[i]=c[y];
		}
		bool flag=0;
		for(int l=1;l<=t;l+=8192)
		{
			int r=min(t,l+8191);
			if(!topsort(l,r)) {flag=1; break;}
		}
		if(flag) {puts("NO"); continue;}
		puts("YES");
		cout<<m<<endl;
		for(int x=1;x<=n;x++)
			for(int i=head[x];i;i=Next[i])
			{
				int y=ver[i];
				printf("%d %d\n",x,y);
			}
	}
	return 0;
}
