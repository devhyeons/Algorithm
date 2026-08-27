#include <string>
#include <vector>
#include <map>

using namespace std;

int stringToNumber(string times){
    int h = stoi(times.substr(0,2));
    int m  = stoi(times.substr(3,2));
    int s =  stoi(times.substr(6,2));
    return h*3600 + m*60 + s;
}


string numberToString(int numbers){
    int h = numbers/3600;
    numbers = numbers%3600;
    int m = numbers/60;
    int s = numbers%60;
    
    string sh = to_string(h);
    string sm = to_string(m);
    string ss = to_string(s);
    
    if (sh.size() == 1) {
        sh = "0"+sh;
    }
    if (sm.size() == 1){
        sm = "0"+sm;
    }
    if (ss.size()==1){
        ss = "0"+ss;
    }
    
    return sh+":"+sm+":"+ss;
}

long long arr[99*3600 + 59*60 + 59+1];

string solution(string play_time, string adv_time, vector<string> logs) {
    
    int play = stringToNumber(play_time);
    int adv = stringToNumber(adv_time);
 
    for (auto l : logs){
        int startTime = stringToNumber(l.substr(0,8));
        int endTime  = stringToNumber(l.substr(9,8));
        
        arr[startTime]++;
        arr[endTime]--;  
    }
    
    for (int i=1; i<=play; i++){
        arr[i] = arr[i-1]+arr[i];
    }
    
    // 0초부터 i초까지 누적시간
    for (int i=1; i<=play; i++){
        arr[i] = arr[i-1]+arr[i];
    }
    
    long long maxStart = 0;
    long long maxView = arr[adv-1]; // 0~adv-1까지 누적 시간
    
    for (int i=1; i<=play-adv+1; i++){
        int end = i+adv-1;
        long long curView = arr[end]-arr[i-1];
        if (curView > maxView){
            maxView = curView;
            maxStart = i;
        }
    }

    return numberToString(maxStart);
}