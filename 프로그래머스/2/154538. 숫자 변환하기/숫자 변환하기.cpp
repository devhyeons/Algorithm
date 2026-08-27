#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

int dx[3];

int bfs(int start, int distV, int n){
    int dist[1000001];
    
    for (int i=0; i<=distV; i++){
        dist[i] = -1;
    }
    
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        
        //cout << cur << "\n";
        
        if (cur == distV){
            return dist[cur];
        }
        
        for (int dir =0; dir<3; dir++){
            int nx;
            if (dir == 0){
                nx = cur + n;
            }
            else {
                nx = cur * dx[dir];
            }
            
            if (nx > distV) continue;
            if (dist[nx] != -1) continue;
            dist[nx] = dist[cur]+1;
            q.push(nx);
        }
    }
    
    return -1; 
}

int solution(int x, int y, int n) {
    int answer = 0;
    dx[0] = -1;
    dx[1] = 2;
    dx[2] = 3;
    
    answer = bfs(x,y,n);
    
    
    return answer;
}