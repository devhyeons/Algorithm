#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// 파기해야할 개인정보의 번호를 오름차순으로 배열에 담아 Return

// A : 유효기간 12달이라 할 때, 2021-01-05에 수집되었다면
// 2022-01-05부터 파기되어야 함. 

int term[27];
string today;

vector<string> splitString(string a){
    stringstream ss(a);
    string word;
    vector<string> result;
    
    while(ss >> word) {
        result.push_back(word);
    }
    return result;
}

vector<string> splitDots(string a){
    vector<string> res;
    string temp;
    stringstream ss(a);
    
    while(getline(ss, temp, '.')){
        res.push_back(temp);
    }
    
    return res;
}

int plusString(vector<string> orin){
    string total = "";
    for (auto o : orin){
        total = total + o;
    }
    return stoi(total);
}

int toDays(vector<string> d){
    int y = stoi(d[0]);
    int m = stoi(d[1]);
    int day = stoi(d[2]);
    
    return y*12*28 + m *28 + day; 
}

bool isEnd(string days, char idxs){
    // 약관 지났는지 확인 boolean 함수 
    vector<string> startDays = splitDots(days);
    vector<string> curDays = splitDots(today);
    
    int months = term[idxs-'A'];
    int startDay = toDays(startDays);
    int curDay = toDays(curDays);
    
    int expireDay = startDay + (months * 28)-1; //하루 빼줘야함..
    
    return expireDay < curDay;
}

vector<int> solution(string todays, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    int n = privacies.size();
    today = todays;
    
    for (auto t : terms){
        vector<string> res = splitString(t);
        
        // A약관에 3 이 들어있다. (달 수 존재)
        char idx = res[0][0];
        term[idx -'A'] = stoi(res[1]);
    }
    
    for (int i=0; i<n; i++){
        vector<string> res = splitString(privacies[i]);
        string days = res[0];
        char idx = res[1][0];
        
        cout << "\n";
        cout << "days = " << days << " idx= " << idx << "\n"; 
        
        if (isEnd(days, idx)){
            answer.push_back(i+1);
        }
    }
    
    sort(answer.begin(), answer.end());
    
    return answer;
}