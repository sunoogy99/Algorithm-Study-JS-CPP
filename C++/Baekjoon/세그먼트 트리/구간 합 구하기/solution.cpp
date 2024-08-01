#include <iostream>
#include <vector>
using namespace std;

int N, M, K;
// N: 수의 개수, M: 수의 변경이 일어나는 횟수, K: 구간의 합을 구하는 횟수
// N: 최대 100만
// M, K: 최대 1만

vector<long long> segTree; // 구간합 2^63 - 1까지 가능
vector<long long> numbers;

long long init(int node, int s, int e) {
	if (s == e) return segTree[node] = numbers[s];

	int m = (s + e) / 2;
	long long a = init(node * 2, s, m);
	long long b = init(node * 2 + 1, m + 1, e);
	return segTree[node] = a + b;
}

long long update(int node, int s, int e, int ii, long long value) {
	// ii : update할 index
	// value : update할 값

	// 현재 범위 이내에 있지 않은 경우, 그대로 반환
	if (s > ii || e < ii) return segTree[node];

	segTree[node] = value; // 일단 값 넣기

	// 단말 노드이면서 ii를 만족하는 경우 -> 값 갱신
	if (s == e) return segTree[node];

	int m = (s + e) / 2;
	long long a = update(node * 2, s, m, ii, value);
	long long b = update(node * 2 + 1, m + 1, e, ii, value);
	return segTree[node] = a + b;
}

long long query(int node, int ts, int te, int qs, int qe) {
	// 트리 구간이 질의 구간'에' 포함되는 경우 (트리 구간 <= 질의 구간)
	// 해당 노드 값 반환
	if (ts >= qs && te <= qe) return segTree[node];

	// 트리 구간과 질의 구간이 전혀 겹치지 않는 경우
	// 0을 반환하여 추후 구간합 구할 때 아무 변화 일어나지 않도록 하기 위함
	if (te < qs || ts > qe) return 0;

	// 일부 겹침 혹은 트리구간이 질의 구간'을' 포함 (질의 구간 <= 트리 구간)
	int m = (ts + te) / 2;
	long long a = query(node * 2, ts, m, qs, qe);
	long long b = query(node * 2 + 1, m + 1, te, qs, qe);
	return a + b;
}

int main() {
	cin >> N >> M >> K;

	numbers.resize(N + 1);
	for (int i = 1; i <= N; i++) {
		cin >> numbers[i];
	}

	segTree.resize(N * 4);
	init(1, 1, N);

	vector<long long> ans;
	for (int i = 0; i < M + K; i++) {
		long long a, b, c;
		cin >> a >> b >> c;

		// update 
		if (a == 1) {
			update(1, 1, N, b, c);
		}
		// query (구간합)
		else if (a == 2) {
			ans.push_back(query(1, 1, N, b, c));
		}
	}

	for (long long res : ans) {
		cout << res << '\n';
	}

	return 0;
}