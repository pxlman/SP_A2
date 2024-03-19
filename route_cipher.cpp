//ومن يتوكل على الله فهو حسبه

//DATE: 3/16/2024
//File name: route_cipher
#include <bits/stdc++.h>

using namespace std;

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

    cout << "enter the message you want to encrypt:  " << endl;
    string message;
    getline(cin, message);

    //in case we want to cipher we check if every char is valid (alphabetic)
    while (not isvalidmessage(message)){
        cout << "invalid input, please grow up:  ";
        getline(cin, message);
    }
    return message;

}




string route_cipher(){


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

    return encrypted;
}


//we do the same as function cipher
string route_decipher(){

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

    return decrypted;
}

int main() {

    cout << route_decipher();


}