#include <bits/stdc++.h>

#define fileopen(a, b) freopen(((std::string)a + ".inp").c_str(), "r", stdin); freopen(((std::string)b + ".out").c_str(), "w", stdout);
#define fileopen1(a) freopen(((std::string)a + ".inp").c_str(), "r", stdin); freopen(((std::string)a + ".out").c_str(), "w", stdout);

using namespace std;
#define ll long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef pair<ll,ll> ii;
ll const mod = 1e9 + 7, MAXN = 2e5 + 5,oo = 3e18;

ll tc;
char mat[200][200];
ii nearest[200][200][4];

int n,m;

int dx[]{-1,0,1,0};
int dy[]{0,1,0,-1};

bool vis[200][200][4];

bool inside (int i, int j){
	return i >= 1 && i <= n && j >= 1 && j <= m;
}

bool part1_custom(){

	for (int i = 1 ; i <= n ; i++){
		for (int j = 1 ; j <= m ; j++){
			for (int dir = 0 ; dir < 4 ; dir++){
				vis[i][j][dir] = false;
			}
		}
	}

	ii pos;
	int dir = 0;
	for (int i = 1 ; i <= n ; i++){
		for (int j = 1 ; j <= m ; j++){
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
				else if (mat[i][j] == '<'){
					dir = 3;
				}
				break;
			}
		}
	}


	while(true){

		if (vis[pos.fi][pos.se][dir] == true){
			return true;
		}

		vis[pos.fi][pos.se][dir] = true;

		ii next_pos = make_pair(pos.first + dx[dir],pos.second + dy[dir]);

		if (!inside(next_pos.fi,next_pos.se)){
			return false;
		}
		else {
			if (mat[next_pos.fi][next_pos.se] == '#'){
				dir = (dir + 1) % 4;
			}
			else {
				pos = next_pos;
				
			}
		}
	}

	return false;
}


void part1(){
	ii pos;
	int dir = 0;
	
	for (int i = 1 ; i <= n ; i++){
		for (int j = 1 ; j <= m ; j++){
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

	while (true){
		vis[pos.fi][pos.se][dir] = true;

		ii next_pos = make_pair(pos.first + dx[dir],pos.second + dy[dir]);

		if (!inside(next_pos.fi,next_pos.se)){
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
}

void caau(){
    // calm
	string line;
	while (getline(cin,line)){
		n++;
		for (int i = 1 ; i <= line.size() ; i++){
			mat[n][i] = line[i - 1];
		}
		m = line.size();
	}

	/*for (int i = 1 ; i <= n ; i++){
		for (int j = 1 ; j <= m ; j++){
			for (int dir = 0 ; dir < 4 ; dir++){
				
				if (dir == 1 || dir == 2) continue;

				if (mat[i][j] == '#'){
					nearest[i][j][dir] = mp(i,j);
					continue;
				}

				int di = i + dx[dir];
				int dj = j + dy[dir];

				if (!inside(di,dj)){
					nearest[i][j][dir] = mp(-1,-1);
				}
				else {
					nearest[i][j][dir] = nearest[di][dj][dir];
				}
			}
		}
	}

	for (int i = n ; i >= 1 ; i--){
		for (int j = m ; j >= 1 ; j--){
			for (int dir = 0 ; dir < 4 ; dir++){
				
				if (dir == 0 || dir == 3) continue;

				if (mat[i][j] == '#'){
					nearest[i][j][dir] = mp(i,j);
					continue;
				}

				int di = i + dx[dir];
				int dj = j + dy[dir];

				if (!inside(di,dj)){
					nearest[i][j][dir] = mp(-1,-1);
				}
				else {
					nearest[i][j][dir] = nearest[di][dj][dir];
				}
			}
		}
	}*/

	int cnt = 0;
	for (int i = 1 ; i <= n ; i++){
		for (int j = 1 ; j <= m ; j++){
			if (mat[i][j] == '.'){
				mat[i][j] = '#';
				cnt += part1_custom();
				mat[i][j] = '.';
			}
		}
	}

	cout << cnt << endl;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    tc = 1;
    while (tc--) caau();
}
