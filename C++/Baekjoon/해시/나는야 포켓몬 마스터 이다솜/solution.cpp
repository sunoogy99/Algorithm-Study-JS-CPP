#include <iostream>
#include <string>
#include <map>
using namespace std;

int N, M;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;

	map<int, string> findNameById;
	map<string, int> findIdByName;
	for (int i = 1; i <= N; i++) {
		string name;
		cin >> name;

		findNameById[i] = name;
		findIdByName[name] = i;
	}

	for (int i = 1; i <= M; i++) {
		string line;
		cin >> line;
		
		if (line[0] >= '0' && line[0] <= '9') {
			int id = stoi(line); // string to integer
			string ret = findNameById[id];
			cout << ret << '\n';
		}
		else {
			int ret = findIdByName[line];
			cout << ret << '\n';
		}
	}

	return 0;
}