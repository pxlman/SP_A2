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




string route_cipher(int height, int width, vector<vector<char>> matrix){

    //intializing variables
    //steps is the number of encryption steps we did so far so that if it reaches the num of elements, we are done
    int steps{0};
    string encrypted;
    //note that it is just an iterator that increments 1 every iteration
    int it{0};
    int n_elements{height * width};

    while (true){

        //a loop for going DOWN starting from up right including the element down
        for (int i = it; i < height - it - 1; ++i) {
            encrypted += matrix[i][width - it - 1];
            steps++;
        }
        //we need to check this condition after each loop
        if (steps >= n_elements)
            break;

        //a loop for going LEFT
        //and it starts from what the last loop has ended
        //including the element in the very left side
        for (int i = width - it - 1; i >= it; --i) {
            encrypted += matrix[height - it - 1][i];
            steps++;
        }
        if (steps >= n_elements)
            break;


        //another loop for going UP including the element at the top
        for (int i = height - 2 - it; i >= it; --i) {
            encrypted += matrix[i][it];
            steps++;
        }
        if (steps >= n_elements)
            break;


        //and again another loop for going right including the element on the very right side
        for (int i = it + 1; i < width - 1 - it; ++i) {
            encrypted += matrix[it][i];
            steps++;
        }
        if (steps >= n_elements)
            break;

        it++;
    }
    return encrypted;

}


//we do the same as function cipher
string route_decipher(int height, int width, string encrypted){

    //intializing the matrix with stars
    vector<vector<char>> matrix(height);
    for (int i = 0; i <height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i].push_back('*');
        }
    }

    int next{0};
    int it{0};

    while(true){

        //loop for going down
        for (int i = it; i < height; ++i) {
            // if the current square is already filled then stop here please
            if (matrix[i][width - 1 - it] != '*'){
                break;
            }
            matrix[i][width - 1 - it] = encrypted[next++];
        }
        if (next >= encrypted.size())
            break;



        //loop for going left
        for (int i = width - 2 - it; i >= 0 ; --i) {
            if (matrix[height - 1 - it][i] != '*'){

                break;
            }
            matrix[height - 1 - it][i] = encrypted[next++];
        }

        if (next >= encrypted.size())
            break;


        //loop for going up
        for (int i = height - 2 - it; i >= 0 ; --i) {
            if (matrix[i][it] != '*'){

                break;
            }
            matrix[i][it] = encrypted[next++];
        }
        if (next >= encrypted.size())
            break;


        //loop for going right
        for (int i = it + 1; i < width; ++i) {
            if (matrix[it][i] != '*'){

                break;
            }
            matrix[it][i] = encrypted[next++];
        }
        if (next >= encrypted.size())
            break;

        it++;
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

bool isvalidmessage(string message){

    for(char ch : message)
        if (ch != ' ' && not isalpha(ch))
            return false;
    return true;

}


int main() {

    //taking input and declaring variables
    cout << "Welcome to route cipher, please enter your message: ";
    string tempmessage;
    getline(cin, tempmessage);
    while(not isvalidmessage(tempmessage)){
        cout << "only alphabets are allowed";
        getline(cin, tempmessage);
    }

    //transfering the message to upper
    string message;
    for (char ch : tempmessage)
        if (ch != ' ')
            message += toupper(ch);

    string tempkey;
    cout << "please enter the secret key: ";
    cin >> tempkey;
    while (tempkey.size() != 1 or not isdigit(tempkey[0])){
        cout << "not a valid key, you stupid user";
        cin >> tempkey;
    }
    int key = stoi(tempkey);
    //we get the heigth of the matrix
    int height = message.size() / key;
    //we handel the case that the matrix has empty slots
    if (message.size() % key != 0)
        height = (message.size() / key) + 1;

    int width = key;
    vector<vector<char>> matrix(height);

    //we use this function to intialize all elements to X
    for (int i = 0; i <height; ++i) {
        for (int j = 0; j <width; ++j) {
            matrix[i].push_back('X');
        }
    }

    //filling our matrix with characters
    for (int i = 0, k = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j, ++k) {
            if (k >= message.size())
                break;
            matrix[i][j] = message[k];
        }
    }

    cout << route_decipher(height, width, message);

}