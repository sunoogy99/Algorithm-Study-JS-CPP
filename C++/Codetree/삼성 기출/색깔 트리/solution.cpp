#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#define RED 1
#define ORANGE 2
#define YELLOW 3
#define GREEN 4
#define BLUE 5

int Q, mid, pid, color, maxDepth;
vector<int> roots; // 트리의 루트 노드 번호를 저장. 여러 개의 트리 존재함 -> 문제에서 간과한 부분...

// Node 정의
struct Node {
	int mid; // node id
	int pid; // parent id
	int color;
	int depth;
	vector<int> children;
	vector<set<int>> worth;

	Node(int m, int p, int c, int d) : mid(m), pid(p), color(c), depth(d) {
		worth.resize(6);
	}
};

Node* nodes[100001]; // 노드 정보

// 노드 추가 시, 부모 노드 정보 업데이트 함수
void updateParentNode(int pid, Node* child, bool isDel) {
	// 부모 노드 id가 -1인 경우, 진행 x
	if (pid == -1) return;

	Node* parent = nodes[pid];

	for (int i = 1; i < 6; ++i) {
		// 자식 노드에 색깔이 있는 경우
		if (child->worth[i].size() > 0) {
			// 부모 노드 색깔에 자식 노드 id 추가한다.
			parent->worth[i].insert(child->mid);
		}
		else {
			// 색깔 변경으로 가치 제거하는 경우
			if (isDel) {
				set<int>::iterator it = parent->worth[i].find(child->mid);
				if (it != parent->worth[i].end()) {
					parent->worth[i].erase(it);
				}
			}
		}
	}

	updateParentNode(parent->pid, parent, isDel);
}

// 노드 추가
void addNode(int mid, int pid, int color, int maxDepth) {
	// 루트 노드 등록
	if (pid == -1) {
		roots.push_back(mid);

		Node* newNode = new Node(mid, pid, color, maxDepth);

		newNode->worth[color].insert(mid);

		nodes[mid] = newNode;
	}
	else {
		// 부모 노드의 depth로 검증
		int pDepth = nodes[pid]->depth;
		if (pDepth - 1 <= 0) return;

		// depth는 부모 depth - 1로 갱신
		Node* newNode = new Node(mid, pid, color, min(maxDepth, pDepth - 1));

		// 가치 항목에 자신의 색깔 추가 (id로 추가)
		newNode->worth[color].insert(mid);

		nodes[mid] = newNode;

		nodes[pid]->children.push_back(mid);

		updateParentNode(pid, newNode, false);
	}
}

void updateChildNode(int mid, int color) {
	Node* curNode = nodes[mid];
	curNode->color = color;

	for (int i = 1; i < 6; ++i) {
		if (i != color) curNode->worth[i].clear();
		else curNode->worth[i].insert(curNode->mid);
	}

	for (int cid : curNode->children) {
		curNode->worth[color].insert(cid);
		updateChildNode(cid, color);
	}
}

// 색깔 변경
void changeColor(int mid, int color) {
	// 자식 노드 색깔, 가치 업데이트
	updateChildNode(mid, color);

	// 부모 노드 색깔, 가치 업데이트
	Node* curNode = nodes[mid];
	updateParentNode(curNode->pid, curNode, true);
}

// 색깔 조회
int retrieveColor(int mid) {
	return nodes[mid]->color;
}

// 노드의 가치 계산 결과를 반환하는 함수
int calculateWorth(int curId) {
	Node* curNode = nodes[curId];

	// 현재 노드의 가치 계산
	int cnt = 0;
	for (int i = 1; i < 6; ++i) {
		if (curNode->worth[i].size() > 0) {
			cnt++;
		}
	}

	return cnt * cnt;
}

// 트리 전체를 순회하여 가치 제곱의 합을 구하는 함수
int traversal(int curId) {
	Node* curNode = nodes[curId];

	int curWorth = calculateWorth(curId);

	for (int cid : curNode->children) {
		curWorth += traversal(cid);
	}

	return curWorth;
}

// 점수 조회 -> tree 순회
int retrieveScore() {
	int sum = 0;
	for (int rootId : roots) {
		sum += traversal(rootId);
	}
	return sum;
}

/*
	100. 노드 추가
	200. 색깔 변경
	300. 색깔 조회
	400. 점수 조회
*/

int main() {
	cin >> Q;

	int op;
	while (Q--) {
		cin >> op;

		if (op == 100) {
			cin >> mid >> pid >> color >> maxDepth;
			addNode(mid, pid, color, maxDepth);
		}
		else if (op == 200) {
			cin >> mid >> color;
			changeColor(mid, color);
		}
		else if (op == 300) {
			cin >> mid;
			cout << retrieveColor(mid) << '\n';
		}
		else if (op == 400) {
			cout << retrieveScore() << '\n';
		}
	}

	return 0;
}