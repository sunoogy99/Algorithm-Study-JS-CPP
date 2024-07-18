#include <iostream>
using namespace std;

int t;
int N;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> t;

	for (int i = 1; i <= t; i++) {
		cin >> N;
		cout << '#' << i << ' ' << N / 3 << '\n';
	}

	return 0;
}