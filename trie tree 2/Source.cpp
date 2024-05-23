#include <iostream>
#include <fstream> 
#include "Stack.h"
#include<vector>
using namespace std;

struct Trie {
    Trie* children[26];
    bool end;

    Trie() {
        end = false;
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

Trie* createNode() {
    return new Trie();
}
void insert(Trie* root, string& word) {
    Trie* curr = root;
    for (int i = 0; i < word.length(); i++) {
        

        int index = word[i] - 97;

        if (curr->children[index] == nullptr) {

            curr->children[index] = new Trie();
        }

        curr = curr->children[index];
    }
    curr->end = true;
}


bool search(Trie* root, string& word) {
    Trie* curr = root;
    for (int i = 0; i < word.length(); i++) {
        int index = word[i] - 97;
        if (curr->children[index] == nullptr) {
            return false;
        }
        curr = curr->children[index];
    }
    return curr->end;
}



bool Empty(Trie* node) {
    for (int i = 0; i < 26; i++) {

        if (node->children[i] != nullptr) {
            return false;
        }
    }
    return true;
}

Trie* deleteFunction(Trie* root, string word, int word_index = 0) {

    if (!root)
        return NULL;


    if (word_index == word.length()) {

        if (root->end)
            root->end = false;


        if (Empty(root)) {
            delete root;
            root = NULL;
        }

        return root;
    }

    
    int index = word[word_index] - 97;

    // delete the next character in the word
    root->children[index] = deleteFunction(root->children[index], word, word_index + 1);

    return root;
}
 


void printAll(Trie* node, const string& current = "") {
    if (!node) {
        return;
    }
    if (node->end) {
        cout << current << endl;
    }


    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {

            printAll(node->children[i], current + char(97 + i));
        }
    }
}


void searchMultiple(Trie* root, Stacks<string>& words) {
    string word;
    while (!words.isEmpty()) {

        if (words.pop(word)) {

            bool found = search(root, word);
            if (found) {
                cout << "Word: " << word << " is found" << endl;
            }
            else {
                cout << "Word: " << word << " is not found" << endl;
            }
        }
    }
}


void Prefix(Trie* node, string& prefix, string current, Stacks<string>& results) {
    if (!node) {

        return;
    }

    if (current.length() >= prefix.length() && node->end) { // the current match a word in the trie
        results.push(current);
    }

    for (int i = 0; i < 26; i++) {

        if (node->children[i]) {
            char nextChar = 97 + i;


            if (current.length() >= prefix.length() || nextChar == prefix[current.length()]) { // current not match a word


                Prefix(node->children[i], prefix, current + nextChar, results);
            }
        }
    }
};



void Suffix(Trie* node, string& suffix, string currentWord, int suffixIndex, vector<string>& results) {
    if (!node) {

        return;
    }

    if (node->end && suffixIndex == suffix.length()) {
        results.push_back(currentWord);
    }


    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            char nextChar = 97 + i;

            if (suffixIndex < suffix.length() && nextChar == suffix[suffixIndex]) {

                Suffix(node->children[i], suffix, currentWord + nextChar, suffixIndex + 1, results);
            }
            else {

                Suffix(node->children[i], suffix, currentWord + nextChar, 0, results);
            }
        }
    }
}

void Fuzzy(Trie* root, string& fuzzyword, Stacks<string>& results) {
    string inputPrefix;
    int i = 0;


    while (i < fuzzyword.length() && fuzzyword[i] != '?') {

        inputPrefix += fuzzyword[i];
        i++;
    }


    Prefix(root, inputPrefix, "", results); 


}






int main() {
    Trie* root = createNode();

    ifstream File("dataset.txt");
    string words;
    File >> words;
    while (File >> words) {
        insert(root, words);
    }
    File.close();

    cout << "How many words you want to insert: ";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the word: ";
        string ins;
        cin >> ins;
        insert(root, ins);
    }




    cout << "All words in the Trie: " << endl;
    printAll(root, "");


    while (true) {
        string search_word;
        cout << "Enter a word to search: ";
        cin >> search_word;


        if (search(root, search_word)) {
            cout << "word: " << search_word << " is found" << endl;
        }
        else {
            cout << "word: " << search_word << " is not found" << endl;
        }

        char input;
        cout << "Do you want to search another word? (y/n): ";
        cin >> input;

        if (input == 'n' || input == 'N') {
            break;
        }
    }
    cout << "Enter a word to delete: ";
    string deletion;
    cin >> deletion;
    if (search(root, deletion)) {
        deleteFunction(root, deletion);
        cout << "the word " << deletion << " deleted successfully" << endl;
    }
    else
    {
        cout << "Word is not found in trie" << endl;
    }
    cout << "Enter the word you deletd to check: ";
    string check;
    cin >> check;
    if (search(root, check)) {
        cout << "the word is found " << endl;

    }
    else
    {
        cout << "the word is not found " << endl;
    }



    Stacks<string> stack;

    int N;
    cout << "Enter the number of words you want to search: ";
    cin >> N;


    cout << "Enter " << N << " words: ";
    for (int i = 0; i < N; i++) {
        string Multi;
        cin >> Multi;

        stack.push(Multi);
    }
    searchMultiple(root, stack);



    Stacks<string> prefix;
    cout << "Enter a prefix to search: ";
    string pre;
    cin >> pre;
    Prefix(root, pre, "", prefix);
    string pre_word;
    cout << "Words with prefix " << pre << ": " << endl;
    if (prefix.isEmpty()) {
        cout << "No words found with this prefix." << endl;
    }
    else {
        while (!prefix.isEmpty()) {
            if (prefix.pop(pre_word)) {
                cout << pre_word << endl;
            }
        }
    }

    vector<string> suffix;
    cout << "Enter a suffix to search: ";
    string suff;
    cin >> suff;
    Suffix(root, suff, "", 0, suffix);
    cout << "Words ending with " << suff << ":\n";

    if (suffix.empty()) {
        cout << "No words found ending with this suffix " << endl;
    }
    else {
        vector<string>::iterator i;
        for (i = suffix.begin(); i != suffix.end(); i++) {
            cout << *i << endl;
        }
    }



    Stacks<string> fuzzy;
    cout << "Enter fuzzy word: ";
    string fuzz;
    cin >> fuzz;
    Fuzzy(root, fuzz, fuzzy);
    cout << "Fuzzy search results for " << fuzz << ":\n";

    if (fuzzy.isEmpty()) {
        cout << "No fuzzy matches found for yout input " << endl;
    }
    else {
        while (!fuzzy.isEmpty()) {
            fuzzy.pop(fuzz);
            cout << fuzz << endl;
        }
    }


    return 0;
}


