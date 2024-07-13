#include <iostream>
#include <unordered_set>
using namespace std;

int N, M;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;

	unordered_set<int> sangun;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		sangun.insert(num);
	}

	cin >> M;

	for (int i = 0; i < M; i++) {
		int num;
		cin >> num;

		if (sangun.find(num) != sangun.end()) {
			cout << 1 << ' ';
		}
		else {
			cout << 0 << ' ';
		}
	}

	return 0;
}