#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

struct Robot{
    int num;
    int curX, curY;
    int mIdx;
    bool arrived = false;
};

vector<Robot> robots;

vector<vector<int>> points;
vector<vector<int>> routes;


bool AllRobotArrived(){

    for(auto &r : robots){
        if(!r.arrived)
            return false;
    }

    return true;
}


// 이동
void move(Robot &r){

    int curM = routes[r.num][r.mIdx] - 1;

    int targetX = points[curM][0];
    int targetY = points[curM][1];


    // r 먼저 이동
    if(targetX != r.curX){

        if(targetX > r.curX)
            r.curX++;
        else
            r.curX--;

    }
    else{

        if(targetY > r.curY)
            r.curY++;
        else
            r.curY--;

    }


    // 포인트 도착
    if(r.curX == targetX && r.curY == targetY){

        r.mIdx++;

    }
}


// 충돌 체크
int checkCollision(){

    set<pair<int,int>> pos;
    set<pair<int,int>> collision;


    for(auto &r : robots){

        if(r.arrived)
            continue;


        pair<int,int> cur = {r.curX, r.curY};


        if(pos.count(cur))
            collision.insert(cur);
        else
            pos.insert(cur);
    }


    return collision.size();
}



int solution(vector<vector<int>> c_points, vector<vector<int>> c_routes) {

    int answer = 0;

    points = c_points;
    routes = c_routes;

    robots.clear();



    // 로봇 생성
    for(int i=0; i<routes.size(); i++){

        int start = routes[i][0] - 1;


        robots.push_back({
            i,
            points[start][0],
            points[start][1],
            1,          // 첫 번째 포인트는 이미 도착 상태
            false
        });
    }



    // 0초 위치 체크
    answer += checkCollision();



    while(!AllRobotArrived()){


        // 모든 로봇 이동
        for(auto &r : robots){

            if(r.arrived)
                continue;

            move(r);
        }



        // 이동 후 충돌 체크
        answer += checkCollision();



        // 목적지 끝난 로봇 제거
        for(auto &r : robots){

            if(!r.arrived && r.mIdx == routes[r.num].size()){

                r.arrived = true;
            }
        }
    }



    return answer;
}