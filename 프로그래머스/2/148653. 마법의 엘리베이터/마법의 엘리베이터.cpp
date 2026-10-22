#include <string>
#include <vector>

using namespace std;

// 마법의 엘리베이터는 절댓값이 10^c 형태인 정수들 적힌 버튼 있다.
// 버튼 누르면 현재 층 + 버튼 값 인 층으로 이동
// 단 엘베 위치층과 버튼 값 더했을 때 0보다 작으면 안움직임

// 0층이 가장 아래층, 엘레베이터는 현재 민수 있는층에 존재
// 버튼 하나당 마법의 돌 한개 사용
// 16층 민수 0층 가려면 -1 6번, -10 1번 눌러서 총 7개 소모
// 하지만 +1 4개, -10 2개 사용해서 6개로 0층 가능

// 최소한의 버튼 눌러서 가려고할 때, 0층 갈 수 있는 최소 돌 수는?
// DP 문제 ? 

int solution(int storey) {
    int answer = 0;
    
    int cur = storey;
    while(cur != 0){
        int rest = cur % 10;
        cur = cur / 10;
        if (rest > 5){
            answer = answer + (10-rest);
            cur ++;
        }
        else if (rest < 5){
            answer = answer + rest;
        }
        else {
            if (cur%10 >=5) {
                answer = answer + (10-rest);
                cur ++;
            }
            else {
                answer = answer + rest;
            }
        }
    }
    
    return answer;
}