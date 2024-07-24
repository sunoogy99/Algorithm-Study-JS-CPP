#include <iostream>
#include <cmath>
using namespace std;

int N, K;
int grid[1001][1001];

// 1-based index
int dx[5] = { 0, 0, -1, 0, 1 };
int dy[5] = { 0, 1, 0, -1, 0 };

// 이동 방향 변경
// 사용법) swapMoveDir(dx[i], dy[i]);
void swapMoveDir(pair<int, int>& moveDir, int coefficient) {
	moveDir = { moveDir.second * coefficient, moveDir.first * coefficient };
}

// 빛이 격자 안에 있는지 판단하는 함수
bool inRange(int x, int y) {
	return x > 0 && x <= N && y > 0 && y <= N;
}

// K가 어느 지점에서 시작하는지 좌표 반환하기
pair<int, int> findStartPos(int k, pair<int, int>& moveDir) {
	int dir = ceil((double)k / N); // 어느 방향인지 찾기
	// k, N 모두 정수이므로, 그냥 k/N을 하면 소수값으로 나오지 않아 ceil 함수 적용 의미가 없음
	// 1 - 하향 (0, 1)
	// 2 - 좌향 (-1, 0)
	// 3 - 상향 (0, -1)
	// 4 - 우향 (1, 0)

	moveDir = { dx[dir], dy[dir] };

	// 시작 좌표 구하기
	int rest = k % N == 0 ? N : k % N;
	int idx;
	
	if (dir == 1 || dir == 2) idx = rest;
	else if (dir == 3 || dir == 4) idx = N + 1 - rest; // 3, 4 방향에서는 index가 반대 순서대로 구해짐
	else return { -1, -1 }; // 잘못된 값

	// row, col 기준이 아니라 x, y 좌표 기준임
	if (dir == 1) return { idx, 0 };
	else if (dir == 2) return { N + 1, idx };
	else if (dir == 3) return { idx, N + 1 };
	else if (dir == 4) return { 0, idx };
	else return { -1, -1 }; // 잘못된 값
}

int main() {
	cin >> N;
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			char c;
			cin >> c;

			// /일 때 방향 전환은 x, y swap 후 -1 곱해줌
			if (c == '/') grid[i][j] = -1;
			// \일 때 방향 전환은 x, y swap 후 1 곱해줌
			else if (c == '\\') grid[i][j] = 1;
		}
	}

	cin >> K;

	pair<int, int> moveDir;
	// K 값으로 맨 처음 시작 좌표 위치 구하기
	pair<int, int> srcPos = findStartPos(K, moveDir); // 여기서 moveDir 초기화됨

	int hitCnt = 0; // 거울에 부딪힌 횟수
	
	// 격자 안에 최초로 들어갔을 때 좌표 값
	int destX = srcPos.first + moveDir.first;
	int destY = srcPos.second + moveDir.second;

	while (inRange(destX, destY)) {
		// grid는 row, col 기준이라 y, x 순으로 접근해야 함
		int swapCoefficient = grid[destY][destX]; // 거울에 의해 부딪혀 방향이 어떻게 변경되는지 바꿔줄 보정 계수 (1 or -1)
		swapMoveDir(moveDir, swapCoefficient); // 거울에 의해 부딪혀 새로운 방향 설정
		hitCnt++; // swap 함수 실행 = 거울에 1번 튕김

		destX += moveDir.first;
		destY += moveDir.second;
	} 

	cout << hitCnt << '\n';
	return 0;
}