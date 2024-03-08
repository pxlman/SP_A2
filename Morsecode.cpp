#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Function to reverse the key-value pairs in the map
map<string, string> reverse_map(map<string, string> original_map) {
    map<string, string> reversed_map;
    for (const auto& pair : original_map) {
        reversed_map[pair.second] = pair.first;
    }
    return reversed_map; // Update the original map with reversed values
}

// Initialize a map to store Morse code of each char
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

// Function to convert a string of text into Morse code
vector<string> convert_to_morse(string& text) {
    vector<string> ans;
    bool is_space = true;
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
    return ans;
}

vector<string> split(string text,string deli){
    int deliLength = deli.size();
    int found = -1;
    vector<string> output;
    string item = "";
    string tillFail = "";
    int lastI;
    for (int i = 0; i < text.size(); ++i){
        if(found == deliLength - 1){
            output.push_back(item);
            item = "";
            found = -1;
            lastI = i;
            tillFail = "";
        }
        if (text[i] == deli[found+1]){
            found += 1;
            tillFail += text[i];
        }else{
            found = -1;
            item += tillFail;
            tillFail = "";
            item += text[i];
        }
    }
    output.push_back(item);
    return output;
}

void convert_to_text(){
    map<string,string> reversed_map = reverse_map(morseCode); // Reverse the morseCode map

    string morseLine;
    getline(cin, morseLine);

    vector<string> morse_symbols = split(morseLine,"   ");

    // Decode each Morse code symbol and form words
    for (auto word: split(morseLine,"   ")) {
        for (auto symbol: split(word," ")) {
            cout << reversed_map[symbol];
        }
        cout << ' ';
    }
}

int main() {
    // fried potato
    // needs to be done
    return 0;
}
