#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

// 앞뒤 뒤집어도 똑같은 문자열 == 팰린드롬 
// s주어질 때, s의 부분 문자열 중 가장 긴 팰린드롬의 길이를 Return

// windowSliding? 
// 투포인터?

// 중간에 팰린드롬이 있을 때 어떻게 구할 수 있을까?
// abdfdbeesssk

// 이분탐색 ?? 
//https://0xd00d00.github.io/2021/08/17/programmers_palindrome.html

int palindrome(string &s, int left, int right){
    while(left >=0 && right < s.size()){
        if (s[left] != s[right]) break;
        left --;
        right++;
    }
    return right-left-1;//문자열 길이 = 거리
}


int solution(string s)
{
    int answer = 1;
    
    for (int i=1; i<s.size(); i++){
        int left = i-1;
        int right = i+1;
        int odd = palindrome(s,left,right);
        int even = palindrome(s,left,right-1);
        answer = max({answer,odd,even});
    }
    return answer;
}