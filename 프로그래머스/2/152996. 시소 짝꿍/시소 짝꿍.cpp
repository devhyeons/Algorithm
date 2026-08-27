#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long cnt[4001] = {0};

long long solution(vector<int> weights) {
    long long answer = 0;
   for (auto w : weights){
        cnt [w]++;
    }
    
sort(weights.begin(), weights.end());

for (int w : weights) {
    cnt[w]--;

    answer += cnt[w];

    if ((3*w)%2==0)
        answer += cnt[(3*w)/2];

    answer += cnt[w*2];

    if ((4*w)%3==0)
        answer += cnt[(4*w)/3];
}
    
    return answer;
}