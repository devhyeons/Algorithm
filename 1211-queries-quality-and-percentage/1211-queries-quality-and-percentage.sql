# Write your MySQL query statement below
-- 중복된 행을 가질 수 있다. 
-- rating < 3 은 품질 낮으누커리
-- quality = rating과 position 비율의 평균
-- poor query percentage : rating < 3 인 쿼리 비율

SELECT q.query_name,
ROUND(AVG(q.rating/q.position * 1.0),2) as quality,
ROUND( SUM(CASE 
        WHEN q.rating < 3 then 1 
        else 0 
        END) / COUNT(*) * 100.0 ,2 ) as poor_query_percentage
FROM Queries as q
GROUP BY q.query_name
