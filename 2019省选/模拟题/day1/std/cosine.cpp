#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int T, n, m;
long double a[200010];
struct SegmentTree
{
	int l, r;
	long double cos_sum, sin_sum, cos_add, sin_add;
}t[800010];
int l, r;
long double cosv, sinv;

void build(int p, int l, int r)
{
	t[p].l = l, t[p].r = r, t[p].cos_add = 1, t[p].sin_add = 0;
	if (l == r)
	{
		t[p].cos_sum = cos(a[l]);
		t[p].sin_sum = sin(a[l]);
		return;
	}
	int mid = (l + r) / 2;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);
	t[p].cos_sum = t[p * 2].cos_sum + t[p * 2 + 1].cos_sum;
	t[p].sin_sum = t[p * 2].sin_sum + t[p * 2 + 1].sin_sum;
}

inline void update(SegmentTree &p, long double cosv, long double sinv)
{
	long double cos_sum = p.cos_sum, sin_sum = p.sin_sum;
	p.cos_sum = cosv*cos_sum - sinv*sin_sum;
	p.sin_sum = cosv*sin_sum + sinv*cos_sum;
	long double cos_add = p.cos_add, sin_add = p.sin_add;
	p.cos_add = cosv*cos_add - sinv*sin_add;
	p.sin_add = cosv*sin_add + sinv*cos_add;
}

inline void spread(int p)
{
	if (fabs(t[p].cos_add - 1) + fabs(t[p].sin_add) > 0)
	{
		update(t[p * 2], t[p].cos_add, t[p].sin_add);
		update(t[p * 2 + 1], t[p].cos_add, t[p].sin_add);
		t[p].cos_add = 1, t[p].sin_add = 0;
	}
}

void change(int p)
{
	if (l <= t[p].l && r >= t[p].r)
	{
		update(t[p], cosv, sinv);
		return;
	}
	int mid = (t[p].l + t[p].r) / 2;
	spread(p);
	if (l <= mid) change(p * 2);
	if (r > mid) change(p * 2 + 1);
	t[p].cos_sum = t[p * 2].cos_sum + t[p * 2 + 1].cos_sum;
	t[p].sin_sum = t[p * 2].sin_sum + t[p * 2 + 1].sin_sum;
}

long double ask(int p)
{
	if (l <= t[p].l && r >= t[p].r) return t[p].cos_sum;
	int mid = (t[p].l + t[p].r) / 2;
	spread(p);
	long double ans = 0;
	if (l <= mid) ans += ask(p * 2);
	if (r > mid) ans += ask(p * 2 + 1);
	return ans;
}

int main()
{
	freopen("cosine.in","r",stdin);
	freopen("cosine.out","w",stdout); 
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
		{
			double v;
			scanf("%lf", &v);
			a[i] = v;
		}
		build(1, 1, n);
		printf("Case #%d:\n", t);
		for (int i = 1; i <= m; i++)
		{
			int op; double v;
			scanf("%d%d%d", &op, &l, &r);
			if (op == 1)
			{
				scanf("%lf", &v);
				cosv=cos(v), sinv=sin(v);
				change(1);
			}
			else {
				printf("%.3lf\n", (double)ask(1));
			}
		}
	}
}

