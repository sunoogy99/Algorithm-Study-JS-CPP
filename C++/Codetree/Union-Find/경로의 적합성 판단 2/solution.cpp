#include <iostream>
using namespace std;

int n, m, k;

int parent[100001];
int height[100001];
int path[100001];

int Find(int x) {
	if (x == parent[x]) return x;
	else return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);

	if (x == y) return;

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
}

int main() {
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		parent[i] = i;
	}

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		Union(x, y);
	}

	for (int i = 0; i < k; i++) {
		cin >> path[i];
	}

	int srcParent = Find(path[0]);

	// K개의 경로가 이어져 있는지 확인
	// Find -> 경로 압축으로 O(logN)에 수행
	// 총 시간 복잡도 = O(KlogN)
	for (int i = 1; i < k; i++) {
		if (srcParent != Find(path[i])) {
			srcParent = 0;
			break;
		}
	}

	if (srcParent != 0) {
		cout << 1 << '\n';
	}
	else {
		cout << 0 << '\n';
	}

	return 0;
}