#include <string>
#include <cctype>
#include <vector>

using namespace std;

// 규칙에 맞지 않는 아이디 입력 시,
// 입력된 아이디와 유사하면서, 규칙에 맞는 아이디 추천 프로그램

// 카카오 아이디 규칙
// 1. 아이디는 3자 이상, 15자 이하 (길이)
// 2. 알파벳 소문자, 숫자, -, _, . 만 사용
// 3. .은 처음과 끝에 사용 x, 연속 사용 x

// 추천 아이디 return 솔루션 


string newId = "";

void step1(){
    // 1단계 new_id의 모든 대문자를 대응되는 소문자로 치환합니다.
    for (auto & n : newId){
        if(isupper(n)){
            n = tolower(n); 
        }
    }
}

void step2(){
    // 2단계 new_id에서 알파벳 소문자, 숫자, 빼기(-), 밑줄(_), 마침표(.)를 제외한 모든 문자를 제거합니다.
    string res = "";
    
    for (auto n : newId){
        if (isalnum(n) || n == '_' || n == '-' || n=='.')
            res = res + n;
    }
    newId = res;
}
void step3(){
    // 3단계 new_id에서 마침표(.)가 2번 이상 연속된 부분을 하나의 마침표(.)로 치환합니다.
    bool prevDot = false;
    
    // 2개이상 전체를 부분 하나로 치환해야 함..
    // 처음 시작과, 끝 idx에 대한 정보 필요.. 
    
    string res = "";
    for (auto n : newId){
        if (n == '.'){
            if (!prevDot) {
                res = res + n;
            } 
            prevDot = true;
        } else {
            res = res + n;
            prevDot = false;
        }
    }
    newId = res;
}
void step4(){
    // 4단계 new_id에서 마침표(.)가 처음이나 끝에 위치한다면 제거합니다.
    if (!newId.empty() && newId.front() == '.') {
        newId.erase(newId.begin());
    }
    
    if (!newId.empty() && newId.back() == '.'){
        newId.pop_back(); 
    }
}
void step5(){
    // 5단계 new_id가 빈 문자열이라면, new_id에 "a"를 대입합니다.
    if (newId == ""){
        newId.push_back('a');
    }
    
}
void step6(){
    // 6단계 new_id의 길이가 16자 이상이면, new_id의 첫 15개의 문자를 제외한 나머지 문자들을 모두 제거합니다.
//      만약 제거 후 마침표(.)가 new_id의 끝에 위치한다면 끝에 위치한 마침표(.) 문자를 제거합니다.
    int n = newId.size();
    
    if (newId.size() >= 16){       
        newId = newId.substr(0,15);
    }
    
    while(!newId.empty() && newId.back() == '.'){
        newId.pop_back();
    }
}
void step7(){
    // 7단계 new_id의 길이가 2자 이하라면, new_id의 마지막 문자를 new_id의 길이가 3이 될 때까지 반복해서 끝에 붙입니다.
    
    if (newId.size() <= 2){
        while(newId.size() < 3){
            newId.push_back(newId.back());
        }
    }
}



string solution(string new_id) {
    newId = new_id;
    string answer = "";
    int n = new_id.size(); 
    
    step1();
    step2();
    step3();
    step4();
    step5();
    step6();
    step7();
    
    return newId;
}