#include<bits/stdc++.h>
using namespace std;

signed main(){
	vector<int> a,b;
	int x,y;
	while (cin >> x >> y){
		a.push_back(x);
		b.push_back(y);
	}

	sort(a.begin(),a.end());
	sort(b.begin(),b.end());

	long long ans = 0;
	for (int i = 0 ; i < a.size() ; i++){
		ans += abs(a[i] - b[i]);
	}

	cout << ans;
	return 0;
}
