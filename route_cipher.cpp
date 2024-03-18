//ومن يتوكل على الله فهو حسبه

//DATE: 3/16/2024
//File name: route_cipher
#include <bits/stdc++.h>

#define ll long long
#define getvec int n; cin >> n; vector<int> v(n); for(int i = 0; i < n; ++i) cin >> v[i];
#define space ' '
#define newline '\n'


using namespace std;



string cipher(int height, int width, vector<vector<char>> matrix){

    int steps{0};
    string encrypted;
    int it{0};
    int n_elements{height * width};
    while (true){

        //a loop for going DOWN starting from up right
        for (int i = it; i < height - it - 1; ++i) {
            encrypted += matrix[i][width - it - 1];
            steps++;
        }
        if (steps >= n_elements)
            break;

        //a loop for going LEFT
        //and it starts from what the last loop has ended
        for (int i = width - it - 1; i >= it; --i) {
            encrypted += matrix[height - it - 1][i];
            steps++;
        }
        if (steps >= n_elements)
            break;


        //another loop for going UP
        for (int i = height - 2 - it; i >= it; --i) {
            encrypted += matrix[i][it];
            steps++;
        }
        if (steps >= n_elements)
            break;


        //and again another loop for going right
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



string decipher(int height, int width, string encrypted){

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



int main() {

    //taking input and declaring variables
    cout << "Welcome to route cipher, please enter your message: ";
    string tempmessage;
    cin >> tempmessage;

    //transfering the message to upper
    string message;
    for (char ch : tempmessage)
        message += toupper(ch);

    cout << "please enter the secret key: ";
    int key;
    cin >> key;
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

    cout << decipher(height, width, message);

}