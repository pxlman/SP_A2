#include<iostream>
#include<regex>
using namespace std;

const string alpha = "abcdefgkijklmnopqrstuvwxyz";
const string zebra = "zebracdfghijklmnopqstuvwxy";
int ind(char c,string text){
	for (int i = 0; i < text.size(); i++){
		if (c == text[i]){
			return i;
		}
	}
	return -1;
}
// A function to encrypt a text to a zerba cipher
string encrypt(string tt){
	string newString = "";
	for (int i = 0; i < tt.size(); i++){
		newString = newString + zebra[ind(tt[i],alpha)];
	}
	return newString;
}
// A function to decrypt a zerba cipher
string decrypt(string tt){
	string newString = "";
	for (int i = 0; i < tt.size(); i++){
		newString = newString + alpha[ind(tt[i],zebra)];
	}
	return newString;

}
int zebraCipher(){
	string tt;
	cout << "Please insert the text to encrypt: ";
	cin >> tt;
	cout << decrypt(tt);
}
