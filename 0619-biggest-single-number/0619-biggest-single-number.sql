# Write your MySQL query statement below
WITH cnts as (
    SELECT num
    FROM MyNumbers as n
    GROUP BY (n.num) 
    HAVING COUNT(n.num) = 1
)

SELECT MAX(num) as num
FROM cnts