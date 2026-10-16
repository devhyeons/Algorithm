#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

// 가장 많이 함께 주문한 단품 메뉴들 - 코스요리 메뉴로 구성
// 코스메뉴 : 최소 2가지 이상 단품메뉴로
// 최소 2명이상 손님으로부터 주문된 조합 -> 코스요리 메뉴후보

// orders : 단품 주문들
// 추가하고 싶어하는 코스요리를 구성하는 단품 메뉴 갯수 : course
// 추가하게될 메뉴 구성 문자열 형태 return

// orders <= 2 * 10
// 원소크기 <= 10 이하

// 오름차순 정렬 return. 
// 가장 많이 함께 주문된 구성 여러개 > 모두 담아서 return

unordered_map<string, int> m;

void makeSet(string o, int cnt, int idx, string s){
    if (s.size() == cnt){
        m[s]++;
        return;
    }
    
    for (int i=idx; i<o.size(); i++){
            s.push_back(o[i]);
            makeSet(o, cnt, i+1, s);
            s.pop_back();
    }
    return;
}


vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    
    for (auto o : orders){
        // 시간 복잡도에 의해서
        // 스카피의 course 만큼 조합을 전부 만들어
        // map에 담아서 채택. 
        
        sort(o.begin(), o.end());
        
        for (auto c : course) {
            makeSet(o,c,0,"");
        }
    }
    
    for (auto c : course){
        int maxV = 0;
        for (auto k : m){
            if (k.first.size() == c){
                maxV = max(k.second, maxV);
            }
        }
        
        if (maxV < 2) continue;
        
        for (auto k : m){
            if (k.first.size() == c && k.second == maxV){
                answer.push_back(k.first);
            }
        }
    }
    
    sort(answer.begin(), answer.end());
    
    
    return answer;
}