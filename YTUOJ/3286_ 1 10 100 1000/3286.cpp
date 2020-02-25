#include<iostream>
#include<algorithm>
using namespace std;
int arr[100001];
int main() {
	arr[0] = 0;
	int i = 1;
	for (i = 1;; i++) {
		arr[i] = (i * (i + 1)) / 2;
		if ((i * (i + 1)) / 2 > 85000000)
			break;
	}
	int T;
	cin >> T;
	while (T--) {
		long long int m;
		cin >> m;
		if (m - arr[lower_bound(arr, arr + i, m) - arr - 1] == 1)
			cout << "1" << endl;
		else
			cout << "0" << endl;
	}
	return 0;
}
