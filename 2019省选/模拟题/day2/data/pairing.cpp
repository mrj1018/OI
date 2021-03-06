#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map> 
using namespace std;
const int u=200012;
struct rec{int l,r,st,ed;}t[u*4];
int a[u],b[u*20],c[u],d[u][20],h[u],s[u],sa[u],rank[u],fir[u],sec[u];
int n,m,tot,l,r,L,R,mid,i,x,y;
map<int,int> hash;

bool comp(int i,int j,int k)
{
	return sec[i]==sec[j]&&sec[i+k]==sec[j+k];
}
void sufarr(int n)
{
	int i,p,l,m=u;
	for(i=0;i<m;i++) c[i]=0;
	for(i=0;i<n;i++) c[rank[i]=a[i]]++;
	for(i=1;i<m;i++) c[i]+=c[i-1];
	for(i=n-1;i>=0;i--) sa[--c[a[i]]]=i;
	for(p=l=1;p<n;l*=2,m=p)
	{
		for(p=0,i=n-l;i<n;i++) sec[p++]=i;
		for(i=0;i<n;i++)
			if(sa[i]>=l) sec[p++]=sa[i]-l;
		for(i=0;i<n;i++) fir[i]=rank[sec[i]];
		for(i=0;i<m;i++) c[i]=0;
		for(i=0;i<n;i++) c[fir[i]]++;
		for(i=1;i<m;i++) c[i]+=c[i-1];
		for(i=n-1;i>=0;i--) sa[--c[fir[i]]]=sec[i];
		memcpy(sec,rank,sizeof(rank));
		rank[sa[0]]=0;
		for(i=p=1;i<n;i++)
			rank[sa[i]]=comp(sa[i],sa[i-1],l)?p-1:p++;
	}
}
void calh()
{
	int i,j,k=0;
	for(i=1;i<=n;i++) rank[sa[i]]=i;
	for(i=0;i<n;h[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];a[i+k]==a[j+k];k++);
}

void rmqst()
{
	int i,j;
	for(i=1;i<=n;i++) d[i][0]=h[i];
	for(i=1;i<19;i++)
		for(j=1;j<=n-(1<<i)+1;j++)
			d[j][i]=min(d[j][i-1],d[j+(1<<i-1)][i-1]);
}
int query(int l,int r)
{
	int k=log(r-l+1.0)/log(2.0);
	return min(d[l][k],d[r-(1<<k)+1][k]);
}

void merge(int l,int mid,int r)
{
	int i=l,j=mid+1,k;
	for(k=l;k<=r;k++)
		if(j>r||i<=mid&&sa[i]<sa[j]) c[k]=sa[i++]; else c[k]=sa[j++];
	for(k=l;k<=r;k++) sa[k]=c[k];
}
void build(int p,int l,int r)
{
	t[p].l=l,t[p].r=r;
	int mid=(l+r)>>1;
	if(l<r) build(p*2,l,mid),build(p*2+1,mid+1,r),merge(l,mid,r);
	t[p].st=tot+1;
	for(int i=l;i<=r;i++) b[++tot]=sa[i];
	t[p].ed=tot;
}
int ask(int p,int l,int r,int k)
{
	if(l<=t[p].l&&r>=t[p].r)
	{
		int L=t[p].st-1,R=t[p].ed,Mid;
		while(L<R)
		{
			Mid=(L+R+1)>>1;
			if(b[Mid]>k) R=Mid-1; else L=Mid;
		}
		return L-t[p].st+1;
	}
	int mid=(t[p].l+t[p].r)>>1,ans=0;
	if(l<=mid) ans+=ask(p*2,l,r,k);
	if(r>mid) ans+=ask(p*2+1,l,r,k);
	return ans;
}

int main()
{
	freopen("pairing.in","r",stdin);
	freopen("pairing.out","w",stdout);
	cin>>n;
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	for(n--,i=0;i<n;i++) a[i]=a[i+1]-a[i];
	a[n]=1e9;
	for(i=n+1;i<=2*n;i++) a[i]=-a[i-n-1];
	n=n*2+1;
	for(i=0;i<n;i++)
	{
		if(!hash[a[i]]) hash[a[i]]=++tot;
		a[i]=hash[a[i]];
	}
	tot=0;
	sufarr(n+1);
	calh();
	rmqst();
	for(i=1;i<=n;i++)
	{
		s[i]=s[i-1]+(sa[i]>n/2);
		if(sa[i]<=n/2) sa[i]=n+i;
	}
	build(1,0,n);
	cin>>m;
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		if(x==y) {printf("%d\n",n/2); continue;}
		l=1,r=rank[x-1]+1;
		while(l<r)
		{
			mid=(l+r)>>1;
			if(query(mid,rank[x-1])<y-x) l=mid+1; else r=mid;
		}
		L=l-1;
		l=rank[x-1],r=n;
		while(l<r)
		{
			mid=(l+r+1)>>1;
			if(query(rank[x-1]+1,mid)<y-x) r=mid-1; else l=mid;
		}
		R=l;
		printf("%d\n",s[R]-s[L-1]-ask(1,L,R,n/2+y)+ask(1,L,R,n/2+x-y+x-1));
	}
	return 0;
}
