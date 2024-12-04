#include <bits/stdc++.h>
using namespace std;

bool check (string s){
	return (s == "XMAS") || (s == "SAMX");
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

	for (int i = 0 ; i < n ; i++){
		for (int j = 0 ; j < m ; j++){
			string tmp = "";

			// horizontal
			for (int k = j ; k < j + 4 ; k++){
				if (k >= m){
					break;
				}
				tmp += mat[i][k];
			}
			if (check(tmp)){
				//cout << i << " " << j << " hori" << endl;
				cnt++;
			}

			tmp = "";

			// vertical
			for (int k = i ; k < i + 4 ; k++){
				if (k >= n){
					break;
				}
				tmp += mat[k][j];
			}

			if (check(tmp)){
				//cout << i << " " << j << " vertical" << endl;
				cnt++;
			}

			tmp = "";

			// diagonal
			for (int k = 0 ; k < 4 ; k++){
				if (i + k >= n || j + k >= m){
					break;
				}
				tmp += mat[i + k][j + k];
			}

			if (check(tmp)){
				//cout << i << " " << j << " diagonal" << endl;
				cnt++;
			}

			tmp = "";

			for (int k = 0 ; k < 4 ; k++){
				if (i + k >= n || j - k < 0){
					break;
				}
				tmp += mat[i + k][j - k];
			}

			if (check(tmp)){
				cnt++;
			}
		}
	}

	cout << cnt;
}

