#include <string>
#include <vector>
#include <bitset>
#include <iostream>

using namespace std;

// 비밀 지도를 해독하여, '#', ' '으로 구성된 문자열 배열 출력 .. 


// 해독 방법
// 모두 공백 = 공백
// 1은 벽, 공백은 0

// 두개 or 하라

char arr[17][17];
int n;

string toBinary(int num){
    bitset<16> b(num);
    string s = b.to_string();
    
    return s.substr(16-n,n);
}

vector<string> solution(int n1, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    n = n1;
    
    // arr1 해독
    for (int i=0; i<n; i++){
        int num = arr1[i];
        string sb = toBinary(num);
         cout << "sb = " << sb << "\n";
        for (int j=0; j<sb.size(); j++){
            if (sb[j] == '1'){
                arr[i][j] = '#'; 
            }else {
                arr[i][j] = ' ';
            }
        }
    }
    
    
    // arr2 해독
      for (int i=0; i<n; i++){
        int num = arr2[i];
        string sb = toBinary(num);
        for (int j=0; j<sb.size(); j++){
            if (sb[j] == '1'){
                arr[i][j] = '#'; 
            } else {
                if (arr[i][j] != ' ') continue;
                arr[i][j] = ' ';
            }
        }
    }
    
    // 정답 출력
    for (int i=0; i<n; i++){
        string tmp = "";
        for (int j=0; j<n; j++){
            tmp = tmp + arr[i][j];
        }
        answer.push_back(tmp);
    }
    
    return answer;
}