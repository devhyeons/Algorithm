#include <string>
#include <vector>

using namespace std;

// 길이가 10^5이기도하고
// 실제 운반 순서보다는, 운반 가능한 최소 시간을 구함
// 따라서 이분탐색, 파라미터 서치를 활용.. 
// 각 도시끼리 경로는 없고, 도시 A,B,C에서 New도시로만 존재.

// check함수 구현이 가장 어렵. 
// ex) mid라는 시간이 주어졌을 때,
// 모든 도시가 새 도시로 운반 가능한 갯수는 ? 
// 즉 모든 도시의 트럭들은 전부 동시에 움직일 수 있다. 

bool check(
    long long times,
    int a, int b,
    vector<int> g,
    vector<int> s,
    vector<int> w,
    vector<int> t
) {
    
    // 도시를 짓는데 전달 시간 <= mid 가능한가? check
    
    long long totalGold = 0;
    long long totalSilver = 0;
    long long totalBoth = 0;
    
    for (int i=0; i<g.size(); i++){
    
    // 1. 왕복 가능 횟수
    long long cnt = times/(2LL * t[i]); 
    
    // 2. 마지막 편도 운행까지
    if (times % (2LL*t[i]) >= t[i] ){
        cnt ++;
    }
    
    long long capacity = cnt * w[i];
    
    totalGold = totalGold + min((long long)g[i], capacity);
    totalSilver = totalSilver + min((long long)s[i], capacity);
    totalBoth += min((long long)g[i] + s[i], capacity);
    
    }
    
    return totalGold >= a
    && totalSilver >= b
    && totalBoth >= (long long) a+b;
    
    // 실제로 어느 도시에서 얼마를 배분하는지보다
    // 실제 이 배분이 시간 내 존재하는지만 확인.. -> check 진행.

}


long long solution(int a, int b, vector<int> g, vector<int> s, vector<int> w, vector<int> t) {
    
    long long left = 0;
    long long right = 4 * 100000000000000;
    long long answer = right; 
    
    while(left <= right){
        long long mid = left + (right - left) / 2;
        
        if (check(mid, a,b,g,s,w,t)) {
            answer = mid;
            right = mid -1;
        }
        else {
            left = mid+1; 
        }
    }
    
    return answer;
}