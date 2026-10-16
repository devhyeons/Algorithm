#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

// 양의 정수 n => k진수로 바꿀 때
// 변환된 수 안에 아래 조건이 맞는 소수가 몇개인지?

// 0P0 : 소수 양쪽에 0이 있는 경우
// P0 : 소수 오른쪽에만 0있고, 왼쪽에는 없는 경우
// 0P : 소수 왼쪽에만 0 있고, 오른쪽에는 아무것도 없는 경우
// P : 소수 양쪽에 아무것도 없는 경우

// 437674를 3진수로 바꾸면 .. 211020101011 인데..
// 여기서 찾을 수 있는 조건에 맞는 소수는  . . . 총 3개
// 211 : P0형태
// 2는 0P0형태
// 11은 0P형태..


// 풀이 과정 
// 1. n -> k진수로 변경
// 2. 소수형태 찾기 

bool isPrime(string a, int startIdx, int endIdx){
    string curS = "";
    if (startIdx > endIdx ) return false;
    
    for (int i=startIdx; i<=endIdx; i++){
        curS = curS + a[i];
    }
    
    if (curS.empty()) return false;
    
    long long n = stoll(curS);
    
    if (n<2) return false; 
     for (long long i=2; i*i<=n; i++){
         if (n % i == 0) return false;
     }
    
    return true; 
}


int solution(int n, int k) {
    int answer = 0;
    int nums = n;
    string s;
    int rest = 0;
    
    // 1. 진수 변경
    while(n != 0){
        rest = n%k;
        n = n/k;
        s.push_back(rest+'0');
    }
    
    reverse(s.begin(), s.end());
    
    // 2. 소수 찾기
    int startIdx = 0;
    
    for (int i=0; i<s.size(); i++){
        cout << startIdx << "\n";
        if (s[i] == '0'){
            if (i!=0){
                if (s[startIdx] == '0'){
                    if (isPrime(s, startIdx+1, i-1)) {
                        answer ++;
                    }
                }
                else{
                    if (isPrime(s,startIdx, i-1 )){
                        answer ++;
                    }
                }
                  startIdx = i;
            }
        }
    }
    
    if (s[startIdx] == '0'){
        startIdx ++;
    }
    
    if (startIdx < s.size()){
        if (isPrime(s, startIdx, s.size()-1)){
            answer++;
        }
    }
    
    
    return answer;
}