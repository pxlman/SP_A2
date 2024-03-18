//ومن يتوكل على الله فهو حسبه

//DATE: 3/18/2024
//File name: Rail_fence
#include <bits/stdc++.h>


using namespace std;

//because we refuse special chars
bool isvalidmessage(string message){

    for(char ch : message)
        if (ch != ' ' && not isalpha(ch))
            return false;
    return true;

}

string takeinput1(string message){

    while(not isvalidmessage(message)){
        cout << "only alphabetic letters, if you don't like it, don't use my program";
        getline(cin, message);
    }
    return message;
}


string rail_fence_cipher(string message){

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
    return encrypted;

}

string rail_fence_decipher(string message){

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

    return decrypted;
    
}

int main() {

    //taking input
    string input_message;
    getline(cin, input_message);
    input_message = takeinput1(input_message);

    //removing the spaces
    string message;
    for (char ch : input_message){
        if (ch != ' ')
            message += ch;
    }

    cout << rail_fence_decipher(message);
//    cout << rail_fence_cipher(message);

}