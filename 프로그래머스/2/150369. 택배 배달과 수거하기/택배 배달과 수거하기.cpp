#include <string>
#include <vector>

using namespace std;

// 트럭에 재활용 택배 최대 cap 개 실을 수 있다.
// 각 집에 배달 및 수거할 때, 물류창고까지 돌아올 수 있는 최소 이동거리는/

// 이분탐색? 그리디? 
// 멀리 있는 집 먼저 처리하는 것이 가장 효율적.. 

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    long long answer = 0;
    long long remainDelivery =0, remainPickup = 0;
    
    for (int i= n-1; i>=0; i--){
        remainDelivery = deliveries[i]+remainDelivery;
        remainPickup = pickups[i] + remainPickup;
        
        // 아직 배달 또는 수거할 것이 남아있다면
        while (remainDelivery >0 || remainPickup >0 ) {
            remainDelivery = remainDelivery - cap;
            remainPickup = remainPickup - cap;
            
            // cap을 제거해서 만약 remain값이 -(음수)가 되면,
            // 다른 집의 것도 미리 처리했다는 뜻으로 여유 공간 남은 채 시작하게 됨.
            answer = (i+1)*2 + answer;
        }
    }
    
    return answer;
}