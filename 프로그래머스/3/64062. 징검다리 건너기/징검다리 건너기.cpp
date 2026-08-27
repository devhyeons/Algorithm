#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// 징검다리는 일렬로 놓여있고, 숫자가 적혀있음
// 디딤돌의 숫자는 한번 밟을때마다 1 씩 줄어듬 -> 0되면 더이상 밟을수 없다.

// 다음 디딤돌로 한번에 여러개 뛸 수 있다 -> 밟을수있는게 여러개인 경우 가장 가까운 디딤돌로만 건너뛰기 가능

// 한번에 한명씩 징검다리 건너고 -> 다 건너야지 그 다음 친구 건넘
// 최대 몇명까지 징검다리 건널 수 있는 return 
// 디딤돌의 최대칸수, 디딤돌 적힌 숫자

// 아이디어
// sliding window로 K+1 window 크기 잡은 다음
// 그 구간의 최댓값을 찾아서, 전체 min에 맞도록 갱신 진행 
// 그리고 나온 min이 최대로 사람이 건널 수 있는 수라는 판단. 

// mid명까지 건널 수 있는지 검사
bool canCross(const vector<int>& stones, int k, int people) {
    int zeros = 0;
    for (int stone : stones) {
        if (stone - people < 0) {
            zeros++;
            if (zeros >= k) return false;
        } else {
            zeros = 0; 
        }
    }
    return true;
}

int solution(vector<int> stones, int k) {
    int answer = 0;
    int left = 1;
    int right = *max_element(stones.begin(), stones.end());
    
    while (left <= right) {
        int mid = (left + right) / 2;
        
        if (canCross(stones, k, mid)) {
            answer = mid;       
            left = mid + 1;
        } else {
            right = mid - 1;   
        }
    }
    
    return answer;
}