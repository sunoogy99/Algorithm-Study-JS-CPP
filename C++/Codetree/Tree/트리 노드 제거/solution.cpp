#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n;
vector<vector<int>> tree;
vector<int> parent; // �� ����� �θ� ��带 ����
vector<bool> alive; // ��� ���� �� ��� �ִ� ���� �ε��� ���
queue<int> delq; // ������ ������ �����ϴ� ť

int main() {
	cin >> n;

	tree.resize(n);
	parent.resize(n);
	alive.resize(n, true);

	int par; // �θ� ��� ��ȣ
	for (int i = 0; i < n; i++) {
		cin >> par;

		parent[i] = par;

		if (par == -1) continue; // ��Ʈ ����� ���, �Ѿ��
		tree[par].push_back(i);
	}

	int delNode;
	cin >> delNode; // ������ ��� �Է�

	delq.push(delNode);
	
	par = parent[delNode];

	// ���� ��尡 ��Ʈ ��尡 �ƴ� ���
	if (par != -1) {
		// �θ� ��忡�� �ش� ��� ����
		auto it = find(tree[par].begin(), tree[par].end(), delNode);
		if (it != tree[par].end())
			tree[par].erase(it);
	}

	while (!delq.empty()) {
		int dNode = delq.front();
		delq.pop();
		alive[dNode] = false; // Ž�� ������ ��忡�� ���� ���� ����

		for (int c : tree[dNode]) {
			delq.push(c);
		}
	}

	int leafCnt = 0;
	for (int i = 0; i < n; i++) {
		if (alive[i] && tree[i].size() == 0)
			leafCnt++;
	}

	cout << leafCnt;
	return 0;
}