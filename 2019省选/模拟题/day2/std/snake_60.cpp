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
#define fir first
#define sec second
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long ll;

struct vec{
	int x,y;
	vec(int _x=0,int _y=0):x(_x),y(_y){}
	inline vec operator -(const vec &a)const{
		return vec(x-a.x,y-a.y);
	}
	inline long long cross(const vec &a)const{
		return 1LL*x*a.y-1LL*y*a.x;
	}
}p[1010],stack[1010];

bool cmp (const vec &a,const vec &b){
	if(a.y!=b.y) return a.y<b.y;
	return a.x<b.x;
}

void solve(vector<vec> &v){
	int top=0;
	if(v.size()<=2) return;
	sort(v.begin(),v.end(),cmp);
	for(int i=0;i<v.size();i++){
		while(top>1&&(stack[top]-stack[top-1]).cross(v[i]-stack[top])<=0) top--;
		stack[++top]=v[i];
	}
	int res=top;
	for(int i=v.size()-1;i>=0;i--){
		while(top-res>0&&(stack[top]-stack[top-1]).cross(v[i]-stack[top])<=0) top--;
		stack[++top]=v[i];
	}
	v.clear();
	for(int i=1;i<top;i++)
		v.push_back(stack[i]);
}

bool in(vec p,vector<vec> &V){
	int sz=V.size();
	if(V.size()<=2) return false; 
	for(int i=0;i<sz-1;i++)
		if((V[i+1]-V[i]).cross(p-V[i])<=0) return false;
	if((V[0]-V[sz-1]).cross(p-V[sz-1])<=0) return false;
	return true;
}

int n;

bool check(int x){
	vector<vec>v;
	v.clear();
	for(int i=1;i<=x;i++)
		v.push_back(p[i]);
	solve(v);
	if(in(p[x],v)||in(p[x+1],v)) return false;
	v.clear();
	for(int i=x+1;i<=n;i++)
		v.push_back(p[i]);
	solve(v);
	if(in(p[x],v)||in(p[x+1],v)) return false;
	v.clear();
	return true;
}

int main() {
	freopen("snake.in","r",stdin);
	freopen("snake.out","w",stdout);
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++){
			scanf("%d%d",&p[i].x,&p[i].y);
		}
		bool ans=1;
		for(int i=1;i<n;i++){
			if(!check(i)){
				puts("Impossible");
				ans=0;
				break;
			}
		}
		if(ans) puts("Possible");
	}
	return 0;
}
