#include <bits/stdc++.h>
#include <sstream>
#include <string>
using namespace std;

vector<int> parse_list (string &s){
	vector<int> res;
	string num = "";
	for (char c : s){
		if (c == ','){
			if (num.size() > 0){
				res.push_back(stoi(num));
			}
			num = "";
		}
		else {
			num += c;
		}
	}
	if (num.size() > 0){
		res.push_back(stoi(num));
	}

	return res;
}

pair<int,int> parse_edge (string &s){
	pair<int,int> res;
	string num = "";
	for (char c : s){
		if (c == '|'){
			res.first = stoi(num);
			num = "";
		}
		else {
			num += c;
		}
	}
	res.second = stoi(num);

	return res;
}

int main() {
	string line;

	map<int,vector<int>> edges;

	while (getline(cin,line)){
		if (line.size() == 0){
			break;
		}
		pair<int,int> edge = parse_edge(line);
		edges[edge.second].push_back(edge.first);
	}

	long long sum = 0;

	while (getline(cin,line)){
		if (line.size() == 0){
			break;
		}
		
		vector<int> nums = parse_list(line);
		set<int> invalid;
		
		bool validSequence = true;

		for (int num : nums){
			if (invalid.find(num) != invalid.end()){
				validSequence = false;
				break;
			}

			for (int oth : edges[num]){
				invalid.insert(oth);
			}
		}

		if (validSequence){
			sum += nums[nums.size() / 2];
		}
	}

	cout << sum;
}

