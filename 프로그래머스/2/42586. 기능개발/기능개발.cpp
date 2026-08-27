#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <cmath>


using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    stack<int> s;
    
    int maxV = -1;
    
    for (int i=0; i<progresses.size(); i++){
        int rest = ceil((double)(100 - progresses[i]) / speeds[i]);
            cout << rest << "\n";
        if (s.empty()) {
                s.push(rest);
                maxV = max(maxV, rest);
            }
        
        else {
            if (maxV >= rest) {
                s.push(rest);        
            }
            else {
                int cnt = 0;
                while(!s.empty()) {
                    s.pop();
                    cnt++;
                }
                answer.push_back(cnt);
                s.push(rest);
                maxV = rest;
            }
     
        }
    
    }
   if (!s.empty()){
            answer.push_back(s.size());
   }
    
    return answer;
}