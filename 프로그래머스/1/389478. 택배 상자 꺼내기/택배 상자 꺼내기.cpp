#include <string>
#include <vector>
#include <cmath>

using namespace std;

int arr[101][101] = {0};

int solution(int n, int w, int num) {
    int answer = 0;
    
    int rows = (n+w-1)/w;
    
    int cur = 1; //채워 넣을 값
    
    for (int line = 0; line < rows; line++){
        if (line %2 == 0){
            for (int i=0; i<w && cur <= n; i++){
                arr[line][i] = cur++;
            }
        }
        
        else {
            for (int i=w-1; i>=0 && cur <=n; i--){
                arr[line][i] = cur++;
            }
        }
    }    
    
    int targetRow = -1, targetCol= -1;
    
    for (int i=0; i<rows; i++){
        for (int j=0; j<w; j++){
            if (arr[i][j] == num){
                targetRow = i;
                targetCol = j;
            }
        }
    }
    
    for (int i= targetRow; i<rows; i++){
        if (arr[i][targetCol] != 0){
            answer ++;
        }
    }
    return answer;
}