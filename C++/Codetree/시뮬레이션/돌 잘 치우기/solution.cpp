#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int n, k, m;
int grid[101][101];
bool visited[101][101];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

bool inRange(int x, int y) {
	return x > 0 && x <= n && y > 0 && y <= n;
}

bool canGo(int x, int y) {
	if (!inRange(x, y)) return false;
	else if (visited[x][y] || grid[x][y]) return false;
	else return true;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k >> m;

	vector<pair<int, int>> rocks;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];

			if (grid[i][j]) {
				rocks.emplace_back(i, j);
			}
		}
	}

	vector<pair<int, int>> starts;
	for (int i = 0; i < k; i++) {
		int row, col;
		cin >> row >> col;
		starts.emplace_back(row, col);
	}

	// 조합을 구하기 위해 m개의 true와 돌의 개수 - m 개의 false를 반환한다.
	int rockCnt = rocks.size();
	vector<bool> comb(rockCnt);
	// ex) m: 2, 돌의 개수: 8 -> comb: 0 0 0 0 0 0 1 1
	fill(comb.end() - m, comb.end(), true);
	
	int maxVal = INT_MIN;
	do {
		// 돌 치우기
		for (int i = 0; i < rocks.size(); i++) {
			if (comb[i]) {
				pair<int, int> pos = rocks[i];
				grid[pos.first][pos.second] = 0;
			}
		}

		// BFS 실행하기
		int visitCnt = 0;
		for (const pair<int, int> pos : starts) {
			if (visited[pos.first][pos.second]) {
				continue;
			}

			queue<pair<int, int>> q;
			q.emplace(pos);
			visited[pos.first][pos.second] = true;
			visitCnt++;

			while (!q.empty()) {
				int curX = q.front().first;
				int curY = q.front().second;
				q.pop();

				for (int i = 0; i < 4; i++) {
					int newX = curX + dx[i];
					int newY = curY + dy[i];

					if (canGo(newX, newY)) {
						q.emplace(newX, newY);
						visited[newX][newY] = true;
						visitCnt++;
					}
				}
			}
		}

		if (visitCnt > maxVal) {
			maxVal = visitCnt;
		}

		// 되돌리기
		for (int i = 0; i < rocks.size(); i++) {
			if (comb[i]) {
				pair<int, int> pos = rocks[i];
				grid[pos.first][pos.second] = 1;
			}
		}

		memset(visited, false, sizeof(visited));
	} while (next_permutation(comb.begin(), comb.end()));

	cout << maxVal << '\n';
	return 0;
}