#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

// 1:08

// I 숫자 : 큐에 주어진 숫자 삽입
// D 1 : 큐 최댓값 삭제
// D -1 : 큐 최솟값 삭제

// 모든 연산 처리 후 큐 비어있으면 [0,0]
// 비어있지 않으면 [최댓값, 최솟값] return

// 최소 queue
// 최대 queue 2가지 준비. pq
// set으로 삭제된 값인지 확인.

// operations <= 10^6

priority_queue<int> maxPq;
priority_queue<int, vector<int>, greater<int>> minPq;


// substr (시작 idx, 갯수)
// subst  (시작 idx, 마지막까지) ? -1
// substr => return string (not char)

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    
    for (int i=0; i<operations.size(); i++){

        int num = stoi(operations[i].substr(2, -1));
//        cout << "num = " << num << "\n";
        
        int flag = 0;
        int deletedV = -1;
        
        if (operations[i].substr(0,1) == "I"){
            // 숫자 삽입
            maxPq.push(num);
            minPq.push(num);
        }
        
        else {
            
            if (maxPq.empty() || minPq.empty()) {
                continue;
            }
            
            if (operations[i].substr(2,2) == "-1"){
                int minV = minPq.top();
//                cout << "minV = " << minV << "\n";
                deletedV = minV;
                minPq.pop();
                flag = 1;
            }
            else {
                // 최대 삭제
                int maxV = maxPq.top();
//                cout << "maxV = " << maxV << "\n";
                deletedV = maxV;
                maxPq.pop();
                flag = 2;
            }
        }
            
        vector<int> candi;
            
        if (flag == 1){
                while(!maxPq.empty()){
                if (maxPq.top() != deletedV){
                    candi.push_back(maxPq.top());
                    maxPq.pop();
                }
                
                else {
                    maxPq.pop();
                }
            }
            
            for (auto c : candi){
                maxPq.push(c);
            }
          }
            
            if (flag == 2){
                while(!minPq.empty()){
                if (minPq.top() != deletedV){
                    candi.push_back(minPq.top());
                    minPq.pop();
                }
                
                else {
                    minPq.pop();
                }
            }
            
            for (auto c : candi){
                minPq.push(c);
            }
          }     
        }
    
    if (maxPq.empty() || minPq.empty()){
        answer.push_back(0);
        answer.push_back(0);
        return answer;
    }
    
    else { 
        answer.push_back(maxPq.top());
        answer.push_back(minPq.top());
        return answer;
    }
    
    
    return answer;
}