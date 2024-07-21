#include <iostream>
using namespace std;

int N;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

// 방향 문자에서 dx, dy 인덱스로 변환하는 함수
int getMoveDir(char dir) {
	if (dir == 'N') {
		return 0;
	}
	else if (dir == 'E') {
		return 1;
	}
	else if (dir == 'S') {
		return 2;
	}
	else if (dir == 'W') {
		return 3;
	}
	else return -1;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;

	pair<int, int> start = { 0, 0 };
	int moveCnt = 0;
	bool isArrived = false;

	for (int i = 0; i < N; i++) {
		char dir;
		int distance;
		cin >> dir >> distance;

		int moveDir = getMoveDir(dir);
		for (int j = 0; j < distance; j++) {
			start.first += dx[moveDir];
			start.second += dy[moveDir];
			moveCnt++;

			if (start.first == 0 && start.second == 0) {
				isArrived = true;
				break;
			}
		}

		if (isArrived) break;
	}

	if (isArrived) cout << moveCnt << '\n';
	else cout << -1 << '\n';

	return 0;
}