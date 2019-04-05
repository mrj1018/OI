#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int n,m,a[100010];
int main()
{
	freopen("pairing.in","w",stdout);
	srand((unsigned)time(0));
	cin>>n>>m;
	cout<<n<<endl;
	int t=100;
	for(int i=0;i<t;i++)
	{
		int s=rand()%t+t+1;
		for(int j=n/t*i+1;j<=n/t*(i+1);j++)
			if(i==0) printf("%d ",a[j%t]=rand()%t+1);
			else if(i&1) printf("%d ",s-a[j%t]);
			else printf("%d ",a[j%t]);
	}
	puts("");
	cout<<m<<endl;
	t=10;
	while(m--)
	{
		int l=rand()*rand()%(n-t)+1,r=rand()*rand()%t;
		if(m>50000)
		{
			l=rand()*rand()%n+1,r=rand()*rand()%n+1;
			if(l>r) swap(l,r);
			printf("%d %d\n",l,r);
			continue;
		}
		printf("%d %d\n",l,l+r);
	}
}
