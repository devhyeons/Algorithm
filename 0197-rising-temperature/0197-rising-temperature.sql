# Write your MySQL query statement below
-- 어제보다 높은 온도를 가진 모든 날짜ㅡ이 id 찾기

SELECT w1.id
FROM Weather as w1 JOIN Weather as w2
WHERE w1.recordDate > w2.recordDate AND  
DATEDIFF(w1.recordDate, w2.recordDate) = '1' AND
w1.temperature > w2.temperature 