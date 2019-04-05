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
int ver[N],Next[N],head[N],c[N],dfn[N],low[N],s[N],ins[N],du[N],a[N],b[N],deg[N],A[N],B[N];
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
	for(int i=1;i<=m;i++)
		if(c[B[i]]>=l&&c[B[i]]<=r&&d[c[A[i]]][c[B[i]]-l]==0)
			return 0;
	for(int i=1;i<=qu;i++)
		if(c[b[i]]>=l&&c[b[i]]<=r&&d[c[a[i]]][c[b[i]]-l]==1)
			return 0;
	return 1;
}

FILE *fin, *fout;

int main(int argc, char* argv[])
{
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "r");
	while(fscanf(fin,"%d%d",&n,&m)!=EOF)
	{
		memset(head,0,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(c,0,sizeof(c));
		memset(du,0,sizeof(du));
		for(int i=1;i<=n;i++) go[i].clear();
		tot=num=p=t=0;
		for(int i=1;i<=m;i++)
		{
			int x,y;
			fscanf(fin,"%d%d",&x,&y);
			add(x,y);
			A[i]=x,B[i]=y;
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
		//for(int i=1;i<=m;i++) A[i]=c[A[i]],B[i]=c[B[i]];
		fscanf(fin,"%d",&qu);
		for(int i=1;i<=qu;i++)
		{
			int x,y;
			fscanf(fin,"%d%d",&x,&y);
			a[i]=x,b[i]=y;
		}
		bool flag=0;
		for(int l=1;l<=t;l+=8192)
		{
			int r=min(t,l+8191);
			if(!topsort(l,r)) {flag=1; break;}
		}
		char out[23];
		fscanf(fout,"%s",out);
		if(flag)
		{
			fprintf(stderr,"NO\n");
			if(strcmp(out,"NO"))
			{
				freopen(argv[5], "w", stdout);
				printf("0\n");
				fclose(stdout);
				exit(0);
			}
			continue;
		}
		fprintf(stderr,"YES\n");
		if(strcmp(out,"YES"))
		{
			freopen(argv[5], "w", stdout);
			printf("0\n");
			fclose(stdout);
			exit(0);
		}
		memset(head,0,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(c,0,sizeof(c));
		memset(du,0,sizeof(du));
		for(int i=1;i<=n;i++) go[i].clear();
		tot=num=p=t=0;
		int mo;
		fscanf(fout,"%d",&mo);
		fprintf(stderr,"%d\n",mo);
		if(mo>n+m+qu)
		{
			freopen(argv[5], "w", stdout);
			printf("0\n");
			fclose(stdout);
			exit(0);
		}
		for(int i=1;i<=mo;i++)
		{
			int x,y;
			fscanf(fout,"%d%d",&x,&y);
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
		flag=0;
		for(int l=1;l<=t;l+=8192)
		{
			int r=min(t,l+8191);
			if(!topsort(l,r)) {flag=1; break;}
		}
		if(flag)
		{
			freopen(argv[5], "w", stdout);
			printf("0\n");
			fclose(stdout);
			exit(0);
		}
	}
	freopen(argv[5], "w", stdout);
	printf("10\n");
	fclose(stdout);
	return 0;
}
