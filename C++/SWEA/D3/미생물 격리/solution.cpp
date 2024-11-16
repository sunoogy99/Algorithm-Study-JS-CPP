#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int T, testCase;
int N, M, K;

// 1-based direction이므로 5칸으로 생성
int dy[5] = { -1, -1, 1, 0, 0 };
int dx[5] = { -1, 0, 0, -1, 1 };

bool inRange(int y, int x) {
	return y >= 0 && y < N && x >= 0 && x < N;
}

// 약품 처리된 셀 위에 있는지 판단
bool onDrug(int y, int x) {
	return y == 0 || y == N - 1 || x == 0 || x == N - 1;
}

struct Group {
	int y;
	int x;
	int bugCnt;
	int dir;
	bool isAlive = true; // 군집이 생존했는지? 사라지거나, 다른 군집에 합쳐진 경우 false

	Group(int y, int x, int b, int d) : y(y), x(x), bugCnt(b), dir(d) {}
};

// 미생물 수가 많을 수록 우선 순위 높아짐
struct comp {
	bool operator() (Group* a, Group* b) const {
		return a->bugCnt < b->bugCnt;
	}
};

vector<Group*> groups;
priority_queue<Group*, vector<Group*>, comp> groupsOnGrid[101][101];

int runTask() {
	// y: row, x: col
	int y, x;
	int bugCnt, dir;

	// 초기 정보 입력
	for (int gId = 1; gId <= K; ++gId) {
		cin >> y >> x >> bugCnt >> dir;

		Group* curGroup = new Group(y, x, bugCnt, dir);
		groups[gId] = curGroup;
	}

	// M 시간 동안 이동
	while (M--) {
		// 군집 전체 이동
		for (int gId = 1; gId <= K; ++gId) {
			if (groups[gId]->isAlive) {
				Group* curGroup = groups[gId];

				int newY = curGroup->y + dy[curGroup->dir];
				int newX = curGroup->x + dx[curGroup->dir];

				if (inRange(newY, newX)) {
					curGroup->y = newY;
					curGroup->x = newX;

					if (onDrug(newY, newX)) {
						curGroup->bugCnt = curGroup->bugCnt / 2;

						if (curGroup->bugCnt == 0) {
							curGroup->isAlive = false;
							continue;
						}
						else {
							// 180도 회전
							if (curGroup->dir == 1) curGroup->dir = 2;
							else if (curGroup->dir == 2) curGroup->dir = 1;
							else if (curGroup->dir == 3) curGroup->dir = 4;
							else if (curGroup->dir == 4) curGroup->dir = 3;
						}
					}
				}
			}
		}

		// 군집 격자에 넣기
		for (int gId = 1; gId <= K; ++gId) {
			if (groups[gId]->isAlive) {
				Group* curGroup = groups[gId];
				groupsOnGrid[curGroup->y][curGroup->x].push(curGroup);
			}
		}

		// 군집 합치기 (격자에서 빼기)
		// 격자는 미생물 군집 합치기 위한 자료구조임
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				if (!groupsOnGrid[i][j].empty()) {
					Group* bigGroup = groupsOnGrid[i][j].top();
					groupsOnGrid[i][j].pop();

					while (!groupsOnGrid[i][j].empty()) {
						Group* smallGroup = groupsOnGrid[i][j].top();
						groupsOnGrid[i][j].pop();

						bigGroup->bugCnt += smallGroup->bugCnt;
						smallGroup->isAlive = false;
					}
				}
			}
		}
	}

	int ans = 0;

	// 전체 미생물 수 카운트
	for (int gId = 1; gId <= K; ++gId) {
		if (groups[gId]->isAlive) {
			ans += groups[gId]->bugCnt;
		}
	}

	return ans;
}

void initialize() {
	groups.clear();
	groups.resize(K + 1);

	for (int i = 0; i < 101; ++i) {
		for (int j = 0; j < 101; ++j) {
			while (!groupsOnGrid[i][j].empty()) {
				groupsOnGrid[i][j].pop();
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> T;

	for (testCase = 1; testCase <= T; ++testCase) {
		cin >> N >> M >> K;

		initialize();
		int ans = runTask();
		cout << "#" << testCase << " " << ans << '\n';
	}

	return 0;
}