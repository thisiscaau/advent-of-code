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

bool valid (vector<int> &nums, map<int,vector<int>> &edges){
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

	return validSequence;
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

		if (valid(nums,edges)){
			continue;
		}

		set<int> significantNodes;

		for (int num : nums){
			significantNodes.insert(num);

		}

		map<int,vector<int>> significantEdges;
		map<int,int> in_deg;

		for (int num : significantNodes){
			for (int oth : edges[num]){
				if (significantNodes.find(oth) != significantNodes.end()){
					in_deg[num]++;
					significantEdges[oth].push_back(num);
				}
			}
		}

		queue<int> q;
		vector<int> res;

		for (int num : significantNodes){
			if (in_deg.find(num) == in_deg.end()){
				// in_deg = 0
				q.push(num);
			}
		}

		while (!q.empty()){
			int num = q.front(); q.pop();
			res.push_back(num);
			for (int oth : significantEdges[num]){
				if (--in_deg[oth] == 0){
					q.push(oth);
				}
			}
		}

		sum += res[res.size() / 2];
	}

	cout << sum;
}

