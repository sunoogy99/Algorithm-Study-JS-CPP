#include <iostream>
#include <queue>
using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

int R, C, K;
int SUM;

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

pair<int, bool> FOREST[71][71]; // (gid, entry)
bool visited[71][71];

/// 숲 초기화 함수
void clearForest() {
	// memset으로 초기화 가능 -> 추후 수정
	for (int i = 0; i <= R; i++)
		for (int j = 0; j <= C; j++)
			FOREST[i][j] = make_pair(0, false);
}

class Golem {
private:
	// inRange 함수의 오류 존재.
	// 숲 진입 전에 일부만 들어간 것도 통과시키기 위해 y에 대해 0을 허용했음
	// 이 로직을 inForest에 사용하면, 맨 윗부분이 숲에 들어오지 못한 상태도
	// 숲 안에 존재한다고 판별해버림 -> 히든 테스트케이스 오답 처리 발생
	// 때문에, inForest에서는 별도로 처리해줬음
	bool inRange(int y, int x) {
		return y >= 0 && y <= R && x > 0 && x <= C;
	}
	
	// 한 칸 아래 이동 가능한지 체크
	bool canGoDown(int y, int x) {
		// 숲 범위 안에 있는 경우
		if (inRange(y + 2, x) && inRange(y + 1, x - 1) && inRange(y + 1, x + 1)) {
			// 이동하는 위치가 비어 있는 경우
			if (!FOREST[y + 2][x].first && !FOREST[y + 1][x - 1].first && !FOREST[y + 1][x + 1].first)
				return true;
			else return false;
		}
		else return false;
	}
	
	// 서, 동쪽이 x 좌표 값 조정 시 -, +인지 여부만 다르게 하면 로직이 동일함 -> 함수 통일 가능
	bool canRotateGoDown(int y, int x, int dir) {
		int f[2] = { 1, 2 }; // 보정 상수

		// 회전 방향에 따른 값 보정
		if (dir == WEST) {
			f[0] *= -1;
			f[1] *= -1;
		}

		// 숲에 모두 들어온 상태에서 회전하는 경우
		if (inRange(y - 1, x + f[0]) && inRange(y, x + f[1]) && inRange(y + 1, x + f[1]) &&
			inRange(y + 1, x + f[0]) && inRange(y + 2, x + f[0])) {
			if (!FOREST[y - 1][x + f[0]].first && !FOREST[y][x + f[1]].first && !FOREST[y + 1][x + f[1]].first &&
				!FOREST[y + 1][x + f[0]].first && !FOREST[y + 2][x + f[0]].first) {
				return true;
			}
			else return false;
		}
		// 두 칸만 숲에 걸친 경우
		else if (y == 1 && inRange(y, x + f[1]) && inRange(y + 1, x + f[1]) && 
			inRange(y + 1, x + f[0]) && inRange(y + 2, x + f[0])) {
			if (!FOREST[y][x + f[1]].first && !FOREST[y + 1][x + f[1]].first &&
				!FOREST[y + 1][x + f[0]].first && !FOREST[y + 2][x + f[0]].first) {
				return true;
			}
			else return false;
		}
		// 한 칸만 숲에 걸친 경우
		else if (y == 0 && inRange(y + 1, x + f[1]) && inRange(y + 1, x + f[0]) && inRange(y + 2, x + f[0])) {
			if (!FOREST[y + 1][x + f[1]].first && !FOREST[y + 1][x + f[0]].first && !FOREST[y + 2][x + f[0]].first) {
				return true;
			}
			else return false;
		}
		// 숲에 걸친 부분이 없는 경우
		else if (y == -1 && inRange(y + 2, x + f[0])) {
			if (!FOREST[y + 2][x + f[0]].first) return true;
			else return false;
		}
		else return false;
	}

public:
	pair<int, int> pos; // y, x 좌표 : (row, col) 순서
	int exit; // 출구 번호
	int id; // 골렘 ID (몇 번째 골렘인지)

	// 생성자
	Golem(int c, int d, int gid) {
		pos.first = -1; // 숲 진입 전 y좌표를 -1로 설정. 0으로 하면, 골렘 일부가 숲으로 들어감
		pos.second = c;
		exit = d;
		id = gid;
	}

	/// 숲 남쪽으로 이동하는 함수. 어떻게 이동하는지 로직은 감춘다.
	bool goDown() {
		int y = pos.first;
		int x = pos.second;

		// 1번) 한 칸 아래 이동
		if (canGoDown(y, x)) {
			pos.first += 1;
			return true;
		}

		// 2번) 서쪽으로 회전 + 한 칸 아래 이동 & 출구 반시계 방향 90도 회전 (d + 3) % 4
		else if (canRotateGoDown(y, x, WEST)) {
			pos.first += 1;
			pos.second -= 1;
			exit = (exit + 3) % 4;
			return true;
		}

		// 3번) 동쪽으로 회적 + 한 칸 아래 이동 & 출구 시계 방향 90도 회전 (d + 1) % 4
		else if (canRotateGoDown(y, x, EAST)) {
			pos.first += 1;
			pos.second += 1;
			exit = (exit + 1) % 4;
			return true;
		}

		// 더 이상 이동이 불가능한 경우
		else return false;
	}

	// 골렘이 숲에 완전히 들어가 있는지 체크 
	bool inForest() {
		// 가장 윗부분이 숲에 진입한 상태인지만 확인하면 된다.
		if (pos.first - 1 > 0) return true;
		else return false;
	}

	// 골렘 id를 숲에 고정(기록)하는 함수 
	// 출입구는 ENTRY(1e6) 숫자로 기록하여 식별할 수 있도록 한다.
	void fixOnForest() {
		int y = pos.first;
		int x = pos.second;

		FOREST[y][x] = make_pair(id, false);

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (i == exit) FOREST[ny][nx] = make_pair(id, true); // ENTRY + id로 현재 골렘의 출구임을 표시
			else FOREST[ny][nx] = make_pair(id, false);
		}
	}
};

// Golem에서랑 다른 범위 체크 (y > 0)
bool inRange(int y, int x) {
	return y > 0 && y <= R && x > 0 && x <= C;
}

bool canGo(int y, int x, int beforeGid, bool isEntry) {
	if (!inRange(y, x)) return false;
	else if (FOREST[y][x].first == 0 || visited[y][x]) return false;
	else if (FOREST[y][x].first != beforeGid) {
		if (isEntry) return true;
		else return false;
	}
	else return true;
}

// BFS 함수) 정령이 이동한 최하단 위치 반환 
int spiritMove(int y, int x) {
	// visited 초기화
	for (int i = 0; i <= R; i++)
		for (int j = 0; j <= C; j++)
			visited[i][j] = false;

	int maxBottom = 0; // 최하단 위치 기록

	queue<pair<int, int>> q;
	q.emplace(y, x); // 현재 위치 넣기
	visited[y][x] = true;

	while (!q.empty()) {
		int curY = q.front().first;
		int curX = q.front().second;
		q.pop();

		int beforeGid = FOREST[curY][curX].first;
		int isEntry = FOREST[curY][curX].second;

		for (int i = 0; i < 4; i++) {
			int ny = curY + dy[i];
			int nx = curX + dx[i];

			if (canGo(ny, nx, beforeGid, isEntry)) {
				visited[ny][nx] = true;

				// 정령이 이동한 최하단 위치 갱신
				if (ny > maxBottom) maxBottom = ny;

				q.emplace(ny, nx);
			}
		}
	}

	return maxBottom;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	cout.tie(0);

	cin >> R >> C >> K;

	int c; // c: 출발 열
	int d; // d: 출구 방향 (0: 북, 1: 동, 2: 남, 3: 서)

	for (int gid = 1; gid <= K; gid++) {
		cin >> c >> d;

		Golem g = Golem(c, d, gid);

		while (true) {
			// 더이상 내려갈 수 없는 경우
			if (!g.goDown()) {
				// 골렘이 숲 안에 들어간지 체크
				if (g.inForest()) {
					// 숲에 골렘 정보 기록
					g.fixOnForest();

					// 현재 정령 위치
					int jy = g.pos.first;
					int jx = g.pos.second;

					int bottomRow = spiritMove(jy, jx);
					SUM += bottomRow;
				}
				// 숲 밖에서 걸친 경우, 숲 초기화
				else {
					clearForest();
				}

				break;
			}

			// if문 안 걸리면 골렘은 계속 내려간다
		}
	}

	cout << SUM << '\n';
	return 0;
}