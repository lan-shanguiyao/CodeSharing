#include<iostream>
#include<algorithm>
#include<utility>
using namespace std;
const int N = 1005;
const int K = 20;
const int A = 20;
struct Team {
	int time[K];	//通过时间
	int num[K];	  //提交次数
	int key;	//队伍序号
	int ans;	//罚时
	int count;	//正确题目个数
}T[N];
int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		T[i].key = i + 1;
		T[i].ans = T[i].count = 0;
		for (int j = 0; j < k; j++) {
			cin >> T[i].time[j] >> T[i].num[j];
		}
		//计算罚时与AC题目个数
		for (int l = 0; l < k; l++) {
			if (T[i].time[l] != 0 && T[i].num[l] != 0) {
				T[i].ans += (T[i].num[l] - 1) * A + T[i].time[l];
				//cout << "   " << T[i].ans << endl;
				T[i].count += 1;
			}
		}
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			//如果AC题目个数相等
			if (T[j].count == T[j + 1].count) {
				if (T[j].ans > T[j + 1].ans)
					swap(T[j], T[j + 1]);
			}
			//如果不相等
			if (T[j].count < T[j + 1].count) {
				swap(T[j], T[j + 1]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << T[i].key << endl;
	}
	return 0;
}
