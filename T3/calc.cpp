#include<iostream>
#include <regex>
#include <string>
#include <ctype.h>
using namespace std;

// This must convert the double value to a readable separated fraction if it can be and a fraction if can't and a whole number if it is.
string decToFrac(double num){
	string fractionForm;
	// your code here...
	return fractionForm;
}

int main(){
	// The regex of the whole valid line
	regex lineRegex("(-?[0-9]*[+-/*]?-?[0-9]*) ([+-/*]) (-?[0-9]*[+-/*]?-?[0-9]*)");
	// The regax of each sub regex in the line which represent a rational part
	regex rational("(-?[0-9]*)([/]?)(-?[1-9][0-9]*)");
	// A number which can be +ve of -ve
	regex number("(-?[1-9][0-9]*)");
	// holds the rationals as a string and the operation at from 1-3 indices
	smatch matchingRationals;
	// The text he will input
	string text;
	getline(cin,text);
	// text = "-123/42 * 12/3";
	// The final number as a decimal value may be +ve of -ve
	double finalNum;

	if (regex_search(text, matchingRationals, lineRegex)){
		// Getting the two rationals from the line
		string minForm[2] = {matchingRationals[1],matchingRationals[3]};
		// The operation between the two rationals
		string mainOperation = matchingRationals[2];
		// Preparing the to rational values'variables
		double nums[2];
		// A for loop looping on each rational and calculating it's value
		for (int i = 0; i < 2; i++)
		{
			/* code */
			// holds each number in the rational
			smatch matchingNumbers;
			// case of it's a rational
			if(regex_search(minForm[i],matchingNumbers,rational)){
				if(stoi(matchingNumbers[3]) == 0){
					cout << "Can't divide by zero";
					return 1;
				} else {
					nums[i] = (double)stoi(matchingNumbers[1]) / stoi(matchingNumbers[3]);
				}
			}
			// case of it's a whole number as in docs of the dc.
			else if (regex_match(minForm[i],number)){
				nums[i] = stoi(minForm[i]);
			}
			// cout << nums[i] << " \n";
		}
		// Calculating the final number value
		if (mainOperation == "/"){
			if(nums[1] == 0){
				cout << "Can't divide by zero";
				return 1;
			} else {
				finalNum = nums[0] / nums[1];
			}
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

	}
	// Case of invalid input
	else {
		cout << "Please insert a valid calculation";
	}

}
