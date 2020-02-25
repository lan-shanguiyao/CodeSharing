#include<iostream>
#include<algorithm>
#define F 100
#define INF 10000000000
using namespace std;

int A[F][F];

int main() {
	int m, n;
	cin >> m >> n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			cin >> A[i][j];
	for (int i = 0; i < m; i++) {
		int s[F] = { INF };
		for (int j = 0; j < n; j++)
			s[j] = A[i][j];
		sort(s, s + n);
		int min = s[0];
		int flag = -1;
		for (int k = 0; k < n; k++) 
			if (A[i][k] == min)
				flag = k; //ÐÐ×îÐ¡
		for (int j = 0; j < m; j++)
			s[j] = A[j][flag];
		sort(s, s + m);
		int max = s[m - 1];
		if (max == A[i][flag])
			cout << A[i][flag];
	}
	return 0;
}
