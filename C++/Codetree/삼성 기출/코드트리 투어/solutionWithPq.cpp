#include <iostream>
#include <set>
#include <queue>
#include <vector>
using namespace std;

const int INF = 1e9;

int Q;
int n, m;
int u, v, w;
int start = 0; // ��� ����

vector<int> costs; // ������ ���� �ִ� �Ÿ� ����

struct Product {
	int id;
	int revenue;
	int dest;
	int cost;

	Product(int id, int r, int d, int c) : id(id), revenue(r), dest(d), cost(c) {}
	/*
		bool operator<(const Product& comp) const {
			if (revenue - cost == comp.revenue - comp.cost)
				return id > comp.id;
			return revenue - cost < comp.revenue - comp.cost;
		}
	*/
};

// Product Comp. set���� Ǯ�Ÿ� �ε�ȣ �ݴ�� �ϱ�
struct comp {
	bool operator() (Product* a, Product* b) const {
		// costs�� �켱���� ������ �� �ֳ�? -> ���� �ȵ�
		if (a->revenue - a->cost == b->revenue - b->cost) {
			return a->id > b->id;
		}
		return a->revenue - a->cost < b->revenue - b->cost;
	}
};

struct cmp {
	bool operator() (pair<int, int> a, pair<int, int> b) const {
		// ���� ������ ���� ���, ����� ������ �տ� ������ �Ѵ�.
		if (a.first == b.first)
			return a.second > b.second;
		// ���� ������ �ٸ� ���, ���� ��ȣ�� ������ �տ� ������ �Ѵ�.
		else return a.first < b.first;
	}
};

vector<set<pair<int, int>, cmp>> graph; // �׷���. ������ �ε����� �����ϴ� ��찡 ���� ������ set ��� ����
priority_queue<Product*, vector<Product*>, comp> prodQ; // ��ǰ �켱������ ����� ������ ť
bool isDeleted[30001];

// ���ͽ�Ʈ��� ������ s�κ��� �ִ� �Ÿ� ���ϱ�
// ���ͽ�Ʈ�� �߸��Ƴ�? O(ElogV)
void dijikstra(int s) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
	pq.push(make_pair(0, s)); // ���� ������ ���� ����� 0
	costs[s] = 0;

	while (!pq.empty()) {
		int curCost = pq.top().first;
		int curX = pq.top().second;
		pq.pop();

		// ���� �湮�� ������ costs���� ���� ���, �湮�� �ʿ� ����
		if (curCost > costs[curX]) continue;

		for (pair<int, int> e : graph[curX]) {
			int nextX = e.first;
			int weight = e.second;

			// ���� �湮 üũ�� �ϴ� ���� �´� �����ΰ�? -> ����
			if (costs[curX] + weight < costs[nextX]) {
				costs[nextX] = costs[curX] + weight;
				pq.push(make_pair(costs[nextX], nextX));
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> Q;

	int op, id, rev, des;
	while (Q--) {
		cin >> op;

		if (op == 100) {
			cin >> n >> m;

			graph.resize(n);
			costs.resize(n, INF);

			// �׷��� ����
			for (int i = 0; i < m; ++i) {
				cin >> u >> v >> w;
				graph[u].insert(make_pair(v, w));
				graph[v].insert(make_pair(u, w));
			}

			// ���ͽ�Ʈ��� �ִ� �Ÿ� ����
			dijikstra(start);
		}
		else if (op == 200) {
			cin >> id >> rev >> des;
			Product* newProd = new Product(id, rev, des, costs[des]);
			prodQ.push(newProd); // O(logn) -> 3�� logn
			isDeleted[id] = false; // ���� ��ǰ ���� �õ��� ���� �� ��찡 ���� �� ����
		}
		else if (op == 300) {
			cin >> id;
			isDeleted[id] = true;
		}
		else if (op == 400) {
			while (true) {
				if (prodQ.empty()) {
					cout << -1 << '\n';
					break;
				}

				Product* curProd = prodQ.top();
				
				if (isDeleted[curProd->id]) {
					prodQ.pop();
				}
				else if (curProd->revenue - costs[curProd->dest] < 0 || costs[curProd->dest] == INF) {
					cout << -1 << '\n';
					break;
				}
				else {
					cout << curProd->id << '\n';
					prodQ.pop();
					break;
				}
			}
		}
		else if (op == 500) {
			cin >> start;

			costs.clear();

			costs.resize(n, INF);

			dijikstra(start);

			// set���� erase�� �ؼ� ������
			// �� ���� cost �����ϸ�, set �켱���� �ٲ�
			vector<Product*> tmp;
			while (!prodQ.empty()) {
				Product* p = prodQ.top();
				prodQ.pop();
				p->cost = costs[p->dest];
				tmp.push_back(p);
			}

			for (auto p : tmp) {
				prodQ.push(p);
			}
		}
	}

	return 0;
}

/*
	Ʋ�� ����
	28
	100 9 17 8 8 2 1 0 5 3 0 1 6 3 1 6 3 3 2 2 4 0 1 1 8 4 3 6 5 5 3 6 5 5 2 4 6 5 5 4 6 5 5 4 1 5 3 3 2 4 3 8 3 1
	300 4
	300 14
	200 19 7 6
	300 19
	200 7 10 3
	200 5 6 1
	200 1 2 2
	200 14 7 6
	500 8
	200 27 3 2
	300 7
	400
	300 8
	300 22
	200 29 2 6
	300 29
	400
	500 2
	200 23 3 5
	200 15 9 6
	200 17 7 4
	300 17
	400
	300 14
	300 27
	400
	200 18 2 5

	���
	14
	5
	27
	1
*/

/*
	�����ϴ� ����: ���ͽ�Ʈ�� (�ִ� �Ÿ�)

	100: �ڵ�Ʈ�� ���� �Ǽ� (1��)
	200: ���� ��ǰ ���� (30,000��)
	300: ���� ��ǰ ��� (30,000��)
	400: ������ ���� ��ǰ �Ǹ� (30,000��)
	500: ���� ��ǰ�� ����� ���� (15��)

	������ ��: �ִ� 10,000��
	���ͽ�Ʈ��: (V+E)LOGE (?) -> 3�����̸� �ð� �ʰ���
	�ٵ�, ���� ��ǰ ����� ���� �� �ϸ�, ���س��� �����ؼ� ���� ��
	�׸��� V�� �ִ� 2,000���� 200�� ��ɿ� ���ؼ� �Ϻδ� �����س��� ���� �ᵵ �� ��

	200�� ��ɾ ���ؼ���
	���� �������� ���� cost�� ������ �ִ� ���� ���⸸ �߰��ؼ� �ְ�
	������ ���� ���� ���� ���ͽ�Ʈ��� ���� ���� ����� �Բ� �ֱ�

	�̵��� 0�̾ �ȴ�.
	���� �Ұ����� ���� ���Ѵ�� ǥ��?

	400���� ����� �� ������ -1 ����ϰ�, pq���� ������ ����

	500�� ��ɾ��� ���, pq�� �ִ� �ֵ� �̾Ƽ� �ٲ� ������� �ٽ� ���ͽ�Ʈ�� �����ؼ� �� �����ؼ� �־��ֱ�

*/