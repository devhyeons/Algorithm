#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

// mine 작업 끝낼때까지 필요한 최소한의 피로도 
// picks 곡괭이 수 = [dia cnt, iron cnt, stone cnt]

// diamond가 많은 곳에 -> 다이아 곡괭이 배분 -> 최소한의 피로도
// 5개씩 나눠서 dCnt, iCnt, sCnt에 따라 분배
// 이 때 곡괭이 수 vs 광물 수 중 min(곡괭, 광물) 
// max = 곡괭 수 * 5 


int tired[3][3] = {
    {1,1,1},
    {5,1,1},
    {25,5,1}
};

struct Mine{
    int dCnt = 0;
    int iCnt = 0;
    int sCnt = 0;
};

bool comp(Mine a, Mine b){
    if (a.dCnt != b.dCnt) return a.dCnt > b.dCnt;
    if (a.iCnt != b.iCnt ) return a.iCnt > b.iCnt;
    return a.sCnt > b.sCnt;
}

int solution(vector<int> picks, vector<string> minerals) {
    int answer = 0;
    int maxV = 0;
    
    for (auto p : picks){
        maxV= maxV + p;
    }
    
    cout << maxV << "\n\n";
    vector<Mine> mines;
    
    int mins = min((int)minerals.size(), maxV *5);
    int ends;
    if (mins%5 == 0){
        ends = mins/5;
    }
    
    else {
        ends = (mins/5) + 1;
    }
    
    // 5개씩 나눠서 cnt 넣기
    for (int i=0; i<ends; i++){
        Mine m;
        for (int j=0; j<5; j++){
            int idx = i*5 + j;
            if (idx < mins){
                if (minerals[idx] == "diamond"){
                    m.dCnt ++;
                }
                else if (minerals[idx] == "iron"){
                    m.iCnt ++;
                }
                
                else if (minerals[idx] == "stone"){
                    m.sCnt ++;
                }
                else {
                    continue;
                }
            }
        }
        mines.push_back(m);
    }
    
    sort(mines.begin(), mines.end(), comp);
    
    
    for (auto m : mines){
        cout << m.dCnt << " " << m.iCnt << " " << m.sCnt << "\n";
    }
    
    
    for (int i=0; i<mines.size(); i++){
        int pIdx = -1;
        Mine cur = mines[i];
        if (picks[0] > 0 ){
            pIdx  =0;
            picks[0]--;
        }
        else if (picks[1] > 0){
            pIdx = 1;
            picks[1]--;
        }
        else {
            pIdx = 2;
            picks[2]--;
        }
        
        answer = answer + tired[pIdx][0] * cur.dCnt
                        + tired[pIdx][1] * cur.iCnt
                        + tired[pIdx][2] * cur.sCnt;
    }
    
    
    
    return answer;
}