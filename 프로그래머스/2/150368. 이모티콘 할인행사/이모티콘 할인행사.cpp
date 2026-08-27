#include <string>
#include <vector>

using namespace std;

// 1. 플러스 서비스 가입자 최대한 늘리기
// 2. 판매액 최대한 늘리기 

// 1번이 우선, 2번 그 다음 

// n명의 카카오 사용자에게, 이모티콘 m개 할인 판매
// 이모티콘 마다 할인율 다르다. 

int en;
int maxUsers = -1;
int maxSales = -1;

// 할인율
int rate[4] = {10, 20, 30, 40};

vector<vector<int>> users;
vector<int> emoticons;

pair<int,int> calDiscount(vector<int> d){
    vector<int> ne;
    int joinUsers = 0;
    int sumSales = 0;
    for (int i=0; i<en; i++){
        int newMoji = emoticons[i] * (100-d[i]) / 100;
        ne.push_back(newMoji);
    }
    
    for (auto u : users){
        int preferRate = u[0];
        int sum = u[1];
        int curSum = 0;
        for (int i=0; i<en; i++){
            if (preferRate <= d[i]){
                curSum = curSum + ne[i];
            }
        }
        
        if (curSum >= sum){
            joinUsers++;
        } else {
            sumSales = curSum + sumSales;
        }
    }
    
    return {joinUsers, sumSales};
}

void backTracking(int cur, vector<int> discounts){
    if (cur == en){
        auto [mu, ms] = calDiscount(discounts);
        if (maxUsers < mu){
            maxUsers = mu;
            maxSales = ms;
            return;
        }
        else if (maxUsers == mu){
            maxSales = max(maxSales, ms);
            return;
        }
        return;
    }
    
    for (int i=0; i<4; i++){
        discounts.push_back(rate[i]);
        backTracking(cur+1, discounts);
        discounts.pop_back();
    }
}

vector<int> solution(vector<vector<int>> userss, vector<int> emoticonss) {
    vector<int> answer;
    users = userss;
    emoticons = emoticonss;
    en = emoticons.size();
    
    vector<int> d;
    backTracking(0, d);
    
    answer.push_back(maxUsers);
    answer.push_back(maxSales);
    return answer;
}