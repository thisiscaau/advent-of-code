#include <bits/stdc++.h>
#include <sstream>
using namespace std;

int main() {
	string line;
	int cnt = 0;

	while (getline(cin,line)){
		stringstream inp(line);
		
		vector<int> num;
		int x;
		while (inp >> x){
			num.push_back(x);
		}

		int n = num.size();

		vector<int> prefixDirection(n,0);
		vector<int> suffixDirection(n,0);

		// 0 = not safe, 1 = increasing, -1 = decreasing, 2 = single number
		prefixDirection[0] = 2;
		for (int i = 1 ; i < n ; i++){
			int dif = num[i] - num[i - 1];
			
			if (abs(dif) < 1 || abs(dif) > 3){
				prefixDirection[i] = 0;
				continue;
			}

			if (i == 1){
				if (num[i] > num[i - 1]){
					prefixDirection[i] = 1;
				}
				else if (num[i] < num[i - 1]){
					prefixDirection[i] = -1;
				}
				else {
					prefixDirection[i] = 0;
				}
				continue;
			}

			if (prefixDirection[i - 1] == 0){
				prefixDirection[i] = 0;
				continue;
			}

			if ((dif * prefixDirection[i - 1]) < 0){
				prefixDirection[i] = 0;
			}
			else {
				prefixDirection[i] = prefixDirection[i - 1];
			}
		}

		suffixDirection[n - 1] = 2;
		for (int i = n - 2 ; i >= 0 ; i--){
			int dif = num[i + 1] - num[i];
			if (abs(dif) < 1 || abs(dif) > 3){
				suffixDirection[i] = 0;
				continue;
			}

			if (i == (n - 2)){
				if (num[i] > num[i + 1]){
					suffixDirection[i] = -1;
				}
				else if (num[i] < num[i + 1]){
					suffixDirection[i] = 1;
				}
				else {
					suffixDirection[i] = 0;
				}
				continue;
			}

			if (suffixDirection[i + 1] == 0){
				suffixDirection[i] = 0;
				continue;
			}

			if (dif * suffixDirection[i + 1] < 0){
				suffixDirection[i] = 0;
			}
			else {
				suffixDirection[i] = suffixDirection[i + 1];
			}
		}

		if (suffixDirection[0] != 0){
			// no need for modification
			cnt++;
			continue;
		}

		bool safe = false;

		for (int i = 0 ; i < n ; i++){
			if (i == 0){
				if (suffixDirection[i + 1] != 0){
					safe = true;
					break;
				}
				continue;
			}

			if (i == n - 1){
				if (prefixDirection[i - 1] != 0){
					safe = true;
					break;
				}
				continue;
			}

			int leftDirection = prefixDirection[i - 1];
			int rightDirection = suffixDirection[i + 1];
			int dif = num[i + 1] - num[i - 1];

			if ((leftDirection == 0) || (rightDirection == 0) || abs(dif) > 3 || abs(dif) < 1){
				continue;
			}

			if (leftDirection == rightDirection){
				if (leftDirection == 2){
					safe = true;
					break;
				}

				if (dif * leftDirection > 0){
					safe = true;
					break;
				}
			}
			else {

				if ((leftDirection != 2) && (rightDirection != 2)){
					continue;
				}

				if (leftDirection == 2 && (dif * rightDirection) > 0){
					safe = true;
					break;
				}

				if (rightDirection == 2 && (dif * leftDirection) > 0){
					safe = true;
					break;
				}
			}
		}

		cnt += safe;
	}

	cout << cnt;
}

