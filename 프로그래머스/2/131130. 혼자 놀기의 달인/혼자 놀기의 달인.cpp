#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream> 

using namespace std;

vector<int> cards;

int makeGroup(int start){
   
    int total = -1;
    
    bool visited1[101] = {false};
    bool visited2[101] = {false};
    
    visited1[start] = true;
    
    int curIdx = cards[start]-1;
    int cnt1 = 1;
    while(!visited1[curIdx]){
       // cout <<"curIdx = " << curIdx << "\n";
        visited1[curIdx]= true;
        cnt1++;
        curIdx = cards[curIdx]-1;
    }

 /*   cout << cnt1 << "\n";
    cout <<" ======================== " << "\n\n"; */
    
    for (int i=0; i<cards.size(); i++){
        int cnt2 = 0;
        if (!visited1[i]) {
            int s2 = i;
            visited2[s2] = true;
            curIdx = cards[s2]-1;
            cnt2 = 1;
            
            while(!visited1[curIdx] && !visited2[curIdx]) {
                visited2[curIdx] = true;
                cnt2 ++;
                curIdx = cards[curIdx]-1;
            }
        }
        
        total = max(total, cnt1 * cnt2);
 
        for (int j=0; j<101; j++){
            visited2[j] = false; 
        }
    }
    
    return total;
}
int solution(vector<int> c_cards) {
    int answer = 0;
    cards = c_cards; 

    for (int i=0; i<cards.size(); i++){
        answer = max(answer, makeGroup(i));
    }
    
    return answer;
}