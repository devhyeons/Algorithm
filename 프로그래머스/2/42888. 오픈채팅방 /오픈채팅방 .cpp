#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>

using namespace std;

// 들어오면 : 들어왔습니다. 출력
// 나오면 : 나갔습니다. 출력

// 채팅방에서 닉네임 변경하는 방법은 2가지이다.
// - 채팅방 나간 후, 새로운 닉네임 다시 들어가기
// - 채팅방에서 닉네임 변경하기

// 닉네임 변경 시, 기존 채팅방에 출력되어 있던 메시지 닉네임도 전부 변경

// 닉네임 변경 기록 담길 때, 모든 기록 처리된 후 최종 방 개설한 사람이 보는 메시지
// 문자열 배열 return 

vector<string> splitWord(string s){
    vector<string> res;
    string token;
    stringstream ss(s);
    
    while(getline(ss, token, ' ')){
        res.push_back(token);
    }
    return res;
}

struct Users{
    string nickname;
    bool isEnter = false;
    // 들어오면 true
    // 나가면 false, 나갔다가 다시 들어오면 true 
};

unordered_map<string, Users> u;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    
    // 1. record분리
    // 2. map 활용 map[userId] = ninkname
    // if (leave -> enter, 닉네임 변경)
    // if(change -> 닉네임 변경)
    
    for (auto r :record){
        auto res = splitWord(r);
        string state = res[0];
        string userId = res[1];
        string nickname = "";
        if (res.size() == 3){
            nickname = res[2];
        }
        
        if (state == "Enter"){
            u[userId].nickname = nickname;
            u[userId].isEnter = true;
        } else if (state == "Change"){
            u[userId].nickname = nickname;
        } else {
            u[userId].isEnter = false;
        }
    }
    
    for (auto r : record){
        vector<string> res = splitWord(r);
        string state = res[0];
        string userId = res[1];
        string nickname = "";
        if (res.size() == 3){
            nickname = res[2];
        }
        
        if (state == "Enter"){
           answer.push_back(u[userId].nickname+ "님이 들어왔습니다.");
        } else if (state == "Leave"){
           answer.push_back(u[userId].nickname+ "님이 나갔습니다.");
        }
    }
    
    return answer;
}