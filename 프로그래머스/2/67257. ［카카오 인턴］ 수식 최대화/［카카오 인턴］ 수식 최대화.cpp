#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//해커톤 참가 모든 참가자들에게 숫자 + 3가지 연산 (+,-,*)으로
// 이루어진 연산 수식 전달
//참가자들 미션 : 전달받은 수식에 포함된 연산자의
// 우선수위를 자유롭게 재정의해서, 가장 큰 숫자 제출

// 단 연산자의 우선순위 재정의시
// 같은 순위의 연산자는 없다.

// 수식에 포함된 연산자가 n개라면
// 정의할 수 있는 연산자 우선순위 조합 (n)!
// 만약 계산된 결과가 음수라면, 해당 숫자 절댓값 변환 후 제출
// 제출한 숫자가 가장 큰 참가자 우승자. 
// 우승자 제출 숫자 -> 우승상금

// 피연산자가 999를 포함하는 수식은 입력 x
// 피연산자 음수도 x
// 최대 3!으로 계산.. 

long long maxV = 0;
char op[3] = {'+', '*', '-'};
bool visited[3];
string st = "";

void initVisited(){
    for (int i=0; i<3; i++){
        visited[i] = false;
    }
}

long long calNum(vector<char> exp){
    vector<long long> nums;
    vector<char> ops;
    int num = 0;
    for (auto s : st){
        if (s >= '0' && s <= '9'){
            num = num * 10 + (s-'0'); // char to number 
        }
        
        else {
            nums.push_back(num);
            ops.push_back(s);
            num = 0;
        }
    }
    nums.push_back(num);
    
    // 연산자 우선순위대로 계산
    for (auto curOp : exp){
        int i = 0;
        while(i < ops.size()){
            if (ops[i] == curOp){
                long long result = 0;
                
                if (curOp == '+'){
                    result = nums[i] + nums[i+1];
                }
                else if (curOp == '-'){
                    result = nums[i] - nums[i+1];
                }
                else {
                    result = nums[i] * nums[i+1];
                }
                
                nums[i] = result;
                nums.erase(nums.begin()+i+1); //뒤에 삭제;
                ops.erase(ops.begin()+i); // 해당 연산자 삭제 
            }
            
            else {
                i++;
            }
        }
    }
    
    return llabs(nums[0]); //0에 모든 값 계산이 저장되어있다.
}

void dfs(int cnt, vector<char> exp){
    if (exp.size() == 3){
        maxV= max(maxV, calNum(exp)); 
        return;
    }
    
    for (int i=0; i<3; i++){
        if (!visited[i]){
            visited[i] = true;
            exp.push_back(op[i]);
            dfs(cnt+1, exp);
            exp.pop_back();
            visited[i] = false;
        }
    }
}

long long solution(string expression) {
    long long answer = 0;
    st = expression;
    
    // dfs로 연산자 우선순위 브루트포스
    initVisited();
    vector<char> exp;
    dfs(0,exp);
    
    answer = maxV; // 갱신 maxV Answer로 
    
    return answer;
}