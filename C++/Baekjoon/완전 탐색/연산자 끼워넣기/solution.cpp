#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
using namespace std;

#define ADD 0
#define SUB 1
#define MUL	2
#define DIV	3

int N;
int numbers[12];
int oper[4];

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> numbers[i];
	}

	for (int i = 0; i < 4; i++) {
		cin >> oper[i];
	}

	string operString = "";
	char operChar[4] = { '+', '-', '*', '/' };
	for (int i = 0; i < 4; i++) {
		// 문자 여러 번 반복해서 추가하는 방법 string(횟수, 반복할 문자)
		operString += string(oper[i], operChar[i]);
	}

	// next_permutation을 사용할 때 정렬해서 사용해야 모든 경우의 수에 대해 탐색할 수 있음
	// 정렬 시 참고 사항 - ASCII CODE 순서 - *, +, -, /
	sort(operString.begin(), operString.end());

	int maxVal = INT_MIN;
	int minVal = INT_MAX;
	do {
		int val = numbers[0]; // 초기값
		for (int i = 0; i < operString.length(); i++) {
			int val2 = numbers[i + 1];
			if (operString[i] == '+') {
				val = val + val2;
			}
			else if (operString[i] == '-') {
				val = val - val2;
			}
			else if (operString[i] == '*') {
				val = val * val2;
			}
			else if (operString[i] == '/') {
				val = val / val2;
			}
		}

		maxVal = max(val, maxVal);
		minVal = min(val, minVal);
	} while (next_permutation(operString.begin(), operString.end()));

	cout << maxVal << '\n' << minVal << '\n';
	return 0;
}