#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;



bool comp(vector<string> a, vector<string> b){
    string timeA = a[0].substr(0,2) + a[0].substr(3,2);
    string timeB = b[0].substr(0,2) + b[0].substr(3,2);
    
    if (timeA != timeB) return stoi(timeA) < stoi(timeB); 
    string timeEA = a[1].substr(0,2) + a[1].substr(3,2);
    string timeEB = b[1].substr(0,2) + b[1].substr(3,2);
    return  stoi(timeEA) < stoi(timeEB);
}
    
int returnTime(string t){
    string c_t = t.substr(0,2) + t.substr(3,2);
    return stoi(c_t);
}
                
int returnAddTime(string t){
    string c_t;
  int m = stoi(t.substr(3,2));
    
    if (m+10 >= 60) {
        int rest = (m+10)%60;
        int add = (m+10)/60;
        
        string h = to_string(stoi(t.substr(0,2))+1);
        string m;
      
        if (rest < 10) {
            m = "0" + to_string(rest);
        }
        else {
            m = to_string(rest);
        }
        
        
        return stoi(h+m);
    }
    
    else {  
        c_t = t.substr(0,2) + t.substr(3,2);
        return stoi(c_t) + 10; 
    }
}
                

int solution(vector<vector<string>> book_time) {
    int answer = 0;
    
    sort(book_time.begin(), book_time.end(), comp);
    vector<string> endTimes; 
    
    for (int i=0; i<book_time.size(); i++){
        if (endTimes.empty()) {
            endTimes.push_back(book_time[i][1]);
        }
        
        else {
            int curStart = returnTime(book_time[i][0]);
            bool flag = false; 
            for (int j=0; j<endTimes.size(); j++) {
                int cleanEnd = returnAddTime(endTimes[j]);
                if (cleanEnd <= curStart){
                    endTimes[j] = book_time[i][1];
                    flag = true;
                    break; 
                }
            }
            
            if (!flag){
                endTimes.push_back(book_time[i][1]);
            }
        }
    }
    
    answer = endTimes.size(); 
    
    return answer;
}