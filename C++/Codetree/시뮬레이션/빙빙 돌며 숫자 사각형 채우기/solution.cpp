#include <iostream>
using namespace std;

int n, m; // n : row, m : column
int grid[101][101];

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

bool inRange(int x, int y) {
	return x > 0 && x <= m && y > 0 && y <= n;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;

	pair<int, int> pos = { 1, 1 }; // 출발점 x, y
	int moveDir = 0; // 움직이는 방향

	int num = 1;
	grid[pos.second][pos.first] = num;

	for (int i = 2; i <= n * m; i++) {
		// 새로 이동할 지점 선택
		int newX = pos.first + dx[moveDir];
		int newY = pos.second + dy[moveDir];

		// 이동 가능 여부 판별 후 방향 전환
		if (!inRange(newX, newY) || grid[newY][newX] != 0) {
			moveDir = (moveDir + 1) % 4;
		}

		// 기록할 지점 좌표 설정
		pos.first = pos.first + dx[moveDir];
		pos.second = pos.second + dy[moveDir];

		// x, y => col, row이므로 순서를 pos.second, pos.first로 주어야 함
		grid[pos.second][pos.first] = i;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << grid[i][j] << ' ';
		}

		cout << '\n';
	}

	return 0;
}