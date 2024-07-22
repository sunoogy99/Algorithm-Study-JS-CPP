#include <iostream>
#include <string>
using namespace std;

string operList;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> operList;

	pair<int, int> start = { 0, 0 };

	int moveDir = 0;
	int moveCnt = 0;
	bool isArrived = false;
	for (char dir : operList) {
		if (dir == 'L') {
			moveDir = (moveDir + 3) % 4;
		}
		else if (dir == 'R') {
			moveDir = (moveDir + 1) % 4;
		}
		else {
			start.first += dx[moveDir];
			start.second += dy[moveDir];
		}

		moveCnt++;

		if (start.first == 0 && start.second == 0) {
			isArrived = true;
			break;
		}
	}

	if (isArrived) {
		cout << moveCnt << '\n';
	}
	else {
		cout << -1 << '\n';
	}

	return 0;
}