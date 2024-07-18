#include <iostream>
#include <climits>
#include <cstring>
using namespace std;

int T, N, P;
int groupElement[101];

unsigned long long findMax() {
	for (int i = 1; i <= P; i++) {
		groupElement[i] += N / P;
	}

	// 나머지 균등 분배 -> 곱의 최대 경우 나옴
	int remain = N % P;
	for (int i = 1; i <= remain; i++) {
		groupElement[i] += 1;
	}

	unsigned long long sum = 1;
	for (int i = 1; i <= P; i++) {
		sum *= groupElement[i];
	}

	return sum;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;

	for (int i = 1; i <= T; i++) {
		cin >> N >> P;

		memset(groupElement, 0, sizeof(groupElement));
		unsigned long long maxVal = findMax();
		cout << '#' << i << ' ' << maxVal << '\n';
	}

	return 0;
}