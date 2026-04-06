#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>

using namespace std;

// 그리디

// 회의 시간 안 겹치게 회의실 사용 가능한 최대 갯수는?

// I : 시작-끝시간 주어짐
// 끝남과 동시에 다음회의 시작 가능


int n;

struct conf{
    int start, ends;
};


bool comp (conf a, conf b){
    if (a.ends != b.ends){
        return a.ends < b.ends;
    }
    return a.start < b.start;
}
vector<conf> confs;

int st, ed;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    
    for (int i=0; i<n; i++){
        cin>> st >> ed;
        confs.push_back({st,ed});
    }

    sort(confs.begin(), confs.end(), comp);

    int curEnd = confs[0].ends;
    int ans = 1;

    for(int i=1; i<n; i++){
        if (curEnd <= confs[i].start){
            ans ++;
            curEnd = confs[i].ends;
        }
    }

    cout << ans << "\n";

    return 0;
}