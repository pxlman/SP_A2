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
    return reversed_map; // Return the reversed map
}

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
void convert_to_text() {
    map<string,string> reversed_map = reverse_map(morseCode); // Reverse the morseCode map

    string morseLine;
    getline(cin, morseLine); // Read Morse code input from user

    vector<string> morse_symbols = split(morseLine, "   "); // Split Morse code into words

    // Decode each Morse code symbol and form words
    for (auto word: split(morseLine, "   ")) {
        for (auto symbol: split(word, " ")) {
            // Check if the symbol exists in the reversed map
            if(reversed_map.find(symbol) != reversed_map.end()) {
                cout << reversed_map[symbol]; // Output the decoded Morse code
            }
            else {
                cout << "?"; // If not found, add a ?
            }
        }
        cout << ' '; // Output space between words
    }
    cout << endl;
}

int main() {
    // i love fried potato
    cout << "ahlan ya user ya habibi\n welcome to morse code cipher & decipher\n";

    char choice;
    while (true){
        cout << "please choose an option\n"
                "1) cipher text to morse code\n"
                "2) decipher morse code to text\n"
                "3) Exit";

        cin >> choice;
        cin.ignore(); // Ignore the newline character left in the input buffer
        if(choice == '1'){
            string text;
            cout << "please enter your text: ";
            getline(cin,text);
            convert_to_morse(text);
        }
        else if(choice == '2'){
            cout << "Enter the Morse code you want to convert to text (use ' ' to separate characters and '   ' to separate words): ";
            convert_to_text();
        }
        else if(choice == '3'){
            cout << "thanks for using our program";
            return 0;
        }
        else {
            cout << "please choose a valid option";
        }

        cout << "\nPress Enter to continue...";
        cin.get(); // Wait for the user to press Enter to loop again
    }
}
