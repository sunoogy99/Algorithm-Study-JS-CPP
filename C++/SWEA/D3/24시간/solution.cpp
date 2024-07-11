#include <iostream>
using namespace std;

int t;
int a, b;

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin >> t;

    for (int i = 1; i <= t; i++) {
        cin >> a >> b;
        cout << '#' << i << ' ' << (a + b) % 24 << '\n';
    }

    return 0;
}