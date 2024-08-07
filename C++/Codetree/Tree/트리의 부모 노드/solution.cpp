#include <iostream>
using namespace std;

int n;
int parent[100001];

int main() {
	cin >> n;

	int a, b;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;

		parent[b] = a;
	}

	for (int i = 2; i <= n; i++) {
		cout << parent[i] << '\n';
	}

	return 0;
}