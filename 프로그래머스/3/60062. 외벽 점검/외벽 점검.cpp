#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 레스토랑 구조는 완전 동그란 모양, 외벽 총 둘레 n미터
// 외벽 몇몇 지점 손상될 수 있는 취약 지점 존재
// 따라서 점검 하려는데, 점검 시간 = 1시간 제한

// 친구들은 1시간 동안 이동할 수 있는 거리 제각각
// 최소한의 친구 투입 후 취약지점 점검, 나머지 친구 내부공사

// 레스토랑 정북 방향 지점을 0으로 나타냄
// 취약지점 위치는 정북 방향 지점으로부터 시계 방향 떨어진 거리로 나타냄
// 친구들은 출발지로부터 시계 or 반시계 방향으로 외벽 따라서만 이동

// 외벽길이 n
// 취약지점 위치 weak
// 각 친구 1시간동안 이동거리 dist
// 취약지점 점검 위해 보내야하는 친구 최솟값은? 

// n <= 100
// weak 길이 <= 1~15
// dist 길이 1~8이하 -> 즉 친구 수가 8명 이하라는 뜻

int solution(int n, vector<int> weak, vector<int> dist) {
    
    int len = weak.size();
    int answer = dist.size() + 1;
    
    for (int i=0; i<len; i++){
        weak.push_back(weak[i] + n); //원형 배열 펼치기
    }
    
    // 순열 준비
    sort(dist.begin(), dist.end());
    
    do{
        
        for (int start = 0; start < len; start ++){
            //1) 시작 위치 변경 
            
            int cnt = 1; //첫번째 친구 투입 
            int coverage = weak[start] + dist[cnt-1];
            // 첫번째 위치에서부터 ~ 그 친구가 커버 가능한 dist
            
            // 현재 친구가 다음 취약 지점까지 갈 수 없으면
            // 새로운 친구를 투입한다.
            for (int i=start; i<start + len; i++){
                // 2) 취약 지점 하나씩 점검
                if (weak[i] > coverage){
                    cnt ++;
                    
                    if (cnt > dist.size()){
                        break;
                    }
                    
                    coverage = weak[i] + dist[cnt-1];
                }
            }
            answer = min(answer, cnt);
            
        }
        
        
        
    } while(next_permutation(dist.begin(),dist.end()));         // 친구들의 투입 순서 전부 확인 순열.
    // 투입 순서에 따라 값이 달라질 수 있기 때문.
    
    if (answer > dist.size()) return -1;
    
    
    return answer;
}