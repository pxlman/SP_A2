// FCAI – Structured Programming – 2024 - Assignment 2
// File:  CS112_A2_T2_S21,22_20230227_20230005_20230062.cpp
// Purpose: Encrypt and Decrypt programs
// section number : All of us in S21,22
// Author,ID,Emails and Parts done:
// 1) Ahmed Ashraf Lotfy - 20230005 - agxgv7573@gmail.com - Cipher5
// 2) Islam Waleed Salah - 20230062 - islamalshaer@gmail.com - Cipher2
// 3) Abdullah Ali Kamal - 20230227 - aakak123456789@gmail.com - Cipher7



#include <iostream>
#include <map>
#include <vector>
#include "string"
#include <ctype.h>

using namespace std;

// **Morse code(Cipher 7) functions**

// Initialize a map to store Morse code of each character
map<string, string> morseCode = {
        {"A", ".-"}, {"B", "-..."}, {"C", "-.-."}, {"D", "-.."}, {"E", "."}, {"F", "..-."},
        {"G", "--."}, {"H", "...."}, {"I", ".."}, {"J", ".---"}, {"K", "-.-"}, {"L", ".-.."},
        {"M", "--"}, {"N", "-."}, {"O", "---"}, {"P", ".--."}, {"Q", "--.-"}, {"R", ".-."},
        {"S", "..."}, {"T", "-"}, {"U", "..-"}, {"V", "...-"}, {"W", ".--"}, {"X", "-..-"},
        {"Y", "-.--"}, {"Z", "--.."}, {" ", " "}, {".", ".-.-.-"}, {",", "--..--"}, {"?", "..--.."},
        {"!", "-.-.--"}, {"0", "-----"}, {"1", ".----"}, {"2", "..---"}, {"3", "...--"},
        {"4", "....-"}, {"5", "....."}, {"6", "-...."}, {"7", "--..."}, {"8", "---.."},
        {"9", "----."}
};


// Function to reverse the key-value pairs in the map
map<string, string> reverse_map(map<string, string> original_map) {
    map<string, string> reversed_map;
    for (const auto& pair : original_map) {
        reversed_map[pair.second] = pair.first;
    }
    return reversed_map; // Return the reversed map
}



// Function to convert a string of text into Morse code
void convert_to_morse(string& text) {
    vector<string> ans;
    bool is_space = true; // Flag to track if there is a space
    for (char c : text) {
        if(c == ' ' && is_space){
            ans.push_back(" ");
            is_space = false;
        }
        // Check if the character exists in the Morse code map
        if (morseCode.find(string(1, toupper(c))) != morseCode.end()) {
            // If found, add its Morse code representation to the ans vector
            ans.push_back(morseCode[string(1, toupper(c))]);
            ans.push_back(" ");
        }
        else {
            // If not found, add a ?
            ans.emplace_back("?");
        }
    }
    // print the ans
    cout << "morse code: ";
    for(auto symbol: ans){
        cout << symbol;
    }
    cout << endl;
}

// Function to split a string into substrings based on a delimiter
vector<string> split(string text, string deli) {
    int deliLength = deli.size();
    int found = -1;
    vector<string> output;
    string item = "";
    string tillFail = "";
    for (int i = 0; i < text.size(); ++i) {
        if(found == deliLength - 1) {
            output.push_back(item); // Add the substring to the output vector
            item = ""; // Reset the temporary string
            found = -1; // Reset the delimiter index
            tillFail = ""; // Reset the temporary string for unmatched characters
        }
        if (text[i] == deli[found + 1]) {
            found += 1; // Increment delimiter index
            tillFail += text[i]; // Add character to temporary string for unmatched characters
        } else {
            found = -1; // Reset delimiter index
            item += tillFail; // Add unmatched characters to the substring
            tillFail = ""; // Reset temporary string for unmatched characters
            item += text[i]; // Add current character to the substring
        }
    }
    output.push_back(item); // Add the last substring to the output vector
    return output;
}

// Function to convert Morse code to text
void convert_to_text(string& morseline) {
    map<string,string> reversed_map = reverse_map(morseCode); // Reverse the morseCode map

    vector<string> output;

    // Decode each Morse code symbol and form words
    for (auto word: split(morseline, "   ")) { // split morse code into words
        for (auto symbol: split(word, " ")) { // split each word into symbols
            // Check if the symbol exists in the reversed map
            if(reversed_map.find(symbol) != reversed_map.end()) {
                output.push_back(reversed_map[symbol]); //  decode Morse code
            }
            else {
                output.push_back("?"); // If not found, add a ?
            }
        }
        output.push_back(" "); //  space between words
    }
    cout << "Text: ";
    for(auto ch: output){
        cout << ch;
    }
    cout << endl;

}



// **Cipher 2 Functions**

/*
 * Main idea :
 *      use the ascii value to convert A to Z and so on
 *      It is easy to configure this equation for encrypting as we take the second letter from the end if the letter is B for example
 *      and the third from the end if the letter is C for example, and we can apply that to all elements
 *      Z - ( (the letter) - A )
 *
 *      for decipher:
 *          (Z - the letter) + A
 *          as we say Y is the second letter from the end, so we revert it to the second letter from
 *          the start, and we can apply that to all letter and the equation still works
 * */

//function for encrypting
void encrypt_cipher2(string & message){
    string encrypted;
    for (char ch : message){
        //we leave the special characters and numbers as is
        if (not isalpha(ch)){
            encrypted += ch;
            continue;
        }
        //we suppose that the normal case that the letter is lower case
        char last_letter = 'z';
        char first_letter = 'a';
        //if it is upper we just change the values but the same equation happens
        if (isupper(ch)){
            last_letter = 'Z';
            first_letter ='A';
        }
        //the equation is described above
        encrypted += (char) (last_letter - (ch - first_letter));
    }
    //too obvious to be explained lol :)
    cout << "encrypted: " << encrypted << endl;
}


void decypher_cipher2(string message){

    string decrypted;

    for (char ch : message){
        if(not isalpha(ch)){
            decrypted += ch;
            continue;
        }

        //we suppose that the normal case that the letter is lower case
        char last_letter = 'z';
        char first_letter = 'a';
        //if it is upper we just change the values but the same equation happens
        if (isupper(ch)){
            last_letter = 'Z';
            first_letter ='A';
        }
        //the equation itself
        decrypted += (char)  ((last_letter - ch) + first_letter);

    }
    cout << "decrypted: " << decrypted << endl;

}


// **Cipher 5 functions**

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
void toZebra(string& text){
    string key="00000000000000000000000000000";
    while (key.size() > ('z'-'a')){
        cout << "Please insert the key to make a new alphabet: ";
        cin >> key;
    }
    cout << "encrypted: " << encrypt(text,autoKeying(key)) << endl;
}
void fromZebra(string& text){
    string key="00000000000000000000000000000";
    while (key.size() > ('z'-'a')){
        cout << "Please insert the key to make a new alphabet: ";
        cin >> key;
    }
    cout << "decrypted: " << decrypt(text,autoKeying(key)) << endl;
}

// main function and menus

void show_menu1() {
    cout << "please choose an  option\n";
    cout << "1) Cipher a message\n";
    cout << "2) Decipher a message\n";
    cout << "3) Exit\n";
}

void show_menu2(){
    cout << "please choose a cipher: \n";
    cout << "1) Morsecode(Cipher7)\n"
            "2) Cipher2\n"
            "3) cipher5\n"
            "4) return\n"
            "5) exit\n";
}
void show_menu3(){
    cout << "please choose a decipher: \n";
    cout << "1) Morsecode(decipher7)\n"
            "2) Decipher2\n"
            "3) Decipher5\n"
            "4) return\n"
            "5) exit\n";
}

void User_input(){
    cout << "Please enter your text\n";
}




int main() {

    // I love fried potato

    string choice1, choice2, choice3;
    string input;

    cout << "Ahlan ya user ya habibi\n";

    while (true) {
        show_menu1();
        cin >> choice1;
        cin.ignore();
        if (choice1 == "1") {
            User_input();
            getline(cin, input);
            show_menu2();
            cin >> choice2;
            cin.ignore();
            if (choice2 == "1") {
                convert_to_morse(input);
            } else if (choice2 == "2") {
                encrypt_cipher2(input);
            } else if (choice2 == "3") {
                toZebra(input);
                cin.ignore();
            } else if (choice2 == "4") {
                continue;
            } else if (choice2 == "5") {
                cout << "Thanks for using our program\n";
                return 0;
            } else {
                cout << "Please choose a valid option\n";
            }
        } else if (choice1 == "2") {
            User_input();
            getline(cin, input);
            show_menu3();
            cin >> choice3;
            cin.ignore();
            if (choice3 == "1") {
                convert_to_text(input);
            } else if (choice3 == "2") {
                decypher_cipher2(input);
            } else if (choice3 == "3") {
                fromZebra(input);
                cin.ignore();
            } else if (choice3 == "4") {
                continue;
            } else if (choice3 == "5") {
                cout << "Thanks for using our program\n";
                return 0;
            } else {
                cout << "Please choose a valid option\n";
            }
        } else if (choice1 == "3") {
            cout << "Thanks for using our program\n";
            return 0;
        } else {
            cout << "Please choose a valid option\n";
        }

        cout << "\nPress Enter to continue...\n";
        cin.get();
    }

}



