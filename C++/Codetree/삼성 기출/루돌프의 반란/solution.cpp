#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

const int RUD = 1e9;

int N, M, P, C, D;
int Rr, Rc;

int graph[51][51]; // 게임판

map<int, pair<int, int>> santa; // 산타 위치 정보 저장
bool isAlive[31]; // 산타의 생존 여부 저장
int isStunned[31]; // 산타의 스턴 시기 저장. isStunned[i] > k(턴)이면 기절
int score[31]; // 산타의 점수 정보 저장

// 루돌프 이동 방법 (상우하좌, 대각선)
int dr[8] = { -1, 0, 1, 0, -1, 1, 1, -1 };
int dc[8] = { 0, 1, 0, -1, 1, 1, -1, -1 };

int getDist(int rr, int rc, int sr, int sc) {
	return (rr - sr) * (rr - sr) + (rc - sc) * (rc - sc);
}

// 루돌프의 이동 정보 저장
struct moveInfo {
	int dist; // 산타와의 거리
	int r; // 바라보는 산타의 r 좌표
	int c; // 바라보는 산타의 c 좌표

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
	// 루돌프가 있지 않고 다른 산타가 있는 경우 이동 불가
	else if (graph[r][c] != RUD && graph[r][c] > 0) return false;
	else return true;
}

// 루돌프의 다음 이동할 위치 찾기
int findNextPosRud() {
	// [개선] 구조체 포인터로 넘겨주자 -> struct comp 만들기
	priority_queue<moveInfo> pq;

	// 산타의 수 - 30명 -> 시간 충분할 것 같음
	// 방향까지 고려하면, 240번 * 1,000번 = 24만
	for (int i = 1; i <= P; ++i) {
		// 생존한 산타 중에 가장 가까운 산타에게 1칸 이동
		if (isAlive[i]) {
			int santaR = santa[i].first;
			int santaC = santa[i].second;

			// 거리 계산
			int dist = getDist(Rr, Rc, santaR, santaC);
			// 방향은 미정
			pq.push(moveInfo(dist, santaR, santaC));
		}
	}

	if (pq.empty()) {
		return -1;
	}
	else {
		moveInfo nxt = pq.top();

		int minCost = 1e9; // 최소 비용
		int d = -1; // 이동 방향

		// 이동할 산타를 정했다면, 8방향 중 가장 가까워 지는 방향으로 이동
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

// 루돌프 이동하기. 이동 가능한 정보만 줌. k: 현재 턴
void moveRud(int dir, int k) {
	// 현재 루돌프 위치 지우기
	graph[Rr][Rc] = 0;

	// 루돌프 위치 좌표 갱신
	Rr += dr[dir];
	Rc += dc[dir];

	// 산타가 있는지 체크
	// 있다면, 루돌프가 산타와 충돌(+ C) -> 생존 여부 체크 -> 기절 -> 상호작용(점수 부여 x)
	if (graph[Rr][Rc] > 0) {
		int curSanta = graph[Rr][Rc]; // 현재 산타 찾기
		graph[Rr][Rc] = RUD; // 루돌프 위치 배정

		// 다음 이동할 산타의 좌표
		int nxtSr = Rr + dr[dir] * C;
		int nxtSc = Rc + dc[dir] * C;

		score[curSanta] += C;

		// 게임판 밖으로 밀려났다면, 탈락시키기
		if (!inRange(nxtSr, nxtSc)) {
			isAlive[curSanta] = false;
			santa[curSanta] = make_pair(-1, -1);
		}
		else {
			isStunned[curSanta] = k + 2;

			// 밀려난 곳에 산타가 없다면 상호작용 없이 루돌프 이동 종료
			if (graph[nxtSr][nxtSc] == 0) {
				graph[nxtSr][nxtSc] = curSanta;
				santa[curSanta] = make_pair(nxtSr, nxtSc);
				return;
			}

			// 상호작용
			while (graph[nxtSr][nxtSc] > 0) {
				int tmp = graph[nxtSr][nxtSc];
				graph[nxtSr][nxtSc] = curSanta;
				santa[curSanta] = make_pair(nxtSr, nxtSc);
				curSanta = tmp;

				nxtSr += dr[dir];
				nxtSc += dc[dir];

				if (!inRange(nxtSr, nxtSc)) {
					isAlive[curSanta] = false; // 버퍼 오버런?
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

				// 상호작용은 스턴 x
			}
		}
	}
	// 산타가 없다면, 루돌프 이동 후 턴 종료
	else {
		graph[Rr][Rc] = RUD;
	}
}

// 산타 번호 sid인 산타의 이동 방향 정하기
int findNextPosSanta(int sid) {
	// dist, dir
	// 우선 거리가 가까워야 하고, 그 다음 방향 우선순위를 고려해야 함
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	// 현재 산타의 위치 정보
	int curSr = santa[sid].first;
	int curSc = santa[sid].second;

	for (int dir = 0; dir < 4; ++dir) {
		int newSr = curSr + dsr[dir];
		int newSc = curSc + dsc[dir];

		if (canGo(newSr, newSc)) {
			int dist = getDist(Rr, Rc, newSr, newSc);
			int prevDist = getDist(Rr, Rc, curSr, curSc);

			if (prevDist <= dist) continue; // 이동 가능하지만 가까워지지 않으면 이동 x

			pq.push(make_pair(dist, dir));
		}
	}

	if (pq.empty()) return -1; // 이동 가능한 위치가 없는 경우, -1 반환
	else return pq.top().second; // 이동 가능한 위치가 있는 경우, 해당 방향 반환
}

// -1인 경우는 다른 곳에서 처리
// 산타 이동하기
// 루돌프와 충돌 x -> 이동해서 저장
// 루돌프와 충돌 -> 점수 갱신 -> 방향 180도 회전 이동 -> 생존 여부 체크 -> 기절 처리 -> 상호작용
void moveSanta(int sid, int dir, int k) {
	// 현재 산타의 위치
	int curSr = santa[sid].first;
	int curSc = santa[sid].second;

	// 산타 자리 비우기
	graph[curSr][curSc] = 0;

	// 다음 산타의 위치
	int nxtSr = curSr + dsr[dir];
	int nxtSc = curSc + dsc[dir];

	// 루돌프가 있는 경우, 충돌 처리
	if (graph[nxtSr][nxtSc] == RUD) {
		// 점수 갱신
		score[sid] += D;

		dir = (dir + 2) % 4; // 180도 회전

		nxtSr = nxtSr + dsr[dir] * D;
		nxtSc = nxtSc + dsc[dir] * D;

		// 게임판 밖으로 나갔다면
		if (!inRange(nxtSr, nxtSc)) {
			isAlive[sid] = false;
			santa[sid] = make_pair(-1, -1);
			return;
		}
		// 게임판 안에 있는 경우, 기절 처리 -> 상호작용
		else {
			// 기절 처리
			isStunned[sid] = k + 2;

			// 밀려난 곳에 산타가 없다면 상호작용 없이 루돌프 이동 종료
			if (graph[nxtSr][nxtSc] == 0) {
				graph[nxtSr][nxtSc] = sid;
				santa[sid] = make_pair(nxtSr, nxtSc);
				return;
			}

			// 상호작용 -> 루돌프 다시 만날 일 없음 (해당 반대 방향으로 이동하므로)
			while (graph[nxtSr][nxtSc] > 0) {
				int tmp = graph[nxtSr][nxtSc];
				graph[nxtSr][nxtSc] = sid;
				santa[sid] = make_pair(nxtSr, nxtSc);
				sid = tmp;

				nxtSr += dsr[dir];
				nxtSc += dsc[dir];

				if (!inRange(nxtSr, nxtSc)) {
					isAlive[sid] = false; // 버퍼 오버런?
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

				// 상호작용은 스턴 x
			}
		}
	}
	// 루돌프가 없는 경우, 이동
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

	graph[Rr][Rc] = RUD; // 루돌프 위치 선정

	int sid, rr, cc; // 산타 번호, 위치 정보 입력 받기 위한 임시 변수
	for (int i = 0; i < P; ++i) {
		cin >> sid >> rr >> cc;
		santa[sid] = make_pair(rr, cc);
		graph[rr][cc] = sid;
		isAlive[sid] = true;
	}

	// 게임 시작
	for (int k = 1; k <= M; ++k) {
		int nxtDir = findNextPosRud();
		// 산타가 없는 경우, 게임 종료
		if (nxtDir == -1) {
			// 게임 종료
			break;
		}
		else {
			// 루돌프 이동
			moveRud(nxtDir, k);

			// 1번 산타부터 P번 산타 이동
			for (int i = 1; i <= P; ++i) {
				// 기절 상태의 산타, 탈락한 산타는 넘어가기
				if (isStunned[i] > k || !isAlive[i]) continue;

				// 다음 이동할 방향 구하기
				int nxtDir = findNextPosSanta(i);
				if (nxtDir == -1) continue; // 이동할 방향이 없는 경우
				moveSanta(i, nxtDir, k);
			}

			// 살아 있는 경우, 점수 추가
			for (int i = 1; i <= P; ++i)
				if (isAlive[i]) score[i]++;

			// 1턴 종료
		}
	}

	printScore();

	return 0;
}