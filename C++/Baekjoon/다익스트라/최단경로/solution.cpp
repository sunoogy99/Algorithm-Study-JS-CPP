#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9; // MAX 값 설정

int V; // 정점 개수 (1 ~ 20,000)
int E; // 간선 개수 (1 ~ 300,000)

int K; // 시작 정점 번호 (1 ~ V)

int u, v, w; // 간선 정보 입력 (u: 출발 정점, v: 끝 정점, w: 가중치)

vector<vector<pair<int, int>>> graph; // 인접 리스트 기반 그래프
vector<int> cost; // 최단 거리 비용 저장

// 출발 정점에서 다른 모든 정점까지의 최단 거리 비용 계산
void dijikstra(int s) {
	// 기본 max heap이므로, min heap (오름차순) 전환
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	
	// 맨 처음에는 (현재 비용, 시작 지점)을 넣는다.
	pq.push(make_pair(0, s));
	cost[s] = 0;

	while (!pq.empty()) {
		int curV = pq.top().second; // 현재 정점 번호
		int curCost = pq.top().first; // 현재 정점 이동 시 가중치
		pq.pop();

		for (pair<int, int> edge : graph[curV]) {
			int nextV = edge.first; // 다음 정점 번호
			int weight = edge.second; // 다음 정점 이동 시 가중치
			
			// 아직 최단 거리가 갱신되지 않은 정점인 경우
			if (cost[nextV] > cost[curV] + weight) {
				// 최단 거리 갱신 + pq에 넣기
				cost[nextV] = cost[curV] + weight;
				pq.push(make_pair(cost[nextV], nextV));
			}
		}
	}
}

int main() {
	// 정점, 간선 개수 입력
	cin >> V >> E;

	// 시작 정점 번호 입력
	cin >> K;

	// 그래프 초기 설정
	graph.resize(V + 1);

	// 최단거리 비용 초기화
	cost.resize(V + 1, INF);

	// 그래프 정보 입력
	for (int i = 0; i < E; i++) {
		cin >> u >> v >> w;

		graph[u].push_back(make_pair(v, w));
	}

	dijikstra(K);

	for (int i = 1; i <= V; i++) {
		if (cost[i] == INF) cout << "INF" << endl;
		else cout << cost[i] << '\n';
	}

	return 0;
}