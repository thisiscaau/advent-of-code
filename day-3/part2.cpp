#include <bits/stdc++.h>
#include <cctype>
using namespace std;

enum State{
	EMPTY,
	COMMAND,
	FIRST,
	SECOND,
	OPEN,
	CLOSE
};

vector<string> Commands{"mul","do","don't"};

bool matchingCommand (string c){
	int sz = c.size();

	for (string command : Commands){
		if (c == command.substr(0,sz)){
			return true;
		}
	}

	return false;
}

int main() {
	string input;
	input.assign(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());

	enum State currentState = EMPTY;

	string firstNum = "";
	string secondNum = "";

	string command = "";

	long long ans = 0;
	bool add = true;

	for (char c : input){
		if (currentState == COMMAND){

			if (c == '('){
				string selectedCommand = "";
				for (string s : Commands){
					if (command == s){
						selectedCommand = s;
						break;
					}
				}

				if (selectedCommand == ""){
					currentState = EMPTY;
				}
				else {
					currentState = OPEN;
				}
			}
			else {
				command += c;
				if (matchingCommand(command) == false){
					command = "";
					currentState = EMPTY;
				}
			}
		}
		else if (currentState == OPEN){
			if (isdigit(c)){
				firstNum += c;
				currentState = FIRST;
			}
			else if (c == ')'){
				if (command == "do"){
					add = true;
				}
				else if (command == "don't"){
					add = false;
				}
				else {
					currentState = EMPTY;
				}
			}
			else {
				currentState = EMPTY;
			}
		}
		else if (currentState == FIRST){
			if (isdigit(c)){
				firstNum += c;
			}
			else if (c == ',' && firstNum.size() > 0){
				currentState = SECOND;
			}
			else {
				firstNum = "";
				secondNum = "";
				currentState = EMPTY;
			}
		}
		else if (currentState == SECOND){
			if (isdigit(c)){
				secondNum += c;
			}
			else if (c == ')' && secondNum.size() > 0){
				ans += stoi(firstNum) * stoi(secondNum) * add;
				firstNum = "";
				secondNum = "";
				currentState = EMPTY;
				continue;
			}
			else {
				firstNum = "";
				secondNum = "";
				currentState = EMPTY;
			}
		}

		if (currentState == EMPTY){
			command = "";
			if (matchingCommand(command + c)){
				currentState = COMMAND;
				command += c;
			}
		}
	}

	cout << ans;
}

