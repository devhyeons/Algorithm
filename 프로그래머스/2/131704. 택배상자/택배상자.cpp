#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

// 택배상자 1~n번까지 번호 증가순 컨테이너 벨트 놓여서 전달
// 컨테이너 벨트는 1번부터 놓인 순서대로 넣을 수 있.
// 택배기사님이 알려준 순서대로 영재가 넣어야 함.

// 현재 컨테이너 벨트 택배가 트럭 순서가 아니면
// 그 상자를 트럭에 실을 순서가 될 때 까지 잠시 다른곳 보관
// 보조 컨테이너 벨트에 둠.
// 보조 컨테이너 벨트는 앞 뒤 이동 가능하지만, 맨 앞 상자만 뺄 수 있다. (LIFO) : Stack 
// 보조 이용해도 원하는대로 못 실으면 더이상 x

// 몇개 실을 수 있는가?
stack<int> s;

// order <= 10^6

int solution(vector<int> order) {
    int answer = 0;
    
    vector<int> boxs;
    
    for (int i=0; i<order.size(); i++){
        boxs.push_back(i+1);
    }
    
    int idx = 0;
    
    for (auto o : order){
        if (boxs[idx] == o){
            answer ++;
            idx ++;
        }
        
        else if (boxs[idx] < o){
            while(idx < boxs.size() && boxs[idx] < o){
                    s.push(boxs[idx]);
                    idx ++;
                }
            
                idx ++;
                answer ++;
        }
        
        else {
                if (s.top() == o){
                    answer ++;
                    s.pop();
                    continue;
                }
                
                break;
            }
        }
    
    return answer;
}