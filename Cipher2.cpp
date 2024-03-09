#include "iostream"
#include "string"


using namespace std;


/*
 * Main idea :
 *      use the ascii value to convert A to Z and so on
 *      It is easy to configure this equation for encrypting as we take the second letter from the end if the letter is B for example
 *      and the third from the end if the letter is C for example and we can apply that to all elements
 *      Z - ( (the letter) - A )
 *
 *      for decipher:
 *          (Z - the letter) + A
 *          as we say Y is the second letter from the end so we revert it to the second letter from
 *          the start and we can apply that to all letter and the equation still works
 * */

//function for encrypting
string encrypt(string & message){
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
        //if it is upper we just change the values but the same equation happents
        if (isupper(ch)){
            last_letter = 'Z';
            first_letter ='A';
        }
        //the equation is described above
        encrypted += (char) (last_letter - (ch - first_letter));
    }
    //too obvious to be explained lol :]
    return encrypted;
}


string decypher(string message){

    string decrypted;

    for (char ch : message){
        if(not isalpha(ch)){
            decrypted += ch;
            continue;
        }

        //we suppose that the normal case that the letter is lower case
        char last_letter = 'z';
        char first_letter = 'a';
        //if it is upper we just change the values but the same equation happents
        if (isupper(ch)){
            last_letter = 'Z';
            first_letter ='A';
        }
        //the equation itself
        decrypted += (char)  ((last_letter - ch) + first_letter);

    }
    return decrypted;

}




int main(){


}