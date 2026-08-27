#include <string>
#include <vector>
#include <set>

using namespace std;

vector<string> cBoard;
int m,n;

bool check(int x, int y){
    char origin = cBoard[x][y];   
    if (x+1 < m && y+1 < n && origin != '.'){
        if (cBoard[x+1][y] == origin && cBoard[x+1][y+1] == origin && cBoard[x][y+1]== origin){
            return true;
        }
    }
    return false;
}

void down(int x, int y){
    int startX = x;
    while(startX+1 < m){
        if (cBoard[startX+1][y] == '.'){
            swap(cBoard[startX+1][y], cBoard[startX][y]);
            startX++;
        }
        else {
            break;
        }
    }
}

void downBoard(){
    for (int i=m-2; i>=0; i--){
        for (int j=0; j<n; j++){
            if (i+1 < m && cBoard[i][j] != '.') down(i,j);
        }
    }
}

int remove(){
    int removeCnt = 0;
    set<pair<int,int>> s;
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            if (check(i,j)){
                s.insert({i,j});
                s.insert({i+1,j});
                s.insert({i,j+1});
                s.insert({i+1, j+1});
            }
        }
    }
    
    for (auto r : s){
        cBoard[r.first][r.second] = '.';
        removeCnt++;
    }
   return removeCnt;
}

int solution(int cm, int cn, vector<string> board) {
    m=cm;
    n=cn;
    int answer = 0;
    cBoard = board;
    
    while(1){
        int removeCnt = remove();
        answer = answer+removeCnt;
        downBoard();
        if (removeCnt == 0) break;
    }
    
    return answer;
}