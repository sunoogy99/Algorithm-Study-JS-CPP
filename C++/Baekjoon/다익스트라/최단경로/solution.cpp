#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9; // MAX �� ����

int V; // ���� ���� (1 ~ 20,000)
int E; // ���� ���� (1 ~ 300,000)

int K; // ���� ���� ��ȣ (1 ~ V)

int u, v, w; // ���� ���� �Է� (u: ��� ����, v: �� ����, w: ����ġ)

vector<vector<pair<int, int>>> graph; // ���� ����Ʈ ��� �׷���
vector<int> cost; // �ִ� �Ÿ� ��� ����

// ��� �������� �ٸ� ��� ���������� �ִ� �Ÿ� ��� ���
void dijikstra(int s) {
	// �⺻ max heap�̹Ƿ�, min heap (��������) ��ȯ
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	
	// �� ó������ (���� ���, ���� ����)�� �ִ´�.
	pq.push(make_pair(0, s));
	cost[s] = 0;

	while (!pq.empty()) {
		int curV = pq.top().second; // ���� ���� ��ȣ
		int curCost = pq.top().first; // ���� ���� �̵� �� ����ġ
		pq.pop();

		for (pair<int, int> edge : graph[curV]) {
			int nextV = edge.first; // ���� ���� ��ȣ
			int weight = edge.second; // ���� ���� �̵� �� ����ġ
			
			// ���� �ִ� �Ÿ��� ���ŵ��� ���� ������ ���
			if (cost[nextV] > cost[curV] + weight) {
				// �ִ� �Ÿ� ���� + pq�� �ֱ�
				cost[nextV] = cost[curV] + weight;
				pq.push(make_pair(cost[nextV], nextV));
			}
		}
	}
}

int main() {
	// ����, ���� ���� �Է�
	cin >> V >> E;

	// ���� ���� ��ȣ �Է�
	cin >> K;

	// �׷��� �ʱ� ����
	graph.resize(V + 1);

	// �ִܰŸ� ��� �ʱ�ȭ
	cost.resize(V + 1, INF);

	// �׷��� ���� �Է�
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