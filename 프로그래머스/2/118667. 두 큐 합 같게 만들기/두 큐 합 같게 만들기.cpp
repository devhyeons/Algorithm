#include <string>
#include <vector>
#include <queue>

using namespace std;
// 각 큐의 원소 합을 같게 만들기 위해 필요한 최소 작업 횟수 Return..
// 어떤 방법으로도 불간으할 경우 -1 return .. 
// 정렬, pq, .. 

// 길이가 같은 두개의 큐 존재
// 하나의 큐 골라서 원소 pop, 추출된 연소 다른 큐에 insert
// 이를 통해서 각 큐의 원소 합이 같도록 만들기, 이때 필요한 최소 횟수는? 

long long sum1 = 0;
long long sum2 = 0;


int solution(vector<int> queue1, vector<int> queue2) {
    int answer = -1; 
    queue<long long> q1, q2;
    
    for (auto x : queue1){
        q1.push(x);
        sum1 = sum1 + x;
    }
    
    for (auto x : queue2){
        q2.push(x);
        sum2 = sum2 + x;
    }
    
    int n = queue1.size();
    int cnt = 0;
    int limit = n*3;
    
    while(sum1 != sum2){
        if (cnt > limit) {
            cnt = -1;
            break;
        }
        
        
        if (sum1 > sum2) {
            long long x = q1.front();
            q1.pop();
            q2.push(x);
            sum1 -= x;
            sum2 += x;
        } else {
            long long x = q2.front();
            q2.pop();
            q1.push(x);
            sum2 -= x;
            sum1 += x;
        }
        cnt++;
        
    }
    
    
    return cnt;
}