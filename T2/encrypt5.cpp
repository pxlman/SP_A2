#include<iostream>
#include<ctype.h>
#include<string>
#define steady std::ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
using namespace std;
const string alpha = "abcdefghijklmnopqrstuvwxyz";
//const string zebra = "zebracdfghijklmnopqstuvwxy";
int ind(char c,string text){
	for (int i = 0; i < text.size(); i++){
		if (c == text[i]){
			return i;
		}
	}
	return -1;
}
// A function to encrypt a text to a zerba cipher
string encrypt(string tt,string zebra){
	string newString = "";
	for (int i = 0; i < tt.size(); i++){
		if(isalpha(tt[i])){
			if(tt[i] > 'Z'){
				newString += zebra[ind(tt[i],alpha)];
			} else {
				newString += char(zebra[ind(tt[i] + 32,alpha)] - 32);
			}
		} else {
			newString += tt[i];
		}
	}
	return newString;
}
// A function to decrypt a zerba cipher
string decrypt(string tt,string zebra){
	string newString = "";
	for (int i = 0; i < tt.size(); i++){
		if(isalpha(tt[i])){
			if(tt[i] > 'Z'){
				newString += alpha[ind(tt[i],zebra)];
			} else {
				newString += char(alpha[ind(tt[i] + 32,zebra)]-32);
			}
		} else {
			newString += tt[i];
		}
	}
	return newString;

}
bool isIn(char c, string t){
	for(char i:t){
		if (i == c){
			return true;
		}
	}
	return false;
}
string autoKeying(string key){
	string newAlpha = key;
	for(char c:alpha){
		if(!isIn(c,key)){
			newAlpha += c;
		}
	}
	return newAlpha;
}
void toZebra(){
	string text;
	cout << "Please insert the text to encrypt: ";
	getline(cin,text);
	string key="00000000000000000000000000000";
	while (key.size() > ('z'-'a')){
		cout << "Please insert the key to make a new alphabet: ";
		cin >> key;
	}
	cout << encrypt(text,autoKeying(key));
}
void fromZebra(){
	string text;
	cout << "Please insert the text to encrypt: ";
	getline(cin,text);
	string key="00000000000000000000000000000";
	while (key.size() > ('z'-'a')){
		cout << "Please insert the key to make a new alphabet: ";
		cin >> key;
	}
	cout << decrypt(text,autoKeying(key));
}
int main(){
	// run this to launch from zebra to alpha
	// toZebra();
	// run this to launch from alpha to zebra
	// fromZebra();
	return 0;
}
