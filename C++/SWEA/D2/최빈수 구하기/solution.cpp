#include <iostream>
#include <climits>
#include <map>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T;
	int test_case;
	int num;

	freopen("input.txt", "r", stdin);

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> num;

		map<int, int> mp;
		int score;

		for (int i = 0; i < 1000; ++i) {
			cin >> score;

			if (mp[score]) {
				mp[score]++;
			}
			else {
				mp[score] = 1;
			}
		}

		int res_score = -1;
		int max_count = 0;
		for (const pair<int, int> kv : mp) {
			if (kv.second > max_count) {
				max_count = kv.second;
				res_score = kv.first;
			}
			else if (kv.second == max_count && kv.first > res_score) {
				res_score = kv.first;
			}
		}

		cout << "#" << num << " " << res_score << '\n';
	}

	return 0;
}