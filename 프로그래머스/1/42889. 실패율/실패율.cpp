#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 실패율 
// = 스테이지 도달 했으나, 아직 클리어하지 못한 플레이어의 수 
//  /  스테이지 도달 플레이어 수 

// 실패율이 높은 스테이지부터 내림차순으로 스테이지의 번호가 담겨 있는 배열 return


// 멈춰 있는 stage번호 담김, 전체 스테이지 n개 

int s[502];  // 스테이지 깬 성공
int f[502]; // 못 깬 사람 수
int totalN;
vector<pair<int, double >> res; //실패율 담기

bool comp (pair<int, double> a, pair<int, double> b){
    if (a.second != b.second) {
         return a.second > b.second;   
    }
    return a.first < b.first;
}


void initN(){
    for (int i=0; i<=totalN; i++){
        f[i] = 0;
        s[i] = 0;
    }
}


vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    totalN = N;
    initN(); 
    res.assign(totalN+1, {0,0}); 
    
    for (auto st : stages){
        // s번째에 멈춰 있으면
        // 1~s-1까지 깸
        for (int i=1; i<=st-1; i++){
            s[i]++;
        }
        if (st <= totalN) f[st]++;
    }
    
    for (int i=1; i<=totalN; i++){
        int reached = f[i]+ s[i];
        if (reached == 0){
            res[i] = {i,0};
        }
        else {
          res[i] = {i, (double)f[i]/reached};  
        }
    }
    
    sort(res.begin()+1, res.end(), comp);
    
    for (int i=1; i<=N; i++){
        answer.push_back(res[i].first);
    }
    
    return answer;
}