#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

int n;

// first: height, second: width
vector<long long> segTree;
vector<long long> numbers;

long long init(int node, int s, int e) {
	if (s == e) return segTree[node] = s; // numbers이 인덱스를 저장

	int m = (s + e) / 2;
	long long leftIdx = init(node * 2, s, m);
	long long rightIdx = init(node * 2 + 1, m + 1, e);

	if (numbers[leftIdx] < numbers[rightIdx])
		return segTree[node] = leftIdx;
	else 
		return segTree[node] = rightIdx;
}

long long query(int node, int ts, int te, int qs, int qe) {
	if (ts >= qs && te <= qe) return segTree[node];

	if (te < qs || ts > qe) return -1;

	int m = (ts + te) / 2;
	long long leftIdx = query(node * 2, ts, m, qs, qe);
	long long rightIdx = query(node * 2 + 1, m + 1, te, qs, qe);

	if (leftIdx == -1) return rightIdx;
	else if (rightIdx == -1) return leftIdx;
	else {
		if (numbers[leftIdx] < numbers[rightIdx]) 
			return segTree[node] = leftIdx;
		else 
			return segTree[node] = rightIdx;
	}
}

long long getMaxArea(int s, int e) {
	if (s > e) return 0;

	long long idx = query(1, 1, n, s, e);
	long long maxArea = numbers[idx] * (e - s + 1);
	long long tmp = max(getMaxArea(s, idx - 1), getMaxArea(idx + 1, e));

	return maxArea = max(maxArea, tmp);
}

int main() {
	while (true) {		
		cin >> n;

		if (n == 0) break;

		segTree.clear();
		numbers.clear();

		segTree.resize(4 * n);
		numbers.resize(n + 1);

		for (int i = 1; i <= n; i++) {
			cin >> numbers[i];
		}

		// min seg tree 만들기
		init(1, 1, n);

		cout << getMaxArea(1, n) << '\n';
	}

	return 0;
}