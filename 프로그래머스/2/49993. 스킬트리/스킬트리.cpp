#include <string>
#include <vector>

using namespace std;
bool visited[32] = {false};

void initVisited(){
    for (auto & v : visited){
        v = false;
    }
}


int solution(string skill, vector<string> skill_trees) {
    int answer = 0;
    
    for (auto s : skill_trees){
        initVisited();
        bool valid = true;
        for (int i=0; i<s.size(); i++){
            
            auto pos = skill.find(s[i]);
            if (pos != string::npos && pos > 0 && !visited[skill[pos-1] - 'A']){
                valid = false;
                break;
            }
            
            visited[s[i]-'A'] = true;
        }
        if (valid) answer ++;     
    }

    
    return answer;
}