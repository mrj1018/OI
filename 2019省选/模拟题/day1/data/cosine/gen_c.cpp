#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T,n,m;
 
int main()
{
	freopen("cosine9.in","w",stdout);
	T=3;
	cout<<T<<endl;
	for (int t = 1; t <= T; t++)
	{
		if(t!=3) n=50000,m=50000; else 
		n=200000,m=200000;
		cout << n << ' ' << m << endl;
		for(int i=1;i<=n;i++) printf("%.3lf ",rand()*0.003*(rand()&2?1:-1));
		cout<<endl; 
		for(int i=1;i<=m;i++)
		{
			int op=rand()%2+1; 
			int l=rand()%n+1,r=rand()%n+1;
			if(l>r) swap(l,r);
			if(op==1) printf("%d %d %d %.3lf\n",op,l,r,rand()*0.003*(rand()&2?1:-1));
			else printf("%d %d %d\n",op,l,r);
		}
	}
}

