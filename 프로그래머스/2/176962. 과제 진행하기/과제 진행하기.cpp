#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

// 다음과 같은 순서대로 과제하려고 계획 세움
// 1. 시작하기로 한 시간 되면 시작
// 2. 새로운 과제를 시작할 시각이 되었을 때,
// 기존 진행중이던 과제 있으면 -> 그 과제 멈추고 새 과제 시작

// 3. 진행중이던 과제 끝냈을 때, 멈춘 과제가 있다면
// 멈춘 과제를 이어서 시작
// 만약 과제 끝난 시각에 (새로 시작), (잠시멈춘 과제)
// 모두 있으면 새로 시작해야하는 과제부터 진행

// 4. 멈춘 과제가 여러개 있을 때, 가장 최근에 멈춘 과제부터 시작

// plans => 과제계획 있을 때,
// 과제 끝낸 순서대로 이름을 배열에 담아 return.
// plans = [name, start(시각), playtime (과제시각)]
// plans.size() <= 10^3 
// plans는 시간순 배열 x 

struct Assignment {
    string name;
    int times;
    int rest; // 남은 시간
};



bool comp(vector<string> a, vector<string> b){
    int ah = stoi(a[1].substr(0,2));
    int am = stoi(a[1].substr(3,2));
    
    int bh = stoi(b[1].substr(0,2));
    int bm = stoi(b[1].substr(3,2));
    
    if (ah != bh) return ah < bh;
    return am < bm;
}

struct Compare{
    bool operator()(Assignment a, Assignment b){
        if (a.times != b.times){
            return a.times < b.times; 
        }
        return a.rest < b.rest;
    }
};

vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;
    vector<Assignment> as;
    stack<Assignment> pq;
    
    sort(plans.begin(), plans.end(), comp);
    for (auto p : plans){
        int h = stoi(p[1].substr(0,2));
        int m = stoi(p[1].substr(3,2));
        
        int realT = h*60 + m;
        
        as.push_back({p[0], realT, stoi(p[2])}); 
    }
    
    for (int i=0; i <as.size(); i++){
        
        int avail  = 0;
        if (i+1 == as.size() ){
            answer.push_back(as[i].name);
            break;
        }
        else {
            avail = as[i+1].times - (as[i].times + as[i].rest);
        }
        
        if (avail == 0){
            // 마치자마자 바로 다음 진행 가능
            cout << "마치자마자 바로 다음" << "\n";
            answer.push_back(as[i].name);
        }        
        else if (avail < 0){
            // 중단 후 > 새 작업 필요. (나중에 다시 작업)
            cout << "중단 필요 = " << as[i].name << "\n";
            int newRest = abs(avail);
            pq.push({as[i].name, as[i].times, newRest});
        }
        else {
            // 시간이 남음, 남을 때 pq중 중단작업 진행. 
            answer.push_back(as[i].name);
            int newRest = avail;
            
            while(newRest > 0 && !pq.empty()){
                auto newA = pq.top();
                pq.pop();
                
                cout << "top = " << newA.name << " " << "\n";
                cout << "newRest = " << newRest << "\n";
                if (newA.rest <= newRest){
                    answer.push_back(newA.name);
                    newRest = newRest - newA.rest;
                }
                else {
                    newA.rest = newA.rest - newRest;
                    pq.push(newA);
                    newRest = 0;
                }
            }
        }
    }
    
    while (!pq.empty()){
        auto t = pq.top();
        pq.pop();
        answer.push_back(t.name);
    }
    
    return answer;
}