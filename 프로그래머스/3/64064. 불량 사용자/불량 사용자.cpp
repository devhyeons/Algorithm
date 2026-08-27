#include <string>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

// 이벤트 응모자 담긴 user_id와 불량 사용자 담긴 banned_id로 주어질 때
// 당첨에서 제외되어야할 제재 아이디 목록은 몇가지 경우인지 return

// 백트래킹 ?? 될거같음. => 입력값 여유있음. 

// backTraking을해도 겹치는 부분이 있음 즉 crodo는 *rodo나 ***** 둘다 되는 부분이라, 목록 자체에 겹치는 상황 발생.

bool visited[9];
int bSize;
int uSize;
set<set<string>> result; 

vector<string> cUser_id;
vector<string> cBanned_id;

bool checkMapping(string user, string banned){
    // string 두개 매핑되는지 확인
    if (user.size() != banned.size()){
        return false;
    }
    for (int i=0; i<banned.size(); i++){
        if ((user[i] != banned[i]) && banned[i] != '*'){
            return false;
        }
    }
    return true;
}

void backTracking(int idx, set<string> & s){
    if (idx == bSize){ // idx -> 불량 사용자 배열을 순회하는 idx
        result.insert(s); // 중복을 피하기 위해서 set<set<string>> result에 하나의 조합인 s를 담음. 
        return;
    }
    
    for (int i=0; i<uSize; i++){
        if (!visited[i] && checkMapping(cUser_id[i], cBanned_id[idx])){
            visited[i] = true;
            s.insert(cUser_id[i]);
            backTracking(idx+1, s); // banned가 모두 매핑되는 경우의수만 가능하므로, 0에서 mapping안되어서
            // if문으로 한번도 안들어오면 그냥 아예 안되는 경우의수. 따라서 idx는 bIndx의 역할로 작용. 
            visited[i] = false; 
            s.erase(cUser_id[i]); //visited false처럼 집합에서도 빼줘야함.
        }
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    cUser_id = user_id;
    cBanned_id = banned_id;
    bSize = banned_id.size();
    uSize = user_id.size();
    
    set<string> s;
    backTracking(0,s);

    return result.size();
}