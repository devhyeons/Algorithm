#include <string>
#include <vector>
#include <stack>
using namespace std;

// 영재가 실어야하는 택배상자 크기 모두 동일
// 1~n번까지 번호 증가순서대로 일렬 놓여서 전달됨.

// 컨테이너 벨트는 한 방향으로만 진행 가능해서, 벨트 놓인 순서대로 상자 내려
// 택배기사님이 알려준 순서대로 영재가 택배상자를 실어야 함.

//만약 컨테이너 벨트 맨 앞 상자가, 현재 트럭에 싣는 순서 아니면
// 그 상자를 트럭에 실을 순서 될때까지 잠시 다른곳 보관
// 보조 컨테이너에 보관

// 보조컨테이너는 벨트 앞뒤로 이동 가능핮지만, 입구 외에 다른 면 막혀있어
// 맨 앞 상자만 뺄 수 있다. (stack)
// 보조 이용해도 원하는대로 불가능 시 -> 더이상 상자 싣지 않음.

// 택배 기사님 원하는 상자 순서 존재, 영재가 몇개 실을 수 있는지 return

// order <= 10*^6
vector<int> boxs;
stack<long long> s;

int solution(vector<int> order) {
    long long answer = 0; 
    long long cur = 1;
    
    for (auto o : order){
     
        while(cur < o){
            s.push(cur);
            cur++;
        }
        
        if (cur == o){
            answer ++;
            cur ++;
        }
        
        else if(!s.empty() && s.top() == o){
            s.pop();
            answer ++;
        }
        
        else {
            break;
        }     
    }
    
    
    return answer;
}