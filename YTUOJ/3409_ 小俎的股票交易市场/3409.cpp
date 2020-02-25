#include<iostream>
#include<algorithm>
using namespace std;
const int N = 35;
int main() {
	int n, m, r;
	cin >> n >> m >> r;
	int s[N], b[N];
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	for (int j = 0; j < m; j++) {
		cin >> b[j];
	}
	sort(s, s + n);
	sort(b, b + m);
	//不购买的情况
	if (s[0] >= b[m - 1]) {
		cout << r << endl;
		return 0;
	}
	cout << r / s[0] * b[m - 1] + r % s[0] << endl;
	return 0;
}
