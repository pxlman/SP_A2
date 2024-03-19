// FCAI – Structured Programming – 2024 - Assignment 2 - task4
// File:  CS112_A2_T4_S21,22_20230227_20230005_20230062.cpp
// Purpose: Encrypt and Decrypt programs
// Last modified :  18/3/2024  1:18 PM
// Version : 5.0
// Teaching Assistant : Rana Abdelkader
// section number : All of us in S21,22
// Author,ID,Emails and Parts done:
// 1) Ahmed Ashraf Lotfy - 20230005 - agxgv7573@gmail.com - Cipher5,3,8
// 2) Islam Waleed Salah - 20230062 - islamalshaer@gmail.com - Cipher2,1,9,6
// 3) Abdullah Ali Kamal - 20230227 - aakak123456789@gmail.com - Cipher7,0,4



#include <iostream>
#include <map>
#include <vector>
#include "string"
#include <cctype>
#include "sstream"
#include "bitset"
#include "regex"
#include "cmath"

using namespace std;


// **Cipher 0 Functions**
void encrypt0(string text, int a, int b) {
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
    cout << "Encrypted: " << result << endl;
}

void decrypt0(string text, int c, int b) {
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
    cout << "Decrypted: " << result << endl;
}

// **Cipher 1 Functions**

/*
 * PLEASE NOTE THIS BEFORE YOU GRADE the route cipher:
 *  after i have done the file, i realized that there is much easier algorithm to perform the cipher
 *
 *  and the algorithm is as following:
 *  we also make a loop for each direction (down-left-up-right)
 *  but this time we don't make such complicated equations as i did in this file
 *  instead every time we start from the boarder to the boarder
 *  for every step we mark the cell as ciphered using the sign '-'
 *
 *  and we skip the dashes at the beginning
 *  and stop when we find a dash at the end
 *
 *  and theoritically it should work just fine
 *  O(n^2)
 *
 * */

bool isvalidmessage(string message){

    for(char ch : message)
        if (ch != ' ' && not isalpha(ch))
            return false;
    return true;

}

string take_input_alphabetic(){

    string message;
    getline(cin, message);

    //in case we want to cipher we check if every char is valid (alphabetic)
    while (not isvalidmessage(message)){
        cout << "invalid input, please grow up:  ";
        getline(cin, message);
    }
    return message;

}




void route_cipher(){


    cout << "Welcome to route cipher, please enter your message: ";
    //getting the message
    string tempmessage = take_input_alphabetic();
    string message;
    //transforming into upper
    for (char ch : tempmessage)
        if (ch != ' ')
            message += toupper(ch);

    //getting the key
    string tempkey;
    cout << "please enter the secret key: ";
    cin >> tempkey;
    while (tempkey.size() != 1 or not isdigit(tempkey[0])){
        cout << "not a valid key, you stupid user";
        cin >> tempkey;
    }
    int key = stoi(tempkey);
    //we get the heigth of the matrix
    int n_rows = message.size() / key;
    //we handel the case that the matrix has empty slots
    if (message.size() % key != 0)
        n_rows = (message.size() / key) + 1;

    int n_columns = key;


    vector<vector<char>> matrix(n_rows);
    //we use this function to intialize all elements to X
    for (int i = 0; i <n_rows; ++i)
        for (int j = 0; j <n_columns; ++j)
            matrix[i].push_back('X');

    for (int i = 0, k = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_columns; ++j) {
            if (k >= message.size())
                break;
            matrix[i][j] = message[k++];
        }
    }

    //we use this dummy variable that increments 1 every loop
    int dummy{0};
    int steps{0};
    string encrypted;
    while(true){

        //loop for going down
        for (int i = 0; i < n_rows; ++i) {
            if(matrix[i][n_columns - 1 - dummy] == '*')
                continue;
            encrypted += matrix[i][n_columns - 1 - dummy];
            matrix[i][n_columns - 1 - dummy] = '*';
            steps++;
        }
        if (steps >= n_rows * n_columns)
            break;

        //loop for going left
        for (int i = n_columns - 1; i >= 0; --i) {
            if (matrix[n_rows - 1 - dummy][i] == '*')
                continue;
            encrypted += matrix[n_rows - 1 - dummy][i];
            matrix[n_rows - 1 - dummy][i] = '*';
            steps++;
        }
        if (steps >= n_rows * n_columns)
            break;

        //loop for going up
        for (int i = n_rows - 1; i >= 0; --i) {
            if (matrix[i][dummy] == '*')
                continue;
            encrypted += matrix[i][dummy];
            matrix[i][dummy] = '*';
            steps++;
        }
        if (steps >= n_rows * n_columns)
            break;

        //loop for going right
        for (int i = 0; i < n_columns; ++i) {
            if (matrix[dummy][i] == '*')
                continue;
            encrypted += matrix[dummy][i];
            matrix[dummy][i] = '*';
            steps++;
        }
        if (steps >= n_rows * n_columns)
            break;

        dummy++;
    }

    cout << "Encrypted: " << encrypted;
}


//we do the same as function cipher
void route_decipher(){

    string tempmessage = take_input_alphabetic();
    string encrypted;
    //transforming into upper
    for (char ch : tempmessage)
        if (ch != ' ')
            encrypted += toupper(ch);

    //getting the key
    string tempkey;
    cout << "please enter the secret key: ";
    cin >> tempkey;
    while (tempkey.size() != 1 or not isdigit(tempkey[0])){
        cout << "not a valid key, you stupid user";
        cin >> tempkey;
    }
    int key = stoi(tempkey);
    //we get the heigth of the matrix
    int height = encrypted.size() / key;
    //we handel the case that the matrix has empty slots
    if (encrypted.size() % key != 0)
        height = (encrypted.size() / key) + 1;

    int width = key;


    //intializing the matrix with stars
    vector<vector<char>> matrix(height);
    for (int i = 0; i <height; ++i)
        for (int j = 0; j < width; ++j)
            matrix[i].push_back('*');


    int next{0};
    int dummy{0};

    while(true){

        //loop for going down
        for (int i = dummy; i < height; ++i) {
            // if the current square is already filled then stop here please
            if (matrix[i][width - 1 - dummy] != '*'){
                break;
            }
            matrix[i][width - 1 - dummy] = encrypted[next++];
        }
        if (next >= encrypted.size())
            break;



        //loop for going left
        for (int i = width - 2 - dummy; i >= 0 ; --i) {
            if (matrix[height - 1 - dummy][i] != '*'){

                break;
            }
            matrix[height - 1 - dummy][i] = encrypted[next++];
        }

        if (next >= encrypted.size())
            break;


        //loop for going up
        for (int i = height - 2 - dummy; i >= 0 ; --i) {
            if (matrix[i][dummy] != '*'){

                break;
            }
            matrix[i][dummy] = encrypted[next++];
        }
        if (next >= encrypted.size())
            break;


        //loop for going right
        for (int i = dummy + 1; i < width; ++i) {
            if (matrix[dummy][i] != '*'){

                break;
            }
            matrix[dummy][i] = encrypted[next++];
        }
        if (next >= encrypted.size())
            break;

        dummy++;
    }


    string decrypted;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(matrix[i][j] != 'X')
                decrypted += matrix[i][j];
        }
    }

    cout << "Decrypted: " << decrypted;
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


// **Cipher 3 Functions**
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


// **Cipher 4 Functions**
void encrypt4(string text){
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
    cout << "Encrypted: " << result;
}

void decrypt4(string text) {
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

    cout << "Decrypted: " << result;
}


bool is_valid4(string text){
    for(char ch: text){
        if(ch != 'a' && ch != 'b' && ch != ' '){
            return false;
        }
    }
    return true;
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


// **Polybius Square Cipher 6**
/*
Main idea is as following

Complexity O()
 */

//a function to check if the char is valid (only a digit)
bool isvalidchar(string s){
    if (s.size() != 1 || not isdigit(s[0]))
        return false;
    return true;
}


//a function to check wheather the message is valid (only characters)
bool isvalidmessage6(string message){

    for(char ch : message)
        if (ch != ' ' && not isalpha(ch))
            return false;
    return true;

}

//a function to check wheather the encrypted message is valid
bool isvalid_encrypted(string encrypted){

    for (char ch : encrypted){
        if (ch != ' ' && not isdigit(ch))
            return false;
    }
    return true;
}


string get_chars_number(char ch, vector<vector<char>> matrix){

    string result;
    //encrypting the j as i
    if (ch == 'J')
        ch = 'I';

    //for each character we get the value on the very left side of the row
    //and the value of the value on the top of the column
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (ch == matrix[i][j]){
                result += matrix[i][0];
                result += matrix[0][j];
                return result;
            }
        }
    }

}


//this function takes 1 if you want to cipher and takes 0 if you want to decipher (as the second parametar)
string take_input_alphabetic(bool cipher){

    cout << "enter the message:  " << endl;
    string message;
    getline(cin, message);

    //in case we want to cipher we check if every char is valid (alphabetic)
    if (cipher){
        while (not isvalidmessage6(message)){
            cout << "invalid input, please grow up:  ";
            getline(cin, message);
        }
    }
        //in case of decipher we check if all are numbers
    else{
        while (not isvalid_encrypted(message)){
            cout << "invalid input, please grow up:  ";
            getline(cin, message);
        }
    }
    return message;

}

int search_for_index(char x, vector<vector<char>> matrix, char axis){

    for (int i = 0; i < 6; ++i) {
        //we decide if we are gonna search horizontally or vertically by checking len value
        int a, b;
        if (axis == 'y'){
            //column is fixed and rows are iterated over
            b = 0;
            a = i;
        }
        else if (axis == 'x'){
            //row is fixed and columns are iterated over
            a = 0;
            b = i;
        }
        if (matrix[a][b] ==  x)
            return i;
    }

}


//a function to seperate every word and put them in a vector
vector<string> get_words(string sentence){

    vector<string> words;
    istringstream iss(sentence);
    string word;
    while (iss >> word) {
        words.push_back(word);
    }

    return words;

}


void polybius_cipher(){
    vector<vector<char>> matrix = {{'0', '1', '2', '3', '4', '5'}, {'1', 'A', 'B', 'C', 'D', 'E'}, {'2','F', 'G', 'H', 'I', 'K'}, {'3', 'L', 'M', 'N', 'O', 'P'}, {'4', 'Q', 'R', 'S', 'T', 'U'}, {'5','V', 'W', 'X', 'Y', 'Z'}};

    string message = take_input_alphabetic(true);

    //getting the key
    cout << "enter the key (write a number and press enter then the next number)  : " << '\n';
    for (int i = 1; i < 6; ++i) {
        string x;
        cin >> x;
        while(not isvalidchar(x)){
            cout << "what the hell is wrong with you? just enter a goddamn number\n is it too hard for such an ignorant person to understand that you should enter a number?   ";
            cin >> x;
        }
        //setting first row to be the key
        matrix[0][i] = x[0];
        //setting the first column
        matrix[i][0] = x[0];
    }

    //looping on every char to encrypt it
    string encrypted;
    for (char ch : message){
        if (ch == ' '){
            encrypted += ' ';
            continue;
        }
        //all are upper case according to problem's definition
        ch = toupper(ch);
        encrypted += get_chars_number(ch, matrix);
    }
    cout << "Encrypted: " << encrypted;
}




void polybius_decipher(){

    vector<vector<char>> matrix = {{'0', '1', '2', '3', '4', '5'}, {'1', 'A', 'B', 'C', 'D', 'E'}, {'2','F', 'G', 'H', 'I', 'K'}, {'3', 'L', 'M', 'N', 'O', 'P'}, {'4', 'Q', 'R', 'S', 'T', 'U'}, {'5','V', 'W', 'X', 'Y', 'Z'}};
    string encrypted = take_input_alphabetic(false);

    //getting the key
    string key;
    cout << "enter the key (write a number and press enter then the next number)  : " << '\n';
    for (int i = 1; i < 6; ++i) {
        string x;
        cin >> x;
        while(not isvalidchar(x)){
            cout << "what the hell is wrong with you? just enter a goddamn number\n is it too hard for such an ignorant person to understand that you should enter a number?   " << endl;
            cin >> x;
        }
        key += x;
        //setting first row to be the key
        matrix[0][i] = x[0];
        //setting the first column
        matrix[i][0] = x[0];
    }

    //initializing variables
    string decrypted;
    vector<string> words;
    words = get_words(encrypted);

    for(string word : words){
        //for every word we take every two numbers representing every char
        for (int i = 0; i < word.size(); ++i) {
            int index1 = search_for_index(word[i], matrix, 'y');
            int index2 = search_for_index(word[i + 1], matrix, 'x');

            //we access the matrix using the indexes to get the cahr
            decrypted += matrix[index1][index2];
            //we skip the second number because we already used it
            i++;
        }
        decrypted += ' ';
    }

    cout << "Decrypted: " << decrypted;

}



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

// **cipher 8 Functions**
bool validText(string text){
    regex exp("^[a-zA-Z_]+$");
    if(regex_match(text,exp)){
        return true;
    }else{
        return false;
    }
}
bool validHex(string hexa){
    regex exp("^[a-f0-9 ]+$");
    return regex_match(hexa,exp);
}
string xorEnc(string plain,string key){
    string ciph = "";
    for (int i = 0; i < plain.size(); i++)
    {
        ciph += char(plain[i]^key[i%(key.size())]);
    }
    return ciph;
}
string intToHex(int num){
    string out;
    int onum = num;
    string hexas = "0123456789abcdef";
    while(num >= 1){
        out += hexas[num%16];
        num /= 16;
    }
    if(onum < 16){
        out += '0';
    }
    reverse(out.begin(),out.end());
    return out;
}
int hexToInt(string hexa){
    int out = 0;
    string hexas = "0123456789abcdef";
    reverse(hexa.begin(),hexa.end());
    for (int i = 0; i < hexa.size(); i++){
        int ind;
        for (int ii = 0; ii < hexas.size(); ii++){
            if(hexa[i] == hexas[ii]){
                ind = ii;
                break;
            }
        }
        out += ind*pow(16,i);
    }
    return out;
}
string hexToCipher(string hexa){
    string out;
    string shex = "";
    for (int i = 0; i < hexa.size(); i++)
    {
        if(hexa[i] != ' '){
            shex += hexa[i];
        }else {
            out += char(hexToInt(shex));
            shex = "";
        }
    }
    return out;
}
string cipherToHex(string ciph){
    string out;
    for (int i = 0; i < ciph.size(); i++)
    {
        out += intToHex(int(ciph[i]));
        out += ' ';
    }
    return out;
}

void toXor(){
    string plain = "8";
    // while(!validText(plain)){
    cout << "Plain Text: ";
    getline(cin,plain);
    // }
    string key;
    cout << "Key: ";
    getline(cin,key);
    cout << "Cipher Text: ";
    for(char c:xorEnc(plain,key)){
        if(isprint(c)){
            cout << c;
        }
    }
    cout << '\n';
    cout << "Hexa Cipher: " << cipherToHex(xorEnc(plain,key)) << '\n';
}

void fromXor(){
    string cipherHex = "";
    while(!validHex(cipherHex)){
        cout << "Hexa Cipher: ";
        getline(cin,cipherHex);
    }
    cout << "Key: ";
    string key;
    getline(cin,key);
    string cipher = hexToCipher(cipherHex);
    cout << "Plain Text: " << xorEnc(cipher,key);
}


// **cipher 9 Functions**
//because we refuse special chars
bool isvalidmessage9(string message){

    for(char ch : message)
        if (ch != ' ' && not isalpha(ch))
            return false;
    return true;

}

string take_input_alphabetic9(){

    cout << "enter the message:  " << endl;
    string message;
    getline(cin, message);

    //in case we want to cipher we check if every char is valid (alphabetic)

    while (not isvalidmessage9(message)) {
        cout << "invalid input, please grow up:  ";
        getline(cin, message);
    }
    return message;

}


void rail_fence_cipher(){

    string input_message = take_input_alphabetic9();
    string message;
    for (char ch : input_message){
        if (ch != ' ')
            message += ch;
    }

    //we fix the key to 4
    vector<vector<char>> matrix(4);

    //we initialize the matrix
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < message.size(); ++j)
            matrix[i].push_back('.');

    //we fill the matrix in diagonal
    bool going_down{true};
    for (int x = 0, y = 0; x < message.size(); ++x) {
        matrix[y][x] = message[x];

        if (y == 0){
            going_down = true;
            y++;
        }
        else if (y == 3){
            going_down = false;
            y--;
        }
        else if (y < 3 && going_down)
            y++;
        else if (y < 3 && not going_down)
            y--;
    }

    //adding the characters to the encrypted string
    string encrypted;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < message.size(); ++j)
            if(matrix[i][j] != '.')
                encrypted += matrix[i][j];
    cout << "Encrypted: " << encrypted;

}

void rail_fence_decipher(){

    string input_message = take_input_alphabetic9();
    string message;
    for (char ch : input_message){
        if (ch != ' ')
            message += ch;
    }


    vector<vector<char>> matrix(4);

    //we initialize the matrix
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < message.size(); ++j)
            matrix[i].push_back('.');

    //mark the positions with dashes
    bool going_down{true};
    for (int x = 0, y = 0; x < message.size(); ++x) {
        matrix[y][x] = '-';

        if (y == 0){
            going_down = true;
            y++;
        }
        else if (y == 3){
            going_down = false;
            y--;
        }
        else if (y < 3 && going_down)
            y++;
        else if (y < 3 && not going_down)
            y--;
    }


    //replace the dashes with letters
    int next{0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < message.size(); ++j) {
            if (matrix[i][j] == '-')
                matrix[i][j] = message[next++];
        }
    }

    //read the matrix in diagonal
    string decrypted;
    going_down = true;
    for (int x = 0, y = 0; x < message.size(); ++x) {

        decrypted += matrix[y][x];
        if (y == 0){
            going_down = true;
            y++;
        }
        else if (y == 3){
            going_down = false;
            y--;
        }
        else if (y < 3 && going_down)
            y++;
        else if (y < 3 && not going_down)
            y--;
    }

   cout << "Decrypted: " << decrypted;

}

// **main function and menus**

void show_menu1() {
    cout << "please choose an  option\n";
    cout << "1) encrypt a message\n";
    cout << "2) Decrypt a message\n";
    cout << "3) Exit\n";
}

void show_menu2(){
    cout << "please choose a program: \n";
    cout << "0) Affine Cipher\n"
            "1) Route Cipher\n"
            "2) Atbash Cipher\n"
            "3) Vignere Cipher\n"
            "4) Baconian Cipher\n"
            "5) Simple Substitution Cipher\n"
            "6) Polybius Square Cipher\n"
            "7) Morse Code\n"
            "8) XOR Cipher\n"
            "9) Rail-fence Cipher\n"
            "10) return\n"
            "11) exit\n";
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
            show_menu2();
            cin >> choice2;
            cin.ignore();
            if (choice2 == "0") {
                int a,b;
                cout << "enter the parameters(A then B): \n";
                cin >> a >> b;
                cin.ignore();
                User_input();
                getline(cin,input);
                encrypt0(input,a,b);
            } else if (choice2 == "1") {
                route_cipher();
                cin.ignore();
            } else if (choice2 == "2") {
                User_input();
                getline(cin,input);
                encrypt_cipher2(input);
            } else if (choice2 == "3") {
                toVignere();
            } else if (choice2 == "4") {
                User_input();
                getline(cin,input);
                encrypt4(input);
            } else if (choice2 == "5") {
                User_input();
                getline(cin,input);
                toZebra(input);
                cin.ignore();
            } else if (choice2 == "6") {
                polybius_cipher();
            } else if (choice2 == "7") {
                User_input();
                getline(cin,input);
                convert_to_morse(input);
            } else if (choice2 == "8") {
                toXor();
            } else if (choice2 == "9") {
                rail_fence_cipher();
            } else if (choice2 == "10") {
                continue;
            } else if (choice2 == "11") {
                cout << "Thanks for using our program\n";
                return 0;
            } else {
                cout << "Please choose a valid option\n";
            }
        } else if (choice1 == "2") {
            show_menu2();
            cin >> choice3;
            cin.ignore();
            if (choice3 == "0") {
                User_input();
                getline(cin,input);
                int c,b;
                cout << "Enter your parameters(c then b): \n";
                cin >> c >> b;
                decrypt0(input,c,b);
                cin.ignore();
            } else if (choice3 == "1") {
                route_decipher();
                cin.ignore();
            } else if (choice3 == "2") {
                User_input();
                getline(cin,input);
                decypher_cipher2(input);
            } else if (choice3 == "3") {
               fromVignere();
            } else if (choice3 == "4") {
                User_input();
                getline(cin,input);
                while(!is_valid4(input)){
                    cout << "only enter a or b: ";
                    User_input();
                    getline(cin,input);
                }
                decrypt4(input);
            } else if (choice3 == "5") {
                User_input();
                getline(cin,input);
                fromZebra(input);
                cin.ignore();
            } else if (choice3 == "6") {
                polybius_decipher();
                cin.ignore();
            } else if (choice3 == "7") {
                User_input();
                getline(cin,input);
                convert_to_text(input);
            } else if (choice3 == "8") {
                fromXor();
            } else if (choice3 == "9") {
                rail_fence_decipher();
            } else if (choice3 == "10") {
                continue;
            } else if (choice3 == "11") {
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