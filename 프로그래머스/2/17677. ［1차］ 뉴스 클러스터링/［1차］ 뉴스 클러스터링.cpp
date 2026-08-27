#include <string>
#include <cctype>
#include <set>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// 두 집합 A,B 사이 유사도는 = 교집합 크기 / 합집합 크기 
// 둘다 공집합이면 1

// 입력으로 들어온 문자열을 두 글자씩 끊어서 다중 집합의 원소로 만든다.
// 이 때 영문자로 된 글자 쌍만 유효하고, 기타 공백이나 숫자, 특수문자가 들어있는 경우는
// 그 글자 쌍을 버린다. 

// 소문자 대문자 차이는 무시한다. 

// 입력으로 들어온 두 문자열 자카드 유사도를 출력한다.
// 0~1사이 실수, 이를 다루기 쉽도록 65536을 곱한 후 소수점 아래 버리고, 정수부만 출력 

vector<string> s1;
vector<string> s2;
unordered_map<string, int> m1;
unordered_map<string, int> m2;

int solution(string str1, string str2) {
    int answer = 0;
    
    int n = str1.size();
    int m = str2.size();
    
    // str1 -> 소문자 치환 후 : 2글자씩 쪼개서 s1에 담기
    for (int i=0; i<str1.size(); i++){
        if (i+1 < n){
            string addV;
            if (isalpha(str1[i]) && isalpha(str1[i+1])){
               addV.push_back(tolower(str1[i]));
               addV.push_back(tolower(str1[i+1]));
               s1.push_back(addV);
                m1[addV]++;
            }
        }
    }
    
    // str2 -> 소문자 치환 후 : 2글자씩 쪼개서 s2에 담기 
    for (int i=0; i<str2.size(); i++){
        if (i+1 < m){
            string addV;
            if (isalpha(str2[i]) && isalpha(str2[i+1])){
               addV.push_back(tolower(str2[i]));
               addV.push_back(tolower(str2[i+1]));
               s2.push_back(addV);
                m2[addV]++;
            }
        }
    }   
    
    // 집합 합집합, 교집합 구해서 -> 계산
    
    int unionCnt =0;
    int interCnt =0;
    for (auto a : m1){
        int b= m2[a.first];
        unionCnt = unionCnt + max(a.second, b);
        interCnt = interCnt + min(a.second, b);
    }
    
    for (auto b : m2){
        if (!m1.count(b.first)){
            unionCnt = unionCnt + b.second;
        }
    }
    
    if (unionCnt == 0) {
        return 65536;
    }
    
    answer = (65536 * interCnt)/unionCnt;
    
    return answer;
}