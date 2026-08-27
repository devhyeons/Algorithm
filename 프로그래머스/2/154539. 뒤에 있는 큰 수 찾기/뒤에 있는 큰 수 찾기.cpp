#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream> 

using namespace std;

bool comp(pair<int,int> a, pair<int,int> b){
    return a.first < b.first;
}

vector<int> solution(vector<int> numbers) {
    int ns = numbers.size();
    vector<pair<int,int>> answer;
    vector<int> result;
    stack<pair<int,int>> q;
    
    
    
    for (int i=0; i<numbers.size(); i++){
        int n = numbers[i];
        if (q.empty()){
            q.push({i,n});
            continue;
        }
        
        if (q.top().second < n){
            answer.push_back({q.top().first, n});
            q.pop();
            
            while(!q.empty() && q.top().second < n)
            {
                answer.push_back({q.top().first, n});
                q.pop();
            } 
            
            q.push({i,n});
        }
        
        else {
            q.push({i,n});
        }
    
    }
    
        
    
    
    while(!q.empty()){
        answer.push_back({q.top().first,-1 });
        q.pop();
    }
    
    sort(answer.begin(), answer.end(), comp);
    
    for (int i=0; i<answer.size(); i++){
        result.push_back(answer[i].second);
    }
    
    
    return result;
}