#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " {" << word1 << " -> " << word2 << "}" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();
    if (abs(len1 - len2) > d) {
        return false;
    }

    int fix = 0;
    int i = 0;
    int j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            fix++;
            if (fix > d) {
                return false;
            }
            if (len1 > len2) {
                i++;
            }     
            else if (len1 < len2) {
                j++;
            }
            else { 
                i++; 
                j++; 
            }         
        } 
        else { 
            i++; 
            j++; 
        } 
    }
    fix += (len1 - i) + (len2 - j);
    return fix <= d;
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
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const auto& word : word_list) {
            if (is_adjacent(last_word, word) && !visited.count(word)) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                
                if (word == end_word) return new_ladder;

                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in) {
        error(file_name, "", "can not open file");
        return;
    }
    string word;
    while (in >> word) {
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        error("", "", "no word found");
        return;
    }

    cout << "Word ladder found: ";

    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << " ";
    }
    cout << " " << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    vector<string> ladder = generate_word_ladder("code", "data", word_list);
    print_word_ladder(ladder);
}