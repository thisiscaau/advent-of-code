// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
#define fi first
#define se second
#define mp make_pair

bool goOut (ii pos, int n, int m){
	if (pos.fi < 0 || pos.fi >= n || pos.se < 0 || pos.se >= m){
		return true;
	}
	return false;
}

int main() {
	string line;
	vector<string> mat;
	while (getline(cin,line)){
		mat.push_back(line);
	}

	int n = mat.size();
	int m = mat[0].size();

	ii pos;
	int dir = 0;
	
	map<ii,bool> vis;

	for (int i = 0 ; i < n ; i++){
		for (int j = 0 ; j < m ; j++){
			if (mat[i][j] != '.' && mat[i][j] != '#'){
				pos = mp(i,j);
				if (mat[i][j] == '^'){
					dir = 0;
				}
				else if (mat[i][j] == '>'){
					dir = 1;
				}
				else if (mat[i][j] == 'v'){
					dir = 2;
				}
				else {
					dir = 3;
				}
			}
		}
	}

	int dx[] = {-1,0,1,0};
	int dy[] = {0,1,0,-1};
	int cnt = 0;

	while (true){
		if (vis.find(pos) == vis.end()){
			vis[pos] = true;
			cnt++;
		}

		ii next_pos = make_pair(pos.first + dx[dir],pos.second + dy[dir]);

		if (goOut(next_pos,n,m)){
			break;
		}
		else {
			if (mat[next_pos.fi][next_pos.se] == '#'){
				dir = (dir + 1) % 4;
				pos = make_pair(pos.first + dx[dir],pos.second + dy[dir]);
			}
			else {
				pos = next_pos;
			}
		}
	}

	cout << cnt;
}

