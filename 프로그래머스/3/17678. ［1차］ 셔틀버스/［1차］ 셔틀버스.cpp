#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

vector<int> busTime; 
priority_queue<int, vector<int>, greater<int>> pq;
string solution(int n, int t, int m, vector<string> timetable) {
    int answer = 0;
    
    cout << "busTime" << "\n";
    int start = 9*60;
    for (int i=0; i<n; i++){
        busTime.push_back(start + (i*t));
    } //N회 t분 간격 
    // 버스 운행 시간 저장
    
    for (int i=0; i<timetable.size(); i++){
        int hour = stoi(timetable[i].substr(0,2)) * 60;
        int min = stoi(timetable[i].substr(3));
        pq.push(hour+min);
    }
    
    for (int i=0; i<busTime.size(); i++){
       int curBus= busTime[i];
        vector<int> boarded; //버스 탄 승객
        
        while(!pq.empty() && pq.top() <= curBus &&boarded.size() < m){
            boarded.push_back(pq.top());
            pq.pop();
        }
        
        
        if (i==busTime.size()-1){
            if (boarded.size() < m){
                answer = curBus;
            }
            
            else {
                answer = boarded.back()-1;
            }
        }
    }
    
    int ahour = answer/60;
    int amin = answer%60;
    
     char buf[6];
    sprintf(buf, "%02d:%02d",ahour, amin);

    return string(buf);
}