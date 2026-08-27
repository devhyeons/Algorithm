#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct route {
    int start;
    int ends;
};

vector<route> c_routes;

bool comp(route a, route b){
    if (a.ends != b.ends) return a.ends < b.ends;
    return a.start < b.start;
}

bool canView(int cnt){
    int camera = c_routes[0].ends;
    int curCnt = 1;
    
    for (int i=1; i<c_routes.size(); i++){
        if (c_routes[i].start <= camera && c_routes[i].ends >= camera) {
            continue;
        }
            camera = c_routes[i].ends;
            curCnt ++;
    }
    return curCnt <= cnt;
}

int solution(vector<vector<int>> routes) {
    int answer = 0;
    
    for (auto r : routes){
        c_routes.push_back({r[0], r[1]});
    }
    
    sort(c_routes.begin(), c_routes.end(), comp);
    
    int left = 1;
    int cnt = routes.size();
    int right = cnt;
    
    while(left <= right){
        int mid = (left + right)/2;
        if (canView(mid)){
            answer = mid;
            right = mid -1;
        }
        else {
            left = mid + 1;
        }
        
    }
    return answer;
}