#include <iostream>
#include <string>
#include <vector>

using namespace std;


class slot {
public:
    string word;
    int activity; // 0 = never used -> 1 = active -> 2 = tombstone

    slot(){
        this->activity = 0;
    }

    slot(string word){
        this->word = word;
        activity = 1;
    }

    void makeInactive(){
        this->activity = 2;
    }

    void makeActive(){
        this->activity = 1;
    }
};



void insert(string val, vector<slot>& map){
    int pos = val[val.size()-1] - 'a';
    
    while(map[pos].activity == 1){
        if(map[pos].word == val){
            map[pos].activity = 1;
            return;
        }
        pos++;
        pos = pos % 26;
    }

    map[pos].word = val;
    map[pos].activity = 1;
}

void remove(string val, vector<slot>& map){
    int pos = val[val.size()-1] - 'a';
    
    int start = (pos + 25) % 26;

    // cout << "val : " << val << endl;

    while(pos != start){
        if(map[pos].activity == 0){
            // cout << "this called for " << val << endl;
            return;
        }
        if(map[pos].word == val){
            // cout << "val : " << val << endl;
            map[pos].activity = 2;
            return;
        }
        pos++;
        pos = pos % 26;
        
    }

    return;
}


int main(){
    vector<slot> vals(26, slot());

    string input;
    getline(cin, input);

    string word = "";
    char key;

    for(auto i : input){
        if(i == 'A' || i == 'D') key = i;
        else if(i != ' ') word += i;
        if(i == ' '){
            if(key == 'A'){
                // cout << "inserting" << endl;
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

    // cout << vals[0].word << endl;

    // Output
    // cout << "Printing: ";
    // cout << vals[1].size() << endl;
    for(auto i : vals){
        if(i.activity == 1){
            cout << i.word << " ";
        } 
    }
    cout << endl;

    return 0;

}