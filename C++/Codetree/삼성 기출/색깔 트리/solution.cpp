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
vector<int> roots; // Ʈ���� ��Ʈ ��� ��ȣ�� ����. ���� ���� Ʈ�� ������ -> �������� ������ �κ�...

// Node ����
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

Node* nodes[100001]; // ��� ����

// ��� �߰� ��, �θ� ��� ���� ������Ʈ �Լ�
void updateParentNode(int pid, Node* child, bool isDel) {
	// �θ� ��� id�� -1�� ���, ���� x
	if (pid == -1) return;

	Node* parent = nodes[pid];

	for (int i = 1; i < 6; ++i) {
		// �ڽ� ��忡 ������ �ִ� ���
		if (child->worth[i].size() > 0) {
			// �θ� ��� ���� �ڽ� ��� id �߰��Ѵ�.
			parent->worth[i].insert(child->mid);
		}
		else {
			// ���� �������� ��ġ �����ϴ� ���
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

// ��� �߰�
void addNode(int mid, int pid, int color, int maxDepth) {
	// ��Ʈ ��� ���
	if (pid == -1) {
		roots.push_back(mid);

		Node* newNode = new Node(mid, pid, color, maxDepth);

		newNode->worth[color].insert(mid);

		nodes[mid] = newNode;
	}
	else {
		// �θ� ����� depth�� ����
		int pDepth = nodes[pid]->depth;
		if (pDepth - 1 <= 0) return;

		// depth�� �θ� depth - 1�� ����
		Node* newNode = new Node(mid, pid, color, min(maxDepth, pDepth - 1));

		// ��ġ �׸� �ڽ��� ���� �߰� (id�� �߰�)
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

// ���� ����
void changeColor(int mid, int color) {
	// �ڽ� ��� ����, ��ġ ������Ʈ
	updateChildNode(mid, color);

	// �θ� ��� ����, ��ġ ������Ʈ
	Node* curNode = nodes[mid];
	updateParentNode(curNode->pid, curNode, true);
}

// ���� ��ȸ
int retrieveColor(int mid) {
	return nodes[mid]->color;
}

// ����� ��ġ ��� ����� ��ȯ�ϴ� �Լ�
int calculateWorth(int curId) {
	Node* curNode = nodes[curId];

	// ���� ����� ��ġ ���
	int cnt = 0;
	for (int i = 1; i < 6; ++i) {
		if (curNode->worth[i].size() > 0) {
			cnt++;
		}
	}

	return cnt * cnt;
}

// Ʈ�� ��ü�� ��ȸ�Ͽ� ��ġ ������ ���� ���ϴ� �Լ�
int traversal(int curId) {
	Node* curNode = nodes[curId];

	int curWorth = calculateWorth(curId);

	for (int cid : curNode->children) {
		curWorth += traversal(cid);
	}

	return curWorth;
}

// ���� ��ȸ -> tree ��ȸ
int retrieveScore() {
	int sum = 0;
	for (int rootId : roots) {
		sum += traversal(rootId);
	}
	return sum;
}

/*
	100. ��� �߰�
	200. ���� ����
	300. ���� ��ȸ
	400. ���� ��ȸ
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