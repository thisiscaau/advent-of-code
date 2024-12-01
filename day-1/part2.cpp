#include<bits/stdc++.h>
using namespace std;

signed main(){
	vector<int> a;
	unordered_map<int,int> b;

	int x,y;

	while (cin >> x >> y){
		a.push_back(x);
		b[y]++;
	}

	long long ans = 0;

	for (int num : a){
		ans += num * b[num];
	}

	cout << ans;

	return 0;
}
