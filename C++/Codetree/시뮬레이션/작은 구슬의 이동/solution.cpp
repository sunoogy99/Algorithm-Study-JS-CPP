#include <iostream>
using namespace std;

int n, t;
int r, c;
char d;

int dx[4] = { 0, 1, -1, 0 };
int dy[4] = { -1, 0, 0, 1 };

bool inRange(int x, int y) {
	return x > 0 && x <= n && y > 0 && y <= n;
}

int getDir(char dir) {
	if (dir == 'U') {
		return 0;
	}
	else if (dir == 'R') {
		return 1;
	}
	else if (dir == 'L') {
		return 2;
	}
	else if (dir == 'D') {
		return 3;
	}
	else {
		return -1;
	}
}

int main() {
	cin >> n >> t;

	cin >> r >> c >> d;

	int moveDir = getDir(d);
	pair<int, int> pos = { c, r }; // x, y 좌표는 col, row와 동일
	for (int i = 1; i <= t; i++) {
		int newX = pos.first + dx[moveDir];
		int newY = pos.second + dy[moveDir];

		if (inRange(newX, newY)) {
			pos = { newX, newY };
		}
		else {
			moveDir = 3 - moveDir;
		}
	}

	cout << pos.second << ' ' << pos.first; // 행 번호, 열 변호 출력 순서
	return 0;
}