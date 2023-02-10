#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <chrono>
#include <random>
using namespace std;

// function initialisation
vector<string> read_guesses(), read_solutions();
string compare(string guess, string target);
double entropy(int green, int yellow, int grey);

// main code
int main() {
    // speed up input and output
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);

    ofstream out_one("results/excludes/one.txt");
    ofstream out_two("results/excludes/two.txt");
    ofstream out_three("results/excludes/three.txt");
    ofstream out_four("results/excludes/four.txt");
    ofstream out_five("results/excludes/five.txt");

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    vector<string> guesses = read_guesses();
    vector<string> solutions = read_solutions();

    // 5 tiles, 26 characters to be excluded
    vector<vector<vector<char>>> guess_tiles(5, vector<vector<char>>(26));

    // compare each guess with each soln
    for (string guess: guesses) {
        for (string soln: solutions) {
            string compare_str = compare(guess, soln);
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 26; j++) {
                    if (j != guess[i] - 'a') {
                        guess_tiles[i][j].push_back(compare_str[i]);
                    }
                }
            }
        }
    }



    // calculate entropy, print results
    for (int tile = 0; tile < 5; tile++) {
        for (int letter = 0; letter < 26; letter++) {
            int green = count(guess_tiles[tile][letter].begin(), guess_tiles[tile][letter].end(), 'g');
            int yellow = count(guess_tiles[tile][letter].begin(), guess_tiles[tile][letter].end(), 'y');
            int grey = count(guess_tiles[tile][letter].begin(), guess_tiles[tile][letter].end(), 'x');
            if (tile == 0) out_one << green << " " << yellow << " " << grey << " " << green + yellow + grey << endl << entropy(green, yellow, grey) << endl;
            else if (tile == 1) out_two << green << " " << yellow << " " << grey << " " << green + yellow + grey << endl << entropy(green, yellow, grey) << endl;
            else if (tile == 2) out_three << green << " " << yellow << " " << grey << " " << green + yellow + grey << endl << entropy(green, yellow, grey) << endl;
            else if (tile == 3) out_four << green << " " << yellow << " " << grey << " " << green + yellow + grey << endl << entropy(green, yellow, grey) << endl;
            else if (tile == 4) out_five << green << " " << yellow << " " << grey << " " << green + yellow + grey << endl << entropy(green, yellow, grey) << endl;
        }
    }
}

// read file and store words in vector
vector<string> read_guesses() {
    fstream words_file;
    vector<string> words;
    words_file.open("texts/guesses.txt", ios::in);
    if (!words_file) {
        cout << "File not found.\n";
    } else {
        while (true) {
            if (words_file.eof()) break;
            string word;
            words_file >> word;
            words.push_back(word);
        }
    }
    return words;
}

vector<string> read_solutions() {
    fstream words_file;
    vector<string> words;
    words_file.open("texts/solutions.txt", ios::in);
    if (!words_file) {
        cout << "File not found.\n";
    } else {
        while (true) {
            if (words_file.eof()) break;
            string word;
            words_file >> word;
            words.push_back(word);
        }
    }
    return words;
}

// compare letters between two strings
string compare(string guess, string target) {
    // initialise variables
    string compare_str = "....."; // string to be returned
    map<char, int> target_map; // to check if letter in guess word is in target word
    for (auto letter: target) target_map[letter]++; // initialise target_map

    // first pass: process EXACT matches
    // change compare_str accordingly, and decrement letter count in target_map
    for (int i = 0; i < 5; i++) {
        if (guess[i] == target[i]) {
            compare_str[i] = 'g';
            target_map[guess[i]]--;
        }
    }

    // second pass: process correct letters and wrong letters
    for (int i = 0; i < 5; i++) {
        // if processed in first pass, move on to next letter
        if (compare_str[i] == 'g') continue;

        // change compare_str and target_map accordingly
        if (target_map[guess[i]] > 0) {
            compare_str[i] = 'y';
            target_map[guess[i]]--;
        } else {
            compare_str[i] = 'x';
        }
    }

    return compare_str;
}

// calculate entropy/bits using the entropy function
double entropy(int green, int yellow, int grey) {
    // int total = green + yellow + grey;
    int total = 12972 * 2315;
    double x_green = (double)green / (double)total;
    double x_yellow = (double)yellow / (double)total;
    double x_grey = (double)grey / (double)total;
    return -(x_green * log2(x_green) + x_yellow * log2(x_yellow) + x_grey * log2(x_grey));
}