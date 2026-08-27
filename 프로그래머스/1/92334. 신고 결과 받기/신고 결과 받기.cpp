#include <string>
#include <iostream>
#include <unordered_map>
#include <cstring>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

// 게시판 불량 이용자를 신고하고, 처리결과를 메일로 발송하는 시스템 개발
// 무지가 개발하려는 시스템은 다음과 같다.

// 각 유저는 한번에 한명의 유저를 신고할 수 있다.
// 신고 횟수에 제한은 없다. -> 서로 다른 유저를 계속해서 신고할 수 있다.
// 한 유저를 여러번 신고할 수도 있지만, 동일한 유저에 대한 신고는 1회로 처리된다.

// K번 이상 신고된 유저는 게시판 이용이 정지되며, 해당 유저를 신고한 모든 유저에게
// 정지 사실을 메일로 발송한다.

//유저가 신고한 모든 내용을 취합하여 마지막 한꺼번에 게시판 이용 정지를 시키면서 정지메일 발송
// 유저별로 처리 결과 메일을 받은 횟수 배열에 담아 return 


unordered_map<string,int> receiveCnt; //신고 받은 횟수 담은 map
unordered_map<int, unordered_set<int>> notice; // 각 id가 신고한 멤버들 담기 (vector에)
unordered_map<string, int> mId;
unordered_map<int, int> mailCnt;

// 신고유저, 신고 받은 유저 분리 함수
vector<string> splitWord(string mem){
    vector<string> res;
    stringstream ss(mem);
    string token;
    
    while(getline(ss, token, ' ')){
        res.push_back(token);
    }
    
    return res;
}


vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    
    for (int i=0; i<id_list.size(); i++){
        mId[id_list[i]] = i; // <muzi, 0> 저장
        
    }
    
    for (auto r : report) {
        auto res = splitWord(r);
        int send = mId[res[0]];
        int receiver = mId[res[1]];
        
        if (!notice[receiver].count(send)){
             receiveCnt[res[1]]++;
             notice[receiver].insert(send);
        }
    }    
    
    for (auto m : receiveCnt){
        if (m.second >= k){
            // 이 친구를 신고한 아이들에게 메일 보내주어야 함.  
            int id = mId[m.first];
            for (auto v : notice[id]){
               mailCnt[v]++;   
            }   
        }
    }
    
    for (int i=0; i<id_list.size(); i++){
        answer.push_back(mailCnt[i]);
    }
    
    return answer;
}