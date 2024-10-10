#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int K, M;

int fragCnt; // 조각 개수
int cnt; // 동일한 조각 개수 (3개 이상이어야 fragCnt에 반영됨)

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int grid[6][6];
bool visited[6][6];
bool isFrag[6][6];

int wall[301]; // 유적 벽면
int curIdx = 1; // 유적 벽면에 써 있는 현재 숫자 인덱스

// 회전한 상태에서 구한 점수, 좌표의 정보 기록
struct rotateInfo {
	int y;
	int x;
	int score;
	int degree;

	rotateInfo(int y, int x, int s, int d) : y(y), x(x), score(s), degree(d) {}

	bool operator<(const rotateInfo& comp) const {
		// 유물 1차 획득 가치가 동일한 경우
		if (score == comp.score) {
			// 회전 각도가 동일한 경우
			if (degree == comp.degree) {
				// 회전 중심 좌표 열이 동일한 경우
				if (x == comp.x) {
					// 회전 중심 좌표 행이 작은 경우가 높은 우선순위
					return y > comp.y;
				}
				// 회전 중심 좌표 열이 다른 경우
				else {
					// 회전 중심 좌표 열이 작은 경우가 높은 우선순위
					return x > comp.x;
				}
			}
			// 회전 각도가 다른 경우
			else {
				// 회전 각도가 작은 경우가 높은 우선순위
				return degree > comp.degree;
			}
		}
		// 유물 1차 획득 가치가 다른 경우
		else {
			// 유물 1차 획득 가치가 큰 경우가 높은 우선순위
			return score < comp.score;
		}
	}
};

// 격자 회전 함수
// 중심 좌표와 회전 각도(시계 방향)를 받는다.
void rotate90Grid(int y, int x) {
	// 꼭짓점 회전 정보
	int dy1[4] = { -1, -1, 1, 1 };
	int dx1[4] = { -1, 1, 1, -1 };

	// 변 회전 정보
	int dy2[4] = { -1, 0, 1, 0 };
	int dx2[4] = { 0, 1, 0, -1 };

	// 모든 변에 대해 이동 -> 각 변의 3칸 중에 꼭짓점 칸과 변 칸만 이동하면 된다.
	int last1 = grid[y + dy1[3]][x + dx1[3]];
	int last2 = grid[y + dy2[3]][x + dx2[3]];

	for (int i = 3; i > 0; --i) {
		grid[y + dy1[i]][x + dx1[i]] = grid[y + dy1[i - 1]][x + dx1[i - 1]];
		grid[y + dy2[i]][x + dx2[i]] = grid[y + dy2[i - 1]][x + dx2[i - 1]];
	}

	grid[y + dy1[0]][x + dx1[0]] = last1;
	grid[y + dy2[0]][x + dx2[0]] = last2;
}

bool inRange(int y, int x) {
	return y > 0 && y <= 5 && x > 0 && x <= 5;
}

bool canGo(int y, int x, int curNum) {
	if (!inRange(y, x)) return false;
	else if (visited[y][x] || grid[y][x] != curNum) return false;
	else return true;
}

// DFS를 통해 조각 개수 세기 (cnt가 3 이상이어야 조각으로 반영)
void dfs(int y, int x, vector<pair<int, int>>& dfsList) {
	int curNum = grid[y][x];
	cnt++;
	visited[y][x] = true;
	dfsList.push_back(make_pair(y, x));

	for (int i = 0; i < 4; ++i) {
		int newY = y + dy[i];
		int newX = x + dx[i];

		if (canGo(newY, newX, curNum)) {
			dfs(newY, newX, dfsList);
		}
	}
}

void getScore(int y, int x) {
	for (int i = 1; i <= 5; ++i)
		for (int j = 1; j <= 5; ++j) {
			visited[i][j] = false;
			isFrag[i][j] = false;
		}

	for (int i = 1; i <= 5; ++i) {
		for (int j = 1; j <= 5; ++j) {
			if (!visited[i][j]) {
				vector<pair<int, int>> dfsList; // dfs로 들어가는 좌표 저장
				dfs(i, j, dfsList);

				if (cnt >= 3) {
					fragCnt += cnt;
					for (pair<int, int> pos : dfsList) {
						isFrag[pos.first][pos.second] = true;
					}
				}

				cnt = 0;
			}
		}
	}
}

struct comp {
	bool operator()(const pair<int, int> a, const pair<int, int> b) {
		if (a.second == b.second) {
			return a.first < b.first;
		}
		else {
			return a.second > b.second;
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> K >> M;

	for (int i = 1; i <= 5; ++i) {
		for (int j = 1; j <= 5; ++j) {
			cin >> grid[i][j];
		}
	}

	for (int i = 1; i <= M; ++i) {
		cin >> wall[i];
	}

	while (K--) {
		priority_queue<rotateInfo> pq;

		// 탐사 진행
		for (int i = 2; i <= 4; ++i) {
			for (int j = 2; j <= 4; ++j) {
				// 각 좌표마다 회전 실행
				for (int l = 0; l < 4; ++l) {
					rotate90Grid(i, j);
					getScore(i, j);

					pq.push({ i, j, fragCnt, (l + 1) % 4 });
					fragCnt = 0;
				}
			}
		}

		// 유물 획득
		rotateInfo top = pq.top();
		pq.pop();

		if (top.score == 0) break; // 최대 가치가 0인 경우 탐사 종료

		cout << "현재 점수: " << top.score << "\n";

		// K번째 탐사에 대한 점수 기록
		int score = 0;

		// 회전 상태로 설정하기
		for (int l = 0; l < top.degree; ++l) {
			rotate90Grid(top.y, top.x);
		}

		// 유물 연쇄 획득
		while (true) {
			// 조각의 위치를 구한 다음, priority_quque에 넣고 해당 위치에 유적 번호를 부여해야 한다.
			getScore(top.y, top.x); // 이 함수로 isFrag 설정 -> true면 조각인 부분

			if (fragCnt == 0) break; // 얻을 수 있는 획득 가치가 0인 경우 탐색 종료

			cout << "추가된 조각: " << fragCnt << '\n';
			cout << "현재 상태" << "\n";

			for (int i = 1; i <= 5; ++i) {
				for (int j = 1; j <= 5; ++j) {
					cout << grid[i][j] << ' ';
				}
				cout << '\n';
			}

			cout << "조각 유무 확인\n";

			for (int i = 1; i <= 5; ++i) {
				for (int j = 1; j <= 5; ++j) {
					if (isFrag[i][j]) cout << 1 << ' ';
					else cout << 0 << ' ';
				}
				cout << '\n';
			}

			score += fragCnt;
			fragCnt = 0;

			priority_queue<pair<int, int>, vector<pair<int, int>>, comp> posPq;

			int cc = 0;
			for (int i = 1; i <= 5; ++i) {
				for (int j = 1; j <= 5; ++j) {
					if (isFrag[i][j]) {
						posPq.push(make_pair(i, j));
						cc++;
					}
				}
			}

			cout << "채워 넣는 조각 수: " << cc << '\n';

			// 유적 벽면의 숫자로 채워넣기
			while (!posPq.empty()) {
				int y = posPq.top().first;
				int x = posPq.top().second;
				posPq.pop();

				grid[y][x] = wall[curIdx];
				curIdx++;
			}
		}

		cout << "최종 점수: " << score << ' ';
	}

	return 0;
}