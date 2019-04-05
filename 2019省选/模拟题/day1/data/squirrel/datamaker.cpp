#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;

const int N = 100000;

inline int func (int x) {
	return pow(x, 8.0 / 5.0) + 1;
}

struct triple {
	int x, y, z;
};
triple arr[N];

int main () {
	freopen("squirrel.in","w",stdout); 
	for (int i = 0; i < N; i++) {
		if (i > 2000) arr[i].x = func(i + rand() % 20 - 20), arr[i].y = func(N - 1 - i);
		else arr[i].x = func(i), arr[i].y = func(N - 1 - i);
	}
	random_shuffle(arr, arr + N);
	for (int i = 0; i < N; i++) {
		arr[i].z = func(i);
	}
	random_shuffle(arr, arr + N);
	printf("%d\n", N);
	for (int i = 0; i < N; i++) {
		printf("%d %d %d\n", arr[i].x, arr[i].y, arr[i].z);
	}
	return 0;
}
