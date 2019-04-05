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
#include <ctime>
#define fir first
#define sec second
#define mp make_pair
#define pb push_back
using namespace std;
int n;

int main() {
	srand(time(0));
	freopen("snake.in","w",stdout); 
	for(int i=1;i<=5;i++)
	{
		n=i*20000;
		int t=100000000;
		cout<<n<<endl;
		int k=rand()%3;
		if(k==0)
		{
			for(int j=1;j<=n;j++)
				printf("%d %d\n",rand()*rand()%t,j*(t/n));	
		}
		else if(k==1)
		{
			for(int j=1;j<=n/2;j++)
				printf("%d %d\n",rand()*rand()%t,j);
			for(int j=n/2+1;j<=n;j++)
				printf("%d %d\n",t*10-rand()*rand()%t,n-j+1);
		}
		else{
			for(int j=1;j<n/4;j++) //x=200000000~300000000, y=100000000~1000000000
				printf("%d %d\n",2*t+rand()*rand()%t,t+j*(8*t/n)+rand()%1000);
			printf("%d %d\n",3*t,10*t);
			for(int j=n/4+1;j<n/2;j++) //x=300000000~800000000, y=900000000~1000000000
				printf("%d %d\n",3*t+(j-n/4)*(5*t/n)+rand()%1000,10*t-rand()*rand()%t);
			printf("%d %d\n",8*t,9*t);
			for(int j=n/4*3-1;j>n/2;j--) //x=800000000~900000000, y=100000000~900000000
				printf("%d %d\n",8*t+rand()*rand()%t,t+(j-n/2)*(8*t/n)+rand()%1000);
			printf("%d %d\n",8*t,t);
			for(int j=n-1;j>n/4*3;j--) //x=1~800000000, y=1~100000000
				printf("%d %d\n",(j-n/4*3)*(8*t/n)+rand()%1000,rand()*rand()%t+1);
			printf("%d %d\n",0,1);
		}
	}
	return 0;
}
