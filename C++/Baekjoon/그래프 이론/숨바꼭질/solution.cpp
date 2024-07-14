#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
using namespace std;

int N, K;

bool inRange(int x) {
	return x >= 0 && x <= 100000;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> K;

	queue<int> q;
	q.push(N);
	int visited[100001];
	/*memset(visited, INT_MAX, sizeof(visited));*/
	fill(visited, visited + 100001, INT_MAX);
	visited[N] = 0;

	while (!q.empty()) {
		int curPos = q.front();
		q.pop();

		int next = visited[curPos] + 1;

		if (inRange(curPos + 1) && next < visited[curPos + 1]) {
			visited[curPos + 1] = next;
			q.push(curPos + 1);
		}

		if (inRange(curPos - 1) && next < visited[curPos - 1]) {
			visited[curPos - 1] = next;
			q.push(curPos - 1);
		}

		if (inRange(curPos * 2) && next < visited[curPos * 2]) {
			visited[curPos * 2] = next;
			q.push(curPos * 2);
		}
	}

	cout << visited[K];
	return 0;
}