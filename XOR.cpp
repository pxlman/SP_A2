#include<iostream>
#include <regex>
#include <string>
#include <cmath>
#include <ctype.h>
using namespace std;

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

int main(){
    toXor();
}
