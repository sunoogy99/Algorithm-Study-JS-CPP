#include <iostream>
#include <string>
using namespace std;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
string oper;

int main() {
    cin >> oper;

    int moveIdx = 0; // ºÏÂÊ ¹æÇâ
    pair<int, int> pos = { 0, 0 };
    for (int i = 0; i < oper.length(); i++) {
        if (oper[i] == 'L') {
            moveIdx = (moveIdx + 3) % 4;
        }
        else if (oper[i] == 'R') {
            moveIdx = (moveIdx + 1) % 4;
        }
        else {
            pos.first += dx[moveIdx];
            pos.second += dy[moveIdx];
        }
    }
    
    cout << pos.first << ' ' << pos.second << '\n';
    return 0;
}