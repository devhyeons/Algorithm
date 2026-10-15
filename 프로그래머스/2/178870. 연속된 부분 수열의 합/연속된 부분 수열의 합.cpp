#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
// 비 내림차순 정렬 수열 있을 때, 부분 수열 찾기
// 기존 수열에서 임의의 두 인덱스 원소와 그 사이 원소 모두 포함하는 부분수열
// 부분수열 합 = k
// 합 k인 경우 여러개 = 길이 가장 짧은 수열
// 길이 가장 짧은 수열 여러개 = 시작 인덱스 가장 작은 수열

bool comp(pair<int,int> a, pair<int,int> b){
    int aLen = a.second - a.first;
    int bLen = b.second - b.first;
    if (aLen != bLen) return (a.second - a.first) < (b.second - b.first);
    
 
        return a.first < b.first;
   
}




vector<int> solution(vector<int> sequence, int k) {
    vector<int> answer;
    vector<pair<int,int>> candi;
    int start = 0;
    int ends = 0;
    int curSum = 0;
    
    while(start < sequence.size()){
        if (curSum < k && ends < sequence.size()){
            curSum = curSum + sequence[ends];
            ends ++;
        }
        
        else if (curSum == k){
            candi.push_back({start, ends-1});
            curSum = curSum - sequence[start];
            start ++;
        }

        else {
        curSum -= sequence[start];
        start++;
        }
    }
    
    sort(candi.begin(), candi.end(), comp);
    answer.push_back(candi[0].first);
    answer.push_back(candi[0].second);
    
    
    return answer;
}