#include <iostream>
#include <string>
#include <cstring>
#include <climits>
#include <cmath>
using namespace std;

int t;
int n;
pair<int, int> company;
pair<int, int> home;
pair<int, int> customers[10];
bool visited[10];
int minVal;

int dfs(int x, int y, int sum) {
	bool allVisited = true; // 모든 지점을 방문했는지 체크 여부

	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			allVisited = false;
			visited[i] = true;
			int diff = abs(customers[i].first - x) + abs(customers[i].second - y);
			dfs(customers[i].first, customers[i].second, sum + diff);
			visited[i] = false;
		}
	}

	// 모든 지점을 방문했다면 집까지의 거리까지 구하기
	if (allVisited) {
		int diff = abs(x - home.first) + abs(y - home.second);
		sum += diff;
		if (sum < minVal) {
			minVal = sum;
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> t;

	for (int i = 1; i <= t; i++) {
		memset(customers, 0, sizeof(customers));
		minVal = INT_MAX;
		cin >> n;	
		cin >> company.first >> company.second >> home.first >> home.second;
		for (int j = 0; j < n; j++) {
			cin >> customers[j].first >> customers[j].second;
		}

		dfs(company.first, company.second, 0);
		cout << '#' << i << ' ' << minVal << '\n';
	}

	return 0;
}