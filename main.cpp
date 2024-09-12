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


// string search(string key){

// }

void insert(string key, vector<vector<Entry*>>& map){
    
    int pos = key[key.size()-1] - 'a';

    int i = 0;
    while(map[pos].size() - i != 0 && map[pos][i]->word != key){ // Making sure value doesn't already exist in map
        if(map[pos][i]->word == key){
            map[pos][i]->makeActive();
            return;
        }
        i++;
    }

    map[pos].push_back(new Entry(key));

    return;

}

void remove(string key, vector<vector<Entry*>>& map){

    int pos = key[key.size()-1] - 'a';

    int i = 0;

    while(map[pos].size() - i != 0 && map[pos][i]->word != key){
        if(map[pos][i]->word == key){
            map[pos][i]->makeInactive();
            return;
        }
        i++;
    }

    return;

}


int main(){

    vector<vector<Entry*>> vals(26, vector<Entry*>());
    string input;
    cin >> input;

    string word = "";

    for(auto i : input){

        if(i == ' '){
            if(word[0] == 'A'){
                insert(word, vals);
            } else {
                remove(word, vals);
            }
            word = "";
        }

        word += i;
    }
    cout << input << endl;
    cout << "Printing: ";

    for(int i = 0; i < vals.size(); i++){
        if(vals[i].size() != 0){
            for(auto j : vals[i]){
                if(j->active){
                    cout << j->word << " ";
                }
            }
            cout << endl;
        }
    }

    return 0;

}