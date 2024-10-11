#include <iostream>
#include <set>
#include <queue>
#include <vector>
using namespace std;

const int INF = 1e9;

int Q;
int n, m;
int u, v, w;
int start = 0; // 출발 지점

vector<int> costs; // 정점에 대한 최단 거리 저장

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

// Product Comp. set으로 풀거면 부등호 반대로 하기
struct comp {
	bool operator() (Product* a, Product* b) const {
		// costs로 우선순위 설정할 수 있나? -> 갱신 안됨
		if (a->revenue - a->cost == b->revenue - b->cost) {
			return a->id > b->id;
		}
		return a->revenue - a->cost < b->revenue - b->cost;
	}
};

struct cmp {
	bool operator() (pair<int, int> a, pair<int, int> b) const {
		// 도착 정점이 같은 경우, 비용이 작은게 앞에 오도록 한다.
		if (a.first == b.first)
			return a.second > b.second;
		// 도착 정점이 다른 경우, 정점 번호가 작은게 앞에 오도록 한다.
		else return a.first < b.first;
	}
};

vector<set<pair<int, int>, cmp>> graph; // 그래프. 간선을 인덱스로 접근하는 경우가 없기 때문에 set 사용 가능
priority_queue<Product*, vector<Product*>, comp> prodQ; // 상품 우선순위에 기반해 저장한 큐
bool isDeleted[30001];

// 다익스트라로 시작점 s로부터 최단 거리 구하기
// 다익스트라가 잘못됐나? O(ElogV)
void dijikstra(int s) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
	pq.push(make_pair(0, s)); // 시작 정점에 대한 비용은 0
	costs[s] = 0;

	while (!pq.empty()) {
		int curCost = pq.top().first;
		int curX = pq.top().second;
		pq.pop();

		// 현재 방문한 지점이 costs보다 작은 경우, 방문할 필요 없음
		if (curCost > costs[curX]) continue;

		for (pair<int, int> e : graph[curX]) {
			int nextX = e.first;
			int weight = e.second;

			// 정점 방문 체크를 하는 것이 맞는 구현인가? -> 맞음
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

			// 그래프 구현
			for (int i = 0; i < m; ++i) {
				cin >> u >> v >> w;
				graph[u].insert(make_pair(v, w));
				graph[v].insert(make_pair(u, w));
			}

			// 다익스트라로 최단 거리 갱신
			dijikstra(start);
		}
		else if (op == 200) {
			cin >> id >> rev >> des;
			Product* newProd = new Product(id, rev, des, costs[des]);
			prodQ.push(newProd); // O(logn) -> 3만 logn
			isDeleted[id] = false; // 여행 상품 삭제 시도를 먼저 한 경우가 있을 수 있음
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

			// set에서 erase를 해서 빼야함
			// 안 빼고 cost 갱신하면, set 우선순위 바뀜
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
	틀린 예제
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

	결과
	14
	5
	27
	1
*/

/*
	생각하는 유형: 다익스트라 (최단 거리)

	100: 코드트리 랜드 건설 (1번)
	200: 여행 상품 생성 (30,000번)
	300: 여행 상품 취소 (30,000번)
	400: 최적의 여행 상품 판매 (30,000번)
	500: 여행 상품의 출발지 변경 (15번)

	간선의 수: 최대 10,000개
	다익스트라: (V+E)LOGE (?) -> 3만번이면 시간 초과임
	근데, 여행 상품 출발지 변경 안 하면, 구해놓고 저장해서 쓰면 됨
	그리고 V가 최대 2,000개라서 200번 명령에 대해서 일부는 저장해놓고 갖다 써도 될 듯

	200번 명령어에 대해서는
	먼저 도착지에 대한 cost가 구해져 있는 경우는 매출만 추가해서 넣고
	구해져 있지 않은 경우는 다익스트라로 구한 다음 매출과 함께 넣기

	이득은 0이어도 된다.
	도달 불가능한 경우는 무한대로 표기?

	400번은 출력할 거 없으면 -1 출력하고, pq에서 뽑지는 않음

	500번 명령어의 경우, pq에 있는 애들 뽑아서 바뀐 출발지로 다시 다익스트라 수행해서 값 갱신해서 넣어주기

*/