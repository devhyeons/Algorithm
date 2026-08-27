#include <string>
#include <cmath>
#include <iostream>
#include <cctype>
#include <vector>

using namespace std;

// 다크게임 3번의 기회로 구성
// 각 기회마다 얻는 점수 1~10

// S, D,T 영역 존재 1,2,3제곱 
// * : 2배
// # : 해당 점수 마이너스

// ** 중첩시 4배
// *# 중첩시 -2배

int mulNum(char d){
    if (d == 'S'){
        return 1;
    } else if (d == 'D'){
        return 2;
    } else {
        return 3; 
    }
}


int solution(string dartResult) {
    int answer = 0;
    vector<int> res;

    for (int i=0; i<dartResult.size(); i++){
        char d = dartResult[i]; 
        if (isdigit(d)){
            int num = d-'0';
            if (i+1 < dartResult.size() && dartResult[i+1] == '0'){
                num = 10;
                i++;
            }
            res.push_back(num);
        } 
        else if (isalpha(d)){
            int lasts = res.back(); 
            res.pop_back();
            lasts = pow(lasts, mulNum(d));
            res.push_back(lasts);
        }
        
        else {
            int lasts = res.back(); 
            res.pop_back();
            if (d == '*'){
                 if (!res.empty()) {
              int secondLasts = res.back();
              res.pop_back();
               secondLasts = secondLasts*2;
                res.push_back(secondLasts);
            }
                lasts = lasts * 2;
            } else {
                lasts = lasts * -1;
            }
            res.push_back(lasts);
        }
    }
    
    for (auto r : res){
        cout << r << " ";
        answer = answer + r;
    }
    
    return answer;
}