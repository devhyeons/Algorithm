#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;





map<string, vector<string>> route;
map<string, bool> visited;
vector<string> ans;
bool flag = false;

void dfs(string cur ,vector<string> path){
	if (visited[cur]){
		if (path.size() == visited.size()){
			ans = path;
			flag = true;
			return;
		}
		return; 
	}
	
	for (auto r : route[cur]){
		if (flag){
			break;
		}
		if (!visited[r]){
			path.push_back(r);
			visited[r] = true;
			dfs(r, path);
			visited[r] = false;
			path.pop_back();
		}
	}
	return;
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    
    for (auto t: tickets) {
	    route[t[0]].push_back(t[1]);
	    visited[t[0]] = false;
    }
    
    for (auto r : route){
	    sort(r.second.begin(), r.second.end()); //문자열 오름차순 배열
    }
    
    vector<string> p;
    visited["ICN"] = true;
    dfs("ICN", p);
    answer = ans;
    
    return answer;
}