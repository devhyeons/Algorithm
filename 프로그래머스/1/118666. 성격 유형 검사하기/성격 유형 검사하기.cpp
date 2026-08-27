#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 검사결과 모든 질문의 성격 유형 점수를 더하여, 각 지표에서 높은 점수를 받은
// 성격 유형 => 검사자의 성격 유형

// 같으면, 두 성격 유형 중 사전순으로 빠른 성격 유형을 검사자의 성격 유형.. 


int score[28];
//vector<string> type = {"RT", "TR", "FC", "CF", "MJ", "JM", "AN", "NA"}; 
// type자체를 pair로 둬서 풀 수 있다. 
// 그러면 returnTypeIdx도 불필요.. 


vector<pair<char,char>> type = { {'R','T'}, {'F','C'}, {'J','M'}, {'A','N'}};
int n;

pair<char, int> calScore(int first, int second, int cNums){
    if (cNums < 4){
        return {first, 4-cNums};
    } else if (cNums == 4){
        return {' ', 0};
    } else {
        return {second, cNums-4};
    }
}

string solution(vector<string> survey, vector<int> choices) {
    string answer = "";
    n = survey.size();
    
    for (int i=0; i<n; i++){
        auto [f,s] = pair<char,char>(survey[i][0], survey[i][1]);
        pair<char, int> res = calScore(f,s,choices[i]);
        if (res.first == ' ') continue;
        score[res.first-'A'] = score[res.first-'A']+res.second;
    }
    
    
    for (auto [a,b] : type){
        if (score[a-'A'] > score[b-'A']){
            answer = answer + a;
        } else if (score[a-'A'] < score[b-'A']){
            answer = answer + b;
        } else {
            answer = answer + min(a,b);
        }
    }
    
    return answer;
}