#include <iostream>
using namespace std;

int n, m;
int group[100001];
int height[100001];

int Find(int x) {
	if (x == group[x]) return x;
	else return group[x] = Find(group[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);

	if (x == y) return;

	if (height[x] < height[y]) {
		group[x] = y;
	}
	else if (height[x] > height[y]) {
		group[y] = x;
	}
	else {
		// 둘이 높이가 같은 경우, y를 x 밑으로 집어 넣음
		// 결과적으로 x의 높이 증가
		group[y] = x;
		height[x]++;
	}
}

int main() {
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		group[i] = i;
	}

	for (int i = 0; i < m; i++) {
		int op, a, b;
		cin >> op >> a >> b;

		if (op == 0) {
			Union(a, b);
		}
		else if (op == 1) {
			int x = Find(a);
			int y = Find(b);
			
			if (x == y) cout << 1 << '\n';
			else cout << 0 << '\n';
		}
	}

	return 0;
}