#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <algorithm>

using namespace std;

// HEAD기준 사전순 정렬, 대소문자 구분 x
// HEAD 동일 경우 Number기준 숫자 정렬
// 9 < 10 < 0011 < 012 < 13 <014 정렬
// 둘다 같을 경우, 입력 유지 (순서 바꾸지 말기.)

struct File{
    string head;
    string number;
    string tail;
};

File splitWord(string s){
    int startIdx = 0;
    File f;
    for (int i=0; i<s.size(); i++){
        if (isdigit(s[i])){
            startIdx = i;
            int cur = i;
            int end = -1;
            while(cur < s.size() && isdigit(s[cur])){
                end = cur;
                cur ++;
            }
            f.head = s.substr(0,startIdx);
            f.number = s.substr(startIdx, end-startIdx+1);
            f.tail = s.substr(end+1,s.size()-end);
            break;
        }
    }
    return f;
}

bool comp(File a, File b){
     transform(a.head.begin(), a.head.end(), a.head.begin(), :: tolower);
    transform(b.head.begin(), b.head.end(), b.head.begin(), :: tolower);
    if (a.head != b.head){
        return a.head < b.head;
    }
    else {
        if (stoi(a.number) != stoi(b.number)){
            return stoi(a.number) < stoi(b.number);
        }
        else {
            return false; //유지 
        }
    }
}


vector<string> solution(vector<string> files) {
    // 1. files, head,number, tail로 분리
    vector<File> rFiles;
    
    for (auto f : files){
        auto a = splitWord(f);
        rFiles.push_back(a);
    }
    
    // 2. 정렬 조건에 맞춰 정렬 후 answer.push_back;
    stable_sort(rFiles.begin(), rFiles.end(), comp);
    
    vector<string> answer;
    
    for (auto r : rFiles){
        string name = r.head + r.number + r.tail;
        answer.push_back(name);
    }
    
    return answer;
}