#include <string>
#include <vector>
#include <unordered_map> 
#include <algorithm>
#include <iostream>


using namespace std;

unordered_map<int,int> um;
vector<pair<int,int>> tan;

bool comp(pair<int,int> a, pair<int,int> b){
    return a.second > b.second; 
}

int solution(int k, vector<int> tangerine) {
    int answer = 0;
    
    for (int i=0; i<tangerine.size(); i++){
        int sizes = tangerine[i];
        um[sizes]++;
    }
    
    
    for (auto m : um){
       tan.push_back({m.first, m.second});
    }
    
        sort(tan.begin(), tan.end(), comp);
            
            int cnt =0;
    int category = 0;
    
    for (auto t : tan){
        if (cnt >= k){
            answer = category;
            return answer;
        }
        
        cnt = cnt + t.second;
        category ++;
        
    }
    answer = category;
    return answer;
}