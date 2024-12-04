#include <bits/stdc++.h>
using namespace std;

bool check (string s){
	return (s == "MAS") || (s == "SAM");
}

int main() {

	string s;
	vector<string> mat;
	while (getline(cin,s)){
		mat.push_back(s);
	}

	int n = mat.size();
	int m = mat[0].size();

	int cnt = 0;

	for (int i = 1 ; i < n - 1 ; i++){
		for (int j = 1 ; j < m - 1; j++){
			string tmp1 = "";
			tmp1 += mat[i - 1][j - 1];
			tmp1 += mat[i][j];
			tmp1 += mat[i + 1][j + 1];

			string tmp2 = "";
			tmp2 += mat[i + 1][j - 1];
			tmp2 += mat[i][j];
			tmp2 += mat[i - 1][j + 1];
			if (check(tmp1) && check(tmp2)){
				cnt++;
			}
		}
	}

	cout << cnt;
}

