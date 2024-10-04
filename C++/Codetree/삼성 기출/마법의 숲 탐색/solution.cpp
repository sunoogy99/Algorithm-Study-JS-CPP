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

/// �� �ʱ�ȭ �Լ�
void clearForest() {
	// memset���� �ʱ�ȭ ���� -> ���� ����
	for (int i = 0; i <= R; i++)
		for (int j = 0; j <= C; j++)
			FOREST[i][j] = make_pair(0, false);
}

class Golem {
private:
	// inRange �Լ��� ���� ����.
	// �� ���� ���� �Ϻθ� �� �͵� �����Ű�� ���� y�� ���� 0�� �������
	// �� ������ inForest�� ����ϸ�, �� ���κ��� ���� ������ ���� ���µ�
	// �� �ȿ� �����Ѵٰ� �Ǻ��ع��� -> ���� �׽�Ʈ���̽� ���� ó�� �߻�
	// ������, inForest������ ������ ó��������
	bool inRange(int y, int x) {
		return y >= 0 && y <= R && x > 0 && x <= C;
	}
	
	// �� ĭ �Ʒ� �̵� �������� üũ
	bool canGoDown(int y, int x) {
		// �� ���� �ȿ� �ִ� ���
		if (inRange(y + 2, x) && inRange(y + 1, x - 1) && inRange(y + 1, x + 1)) {
			// �̵��ϴ� ��ġ�� ��� �ִ� ���
			if (!FOREST[y + 2][x].first && !FOREST[y + 1][x - 1].first && !FOREST[y + 1][x + 1].first)
				return true;
			else return false;
		}
		else return false;
	}
	
	// ��, ������ x ��ǥ �� ���� �� -, +���� ���θ� �ٸ��� �ϸ� ������ ������ -> �Լ� ���� ����
	bool canRotateGoDown(int y, int x, int dir) {
		int f[2] = { 1, 2 }; // ���� ���

		// ȸ�� ���⿡ ���� �� ����
		if (dir == WEST) {
			f[0] *= -1;
			f[1] *= -1;
		}

		// ���� ��� ���� ���¿��� ȸ���ϴ� ���
		if (inRange(y - 1, x + f[0]) && inRange(y, x + f[1]) && inRange(y + 1, x + f[1]) &&
			inRange(y + 1, x + f[0]) && inRange(y + 2, x + f[0])) {
			if (!FOREST[y - 1][x + f[0]].first && !FOREST[y][x + f[1]].first && !FOREST[y + 1][x + f[1]].first &&
				!FOREST[y + 1][x + f[0]].first && !FOREST[y + 2][x + f[0]].first) {
				return true;
			}
			else return false;
		}
		// �� ĭ�� ���� ��ģ ���
		else if (y == 1 && inRange(y, x + f[1]) && inRange(y + 1, x + f[1]) && 
			inRange(y + 1, x + f[0]) && inRange(y + 2, x + f[0])) {
			if (!FOREST[y][x + f[1]].first && !FOREST[y + 1][x + f[1]].first &&
				!FOREST[y + 1][x + f[0]].first && !FOREST[y + 2][x + f[0]].first) {
				return true;
			}
			else return false;
		}
		// �� ĭ�� ���� ��ģ ���
		else if (y == 0 && inRange(y + 1, x + f[1]) && inRange(y + 1, x + f[0]) && inRange(y + 2, x + f[0])) {
			if (!FOREST[y + 1][x + f[1]].first && !FOREST[y + 1][x + f[0]].first && !FOREST[y + 2][x + f[0]].first) {
				return true;
			}
			else return false;
		}
		// ���� ��ģ �κ��� ���� ���
		else if (y == -1 && inRange(y + 2, x + f[0])) {
			if (!FOREST[y + 2][x + f[0]].first) return true;
			else return false;
		}
		else return false;
	}

public:
	pair<int, int> pos; // y, x ��ǥ : (row, col) ����
	int exit; // �ⱸ ��ȣ
	int id; // �� ID (�� ��° ������)

	// ������
	Golem(int c, int d, int gid) {
		pos.first = -1; // �� ���� �� y��ǥ�� -1�� ����. 0���� �ϸ�, �� �Ϻΰ� ������ ��
		pos.second = c;
		exit = d;
		id = gid;
	}

	/// �� �������� �̵��ϴ� �Լ�. ��� �̵��ϴ��� ������ �����.
	bool goDown() {
		int y = pos.first;
		int x = pos.second;

		// 1��) �� ĭ �Ʒ� �̵�
		if (canGoDown(y, x)) {
			pos.first += 1;
			return true;
		}

		// 2��) �������� ȸ�� + �� ĭ �Ʒ� �̵� & �ⱸ �ݽð� ���� 90�� ȸ�� (d + 3) % 4
		else if (canRotateGoDown(y, x, WEST)) {
			pos.first += 1;
			pos.second -= 1;
			exit = (exit + 3) % 4;
			return true;
		}

		// 3��) �������� ȸ�� + �� ĭ �Ʒ� �̵� & �ⱸ �ð� ���� 90�� ȸ�� (d + 1) % 4
		else if (canRotateGoDown(y, x, EAST)) {
			pos.first += 1;
			pos.second += 1;
			exit = (exit + 1) % 4;
			return true;
		}

		// �� �̻� �̵��� �Ұ����� ���
		else return false;
	}

	// ���� ���� ������ �� �ִ��� üũ 
	bool inForest() {
		// ���� ���κ��� ���� ������ ���������� Ȯ���ϸ� �ȴ�.
		if (pos.first - 1 > 0) return true;
		else return false;
	}

	// �� id�� ���� ����(���)�ϴ� �Լ� 
	// ���Ա��� ENTRY(1e6) ���ڷ� ����Ͽ� �ĺ��� �� �ֵ��� �Ѵ�.
	void fixOnForest() {
		int y = pos.first;
		int x = pos.second;

		FOREST[y][x] = make_pair(id, false);

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (i == exit) FOREST[ny][nx] = make_pair(id, true); // ENTRY + id�� ���� ���� �ⱸ���� ǥ��
			else FOREST[ny][nx] = make_pair(id, false);
		}
	}
};

// Golem������ �ٸ� ���� üũ (y > 0)
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

// BFS �Լ�) ������ �̵��� ���ϴ� ��ġ ��ȯ 
int spiritMove(int y, int x) {
	// visited �ʱ�ȭ
	for (int i = 0; i <= R; i++)
		for (int j = 0; j <= C; j++)
			visited[i][j] = false;

	int maxBottom = 0; // ���ϴ� ��ġ ���

	queue<pair<int, int>> q;
	q.emplace(y, x); // ���� ��ġ �ֱ�
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

				// ������ �̵��� ���ϴ� ��ġ ����
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

	int c; // c: ��� ��
	int d; // d: �ⱸ ���� (0: ��, 1: ��, 2: ��, 3: ��)

	for (int gid = 1; gid <= K; gid++) {
		cin >> c >> d;

		Golem g = Golem(c, d, gid);

		while (true) {
			// ���̻� ������ �� ���� ���
			if (!g.goDown()) {
				// ���� �� �ȿ� ���� üũ
				if (g.inForest()) {
					// ���� �� ���� ���
					g.fixOnForest();

					// ���� ���� ��ġ
					int jy = g.pos.first;
					int jx = g.pos.second;

					int bottomRow = spiritMove(jy, jx);
					SUM += bottomRow;
				}
				// �� �ۿ��� ��ģ ���, �� �ʱ�ȭ
				else {
					clearForest();
				}

				break;
			}

			// if�� �� �ɸ��� ���� ��� ��������
		}
	}

	cout << SUM << '\n';
	return 0;
}