#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int n;
int parent[100001];
int height[100001];

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

	//freopen("input.txt", "r", stdin);

	cin >> n;

	for (int i = 1; i <= n; i++) {
		parent[i] = i;
		height[i] = 0; // 안 해도 되긴 하는데, 테스트 케이스 여러 개인 경우에는 초기화 필요함
	}

	int a, b;

	// n-2개의 간선 정보 입력
	for (int i = 1; i <= n - 2; i++) {
		cin >> a >> b;
		Union(a, b);
	}

	// 정점 번호 갱신 -> compress tree로 변형
	// O(nlogn)
	for (int i = 1; i <= n; i++) {
		Find(i);
	}

	// set에 부모 정점 번호를 넣는다.
	// set은 자동으로 오름차순 정렬된다.
	// 서로 다른 2개의 정점 번호가 저장될 것이다.
	map<int, int> mp;
	for (int i = 1; i <= n; i++) {
		printf("parent[%d] = %d\n", i, parent[i]);
		if (mp.find(parent[i]) == mp.end()) {
			mp[parent[i]] = i;
		}
		else {
			mp[parent[i]] = min(mp[parent[i]], i);
		}
	}

	int ans[2];
	int idx = 0;
	for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
		ans[idx] = it->second;
		idx++;
	}

	cout << min(ans[0], ans[1]) << ' ' << max(ans[0], ans[1]) << '\n';
	return 0;
}