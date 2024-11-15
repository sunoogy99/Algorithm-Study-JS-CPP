#include <iostream>
#include <string>

using namespace std;

#define TESTCASE 10

// 완전 탐색 가능
// KMP 알고리즘 써서 풀이도 가능 -> D3에서는 완탐으로 풀어보기

int find_pattern(string str, string pattern) {
	int s_len = str.length();
	int p_len = pattern.length();
	int res = 0;

	for (int i = 0; i <= s_len - p_len; ++i) {
		bool isEqual = true;

		for (int j = 0; j < p_len; ++j) {
			if (str[i + j] != pattern[j]) {
				isEqual = false;
				break;
			}
		}

		if (isEqual) {
			res++;
		}
	}

	return res;
}

int main(int argc, char** argv)
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int test_case;
	int num;

	freopen("test_input.txt", "r", stdin);

	for (test_case = 1; test_case <= TESTCASE; ++test_case)
	{
		cin >> num;

		string str, pattern;
		cin >> pattern;
		cin >> str;

		int ans = find_pattern(str, pattern);

		cout << "#" << num << " " << ans << '\n';
	}

	return 0;
}