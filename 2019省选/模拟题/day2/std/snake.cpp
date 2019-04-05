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
struct poi { long double x, y; };
poi a[100010];
set<pair<long double, int> > f;
int n;
long double eps = 1e-10;

long double mul(poi a, poi b, poi c)
{
	return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

void insert(poi ct, int i)
{
	set<pair<long double, int> >::iterator it, l, r;
	long double z = atan2(a[i].y - ct.y, a[i].x - ct.x);
	l = r = f.lower_bound(make_pair(z, i));
	if (r == f.end()) r = f.begin();
	if (l == f.begin()) l = --f.end(); else l--;
	if (mul(a[i], a[l->second], a[r->second]) < -eps)
	{
		if (l == f.begin()) it = --f.end(); else it = l, it--;
		while (f.size() > 2 && mul(a[i], a[l->second], a[it->second]) > -eps)
		{
			f.erase(l);
			l = it;
			if (l == f.begin()) it = --f.end(); else it = l, it--;
		}
		if (r == --f.end()) it = f.begin(); else it = r, it++;
		while (f.size() > 2 && mul(a[i], a[r->second], a[it->second]) < eps)
		{
			f.erase(r);
			r = it;
			if (r == --f.end()) it = f.begin(); else it = r, it++;
		}
		f.insert(make_pair(z, i));
	}
}

long double dist(poi a, poi b)
{
	return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}

bool in(poi ct, poi p)
{
	long double th = atan2(p.y - ct.y, p.x - ct.x);
	set<pair<long double, int> >::iterator it, l, r;
	l = r = f.lower_bound(make_pair(th, n + 1));
	if (r == f.end()) r = f.begin();
	if (l == f.begin()) l = --f.end(); else l--;
	if (fabs(th - l->first) < eps)
		return dist(ct, p) + eps < dist(ct, a[l->second]);
	if (fabs(th - r->first) < eps)
		return dist(ct, p) + eps < dist(ct, a[r->second]);
	return mul(a[l->second], p, a[r->second]) < -eps;
}

bool check1()
{
	poi ct;
	ct.x = ct.y = 0;
	for (int i = 1; i <= 3; i++)
		ct.x += a[i].x, ct.y += a[i].y;
	ct.x /= 3, ct.y /= 3;
	f.clear();
	for (int i = 1; i <= 3; i++)
		f.insert(make_pair(atan2(a[i].y - ct.y, a[i].x - ct.x), i));
	for (int i = 4; i <= n; i++)
	{
		insert(ct, i);
		if (in(ct, a[i])) return 0;
	}
	return 1;
}

bool check2()
{
	poi ct;
	ct.x = ct.y = 0;
	for (int i = n; i > n - 3; i--)
		ct.x += a[i].x, ct.y += a[i].y;
	ct.x /= 3, ct.y /= 3;
	f.clear();
	for (int i = n; i > n - 3; i--)
		f.insert(make_pair(atan2(a[i].y - ct.y, a[i].x - ct.x), i));
	for (int i = n - 3; i; i--)
	{
		insert(ct, i);
		if (in(ct, a[i])) return 0;
	}
	return 1;
}

int main() {
	freopen("snake.in","r",stdin);
	freopen("snake.out","w",stdout); 
	while (cin >> n)
	{
		for (int i = 1; i <= n; i++)
		{
			double x, y;
			scanf("%lf%lf", &x, &y);
			a[i].x = x, a[i].y = y;
		}
		if (n < 4)
		{
			puts("Possible");
			continue;
		}
		if (!check1() || !check2())
		{
			puts("Impossible");
			continue;
		}
		puts("Possible");
	}
	return 0;
}
