#include <iostream>
using namespace std;

int n, m;
int parent[100001];
int height[100001];
int cnt[100001]; // i랑 연결된 정점 개수 저장

int Find(int x) {
	if (x == parent[x]) return x;
	else return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);

	if (x == y) return;

	// cnt는 부모 노드인 것만 관리하면 됨
	// 2번 연산에 대해서 Find로 rootId 찾아서
	// rootId의 cnt를 반환하면 됨

	if (height[x] < height[y]) {
		parent[x] = y; // y 밑에 x가 달린 것
		cnt[y] += cnt[x];
	}
	else if (height[x] > height[y]) {
		parent[y] = x; // x 밑에 y가 달린 것
		cnt[x] += cnt[y];
	}
	else {
		parent[y] = x;
		height[x]++;
		cnt[x] += cnt[y];
	}
}

int main() {
	cin >> n >> m;

	for (int i = 0; i <= n; i++) {
		parent[i] = i;
		height[i] = 0;
		cnt[i] = 1; // 자기 자신 포함한 개수로 초기 설정
	}

	for (int i = 0; i < m; i++) {
		char op;
		int a, b;

		cin >> op;

		if (op == 'x') {
			cin >> a >> b;
			Union(a, b);
		}
		else if (op == 'y') {
			cin >> a;
			int rootId = Find(a);
			cout << cnt[rootId] << '\n';
		}
	}

	return 0;
}