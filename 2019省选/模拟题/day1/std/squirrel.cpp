#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
using namespace std;
set<int> b;
map<int,int> c;
struct rec{int x,y,z;}a[100010];
int n,m,p,d[100010];
set<pair<int,int> > f;
priority_queue<pair<int,int> > q;

bool operator <(rec a,rec b)
{
	return a.x>b.x;
}

int main()
{
	freopen("squirrel.in","r",stdin);
	freopen("squirrel.out","w",stdout); 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
		b.insert(a[i].y);
	}
	sort(a+1,a+n+1);
	for(set<int>::iterator it=b.begin();it!=b.end();it++)
		c[*it]=++p,d[p]=*it;
	int ans=a[1].x;
	f.insert(make_pair(p+1,0));
	f.insert(make_pair(0,1<<30));
	q.push(make_pair(0,0));
	for(int i=1;i<=n+1;i++)
	{
		int j=c[a[i].y];
		set<pair<int,int> >::iterator it,it2;
		while(q.size())
		{
			it=f.lower_bound(make_pair(q.top().second+1,0));
			if(-q.top().first==d[q.top().second]+it->second) break;
			q.pop();
		}
		ans=min(ans,a[i].x-q.top().first);
		if(i==n+1) break;
		it=f.lower_bound(make_pair(j,a[i].z));
		if(a[i].z<=it->second) continue;
		q.push(make_pair(-a[i].y-it->second,j));
		it--;
		while(it->second<=a[i].z)
		{
			it2=it--;
			f.erase(it2);
		}
		f.insert(make_pair(j,a[i].z));
		q.push(make_pair(-d[it->first]-a[i].z,it->first));
	}
	cout<<ans<<endl;
}
