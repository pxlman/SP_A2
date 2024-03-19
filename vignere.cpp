#include<iostream>
#include <regex>
#include <string>
#include <cmath>
#include <ctype.h>
using namespace std;

// A function to check if a text is alphanumeric and spaces or not
bool validPlainVig(string plain){
	for (int i = 0; i < plain.size(); i++)
	{
		if(!isalnum(plain[i]) && plain[i] != ' '){
			return false;
		}
	}
	return true;
}
// A function to convert any string to uppercases
void upperStr(string &mstr){
	for (int i = 0; i < mstr.size(); i++){
		mstr[i] = toupper(mstr[i]);
	}
}
// A function to convert a plain text with a key to vignere cipher
void toVignere(){
	string plain,key;
	// Getting the plain text from user
	cout << "Plain Text: ";
	getline(cin,plain);
	// While plain text is invalid
	while(!validPlainVig(plain)){
		cout << "Plain Text(Must be alphanumeric and spaces only): ";
		getline(cin,plain);
	}
	// Convert plain text to uppercases only
	upperStr(plain);
	// Getting the key from user
	cout << "Key: ";
	getline(cin,key);
	// while the key is invalid
	while(key.size() < plain.size() || !validPlainVig(key)){
		cout << "Key(Must be alphanumeric and spaces only): ";
		getline(cin,key);
	}
	// Convert key to uppercases only
	upperStr(key);
	string cipher = "";
	for (int i = 0; i < plain.size(); i++){
		if(isalpha(plain[i])){
			cipher += char('A' + (plain[i] + key[i])%26);
		}else {
			cipher += plain[i];
		}
	}
	cout << "Cipher: " << cipher;
}
// A function to convert a vignere cipher with a key to plain text
void fromVignere(){
	string cipher;
	string key;
	// Getting the plain text from user
	cout << "Cipher Text: ";
	getline(cin,cipher);
	// While the cipher is not valid
	while(!validPlainVig(cipher)){
		cout << "Cipher Text(Must be all alphanumeric and spaces): ";
		getline(cin,cipher);
	}
	upperStr(cipher);
	// Getting the key from user while it's not valid
	cout << "Key: ";
	getline(cin,key);
	while(key.size() < cipher.size() || !validPlainVig(key)){
		cout << "Key(must be all alphanumeric and spaces): ";
		getline(cin,key);
	}
	upperStr(key);
	string plain = "";
	// For each char in the cipher
	for (int i = 0; i < cipher.size(); i++){
		// If a char is an alphabatic
		if(isalpha(cipher[i])){
			int val;
			// The invers of the mathmatical operation we encrypted it with
			val = cipher[i] - 65;
			val -= key[i];
			while(val < 65){
				val += 26;
			}
			plain += char(val);
		}else {
			// if it's not an alphabet
			plain += char(cipher[i]);
		}
	}
	// printing out the plain text
	cout << "Plain: " << plain;

}
