#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

const int RUD = 1e9;

int N, M, P, C, D;
int Rr, Rc;

int graph[51][51]; // ������

map<int, pair<int, int>> santa; // ��Ÿ ��ġ ���� ����
bool isAlive[31]; // ��Ÿ�� ���� ���� ����
int isStunned[31]; // ��Ÿ�� ���� �ñ� ����. isStunned[i] > k(��)�̸� ����
int score[31]; // ��Ÿ�� ���� ���� ����

// �絹�� �̵� ��� (�������, �밢��)
int dr[8] = { -1, 0, 1, 0, -1, 1, 1, -1 };
int dc[8] = { 0, 1, 0, -1, 1, 1, -1, -1 };

int getDist(int rr, int rc, int sr, int sc) {
	return (rr - sr) * (rr - sr) + (rc - sc) * (rc - sc);
}

// �絹���� �̵� ���� ����
struct moveInfo {
	int dist; // ��Ÿ���� �Ÿ�
	int r; // �ٶ󺸴� ��Ÿ�� r ��ǥ
	int c; // �ٶ󺸴� ��Ÿ�� c ��ǥ

	moveInfo(int d, int r, int c) : dist(d), r(r), c(c) {}

	bool operator<(const moveInfo& comp) const {
		if (dist == comp.dist) {
			if (r == comp.r)
				return c < comp.c;
			else
				return r < comp.r;
		}
		else return dist > comp.dist;
	}
};

int dsr[4] = { -1, 0, 1, 0 };
int dsc[4] = { 0, 1, 0, -1 };

bool inRange(int r, int c) {
	return r > 0 && r <= N && c > 0 && c <= N;
}

bool canGo(int r, int c) {
	if (!inRange(r, c)) return false;
	// �絹���� ���� �ʰ� �ٸ� ��Ÿ�� �ִ� ��� �̵� �Ұ�
	else if (graph[r][c] != RUD && graph[r][c] > 0) return false;
	else return true;
}

// �絹���� ���� �̵��� ��ġ ã��
int findNextPosRud() {
	// [����] ����ü �����ͷ� �Ѱ����� -> struct comp �����
	priority_queue<moveInfo> pq;

	// ��Ÿ�� �� - 30�� -> �ð� ����� �� ����
	// ������� ����ϸ�, 240�� * 1,000�� = 24��
	for (int i = 1; i <= P; ++i) {
		// ������ ��Ÿ �߿� ���� ����� ��Ÿ���� 1ĭ �̵�
		if (isAlive[i]) {
			int santaR = santa[i].first;
			int santaC = santa[i].second;

			// �Ÿ� ���
			int dist = getDist(Rr, Rc, santaR, santaC);
			// ������ ����
			pq.push(moveInfo(dist, santaR, santaC));
		}
	}

	if (pq.empty()) {
		return -1;
	}
	else {
		moveInfo nxt = pq.top();

		int minCost = 1e9; // �ּ� ���
		int d = -1; // �̵� ����

		// �̵��� ��Ÿ�� ���ߴٸ�, 8���� �� ���� ����� ���� �������� �̵�
		for (int dir = 0; dir < 8; ++dir) {
			int newRr = Rr + dr[dir];
			int newRc = Rc + dc[dir];

			if (inRange(newRr, newRc)) {
				int dist = getDist(newRr, newRc, nxt.r, nxt.c);
				if (dist < minCost) {
					minCost = dist;
					d = dir;
				}
			}
		}

		return d;
	}
}

// �絹�� �̵��ϱ�. �̵� ������ ������ ��. k: ���� ��
void moveRud(int dir, int k) {
	// ���� �絹�� ��ġ �����
	graph[Rr][Rc] = 0;

	// �絹�� ��ġ ��ǥ ����
	Rr += dr[dir];
	Rc += dc[dir];

	// ��Ÿ�� �ִ��� üũ
	// �ִٸ�, �絹���� ��Ÿ�� �浹(+ C) -> ���� ���� üũ -> ���� -> ��ȣ�ۿ�(���� �ο� x)
	if (graph[Rr][Rc] > 0) {
		int curSanta = graph[Rr][Rc]; // ���� ��Ÿ ã��
		graph[Rr][Rc] = RUD; // �絹�� ��ġ ����

		// ���� �̵��� ��Ÿ�� ��ǥ
		int nxtSr = Rr + dr[dir] * C;
		int nxtSc = Rc + dc[dir] * C;

		score[curSanta] += C;

		// ������ ������ �з����ٸ�, Ż����Ű��
		if (!inRange(nxtSr, nxtSc)) {
			isAlive[curSanta] = false;
			santa[curSanta] = make_pair(-1, -1);
		}
		else {
			isStunned[curSanta] = k + 2;

			// �з��� ���� ��Ÿ�� ���ٸ� ��ȣ�ۿ� ���� �絹�� �̵� ����
			if (graph[nxtSr][nxtSc] == 0) {
				graph[nxtSr][nxtSc] = curSanta;
				santa[curSanta] = make_pair(nxtSr, nxtSc);
				return;
			}

			// ��ȣ�ۿ�
			while (graph[nxtSr][nxtSc] > 0) {
				int tmp = graph[nxtSr][nxtSc];
				graph[nxtSr][nxtSc] = curSanta;
				santa[curSanta] = make_pair(nxtSr, nxtSc);
				curSanta = tmp;

				nxtSr += dr[dir];
				nxtSc += dc[dir];

				if (!inRange(nxtSr, nxtSc)) {
					isAlive[curSanta] = false; // ���� ������?
					santa[curSanta] = make_pair(-1, -1);
					break;
				}
				else {
					if (graph[nxtSr][nxtSc] == 0) {
						graph[nxtSr][nxtSc] = curSanta;
						santa[curSanta] = make_pair(nxtSr, nxtSc);
						break;
					}
				}

				// ��ȣ�ۿ��� ���� x
			}
		}
	}
	// ��Ÿ�� ���ٸ�, �絹�� �̵� �� �� ����
	else {
		graph[Rr][Rc] = RUD;
	}
}

// ��Ÿ ��ȣ sid�� ��Ÿ�� �̵� ���� ���ϱ�
int findNextPosSanta(int sid) {
	// dist, dir
	// �켱 �Ÿ��� ������� �ϰ�, �� ���� ���� �켱������ ����ؾ� ��
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	// ���� ��Ÿ�� ��ġ ����
	int curSr = santa[sid].first;
	int curSc = santa[sid].second;

	for (int dir = 0; dir < 4; ++dir) {
		int newSr = curSr + dsr[dir];
		int newSc = curSc + dsc[dir];

		if (canGo(newSr, newSc)) {
			int dist = getDist(Rr, Rc, newSr, newSc);
			int prevDist = getDist(Rr, Rc, curSr, curSc);

			if (prevDist <= dist) continue; // �̵� ���������� ��������� ������ �̵� x

			pq.push(make_pair(dist, dir));
		}
	}

	if (pq.empty()) return -1; // �̵� ������ ��ġ�� ���� ���, -1 ��ȯ
	else return pq.top().second; // �̵� ������ ��ġ�� �ִ� ���, �ش� ���� ��ȯ
}

// -1�� ���� �ٸ� ������ ó��
// ��Ÿ �̵��ϱ�
// �絹���� �浹 x -> �̵��ؼ� ����
// �絹���� �浹 -> ���� ���� -> ���� 180�� ȸ�� �̵� -> ���� ���� üũ -> ���� ó�� -> ��ȣ�ۿ�
void moveSanta(int sid, int dir, int k) {
	// ���� ��Ÿ�� ��ġ
	int curSr = santa[sid].first;
	int curSc = santa[sid].second;

	// ��Ÿ �ڸ� ����
	graph[curSr][curSc] = 0;

	// ���� ��Ÿ�� ��ġ
	int nxtSr = curSr + dsr[dir];
	int nxtSc = curSc + dsc[dir];

	// �絹���� �ִ� ���, �浹 ó��
	if (graph[nxtSr][nxtSc] == RUD) {
		// ���� ����
		score[sid] += D;

		dir = (dir + 2) % 4; // 180�� ȸ��

		nxtSr = nxtSr + dsr[dir] * D;
		nxtSc = nxtSc + dsc[dir] * D;

		// ������ ������ �����ٸ�
		if (!inRange(nxtSr, nxtSc)) {
			isAlive[sid] = false;
			santa[sid] = make_pair(-1, -1);
			return;
		}
		// ������ �ȿ� �ִ� ���, ���� ó�� -> ��ȣ�ۿ�
		else {
			// ���� ó��
			isStunned[sid] = k + 2;

			// �з��� ���� ��Ÿ�� ���ٸ� ��ȣ�ۿ� ���� �絹�� �̵� ����
			if (graph[nxtSr][nxtSc] == 0) {
				graph[nxtSr][nxtSc] = sid;
				santa[sid] = make_pair(nxtSr, nxtSc);
				return;
			}

			// ��ȣ�ۿ� -> �絹�� �ٽ� ���� �� ���� (�ش� �ݴ� �������� �̵��ϹǷ�)
			while (graph[nxtSr][nxtSc] > 0) {
				int tmp = graph[nxtSr][nxtSc];
				graph[nxtSr][nxtSc] = sid;
				santa[sid] = make_pair(nxtSr, nxtSc);
				sid = tmp;

				nxtSr += dsr[dir];
				nxtSc += dsc[dir];

				if (!inRange(nxtSr, nxtSc)) {
					isAlive[sid] = false; // ���� ������?
					santa[sid] = make_pair(-1, -1);
					break;
				}
				else {
					if (graph[nxtSr][nxtSc] == 0) {
						graph[nxtSr][nxtSc] = sid;
						santa[sid] = make_pair(nxtSr, nxtSc);
						break;
					}
				}

				// ��ȣ�ۿ��� ���� x
			}
		}
	}
	// �絹���� ���� ���, �̵�
	else {
		graph[nxtSr][nxtSc] = sid;
		santa[sid] = make_pair(nxtSr, nxtSc);
	}
}

void printScore() {
	for (int i = 1; i <= P; ++i)
		cout << score[i]<< ' ';
}

int main() {
	cin >> N >> M >> P >> C >> D;
	cin >> Rr >> Rc;

	graph[Rr][Rc] = RUD; // �絹�� ��ġ ����

	int sid, rr, cc; // ��Ÿ ��ȣ, ��ġ ���� �Է� �ޱ� ���� �ӽ� ����
	for (int i = 0; i < P; ++i) {
		cin >> sid >> rr >> cc;
		santa[sid] = make_pair(rr, cc);
		graph[rr][cc] = sid;
		isAlive[sid] = true;
	}

	// ���� ����
	for (int k = 1; k <= M; ++k) {
		int nxtDir = findNextPosRud();
		// ��Ÿ�� ���� ���, ���� ����
		if (nxtDir == -1) {
			// ���� ����
			break;
		}
		else {
			// �絹�� �̵�
			moveRud(nxtDir, k);

			// 1�� ��Ÿ���� P�� ��Ÿ �̵�
			for (int i = 1; i <= P; ++i) {
				// ���� ������ ��Ÿ, Ż���� ��Ÿ�� �Ѿ��
				if (isStunned[i] > k || !isAlive[i]) continue;

				// ���� �̵��� ���� ���ϱ�
				int nxtDir = findNextPosSanta(i);
				if (nxtDir == -1) continue; // �̵��� ������ ���� ���
				moveSanta(i, nxtDir, k);
			}

			// ��� �ִ� ���, ���� �߰�
			for (int i = 1; i <= P; ++i)
				if (isAlive[i]) score[i]++;

			// 1�� ����
		}
	}

	printScore();

	return 0;
}