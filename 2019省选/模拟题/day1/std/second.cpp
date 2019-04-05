#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[210], f[100010], T, N, n, m, ans, sum;

int main()
{
	freopen("second.in","r",stdin);
	freopen("second.out","w",stdout);
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		cin >> n; N += n;
		ans = m = sum = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
			if(a[i] > 0) sum += a[i];
		}
		for (int j = 0; j <= sum; j++) f[j] = 0;
		f[0] = 1;
		sort(a + 1, a + n + 1);
		for (int i = 1; i < n; i++)
		{
			if (a[i] <= 0)
			{
				ans -= a[i];
				continue;
			}
			for (int j = m; j >= 0; j--)
				f[j + a[i]] |= f[j];
			m += a[i];
		}
		int delta = m + 1;
		for (int j = 0; j <= m; j++)
			if (f[j] && abs(j - (m - j)) < delta)
				delta = abs(j - (m - j));
		if (a[n] > 0) ans += a[n] - delta; else ans -= a[n];
		printf("Case #%d: %d\n", t, ans);
	}
	//cout << N << endl;
}
