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
                } else if(graph[u][v] < 0){
                    removeTotal += graph[u][v];
                }
            }
        }

        int total = 0;

        for (int i = 1; i < key.size(); i++)
        {
            // cout << key[i] << " ";
            total += key[i];
        }

        
        return total;

    }

    PrimMST(){
        removeTotal = 0;
    }

    // Letter to number
    
};

int l2n(char c){
    return c <= 'Z' ? c - 'A' : c - 'a' + 26;
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
        } else { // else the road exists
            v1[count].push_back(-(l2n(i3[i])));
            removeTotal += l2n(i3[i]);
        }
    }


    if(removeTotal % 2){
        removeTotal++;
    }
    removeTotal = removeTotal / 2;

    // cout << "Remove Total: " << removeTotal << endl;

    
    // Function call
    cout << p.Prims(v1) + removeTotal << endl;
    return 0;
}