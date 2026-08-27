#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

// 1. 길이가 1인 모든 단어를 포함하도록 사전을 초기화한다.
// 2. 사전에서 현재 입력과 일치한 가장 긴 문자열 w를 찾는다.
// 3. w에 해당하는 사전의 색인 번호를 출력하고, 입력에서 w를 제거한다.
// 4. 입력에서 처리되지 않은 다음 글자가 남아있다면 w+c에 해당하는 언어를 사전에 등록한다.
// 5. 2번으로 돌아간다. 

map<string, int> m;

// 초기화 
void initMap(){
    for (int i=1; i<=26; i++){
        string a;
        a.push_back(char('A' + (i-1)));
        m[a] = i;
    }
}

vector<int> solution(string msg) {
    vector<int> answer;
    initMap();
    
    string a;
    int idx = 27;
    int n = msg.size();
    int pos =0;
    
    while(pos < n){
        string w;
        w.push_back(msg[pos]);
        int lastIdx = m[w];
        
        while(pos+1 < n && m.count(w + msg[pos+1])){    
        w = w + msg[pos+1];
        pos ++;
        lastIdx = m[w];    
        }
        
        answer.push_back(lastIdx);
        
        if (pos+1 < n){
            string newWorld = w + msg[pos+1];
            m[newWorld] = idx ++; 
        }
        
        pos ++;
    }
 
    return answer;
}