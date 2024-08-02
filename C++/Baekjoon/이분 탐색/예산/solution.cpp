#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

long long N, M;
vector<long long> costs;

// 상한가 기준으로 예산 나눠줄 수 있는지 여부를 반환하는 함수
bool checkEnough(long long upLimit) {
	long long sum = 0;
	for (int i = 0; i < N; i++) {
		sum += min(upLimit, costs[i]);
	}

	if (sum <= M) return true;
	else return false;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;

	costs.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> costs[i];
	}

	cin >> M;

	sort(costs.begin(), costs.end());

	long long start = 1; // costs[0]으로 설정하면 M이 costs[0]보다 작은 경우 이상한 값이 출력됨
	long long end = costs[N - 1];

	long long ans;
	while (start <= end) {
		long long mid = start + (end - start) / 2;
		
		if (checkEnough(mid)) {
			ans = mid;
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}

	cout << ans << '\n';
	return 0;
}