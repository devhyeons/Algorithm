#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 교체 알고리즘 LRU -> 제일 사용 안한놈 제거 

// 실행시간 계산
// cache hit = 1
// cache miss = 5 

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;
    int used = 0;
    
    vector<string> cache;
    
    if (cacheSize == 0){
        return cities.size() * 5;
    }
    
    for (auto & c : cities){
        
        transform(c.begin(), c.end(), c.begin(), ::tolower);
        
        auto it = find(cache.begin(), cache.end(), c);
        
        if (it != cache.end()){
            cache.erase(it);
            cache.insert(cache.begin(), c);
            answer = answer + 1;
        }  else {
            if (cache.size() == cacheSize){
                cache.pop_back();
            }
            cache.insert(cache.begin(), c);
            answer = answer + 5;
        }
    }
    
    
    return answer;
}