#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

// 판매원에게 배분된 이익금 총합 계산해서 (정수형),
// enroll 순서대로 출력 

// 하나 이익 내면, 자기 추천해준 사람들 따라서 10%씩 이익 분배 

unordered_map<string,string> m; //자신, 자신 델고 온 추천인
unordered_map<string,int> benefit;//enroll순서대로 멤버가 받은 이익 (benefit)

void addBenefit(string startMember, int initAmount){
    string curMember = startMember;
    int curAmount = initAmount;
    while(curMember != "center" && curAmount > 0){
        string recMem = m[curMember];
        int commission = curAmount /10; //10퍼이익
        benefit[curMember] = benefit[curMember] + curAmount - commission;
        curMember = recMem;
        curAmount = commission;
    }
}


vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;
    
    for (int i=0; i<referral.size(); i++){
        if (referral[i] == "-") {
            m[enroll[i]] = "center";
            continue;
        }
        m[enroll[i]] = referral[i]; 
    } //그래프 생성
    
    for (int i=0; i<seller.size(); i++){
        int initAmount = (amount[i] * 100); //최초 멤버 이익금 (추천인 배분 전)
        addBenefit(seller[i], initAmount);
    }
    
    for (int i=0; i<enroll.size(); i++){
        answer.push_back(benefit[enroll[i]]);
    }
    return answer;
}