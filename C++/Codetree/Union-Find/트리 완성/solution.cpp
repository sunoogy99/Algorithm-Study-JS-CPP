#include <iostream>
#include <set>
using namespace std;

int n, m;

int cutCnt;
int attachCnt;

int parent[100001];
int height[100001];

int Find(int x) {
	if (x == parent[x]) return x;
	else return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);

	if (x == y) {
		cutCnt++;
		return;
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
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		parent[i] = i;
		height[i] = 0;
	}

	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;

		Union(a, b);
	}

	// 부모 정점 번호 갱신
	set<int> vertices;
	for (int i = 1; i <= n; i++) {
		int pNum = Find(i);
		vertices.insert(pNum);
	}

	attachCnt = vertices.size() - 1;

	cout << cutCnt + attachCnt << '\n';
	return 0;
}