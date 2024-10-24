// C++ Program for Floyd Warshall Algorithm
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;


class PrimMST
{
    int removeTotal;
public:

    int minKey(vector<int> key, vector<bool> mstSet)
    {
        // Initialize min value
        int min = INT_MAX, min_index;
    
        for (int v = 0; v < key.size(); v++)
            if (mstSet[v] == 0 && key[v] < min)
                min = key[v], min_index = v;
    
        return min_index;
    }


    int Prims(vector<vector<int>> graph){
        vector<int> parent(graph.size(), -1);
        vector<int> key(graph.size(), INT_MAX);
        vector<bool> mstSet(graph.size(), false);

        key[0] = 0;
        

        for(int count = 0; count < graph.size() - 1; count++){
            int u = minKey(key, mstSet);

            mstSet[u] = true;

            for(int v = 0; v < graph.size(); v++){
                if(graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]){
                    parent[v] = u;
                    key[v] = graph[u][v];
                    if(key[v] < 0){
                        this->removeTotal += key[v];
                    }
                }
            }
        }

        int total = 0;

        for (int i = 0; i < key.size(); i++)
        {
            total += key[i];
        }
        
        return total - removeTotal;

    }

    PrimMST(){
        removeTotal = 0;
    }

    // Letter to number
    
};

int l2n(char c){
        return c <= 'Z' ? c - 'A' : c - 'a' + 26;
    }

void printString(string s){
    for(int i = 0; i < s.size(); i++){
        if(s[i] == ','){
            cout << "\n";
        } else {
            cout << s[i] << " ";
        }
    }
}

// Driver's code
int main()
{   
    string i1, i2, i3;
    PrimMST p;
    // i1 = remove or rebuild boolean
    // i2 = build cost
    // i3 = remove cost

    cin >> i1 >> i2 >> i3;

    cout << "\n\n";
    cout << "\n\n";
    cout << "\n\n";


    vector<vector<int>> v1;
    v1.push_back(vector<int>());
    int count = 0;
    int removeTotal = 0;

    for(int i = 0; i < i1.size(); i++){
        if(i1[i] == ','){ // in case of comma, add new vector
            v1.push_back(vector<int>());
            count++;
            continue;
        }
        if(i1[i] == '0'){ // if road does not exist, add sum of removing road and building road
            v1[count].push_back(l2n(i2[i]));
        } else { // else the road exists, add 0
            v1[count].push_back(-(l2n(i3[i])));
            removeTotal -= l2n(i3[i]);
        }
    }



    
    // Function call
    cout << p.Prims(v1) << endl;
    return 0;
}

// This code is contributed by Mythri J L
