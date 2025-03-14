#include "ladder.h"

using namespace std;


void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << word1 << " to "<< word2 << " is invalid" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();

    if (abs(len1 - len2) > d) return false;

    int changes = 0;
    int i = 0;
    int j = 0;

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            changes++;

            if (changes > d) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else{
                i++;
                j++;
            }
        }else{
            i++;
            j++;
        }
    }
    changes += (len1 -1) + (len2 - j);
    return changes <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};

    queue<vector<string>> ladder_queue;
    set<string> visited;
    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = current_ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);

                if (word == end_word) return new_ladder; 

                visited.insert(word);
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};


}


void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Unable to open file " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) word_list.insert(word);
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << " -> ";
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    vector<pair<string, string>> test_cases = {
        {"cat", "dog"}, {"marty", "curls"}, {"code", "data"},
        {"work", "play"}, {"sleep", "awake"}, {"car", "cheat"}
    };

    for (size_t i = 0; i < test_cases.size(); i++) { 
        string start = test_cases[i].first; 
        string end = test_cases[i].second;

        vector<string> ladder = generate_word_ladder(start, end, word_list);
        cout << "Testing: " << start << " -> " << end << " | ";
        print_word_ladder(ladder);
    }
}