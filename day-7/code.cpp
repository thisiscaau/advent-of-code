#include <bits/stdc++.h>
#include <sstream>
using namespace std;

vector<long long> parseLine (string &line){
	vector<long long> res;
	stringstream inp(line);
	string tmp;


	inp >> tmp; tmp.pop_back();
	res.push_back(stoll(tmp));

	while (inp >> tmp){
		res.push_back(stoi(tmp));
	}

	return res;
}

bool part1_backtrack (vector<long long> &equation, int pos, long long value){
	if (value > equation[0]){
		return false;
	}

	if (pos == equation.size() - 2){
		return value == equation[0];
	}

	return part1_backtrack(equation, pos + 1, value + equation[pos + 2]) || part1_backtrack(equation, pos + 1, value * equation[pos + 2]);
}

void part1(vector<string> &lines){
	long long sum = 0;

	for (string line : lines){
		vector<long long> equation = parseLine(line);
		if (part1_backtrack(equation,0,equation[1])){
			sum += equation[0];
		}
	}

	cout << sum << "\n";
}

bool part2_backtrack (vector<long long> &equation, int pos, long long value){
	if (value > equation[0]){
		return false;
	}

	if (pos == equation.size() - 2){
		return value == equation[0];
	}

	return part2_backtrack(equation, pos + 1, value + equation[pos + 2]) || part2_backtrack(equation, pos + 1, value * equation[pos + 2]) || part2_backtrack(equation, pos + 1, stoll(to_string(value) + to_string(equation[pos + 2])));
}

void part2(vector<string> &lines){
	long long sum = 0;

	for (string line : lines){
		vector<long long> equation = parseLine(line);
		if (part2_backtrack(equation,0,equation[1])){
			sum += equation[0];
		}
	}

	cout << sum << "\n";
}

int main() {
	string line;
	vector<string> lines;

	while (getline(cin,line)){
		lines.push_back(line);	
	}

	part1(lines);
	part2(lines);
}

