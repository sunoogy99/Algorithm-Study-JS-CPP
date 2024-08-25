#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

int n, m;
vector<vector<pair<int, int>>> graph;
vector<int> costs;

void dijikstra(int s) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(make_pair(0, s));

	costs[s] = 0;
	
	while (!pq.empty()) {
		int curPos = pq.top().second;
		int curCost = pq.top().first;
		pq.pop();

		for (pair<int, int> edge : graph[curPos]) {
			int nextPos = edge.first;
			int weight = edge.second;

			if (costs[nextPos] > curCost + weight) {
				costs[nextPos] = curCost + weight;
				pq.push(make_pair(costs[nextPos], nextPos));
			}
		}
	}
}

int main() {
	cin >> n >> m;

	costs.resize(n + 1, INF);
	graph.resize(n + 1);

	int s, e, w;
	for (int i = 0; i < m; i++) {
		cin >> s >> e >> w;
		graph[s].push_back(make_pair(e, w));
	}

	dijikstra(1);

	for (int i = 2; i <= n; i++) {
		if (costs[i] == INF) cout << -1 << '\n';
		else cout << costs[i] << '\n';
	}

	return 0;
}