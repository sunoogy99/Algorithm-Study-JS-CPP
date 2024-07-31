// 수의 범위가 매우 큰 상태에서 수의 값과 상관 없이 대소 관계만 필요한 경우 이용하는 방법
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;

	vector<int> numbers(N);
	vector<int> v(N);
	for (int i = 0; i < N; i++) {
		cin >> numbers[i];
		v[i] = numbers[i];
	}

	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());

	for (int i = 0; i < N; i++) {
		numbers[i] = lower_bound(v.begin(), v.end(), numbers[i]) - v.begin();
	}

	for (const int num : numbers) {
		cout << num << ' ';
	}

	return 0;
}