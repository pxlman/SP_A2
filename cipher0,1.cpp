#include <iostream>
#include <string>
#include "bitset"

using namespace std;

string encrypt0(string text, int a, int b) {
    string result = "";
    for (char ch : text) {
        if (isalpha(ch)) {
            ch = toupper(ch);
            // Apply Affine Cipher encryption formula: E(x) = (a * x + b) % 26
            ch = ((a * (ch - 'A') + b) % 26) + 'A';
            result.push_back(ch);
        } else {
            result.push_back(ch);
        }
    }
    return result;
}

string decrypt0(string text, int c, int b) {
    string result = "";
    for (char ch : text) {
        if (isalpha(ch)) {
            ch = toupper(ch);
            int y = ch - 'A';
            // Apply Affine Cipher decryption formula: D(y) = c * (y - b) % 26
            int x = (c * (y - b)) % 26;
            if (x < 0) { // Handle negative result after modulo operation
                x += 26; // Add 26 to make the result positive
            }
            ch = x + 'A'; // Convert the decrypted numeric value to a character
            result.push_back(ch);
        } else {
            result.push_back(ch);
        }
    }
    return result;
}

string encrypt4(string text){
    string result;
    for(char ch: text){
        if(isalpha(ch)){
            ch = toupper(ch);
            char value = ch - 'A'; // Calculate the integer value
            string binary_rep = bitset<5>(value).to_string(); // Convert the int value to binary
            for(char c: binary_rep){
                if(c == '0'){
                    result.push_back('a');
                }
                else{
                    result.push_back('b');
                }
            }
        }
        else if(ch == ' '){
            result.push_back(' ');
        }
        else{
            result.push_back(ch);
        }

        result.push_back(' ');
    }
    return result;
}

string decrypt4(string text) {
    string result = "";

    string binary_rep;
    for(char ch: text){
        if(isalpha(ch)) {
            if (ch == 'a') {
                binary_rep.push_back('0');
            } else if (ch == 'b') {
                binary_rep.push_back('1');
            }
            else if(ch == ' '){
                binary_rep.push_back(' ');
            }
            else{
                binary_rep.push_back(ch);
            }
        }
    }

    string binary_letter = "";
    for(char c: binary_rep){
        if (c != ' ') {
            binary_letter.push_back(c);
            // Check if the binary letter length reaches 5 characters
            if (binary_letter.size() == 5) {
                // Convert the binary letter to its integer value
                int value = stoi(binary_letter, nullptr, 2);
                c = value + 'A'; // Convert the numeric value to the character
                result.push_back(c); // Append the character to the result string
                binary_letter = ""; // reset the binary letter
            }
        }
        else{
            result.push_back(c);
        }
    }

    return result;
}


bool is_valid4(string text){
    for(char ch: text){
        if(ch != 'a' && ch != 'b' && ch != ' '){
            return false;
        }
    }
    return true;
}


int main() {

    int a = 5;
    int b = 8;
    int c = 21;


   string s = "HELLO";
   string h = "aabbb aabaa ababb ababb abbba";

   if(is_valid4(h)){
        cout << "1\n";
   }
   else
        return 0;

   cout << "Encrypted0: " << encrypt0(s, a, b) << endl;
   cout << "Encrypted4: " << encrypt4(s) << endl;

   cout << "Decrypted0: " << decrypt0(s, c, b) << endl;
   cout << "Decrypted4: " << decrypt4(h) << endl;

    return 0;
}
