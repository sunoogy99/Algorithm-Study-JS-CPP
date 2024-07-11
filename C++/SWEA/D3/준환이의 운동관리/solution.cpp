#include <iostream>
using namespace std;

int t;
int L, U, X;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> t;

	for (int i = 1; i <= t; i++) {
		cin >> L >> U >> X;
		int ret = (X < L) ? (L - X) : (X <= U ? 0 : -1);
		cout << '#' << i << ' ' << ret << '\n';
	}

	return 0;
}