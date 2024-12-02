#include <bits/stdc++.h>
#include <sstream>
using namespace std;

int main() {
	string line;
	int cnt = 0;

	while (getline(cin,line)){
		stringstream inp(line);
		
		int num;
		inp >> num; // read in first number
		int previous_number = num;

		bool safe = true;
		int direction = 0; // 0 = tba, 1 = increasing, -1 = decreasing

		while (inp >> num){
			if (!safe){
				continue;
			}

			if (direction == 0){
				if (num > previous_number){
					direction = 1;
				}
				else if (num < previous_number){
					direction = -1;
				}
			}
			
			int dif = num - previous_number;

			if (abs(dif) < 1 || abs(dif) > 3 || (dif * direction) <= 0){
				safe = false;
				continue;
			}

			previous_number = num;
		}

		cnt += safe;
	}

	cout << cnt;
}

