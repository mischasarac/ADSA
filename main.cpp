#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Entry{
public:
    string word;
    bool active;
    Entry(){
        this->word = "";
        this->active = false;
    }

    Entry(string word) : word(word) {
        this->active = true;
    }

    void makeInactive(){
        this->active = false;
    }

    void makeActive(){
        this->active = true;
    }
};

void insert(string key, vector<vector<Entry*>>& map){
    int pos = key[key.size()-1] - 'a';  // Getting position

    int i = 0;
    while(map[pos].size() - i != 0 && map[pos][i]->word != key){ // Ensuring value doesn't already exist in map
        if(map[pos][i]->word == key){
            map[pos][i]->makeActive();
            return;
        }
        i++;
    }

    map[pos].push_back(new Entry(key));  // Inserting the new word at correct index
}

void remove(string key, vector<vector<Entry*>>& map){
    int pos = key[key.size()-1] - 'a';  // Getting position

    int i = 0;
    while(map[pos].size() - i != 0){
        // cout << "map[pos][i]: " << map[pos][i]->word << endl;
        if(map[pos][i]->word == key){
            map[pos][i]->makeInactive();
            return;
        }
        i++;
    }
}

int main(){
    vector<vector<Entry*>> vals(26, vector<Entry*>());
    string input;
    getline(cin, input);

    string word = "";
    char key;

    for(auto i : input){
        if(i == 'A' || i == 'D') key = i;
        else if(i != ' ') word += i;
        if(i == ' '){
            if(key == 'A'){
                insert(word, vals);
                // Printing size of the correct index
                // int pos = word[word.size()-1] - 'a';  // Use last character
                // cout << "pos: " << pos << endl;
                // cout << vals[pos].size() << endl;
            } else {
                remove(word, vals);
            }
            word = "";
        }
    }

    // cout << "vals[0]: " << vals[0].size() << endl;
    // Handling the end case
    if(key == 'A'){
        insert(word, vals);
    } else {
        remove(word, vals);
        // cout << "Removing: " << word << endl;
    }

    // Output
    // cout << "Printing: ";
    // cout << vals[1].size() << endl;
    for(int i = 0; i < vals.size(); i++){
        if(vals[i].size() != 0){
            for(auto j : vals[i]){
                if(j->active){
                    cout << j->word << " ";
                }
            }
        }
    }
    cout << endl;

    return 0;
}
