#include <string>
#include <vector>

using namespace std;
// 순서바꾸지 않고 더하거나 빼서 타켓넘버 만들기. 
// 타겟넘버 만드는 수의 방법을 return 

int copyTarget;
int cnt = 0;
int idxNum = 0;
vector<int> copyNumbers;
int dy[2] = {1,-1};

void dfs(int idx, int sum){
    if (idx == idxNum) {
        if (sum == copyTarget) {
        cnt ++;
    }
       return;
    }
    for (int dir = 0; dir<2; dir ++){
        dfs(idx+1, sum + copyNumbers[idx] * dy[dir]);
    }
    
    return;
}

int solution(vector<int> numbers, int target) {
    int answer = 0;
    copyTarget = target;
    idxNum = numbers.size();
    copyNumbers = numbers;
    
    dfs(0,0);
    
    return cnt;
}