#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int T, testCase;
int N, M, K;

// 1-based direction�̹Ƿ� 5ĭ���� ����
int dy[5] = { -1, -1, 1, 0, 0 };
int dx[5] = { -1, 0, 0, -1, 1 };

bool inRange(int y, int x) {
	return y >= 0 && y < N && x >= 0 && x < N;
}

// ��ǰ ó���� �� ���� �ִ��� �Ǵ�
bool onDrug(int y, int x) {
	return y == 0 || y == N - 1 || x == 0 || x == N - 1;
}

struct Group {
	int y;
	int x;
	int bugCnt;
	int dir;
	bool isAlive = true; // ������ �����ߴ���? ������ų�, �ٸ� ������ ������ ��� false

	Group(int y, int x, int b, int d) : y(y), x(x), bugCnt(b), dir(d) {}
};

// �̻��� ���� ���� ���� �켱 ���� ������
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

	// �ʱ� ���� �Է�
	for (int gId = 1; gId <= K; ++gId) {
		cin >> y >> x >> bugCnt >> dir;

		Group* curGroup = new Group(y, x, bugCnt, dir);
		groups[gId] = curGroup;
	}

	// M �ð� ���� �̵�
	while (M--) {
		// ���� ��ü �̵�
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
							// 180�� ȸ��
							if (curGroup->dir == 1) curGroup->dir = 2;
							else if (curGroup->dir == 2) curGroup->dir = 1;
							else if (curGroup->dir == 3) curGroup->dir = 4;
							else if (curGroup->dir == 4) curGroup->dir = 3;
						}
					}
				}
			}
		}

		// ���� ���ڿ� �ֱ�
		for (int gId = 1; gId <= K; ++gId) {
			if (groups[gId]->isAlive) {
				Group* curGroup = groups[gId];
				groupsOnGrid[curGroup->y][curGroup->x].push(curGroup);
			}
		}

		// ���� ��ġ�� (���ڿ��� ����)
		// ���ڴ� �̻��� ���� ��ġ�� ���� �ڷᱸ����
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

	// ��ü �̻��� �� ī��Ʈ
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