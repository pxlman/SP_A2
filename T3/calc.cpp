#include<iostream>
#include <regex>
#include <string>
#include <ctype.h>
using namespace std;

int indS(string t){
	for (int i = 0; i < t.size(); i++)
	{
		if('/' == t[i]){
			return i;
		}
	}
	return -1;
}

// auto cmatchToArr(std::cmatch &match){
// 	string arr[match.size()];
// 	for (int i = 0; i < match.size(); i++)
// 	{
// 		arr[i] = match.str(i);
// 	}
// 	return arr;
// }

int main(){
	regex lineRegex("(-?[0-9]*[+-/*]?-?[0-9]*) ([+-/*]) (-?[0-9]*[+-/*]?-?[0-9]*)");
	regex rational("(-?[0-9]*)([/]?)(-?[0-9]*)");
	// regex midOperation(" [*/+-] ");
	regex operation("[-+/*]");
	regex number("(-?[1-9][0-9]*)");
	smatch matchingRationals;
	string text;
	text = "-123/42 * 12/3";

	int num1,num2;
	char mOperation;
	double finalNum;

	if (regex_search(text, matchingRationals, lineRegex)){
		// Getting the two rationals from the line
		string minForm[2] = {matchingRationals[1],matchingRationals[3]};
		// The operation between the two rationals
		string mainOperation = matchingRationals[2];
		// Preparing the to rational values'variables
		double nums[2];
		for (int i = 0; i < 2; i++)
		{
			/* code */
			smatch matchingNumbers;
			if(regex_search(minForm[i],matchingNumbers,rational)){
				nums[i] = (double)stoi(matchingNumbers[1]) / stoi(matchingNumbers[3]);
			} else if (regex_match(minForm[i],number)){
				nums[i] = stoi(minForm[i]);
			}
			// cout << nums[i] << " \n";
		}
		if (mainOperation == "/"){
			finalNum = nums[0] / nums[1];
		}
		else if (mainOperation == "*"){
			finalNum = nums[0] * nums[1];
		}
		else if (mainOperation == "-"){
			finalNum = nums[0] - nums[1];
		}
		else if (mainOperation == "+"){
			finalNum = nums[0] + nums[1];
		}
		cout << finalNum;

	} else {
		cout << "Please insert a valid calculation";
	}

}
