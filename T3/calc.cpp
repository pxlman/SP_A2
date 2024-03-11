#include<iostream>
#include <regex>
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
	regex lineRegex("-?[0-9]*[+-/*]?-?[0-9]* [+-/*] -?[0-9]*[+-/*]?-?[0-9]*");
	regex rational("-?[0-9]*[+-/*]?-?[0-9]*");
	regex midOperation(" [*/+-] ");
	regex operation("[-+/*]");
	regex number("-?[1-9][0-9]*");
	smatch matchingRationals;
	string text;
	text = "-123/42 * 12/3";

	int num1,num2;
	char mOperation;


	regex_search(text.cbegin(),text.cend(), matchingRationals, rational);
	for(string i: matchingRationals){
		cout << i << '\n';
	}

}
