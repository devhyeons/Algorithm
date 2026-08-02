#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

struct Robot{
    int num;
    int mIdx; // 현재 target 루트 M idx
    int curX, curY;
    bool arrived = false;
};

vector<Robot> robots;
vector<vector<int>> points;
vector<vector<int>> routes;


bool AllArrived(){
    for (auto r : robots){
        if (!r.arrived){
            return false;
        }
    }
    return true;
}

pair<int,int> move(Robot & r){
    int targetNum = routes[r.num][r.mIdx];
    int targetX = points[targetNum-1][0];
    int targetY = points[targetNum-1][1];
    
    int newX = r.curX;
    int newY = r.curY;

    if (targetX != r.curX){
        if (targetX > r.curX){
            newX = r.curX + 1;
        }
        else {
            newX = r.curX -1;
        }
    }
    else {
        if (targetY > r.curY){
            newY = r.curY+1;
        }
        else{
            newY = r.curY -1;
        }
    }
    
    if ((targetX == newX) && (targetY == newY)){
        // mIdx 변경 
        if (r.mIdx == routes[0].size()-1){
            r.arrived = true;
        }
        else {
            r.mIdx++;
        }
    }
    return {newX, newY};
}


int solution(vector<vector<int>> c_points, vector<vector<int>> c_routes) {
    int answer = 0;
    
    points = c_points;
    routes = c_routes; 
    
    for (int i=0; i<routes.size(); i++){
        int curR = routes[i][0]-1;
        int px = points[curR][0];
        int py = points[curR][1];
        robots.push_back({i,1,px,py,false});
    }
    
    set<pair<int,int>> fs;
    set<pair<int,int>> fv;
    
    for (auto r : robots){
        if (!fs.count({r.curX, r.curY})){
            fs.insert({r.curX, r.curY});
        }
        
        else if (fs.count({r.curX, r.curY}) && !fv.count({r.curX, r.curY})){
            fv.insert({r.curX, r.curY});
            answer ++;
        }
    }
    
    while(!AllArrived()){
        set<pair<int,int>> s;
        set<pair<int,int>> visited;
        vector<pair<int,int>> candi;
        
        for (auto &r : robots){
            if (r.arrived == true) continue;
            auto [x,y] = move(r);
            r.curX = x;
            r.curY = y;
            candi.push_back({x,y});
        }

        for (auto c : candi){
            if (!s.count(c)){
                s.insert(c);
            }
            else if (s.count(c) && !visited.count(c)){
                visited.insert(c);
                answer ++;
            }
        }
    }
    
    
    return answer;
}