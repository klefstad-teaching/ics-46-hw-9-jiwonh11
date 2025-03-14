#include "ladder.h"

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    string start, end;
    cout << "Enter first word: ";
    cin >> start;
    cout << "Enter end word: ";
    cin >> end;

    vector<string> ladder = generate_word_ladder(start, end, word_list);
    cout << "Word ladder from "<< start << " to " << end << ":" << endl;
    print_word_ladder(ladder);

    return 0;
}