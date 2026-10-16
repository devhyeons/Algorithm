#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

// 문자열에서 같은 값이 연속에서 나타나는 것을
// 그 문자의 개수와, 반복되는 값으로 표현
// ex) aabbaccc = 2a2ba3c로 표현

// 더 짧은 문자열 압축 가능한지 확인
// 단위별로 잘면 더 압축 가능.

// 출력 : 1개 이상 단위로 문자열 잘라 압축하여,
// 표현한 문자열 중 가장 짧은 것의 길이 return

// s <= 10^3
// o(n^2)

using namespace std;

bool comp(string a, string b){
    return a.size() < b.size();
}

int solution(string s) {
    
    vector<string> test;
    int answer = 0;
    
    // window 단위로 체킹
    for (int w=1; w<=s.size(); w++){
        string cur = s.substr(0,w); // idx = 0, 추출 갯수 : w 
        string result = "";
        int cnt = 1;
        
        for (int i=w; i<s.size(); i=i+w){
            string next = s.substr(i, w);
            if (cur == next){
                cnt ++;
            }
            
            else{
                if (cnt != 1){
                                 result = result + to_string(cnt) + cur;   
                }
                else {
                    result = result + cur;
                }
                cnt = 1;
                cur = next;
            }
        }
        
        if (cnt != 1){
            result = result + to_string(cnt) + cur;
        }
        else {
            result = result + cur;
        }
        
        test.push_back(result);
    }

    sort(test.begin(), test.end(), comp);
    answer = test[0].size();
    
    return answer;
}