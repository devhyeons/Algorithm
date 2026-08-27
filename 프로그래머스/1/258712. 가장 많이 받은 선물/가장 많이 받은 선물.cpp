#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

// 이번달 선물 주고받은 기록을 바탕으로 다음달에 누가 선물을 많이 받을지 예측

// 주고받은 기록이 있다면 
// 1. 이번달까지 두 사람 사이에 더 많은 선물을 준 사람이 다음달에 선물을 하나 더 받는다.

// 주고받은 기록 x or 수가 같다면
// 선물 지수가 더 큰 사람이,  작은사람에게 선물을 하나 받는다.
// 선물지수 = 이번달까지 친구에게 선물 준 수 - 받은 선물 수 

// 다음달에 가장 선물을 많이 받을친구가 받을 선물 순는 ?

vector<string> friends;
int arr[51][51];
vector<int> res(51);

int returnsIdx(string d){
    for (int i=0; i<friends.size(); i++){
         if (d == friends[i]){
             return i;
         }
    }
    return -1;
}

vector<string> splitGifts(string s){
    stringstream ss(s);
    string word;
    vector<string> result;
    
    while(ss >> word){
        result.push_back(word);
    }
    
    return result;
}

void initFriends(){
    for (int i=0; i<friends.size(); i++){
        for (int j=0; j<friends.size(); j++){
            arr[i][j] = 0;
            res[i] = 0;
        }
    }
}

int calScore(int idx){
    int r = 0;
    int s = 0;
    
    //받은거
    for (int i=0; i<friends.size(); i++){
        if (i==idx) continue;
        r = r + arr[i][idx];
    }
    
    //준거
    for (int i=0; i<friends.size(); i++){
        if (i == idx) continue;
        s = s + arr[idx][i];
     }
    return s-r;
}

bool comp(int a, int b){
    return a > b;
}

int solution(vector<string> cFriends, vector<string> gifts) {
    int answer = 0;
    friends = cFriends;
    int n = friends.size();
    
    initFriends();
    
    for (auto g : gifts){
        vector<string> rs = splitGifts(g);
        
        int sender = returnsIdx(rs[0]); //준친구
        int receiver = returnsIdx(rs[1]); //받은 친구 
        
        arr[sender][receiver]++;
    }
    
    
    for (int i=0; i<friends.size(); i++){
        for (int j=i+1; j<friends.size(); j++){
            if (arr[i][j] > arr[j][i]){
                res[i]++;
            }
            else if (arr[i][j] < arr[j][i]){
                res[j] ++;
            }
            else {
                int iScore = calScore(i);
                int jScore = calScore(j);
                if (iScore > jScore){
                    res[i]++;
                }
                else if (iScore < jScore){
                    res[j]++;
                }
            }
        }
    }
    
    sort(res.begin(), res.end(), comp);
    answer = res[0];
    
    return answer;
}