#include <string>
#include <vector>
#include <algorithm>

using namespace std;
// 자연수 n개로 이루어진 중복 조합 중에 다음 두 조건 만족 = 최고의 집합
// 중복 조합 !!!!! -> 중복 허용되므로 걍 /로 수학적 접근으로 풀 수 있음 (ㄹㅈㄷ)
// 1. 각 원소 합이 s되는 집합
// 2. 각 원소의 곱이 최대가 되는 집합

vector<int> solution(int n, int s) {
    vector<int> answer;
    
    if (n > s){
        answer.push_back(-1);
        return answer;
    }
    
    int q = s/n;
    int r = s%n;
    
    for (int i=0; i<n; i++){
        answer.push_back(q);
    }
    
    for (int i=0; i<r; i++){
        answer[i]++;
    }
    
    sort(answer.begin(), answer.end());
    
    return answer;
}