//ومن يتوكل على الله فهو حسبه

//DATE: 3/17/2024
//File name: BalbosCipher
#include <bits/stdc++.h>


using namespace std;

/*
Main idea is as following

Complexity O()
 */

//a function to check if the char is valid (only a digit)
bool isvalidchar(string s){
    if (s.size() > 1 || s == "" || not isdigit(s[0]))
        return false;
    return true;
}


//a function to check wheather the message is valid (only characters)
bool isvalidmessage(string message){

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
                break;
            }
        }
    }

    return result;
}


void take_input_polybius(string message, bool cipher){

    //in case we want to cipher we check if every char is valid (alphabetic)
    if (cipher){
        while (not isvalidmessage(message)){
            cout << "invalid input, please grow up  ";
            getline(cin, message);
        }
    }
    //in case of decipher we check if all are numbers
    else{
        while (not isvalid_encrypted(message)){
            cout << "invalid input, please grow up  ";
            getline(cin, message);
        }
    }

}


string polybius_cipher(string message, vector<vector<char>> matrix){
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
    return encrypted;
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

string polybius_decipher(string encrypted, string key, vector<vector<char>> matrix){

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

    return decrypted;

}


int main() {


    string message;
    getline(cin, message);

    //this function takes 1 if you want to cipher and takes 0 if you want to decipher (as the second parametar)
    take_input_polybius(message, 0);

    //declaring our matrix with initial values 1 2 3 4 5
    vector<vector<char>> matrix(6);
    matrix = {{'0', '1', '2', '3', '4', '5'}, {'1', 'A', 'B', 'C', 'D', 'E'}, {'2','F', 'G', 'H', 'I', 'K'}, {'3', 'L', 'M', 'N', 'O', 'P'}, {'4', 'Q', 'R', 'S', 'T', 'U'}, {'5','V', 'W', 'X', 'Y', 'Z'}};
    string first_column;
    string first_row;
    cout << "enter the key (write a number and press enter then the next number)  : ";


    //getting the key
    string key;
    for (int i = 1; i < 6; ++i) {
        string x;
        cin >> x;
        while(not isvalidchar(x)){
            cout << "what the hell is wrong with you? just enter a goddamn number\n is it too hard for such an ignorant person to understand that you should enter a number?   ";
            cin >> x;
        }
        key += x;
        //setting first row to be the key
        matrix[0][i] = x[0];
        //setting the first column
        matrix[i][0] = x[0];
    }


    cout << polybius_decipher(message, key, matrix);

}

//24 31345115 13 35314543 35314543