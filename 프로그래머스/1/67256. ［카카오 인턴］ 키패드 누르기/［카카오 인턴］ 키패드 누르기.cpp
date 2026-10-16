#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 키패드에서 왼손, 오른손 엄지만으로 숫자 입력
// 처음 왼 : *
// 처음 오 : #

// 엄지손가락 상하좌우 4가지 방향만 이동 가능
// 키패드 이동 1칸 = 거리 1 
// 왼쪽 3개 숫자 1,4,7 : 왼손 엄지
// 오른쪽 3개 3,6,9 : 오른손 엄지
// 가운데 2,5,8,0 : 두 엄지 중 가까운 엄지 사용
// 거리 동일 시 : 오른손 잡이 - 오른손, 왼손 잡이 : 왼손

// 순서대로 누를 번호랑, 왼손 - 오른손 hand
// 각 번호 누른 손이 왼손, 오른손인지 나타내는 문자열 return

// numbers <= 10^3;
// -> O(n^2) 이상 가능

vector<pair<int,int>> board;

int checkHand(int a){
    if (a==1 || a==4 || a==7){
        // 왼손
        return 1;
    }
    
    else if (a== 3 || a== 6 || a== 9){
        // 오른손
        return 2;
    }
    // both 가능
    else return 3; 
}


void setBoard(){
    board.push_back({3,1}); // 0일때 
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            board.push_back({i,j}); 
        }
    }
}

struct hands{
    int curX, curY;
    bool hands;
};

string solution(vector<int> numbers, string hand) {
    string answer = "";    
    setBoard();
    
    hands leftH;
    hands rightH;
    if (hand == "left"){
        leftH = {3,0,true};
        rightH = {3,2, false};
    }
    
    else {
        leftH = {3,0,false};
        rightH = {3,2,true};
    }
    
    
    for (auto n : numbers){
        int status = checkHand(n);
        
        // 왼
        if (status == 1){
            leftH.curX = board[n].first;
            leftH.curY = board[n].second;
            answer.push_back('L');
        }
        
        // 오른
        else if (status == 2){
            rightH.curX = board[n].first;
            rightH.curY = board[n].second;
            answer.push_back('R');
        }
        
        // both 
        else {
            // 현재 두 거리 체크 
  
            int targetX = board[n].first;
            int targetY = board[n].second;
            
            int leftDist = abs(targetX-leftH.curX) + abs(targetY-leftH.curY);
            int rightDist = abs(targetX-rightH.curX) + abs(targetY-rightH.curY);
            
            
            
            if (leftDist > rightDist){
                rightH.curX = board[n].first;
                rightH.curY = board[n].second;
                answer.push_back('R');
            }
            
            else if (leftDist < rightDist){
             leftH.curX = board[n].first;
            leftH.curY = board[n].second;
            answer.push_back('L');
            }
            
            else{
                cout << leftH.hands  << " = " << "\n";
                cout <<rightH.hands << " = " << "\n";
                if (leftH.hands){
                    //왼손잡이
                                 leftH.curX = board[n].first;
            leftH.curY = board[n].second;
            answer.push_back('L');
                }
                else {
                    // 오른손잡이
                                   rightH.curX = board[n].first;
                rightH.curY = board[n].second;
                answer.push_back('R');
                }
            }
            
        }
    }
    
    return answer;
}