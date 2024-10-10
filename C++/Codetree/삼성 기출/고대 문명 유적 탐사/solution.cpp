#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int K, M;

int fragCnt; // ���� ����
int cnt; // ������ ���� ���� (3�� �̻��̾�� fragCnt�� �ݿ���)

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int grid[6][6];
bool visited[6][6];
bool isFrag[6][6];

int wall[301]; // ���� ����
int curIdx = 1; // ���� ���鿡 �� �ִ� ���� ���� �ε���

// ȸ���� ���¿��� ���� ����, ��ǥ�� ���� ���
struct rotateInfo {
	int y;
	int x;
	int score;
	int degree;

	rotateInfo(int y, int x, int s, int d) : y(y), x(x), score(s), degree(d) {}

	bool operator<(const rotateInfo& comp) const {
		// ���� 1�� ȹ�� ��ġ�� ������ ���
		if (score == comp.score) {
			// ȸ�� ������ ������ ���
			if (degree == comp.degree) {
				// ȸ�� �߽� ��ǥ ���� ������ ���
				if (x == comp.x) {
					// ȸ�� �߽� ��ǥ ���� ���� ��찡 ���� �켱����
					return y > comp.y;
				}
				// ȸ�� �߽� ��ǥ ���� �ٸ� ���
				else {
					// ȸ�� �߽� ��ǥ ���� ���� ��찡 ���� �켱����
					return x > comp.x;
				}
			}
			// ȸ�� ������ �ٸ� ���
			else {
				// ȸ�� ������ ���� ��찡 ���� �켱����
				return degree > comp.degree;
			}
		}
		// ���� 1�� ȹ�� ��ġ�� �ٸ� ���
		else {
			// ���� 1�� ȹ�� ��ġ�� ū ��찡 ���� �켱����
			return score < comp.score;
		}
	}
};

// ���� ȸ�� �Լ�
// �߽� ��ǥ�� ȸ�� ����(�ð� ����)�� �޴´�.
void rotate90Grid(int y, int x) {
	// ������ ȸ�� ����
	int dy1[4] = { -1, -1, 1, 1 };
	int dx1[4] = { -1, 1, 1, -1 };

	// �� ȸ�� ����
	int dy2[4] = { -1, 0, 1, 0 };
	int dx2[4] = { 0, 1, 0, -1 };

	// ��� ���� ���� �̵� -> �� ���� 3ĭ �߿� ������ ĭ�� �� ĭ�� �̵��ϸ� �ȴ�.
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

// DFS�� ���� ���� ���� ���� (cnt�� 3 �̻��̾�� �������� �ݿ�)
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
				vector<pair<int, int>> dfsList; // dfs�� ���� ��ǥ ����
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

		// Ž�� ����
		for (int i = 2; i <= 4; ++i) {
			for (int j = 2; j <= 4; ++j) {
				// �� ��ǥ���� ȸ�� ����
				for (int l = 0; l < 4; ++l) {
					rotate90Grid(i, j);
					getScore(i, j);

					pq.push({ i, j, fragCnt, (l + 1) % 4 });
					fragCnt = 0;
				}
			}
		}

		// ���� ȹ��
		rotateInfo top = pq.top();
		pq.pop();

		if (top.score == 0) break; // �ִ� ��ġ�� 0�� ��� Ž�� ����

		cout << "���� ����: " << top.score << "\n";

		// K��° Ž�翡 ���� ���� ���
		int score = 0;

		// ȸ�� ���·� �����ϱ�
		for (int l = 0; l < top.degree; ++l) {
			rotate90Grid(top.y, top.x);
		}

		// ���� ���� ȹ��
		while (true) {
			// ������ ��ġ�� ���� ����, priority_quque�� �ְ� �ش� ��ġ�� ���� ��ȣ�� �ο��ؾ� �Ѵ�.
			getScore(top.y, top.x); // �� �Լ��� isFrag ���� -> true�� ������ �κ�

			if (fragCnt == 0) break; // ���� �� �ִ� ȹ�� ��ġ�� 0�� ��� Ž�� ����

			cout << "�߰��� ����: " << fragCnt << '\n';
			cout << "���� ����" << "\n";

			for (int i = 1; i <= 5; ++i) {
				for (int j = 1; j <= 5; ++j) {
					cout << grid[i][j] << ' ';
				}
				cout << '\n';
			}

			cout << "���� ���� Ȯ��\n";

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

			cout << "ä�� �ִ� ���� ��: " << cc << '\n';

			// ���� ������ ���ڷ� ä���ֱ�
			while (!posPq.empty()) {
				int y = posPq.top().first;
				int x = posPq.top().second;
				posPq.pop();

				grid[y][x] = wall[curIdx];
				curIdx++;
			}
		}

		cout << "���� ����: " << score << ' ';
	}

	return 0;
}