#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// A나라 -> B나라 침공
// B나라 전략 자원->아이기스 군사기지에 집중
// A -> B의 아이기스 군사기지 폭격함.

// A나라 공격에 대항해서 미사일 요격하려 할 때
// 미사일 최소로 사용해서 폭격 미사일 요격

// A : 미사일 : x축 평행 직선 모양, 개구간 나타내는 (s,e)
// B나라는 특정 x좌표에서 y 수평되도록 미사일 발사
// 발사된 비사일은 해당 x좌표 걸쳐있는 모든 미사일 관통 한번에 요격
// 개구간 (s,e) 폭격 미사일은 (s와 e에서 발사하는) 요격 미사일로 요격 불가

// 폭격 미사일의 x좌표 범위 목록 targets주어질 때
// 모든 폭격 미사일 요격 위한
// 요격미사일 최솟값 return 

vector<vector<int>> targets;

bool comp(vector<int> a, vector<int> b){
    if (a[1] != b[1]) {
        return a[1] < b[1];
    }
    return a[0] < b[0];
}

int can(){
    long long endP = targets[0][1];
    long long ans = 0;
    ans ++;
    
    for (long long i=1; i< targets.size(); i++){
        if (targets[i][0] < endP){
             continue;
        }
        else {
            ans ++;
            endP = targets[i][1];
        }
    }
    
    return ans;
}


int solution(vector<vector<int>> c_targets) {
    int answer = 0;
    
    targets = c_targets;
    
    sort(targets.begin(), targets.end(), comp);
    
    answer = can();
    
    return answer;
}