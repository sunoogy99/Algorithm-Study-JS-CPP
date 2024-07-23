#include <iostream>
using namespace std;

int N, M;
int r, c;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

int grid[101][101];

bool inRange(int x, int y) {
	return x > 0 && x <= N && y > 0 && y <= N;
}

bool isComfortable(int x, int y) {
	int paintCnt = 0;

	for (int i = 0; i < 4; i++) {
		int newX = x + dx[i];
		int newY = y + dy[i];

		if (inRange(newX, newY) && grid[newX][newY] != 0) {
			paintCnt++;
		}
	}

	return paintCnt == 3 ? true : false;
}

int main() {
	cin >> N >> M;

	for (int i = 1; i <= M; i++) {
		cin >> r >> c;
		grid[r][c] = 1; // »öÄ¥

		if (isComfortable(r, c)) {
			cout << 1 << endl;
		}
		else {
			cout << 0 << endl;
		}
	}

	return 0;
}