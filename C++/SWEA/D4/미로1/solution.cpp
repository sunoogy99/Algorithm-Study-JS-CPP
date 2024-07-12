#include <iostream>
#include <string>
#include <cstring> // memset 사용
using namespace std;

int test_num;
int grid[16][16];
bool visited[16][16];
int canArrive;

pair<int, int> start;
//pair<int, int> finish;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

bool inRange(int x, int y) {
	return x >= 0 && x < 16 && y >= 0 && y < 16;
}

bool canGo(int x, int y) {
	if (!inRange(x, y)) return false;
	else if (visited[x][y] || grid[x][y] == 1) return false;
	else return true;
}

void dfs(int x, int y) {
	visited[x][y] = true;

	if (grid[x][y] == 3) {
		canArrive = 1;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int newX = x + dx[i];
		int newY = y + dy[i];

		if (canGo(newX, newY)) {
			dfs(newX, newY);
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	for (int i = 0; i < 10; i++) {
		cin >> test_num;

		// 도달 가능 여부, 방문 여부 모두 초기화
		canArrive = 0;
		memset(visited, false, sizeof(visited));
		memset(grid, 0, sizeof(grid));
		
		for (int j = 0; j < 16; j++) {
			string line;
			cin >> line;

			for (int k = 0; k < 16; k++) {
				grid[j][k] = line[k] - '0';

				// 시작점 설정하기
				if (grid[j][k] == 2) {
					start = make_pair(j, k);
				}
				// 도착점 설정하기 -> 굳이 설정할 필요 없음
				/*else if (grid[j][k] == 3) {
					finish = make_pair(j, k);
				}*/
			}
		}

		dfs(start.first, start.second);
		cout << '#' << test_num << ' ' << canArrive << '\n';
	}	

	return 0;
}