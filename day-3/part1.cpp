// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
#include <cctype>
using namespace std;

enum State{
	EMPTY,
	MUL,
	FIRST,
	SECOND,

};



int main() {
	string input;
	input.assign(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());

	enum State currentState = EMPTY;

	string firstNum = "";
	string secondNum = "";

	string command = "mul";
	int commandPos = 0;

	long long ans = 0;

	for (char c : input){
		if (currentState == EMPTY){
			if (c == command[0]){
				currentState = MUL;
				commandPos = 1;
			}
		}
		else if (currentState == MUL){
			if (c != command[commandPos]){
				if (commandPos == int(command.size()) && c == '('){
					currentState = FIRST;
					commandPos = 0;
				}
				else {
					currentState = EMPTY;

					if (c == command[0]){
						currentState = MUL;
						commandPos = 1;
					}
				}
			}
			else{
				commandPos++;
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

				if (c == command[0]){
					currentState = MUL;
					commandPos = 1;
				}
			}
		}
		else if (currentState == SECOND){
			if (isdigit(c)){
				secondNum += c;
			}
			else if (c == ')' && secondNum.size() > 0){
				ans += stoi(firstNum) * stoi(secondNum);
				//cout << firstNum << " " << secondNum << endl;
				firstNum = "";
				secondNum = "";
				currentState = EMPTY;
			}
			else {
				firstNum = "";
				secondNum = "";
				currentState = EMPTY;

				if (c == command[0]){
					currentState = MUL;
					commandPos = 1;
				}
			}
		}
	}

	cout << ans;
}

