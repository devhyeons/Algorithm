#include <string>
#include <vector>

 long long solution(int a, int b) 
{
     long long answer=0;
     if (a > b) {
            for (int i=b; a>=i; i++)
                answer = answer+i;
        }
       else if (b > a) {
            for (int j=a; b>=j; j++)
                answer = answer+j; 
        }
        else{
            answer = a;
        }
         return answer;
    }