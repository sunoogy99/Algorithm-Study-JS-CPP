#include <iostream>
#include <algorithm>
using namespace std;

int n, m;

int parent[100001];
int height[100001];

int Find(int x) {
	if (x == parent[x]) return x;
	else return parent[x] = Find(parent[x]);
}

bool Union(int x, int y) {
	x = Find(x);
	y = Find(y);

	// 사이클이 생기는 시점
	if (x == y) {
		return false;
	}

	if (height[x] < height[y]) {
		parent[x] = y;
	}
	else if (height[x] > height[y]) {
		parent[y] = x;
	}
	else {
		parent[y] = x;
		height[x]++;
	}

	return true;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		parent[i] = i;
		height[i] = 0;
	}

	int a, b;
	int idx = 999999; // 사이클이 생기는 인덱스
	for (int i = 1; i <= m; i++) {
		cin >> a >> b;

		bool noCycle = Union(a, b);

		if (!noCycle) idx = min(idx, i); // 사이클을 만드는 경우가 여러 경우일 수 있음
	}

	if (idx == 999999) cout << "happy" << '\n';
	else cout << idx << '\n';

	return 0;
}