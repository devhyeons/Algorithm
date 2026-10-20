#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

// 롤케익을 두 조각으로 잘라서 동생과 한 조각씩 나눠먹으려 한다.
// 이 롤케익에는 토핑이 일렬로 올려져있다.
// 잘린 조각 크기와 토핑갯수에 상관없이
// 각 조각에 동일 가짓수의 토핑이 올라가면 공평하게 나누어진것임.

// 롤케이크에 올려진 토핑 번호가 저장되어있을 때
// 롤케익을 공평하게 자르는 방법 수 return 

// topping 길이 <= 10^6
// 최소를 구하는 것이 아니라, 가능 여부만 판단하는 것이다.
// -> parameter-search, two-pointer 활용.xx 투포인터가 아님
// 토핑종류갯수와 그냥 절단 경계값을 map활용해서 구하면 되는것...

unordered_map<int,int> cnts;
unordered_set<int> rs;
unordered_set<int> ls;

int solution(vector<int> topping) {
    int answer = 0;
    
    for (auto t : topping){
        rs.insert(t);
        cnts[t]++;
    }
    
    for (int t : topping){
        ls.insert(t);
        cnts[t]--;
        if (cnts[t] == 0){
            rs.erase(t);
        }
        
        if (rs.size() == ls.size()){
            answer ++;
        }
    }
    
    return answer;
}