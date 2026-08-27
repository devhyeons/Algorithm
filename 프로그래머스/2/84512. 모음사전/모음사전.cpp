#include <string>
#include <vector>

using namespace std;

char arr[5] = {'A', 'E', 'I', 'O', 'U'};

// 이 단어가 사전의 몇번째 단어인지 return 

string g_word;
int answer = 0;
int cnt = 0;

void backTracking(string s){
	if (s == g_word) {
		answer = cnt;
		return;
	}
	
	if (s.size() == 5){
		return;
	}
	
	for (auto i : arr) {
		cnt++;
		backTracking(s+i);
	}
}

int solution(string word) {
    g_word = word;
    backTracking(""); 
    return answer;
}