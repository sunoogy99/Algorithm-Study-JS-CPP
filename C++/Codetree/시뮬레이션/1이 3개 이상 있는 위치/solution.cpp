#include <iostream>
using namespace std;

int n;
int grid[101][101];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

bool inRange(int x, int y) {
	return x > 0 && x <= n && y > 0 && y <= n;
}

int main() {
	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}

	int res = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int oCnt = 0;
			for (int d = 0; d < 4; d++) {
				int newX = i + dx[d];
				int newY = j + dy[d];

				// 칸에 0이 적혀 있어도 방문 가능하며, 주변 칸에 1이 몇 개 있는지 카운트하고
				// 1이 3개 이상이면 res 증가 시킴
				if (inRange(newX, newY) && grid[newX][newY]) {
					oCnt++;
				}
			}

			if (oCnt >= 3) {
				res++;
			}
		}
	}

	cout << res << '\n';
	return 0;
}